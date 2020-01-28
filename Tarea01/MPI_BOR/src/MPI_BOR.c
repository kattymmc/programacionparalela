/*
 ============================================================================
 Name        : MPI_BOR.c
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

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);

    // Obtiene el numero de procesos
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicacion debe ser ejecutada con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determine el rank principal
    int rank = 0;

    // Obteniend el rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada proceso envia su posicion ,el procesos principal recolecta los resultados
    char all_values[4] = {0, 1, 3, 8};
    char my_value = all_values[my_rank], reduction= 0;
    MPI_Reduce(&my_value, &reduction, 1, MPI_UNSIGNED_CHAR, MPI_BOR, rank, MPI_COMM_WORLD);

    if(my_rank == rank)
    {
        printf("El bit-wise O de todos los valores %d.\n", reduction);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
