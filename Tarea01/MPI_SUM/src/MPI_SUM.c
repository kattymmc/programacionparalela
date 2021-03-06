/*
 ============================================================================
 Name        : MPI_SUM.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const double a = 0;
const double b = 10;

/* Declaraciones de funciones */
void Get_input(int argc, char* argv[], int my_rank, double* n_p);
double Trap(double l_endpt, double r_endpt, int trap_count, double base);
double f(double x);

int main(int argc, char** argv) {
  int my_rank, comm_sz, local_n;
  double n, h, local_a, local_b;
  double local_int, total_int;
  double start, finish, local_elapsed, elapsed;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  /*Imprime en consola el nucleo que ejecuto el proceso*/
  printf("soy el core nro. %d de %d\n", my_rank, comm_sz);

  Get_input(argc, argv, my_rank, &n); /*Leer la entrada del usuario*/

  // h y local_n son iguales para todos los procesos
  h = (b - a) / n;
  local_n = n / comm_sz;

  //Duración del intervalo de integración de cada proceso
  local_a = a + my_rank * local_n * h;
  local_b = local_a + local_n * h;

  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();

  /// Calcular la integral local de cada proceso utilizando puntos finales locales
  local_int = Trap(local_a, local_b, local_n, h);
  finish = MPI_Wtime();
  local_elapsed = finish - start;
  MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  // Suma las integrales calculadas por cada proceso
  MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


  if (my_rank == 0) {
    printf("Con n = %.0f trapezoides, el valor de la integral entre %.0f a %.0f = %f \n", n, a, b, total_int);
    printf("Tiempo transcurrido = %f millisegundos \n", elapsed * 1000);
  }

  /* Cerrar MPI */
  MPI_Finalize();

  return 0;
} /* main */
