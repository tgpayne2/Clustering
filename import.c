/*
 *import.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Thomas
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void getDataSize(int* length, int* dim, char *input);
void readData(int length, int dim, double **data, char *input);

double** getInput(int* length, int*dim ,char *input) {
		//default data length and dimension initialized to 0 but found later
		*length=0;
		*dim=0;

		//get size of data to generate dat aarray
		getDataSize(length,dim,input);

		//generate data array

		double** data = makeArray(*length,*dim);
		readData(*length, *dim, data, input);
		return data;
}

void getDataSize(int* length, int* dim, char *input) {

	FILE *file;
	file=fopen(input,"r");
	char line[1000];
	char *token;
	char del[]=",";

	while(fgets(line,sizeof(line),file)) {
		if (*length==0) {
			token=strtok(line,del);
			while (token != NULL) {
				*dim=*dim+1;
				token=strtok(NULL,del);
			}
		}
		*length=*length+1;
	}
}

void readData(int length, int dim, double **data, char *input) {
	FILE *file;
	file=fopen(input,"r");
	char line[1000];
	char *token;
	char del[]=",";
	int l=0;
	int d;
	while(fgets(line,sizeof(line),file)) {
		d=0;
		token = strtok(line,del);
		while (token != NULL) {
			data[l][d]=atof(token);
			token=strtok(NULL,del);
			d++;
		}
		l++;
	}
}
