/*
 ============================================================================
 Name        : MPI_BAND.c
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

    // Obtiene el numero de procesos y verifica que sea 4
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicacion debe ser ejecutada con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }


    int root = 0;

    // Obteniendo rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char all_values[4] = {0, 1, 3, 8};
    char my_value = all_values[my_rank];
    char reduction = 0;
    MPI_Reduce(&my_value, &reduction, 1, MPI_UNSIGNED_CHAR, MPI_BAND, root, MPI_COMM_WORLD);

    if(my_rank == root)
    {
        printf("La logica y de todos los valores es %d.\n", reduction);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
