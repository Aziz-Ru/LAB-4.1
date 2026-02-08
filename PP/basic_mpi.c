#include<mpi.h>
#include<stdio.h>

/*

So… what is MPI_COMM_WORLD?

MPI_COMM_WORLD is a communicator.

A communicator defines:

Which processes exist

Who is allowed to talk to whom

What’s inside MPI_COMM_WORLD?

It contains: All processes started by mpirun Their ranks (0 to N−1) Communication rules

Example: mpirun -np 4 ./a.out

Then: MPI_COMM_WORLD = {0, 1, 2, 3}

MPI_COMM_WORLD is the default communicator that includes all processes in an MPI program and is used for communication among them.
*/



int main(int argc, char *argv[]){
  
  int rank,size;
  //  here we initialize the MPI environment
  // we pass the argument count and argument vector to MPI_Init
   MPI_Init(&argc,&argv);
  //  Get the rank and size of the communicator

  // MPI_Comm_rank() → who am I?

  //MPI_Comm_size() → how many processes?
  // How does each process know who it is?
  //MPI_Comm_rank It tells a process: “Who am I inside this group?”
  // Inside the communicator MPI_COMM_WORLD, tell me my rank number and store it in rank
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   int n=72;
   double start_time = MPI_Wtime();
   int chunk = n/size;
   int end = (rank==size-1)? n: (rank+1)*chunk;
   int start = (rank * chunk)+1;
   
  unsigned long long local_fact=1;
  for(int i=start;i<=end;i++){
    local_fact*=i;
  }
  unsigned long long global_fact=1;
  MPI_Reduce(&local_fact,&global_fact,1,MPI_UNSIGNED_LONG_LONG,MPI_PROD,0,MPI_COMM_WORLD);
  double end_time = MPI_Wtime();
  printf("Time taken by process %d is %lf seconds\n",rank,end_time-start_time);
  if(rank==0){
    printf("Factorial of %d is %llu\n",n,global_fact);
  }

  MPI_Finalize();  

  return 0;
}