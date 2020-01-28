/*
 ============================================================================
 Name        : MPI_MIN.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Este programa se ejecuta con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int root = 0;

    // Obteniendo rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int reduction = 0;
    MPI_Reduce(&my_rank, &reduction, 1, MPI_INT, MPI_MIN, root, MPI_COMM_WORLD);

    if(my_rank == root)
    {
        printf("El minimo de todas las posiciones es %d.\n", reduction);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
