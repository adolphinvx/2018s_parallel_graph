#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0
int main(int argc,char** argv)
{
    int pid,pnum,msg;
    int namelen;
    char pname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&pnum);
    if(pnum%2==1) printf("Number of task needs to be even.\n");
    else{
        int partner;
        MPI_Get_processor_name(pname,&namelen);
        
        printf("hello world! Process %d of %d on %s\n",
            pid,pnum,pname);
        
        if(pid<pnum/2){
            partner=pnum/2+pid;
            MPI_Send(&pid,1,MPI_INT,partner,1,MPI_COMM_WORLD);
            MPI_Recv(&msg,1,MPI_INT,partner,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);        
        }
        else if(pid>=pnum/2){
            partner=pid-pnum/2;
            MPI_Recv(&msg,1,MPI_INT,partner,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);        
            MPI_Send(&pid,1,MPI_INT,partner,1,MPI_COMM_WORLD);
        }
        printf("Task %d is partner with %d\n",pid,msg );
        //if master
        if(pid==MASTER)
        printf("MASTER:Number of MPI tasks is:%d\n",pnum);
    }
    MPI_Finalize();
    return 0;
}
