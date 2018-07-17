#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0
int main(int argc,char** argv)
{
    int pid,pnum;
    int namelen;
    char pname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&pnum);
    MPI_Get_processor_name(pname,&namelen);
    //if not master
    printf("hello world! Process %d of %d on %s\n",
            pid,pnum,pname);
    //if master
    if(pid==MASTER)
    printf("MASTER:Number of MPI tasks is:%d\n",pnum);
    MPI_Finalize();

    return 0;
}
