/*
 ============================================================================
 Name        : MPI_LAND.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicacion se ejecuta con 4 procesos\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int rank = 0;

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    bool my_value = (my_rank != 3);
    bool reduction = false;
    MPI_Reduce(&my_value, &reduction, 1, MPI_C_BOOL, MPI_LAND, rank, MPI_COMM_WORLD);

    if(my_rank == rank)
    {
        printf("La logica and y de todos los valores es %s.\n", reduction ? "true" : "false");
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
