/*
 ============================================================================
 Name        : SumaVectores.c
 Author      : Katherine Miraval
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SUMA 2

void llenarvector(int V[], int N);
void imprimevectores(int V[], int N);

int main(int argc, char *argv[]) {
	int rank, size;
	int N = atoi(argv[1]);
	int A[N], B[N];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {

		llenarvector(A, N);
		llenarvector(B, N);

		MPI_Send(A, N, MPI_INT, 1, 2, MPI_COMM_WORLD);
		MPI_Send(B, N, MPI_INT, 1, 3, MPI_COMM_WORLD);
	} else {
		if (rank == 1) {
			// nodo que recibirá los vectores
			MPI_Recv(A, N, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(B, N, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
			printf("Vector A\n");
			imprimevectores(A, N);
			printf("VECTOR B\n");
			imprimevectores(B, N);
			MPI_Send(A, N, MPI_INT, 2, 2, MPI_COMM_WORLD);
			MPI_Send(B, N, MPI_INT, 2, 3, MPI_COMM_WORLD);
		} else {
			if (rank == 2) {
				//nodo que sumará los vectores
				MPI_Recv(A, N, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(B, N, MPI_INT, 1, 3, MPI_COMM_WORLD, &status);
				int RES[N];
				int i;
				for (i = 0; i < N; i++) {
					RES[i] = (A[i] + B[i]);
				}
				printf("VECTOR RESULTANTE\n");
				imprimevectores(RES, N);
			}
		}
	}
	MPI_Finalize();
	return 0;
}

void llenarvector(int V[], int N) {
	srand(time(NULL));
	int i;
	for (i = 0; i < N; i++) {
		V[i] = (rand() % 100) + 1;
	}
}

void imprimevectores(int V[], int N) {
	int i;
	for (i = 0; i < N; i++) {
		printf("%d\n", V[i]);
	}
}
