/*
 * silloutte.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Thomas
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

void findBi(int i,int k, int * cluster_id, double* all_neighbors,double* b);
double max(double a, double b);
void printVector(int l, double*vector);
void orderVector(int m, double*vector);
void writeSillouette(int k, int length, double *s, int* cluster_id);


double sillouette(int k, int length, int dim, double**data, int * cluster_id, int*cluster_size) {
	int i,j,m,n,o;

	//create s, b, a for calculating silloutte
	double *s;
	double *b;
	double *a;
	if ((s=(double *)malloc(length * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	if ((b=(double *)malloc(length * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	if ((a=(double *)malloc(length * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}

	//for each data point
	for (i=0;i<length; i++) {
		//make list of distances for each neighbor
		double *all_neighbors;
		if ((all_neighbors=(double *)malloc((k) * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
		for (n=0;n<k;n++) {
			all_neighbors[n]=0;
		}
		//for each cluster
		for (j=0;j<k;j++) {
			//check each point to find points in cluster
			for (m=0;m<length;m++) {
				//is data point in cluster?
				if (j==cluster_id[m]) {
					double dist=0;
					for (o=0;o<dim;o++) {
						dist=dist+(data[i][o]-data[m][o])*(data[i][o]-data[m][o]);
					}
					all_neighbors[j]=all_neighbors[j]+dist;
				}
			}
			all_neighbors[j]=all_neighbors[j]/cluster_size[j];
		}
		a[i]=all_neighbors[cluster_id[i]];
		findBi(i,k,cluster_id,all_neighbors,b);
		s[i] = (b[i]-a[i]) / max(a[i],b[i]);
	}


	writeSillouette(k, length, s, cluster_id);

	int r;
	double dsum=0;
	for (r=0;r<length;r++) {
		dsum=dsum+s[r];
	}
	dsum=dsum/length;
	return dsum;
}

void findBi(int i,int k, int * cluster_id, double* all_neighbors,double* b) {
	int m;
	double min=FLT_MAX;
	for(m=0;m<k;m++) {
		if (cluster_id[i]!=m && all_neighbors[m]<min) {
			min=all_neighbors[m];
		}
	}
	b[i]=min;
}

void writeSillouette(int k, int length, double *s, int* cluster_id) {
	char sil[20];
	sprintf(sil,"os_%d.csv",k);
	double *order_s;
	if ((order_s=(double *)malloc(length * sizeof(double)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	int i;

	for (i=0;i<length;i++) {
		order_s[i]=s[i]+cluster_id[i]*10;
	}
	/*
	i=0;
	for (i=0;i<length;i++) {
		order_s[i]=-1*order_s[i];
	}
	*/
	//printVector(length,order_s);
	orderVector(length,order_s);
	/*
	for (i=0;i<length;i++) {
		order_s[i]=-1*order_s[i];
	}
	*/
	//printVector(length,order_s);



	int j;
	int *order_cid;
	if ((order_cid=(int *)malloc(length * sizeof(int)))==NULL) {fprintf(stderr, "malloc error\n"); exit(1);}
	//printVector(length,order_s);
	for (j=0;j<length;j++) {
		int k_val=0;
		while (order_s[j]>1) {
			order_s[j]=order_s[j]-10;
			k_val=k_val+1;
		}
		order_cid[j]=k_val;
	}
	i=0;
	j=0;
	FILE* file = fopen(sil,"w");
	for (i=0;i<length;i++) {
		fprintf(file, "%d,%f\n",order_cid[i],order_s[i]);
	}
	fclose(file);
}

void orderVector(int m, double*vector) {

	int i=1;
	while (i<m) {
		int j=i;
		double temp;
		while (j>0 && vector[j-1]>vector[j]) {
			temp=vector[j];
			vector[j]=vector[j-1];
			vector[j-1]=temp;
			j=j-1;
		}
		i=i+1;
	}
}

double max(double a, double b) {
	if (a>b) {
		return a;
	} else {
		return b;
	}
}

void printVector(int l, double*vector) {
	int i;
	printf("\n");
	for (i=0;i<l;i++) {
		printf("%f, ",vector[i]);
	}
	printf("\n");
}

