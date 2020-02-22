/*
 ============================================================================
 Name        : Ejercicio7.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int n = 10, factorial = 1;
	int i;

	
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	
	
	if (my_rank !=0){
		int local_n = n/p;
		int my_fac=1;
		for(i=(my_rank*local_n+1);i < (my_rank*local_n+local_n+1);i++){
			my_fac=my_fac*i;
		}
		MPI_Send(&my_fac,1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	else{
		int local_n = n/p;
		int my_fac;
		for (i= 1; i< (local_n+1); i++) {
			factorial=factorial*i;
		}
		for(source=1;source<p;source++){
			MPI_Recv(&my_fac, 1, MPI_INT, source, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			factorial=factorial*my_fac;
		}
		printf("El factorial de %d es %d",n,factorial);
	}
	/* shut down MPI */
	MPI_Finalize(); 
	return 0;
}
