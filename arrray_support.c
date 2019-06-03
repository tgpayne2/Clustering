/*
 * arrray_support.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Thomas
 */


#include <stdlib.h>
#include <stdio.h>

double** makeArray(int r, int c) {
	double **arr;
	int i;
	if ((arr=(double **)malloc(r * sizeof(double *)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	for (i=0;i<r;i++) {
		if ((*(arr+i)=(double *)malloc(c * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	}
	return arr;
}

void freeArray(int r, double** array) {
	int i;
	for (i=0;i<r;i++) {
		free(*(array+i));
	}
	free(array);
}

void printArray(int r, int c, double** array) {
	int i,j;
	for (i=0;i<r;i++) {
		for (j=0;j<c;j++) {
			printf("%.4f ",array[i][j]);
			}
		printf("\n");
	}
}
