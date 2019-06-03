/*
 * main.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Thomas
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "header.h"

int main() {
	//input csv data file MUST BE CSV FORMAT
	char input[]="./Adata.csv";
	int k;
	int ka=5;
	int kb=6;
	//maximum number of iterations
	int iter_max=100;
	int length;
	int dim;
	double** data = getInput(&length,&dim,input);

	double min_distance=FLT_MAX;
	int min_k=-1;

	for (k=ka;k<kb;k++) {
		int *cluster_id;
		int *cluster_size;
		//float *distance;
		if ((cluster_id=(int *)malloc(length * sizeof(int)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
		if ((cluster_size=(int *)malloc(k * sizeof(int)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
		//if ((distance=(float *)malloc(length * sizeof(int)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}

		kmeans(k, length, dim, iter_max, data, cluster_id, cluster_size);

		double distance = sillouette(k,length,dim,data,cluster_id,cluster_size);
		if (distance < min_distance) {
			min_distance=distance;
			min_k=k;
		}
		printf("k=%d, mean sillouette = %f\n",k,distance);
		free(cluster_id);
		free(cluster_size);
	}

	printf("minimum mean sillouette is %f when k=%d",min_distance,min_k);

	freeArray(length,data);
	return 0;
}
