/*
 ============================================================================
 Name        : MPI_MAXLOC.c
 Author      : katty
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	    double ain[30], aout[30];
	    int  ind[30];
	    struct {
	        double val;
	        int   rank;
	    } in[30], out[30];
	    int i, myrank, root;

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	    for (i=0; i<30; ++i) {
	        in[i].val = ain[i];
	        in[i].rank = myrank;
	    }
	    MPI_Reduce( in, out, 30, MPI_DOUBLE_INT, MPI_MAXLOC, root, comm);
	    /* At this point, the answer resides on process root
	     */
	    if (myrank == root) {
	        /* read ranks out
	         */
	        for (i=0; i<30; ++i) {
	            aout[i] = out[i].val;
	            ind[i] = out[i].rank;
	        }
	    }
}
