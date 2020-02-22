/*
 * factorial2.c
 *
 *  Created on: 13 feb. 2020
 *      Author: laboratorio-fisi
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num;
void* factorial() {
	int fac = 1;
	for (int a = 1; a <= num; a++) {
		fac = fac * a;
		printf("El factorial es %d", fac);
	}
}
int main() {
	pthread_t t;
	printf("Ingrese el numero del factorial ");
	num = 10;
	pthread_create(&t, NULL, factorial, (void*) &num);
	return 0;
}

