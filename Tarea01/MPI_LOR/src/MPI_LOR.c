/*
 ============================================================================
 Name        : MPI_LOR.c
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

    // Se obtiene el numero de procesos
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicacion debe ser corrida con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determina la posicion(rank)
    int rank = 0;

    // Obteniendo la posicions
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada proceso envia su posicion, el procesos principal recolecta los resultados
    bool my_value = (my_rank == 3);
    bool reduction = false;
    MPI_Reduce(&my_value, &reduction, 1, MPI_C_BOOL, MPI_LOR, rank, MPI_COMM_WORLD);

    if(my_rank == rank)
    {
        printf("La logica de todos los valores son %s.\n", reduction ? "true" : "false");
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}