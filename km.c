/*
 * main.c
 *
 *  Created on: Sep 21, 2017
 *      Author: Thomas
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "header.h"

//find bets k
//generate silloute values for this k
//plot this
//finish pca
//
//add mean value
//make sure finding diff
//


void initCentroids(int k, int dim, double **data, double **centroids);
void updateClusters(int k, int length, int dim, double **data, double **centroids, int *cluster_id, int *cluster_size);
void updateCentroids(int k, int length, int dim, double **data, double **centroids, int *cluster_id, int *cluster_size);
int SSQD(int k, int length, int dim, double **data, double **centroids, int* cluster_id);
void writeData(int k, int length, int dim, double **data, double** centroids, int* cluster_id, int* cluster_size);



//iterate over k values and plot them for the various data sets to generate series of output sillouettes, centroids, and clustervalues.
void kmeans(int k, int length, int dim, int iter_max, double**data, int* cluster_id, int* cluster_size) {

	//clusters size can't be larger than num data points
	if (k<1 || k > length)  {
		exit(-1);
	}



	//make array to contain centroids of each cluster
	double** centroids = makeArray(k,dim);
	//initialize cluster centroids as first k data points
	initCentroids(k,dim,data,centroids);


	int i=0;
	double diff=1.0;
	double ssqd_current=FLT_MAX;
	double ssqd_old;
	//this is where the algorithm happens as described in the hw
	//while (i<iter_max && diff !=0.0) {
	while (i<iter_max) {
		ssqd_old=ssqd_current;
		//reclusters to minimize ssqd based on current centroids
		updateClusters(k, length, dim, data, centroids, cluster_id, cluster_size);
		//updates centroids to reflect new cluster composition
		updateCentroids(k, length, dim, data, centroids, cluster_id, cluster_size);
		//how much better is the current clustering?
		ssqd_current=SSQD(k,length,dim,data,centroids, cluster_id);
		diff=ssqd_current-ssqd_old;
		//printf("%d\n",i);
		i++;
	}


	//output data
	writeData(k, length, dim, data, centroids, cluster_id, cluster_size);
	/*
	sillouette(k,length,dim,data,cluster_id,cluster_size);
	*/
	freeArray(k,centroids);


	//freeArray(length,data);
}

void writeData(int k, int length, int dim, double **data, double **centroids, int* cluster_id, int* cluster_size) {
	char output[20];
	sprintf(output,"output_%d.csv",k);

	//generate and write output file output_*.csv where * is the k value
	FILE* file = fopen(output,"w");
	int i,j;
	fprintf(file,"ID,Data\n");
	for (i=0;i<length;i++) {
		fprintf(file, "%d,",cluster_id[i]);
		for (j=0;j<dim;j++) {
			fprintf(file,"%f,",data[i][j]);
		}
		fprintf(file,"\n");
	}
	fclose(file);

	//append cluster_centroids file with centroids
	FILE* file2 = fopen("./cluster_centroids.csv","a");
	i=0;j=0;
	fprintf(file2,"k=%d\n",k);
	fprintf(file2,"ID,Size,Centroids\n");
	for (i=0;i<k;i++) {
		fprintf(file2, "%d,",i);
		fprintf(file2, "%d,",cluster_size[i]);
		for (j=0;j<dim;j++) {
			fprintf(file2,"%f,",centroids[i][j]);
		}
		fprintf(file2,"\n");
	}
	fprintf(file2,"\n\n");
	fclose(file2);

}

void updateCentroids(int k, int length, int dim, double **data, double **centroids, int *cluster_id, int *cluster_size) {
	int i;
	for (i=0;i<k;i++) {
		cluster_size[i]=0;
	}
	int m,n;
	for (m=0;m<k;m++) {
		for (n=0;n<dim;n++) {
			centroids[m][n]=0.0;
		}
	}
	int p,q;
	for (p=0; p<length; p++) {
		int c_id=cluster_id[p];
		for (q=0;q<dim;q++) {
			//printf("%f ",centroids[cluster_id][q]);
			centroids[c_id][q]=(cluster_size[c_id]*centroids[c_id][q]+data[p][q])/ (cluster_size[c_id]+1);
		}

		cluster_size[c_id]=cluster_size[c_id]+1;
	}

}

int SSQD(int k, int length, int dim, double **data, double **centroids, int* cluster_id) {
	int i,j;
	double cur_ssqd=0.0;
	for (i=0;i<length;i++) {
		for (j=0;j<dim;j++) {
			double diff=data[i][j]-centroids[cluster_id[i]][j];
			cur_ssqd=cur_ssqd+diff*diff;
		}
	}

	return cur_ssqd;
}




void updateClusters(int k, int length, int dim, double **data, double **centroids, int *cluster_id, int *cluster_size) {
	int m,n,p;
	int find_id;
	for (m=0;m<length;m++) {
		double nearest_ssd = FLT_MAX;
		for (n=0;n<k;n++) {
			double current_ssdiff=0.0;
			for (p=0;p<dim;p++) {
				double diff = (data[m][p]-centroids[n][p]);
				current_ssdiff=current_ssdiff+diff*diff;
			}
			if (current_ssdiff<nearest_ssd) {
				nearest_ssd = current_ssdiff;
				find_id=n;
			}
		}
		cluster_id[m]=find_id;
	}
}



void initCentroids(int k, int dim, double **data, double **centroids) {
	int i,j;
	for (i=0;i<k;i++) {
		for (j=0;j<dim;j++) {
			centroids[i][j]=data[i][j];
		}
	}
}




