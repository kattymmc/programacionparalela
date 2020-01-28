/*
 ============================================================================
 Name        : MPI_PROD.c
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
        printf("Puede correr con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determina la posicion principal
    int root = 0;

    // Obteniendo rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada proceso envia su posicion y el proceso principal reune los resultados
    int value = my_rank + 1, reduction= 0;
    MPI_Reduce(&value, &reduction, 1, MPI_INT, MPI_PROD, root, MPI_COMM_WORLD);

    if(my_rank == root)
    {
        printf("El producto de todos los valores es %d.\n", reduction);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
