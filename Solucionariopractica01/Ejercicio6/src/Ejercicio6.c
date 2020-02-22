/*
 ============================================================================
 Name        : Ejercicio6.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"


int main(int argc, char* argv[]){
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int n = 9 , x = 3;
	int A[] = {1,2,1,4,6,3,1,3,1}, *local_a;
	int contador_total=0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	
	int local_n = n/p;
	local_a = malloc(local_n * sizeof(int));

	MPI_Scatter(&A, local_n, MPI_INT, local_a, local_n, MPI_INT, 0, MPI_COMM_WORLD);

	if (my_rank != 0) {
		int local_count = 0;
		int local_n=n/p;
		for (int i = 0; i < local_n; i++) {
			if (local_a[i] == x)
				local_count++;
		}
		MPI_Send(&local_count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	} else {
		int local_n = n/p;
		int local_count;
		for (int i = 0; i < local_n; i++) {
			if (local_a[i] == x) {
				contador_total++;
			}
		}
		for (int j = 1; j < p; j++) {
			MPI_Recv(&local_count, 1, MPI_INT, j, 1, MPI_COMM_WORLD,
					MPI_STATUS_IGNORE);
			contador_total += local_count;
		}
		printf("El elemento %d aparece %d veces\n", x, contador_total);

	}
	/* shut down MPI */
	MPI_Finalize(); 
	
	
	return 0;
}
