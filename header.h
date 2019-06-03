/*
 * header.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Thomas
 */

#ifndef HEADER_H_
#define HEADER_H_

//import.c
double** getInput(int* length, int* dim, char *input);

//km2.c

void kmeans(int k, int length, int dim, int iter_max, double**data, int* cluster_id, int* cluster_size);

//array_support.c
double** makeArray(int r, int c);
void freeArray(int r, double** array);
void printArray(int r, int c, double** array);

//sillouette.c
double sillouette(int k, int length, int dim, double**data, int * cluster_id, int*cluster_size);

#endif /* HEADER_H_ */
