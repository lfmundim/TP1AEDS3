//
// Created by heimdallr on 25/09/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "books.h"

#define MAX_FILES 10000

int compare(const void * book1, const void * book2) {
	bookT *tempA = (bookT *)book1;
	bookT *tempB = (bookT *)book2;
	return strcmp(tempA->title, tempB->title);
}

void sorting(FILE *file1, FILE *file2, FILE *output, int memsize);

void externalSorting(FILE *file, int memsize, int num_books){
	long int i, j, k, count, last, size;
	char straux[MAX_FILES];
	FILE *fileaux, *fileaux2, *fileaux3;
	bookT buffer, *book_array;

	last = num_books%memsize;

	//particiona o arquivo em arquivos de tamanho M
	for(i=0, count=0; count<num_books; i++){
		sprintf(straux, "file%ld.bin", i);
		fileaux = fopen(straux, "wb");
		for(j=0; j<memsize; j++) {
			if(count==num_books) break;
			fscanf(file, "%s %c", buffer.title, &buffer.available);
			fprintf(fileaux, "%s %c\n", buffer.title, buffer.available);
			count++; //numero de arquivos total
		}
		fclose(fileaux);
	}
	//ordena internamente os i arquivos
	for(j=0; j<i; j++){
		if(j==i-1)
			size = last;
		else
			size = memsize;
		book_array = (bookT*)malloc(size*sizeof(bookT));
		sprintf(straux, "file%ld.bin", j);
		fileaux = fopen(straux, "r");
		for(k=0; k<size; k++) {
			fscanf(fileaux, "%s %c", book_array[k].title, &book_array[k].available);
		}
		fclose(fileaux);
		fileaux = fopen(straux, "wb");
		qsort(book_array, size, sizeof(bookT), compare);
		for(k=0; k<size; k++){
			fprintf(fileaux, "%s %c\n", book_array[k].title, book_array[k].available);
		}
		fclose(fileaux);
		free(book_array);
	}

	//intercala os arquivos
	size = (num_books/memsize+1); //conta numero de arquivos
	for(i=0; i<size; i++){ //arquivos
		sprintf(straux, "file%ld.bin", size++);
		fileaux3 = fopen(straux, "wb");

		sprintf(straux, "file%ld.bin", i);
		fileaux = fopen(straux, "rb");
		sprintf(straux, "file%ld.bin", ++i);
		fileaux2 = fopen(straux, "rb");


		sorting(fileaux, fileaux2, fileaux3, memsize);
		fclose(fileaux);
		fclose(fileaux2);
		fclose(fileaux3);
	}
	sprintf(straux, "mv file%ld.bin inorder", size-1);
	system(straux);
	system("rm -f file*.bin");

}

void sorting(FILE *file1, FILE *file2, FILE *output, int memsize){
	//compara as primeiras duas linhas dos arquivos, passa a menor pra um arquivo output
	bookT book1, book2;
	int comp, length1=0, length2=0, size=0, count1=1, count2=1, flag1=0, flag2=0;
	fscanf(file1, "%s %c", book1.title, &book1.available);
	fscanf(file2, "%s %c", book2.title, &book2.available);
	while(1) {
		comp = strcmp(book1.title, book2.title);
		if(feof(file1)==1){
			comp = 1;
			flag1 = 1;
		}
		if(feof(file2)==1){
			comp = -1;
			flag2 = 1;
		}
		if(flag1 == 1 && flag2 == 1){
			break;
		}
		if (comp < 0) {
			size = strlen(book1.title);
			fwrite(book1.title, size*sizeof(char), 1, output);
			fprintf(output, " ");
			fwrite(&book1.available, sizeof(char), 1, output);
			fprintf(output, "\n");
			length1 += size*sizeof(char)+sizeof(char)+2;
			fseek(file1, length1, SEEK_SET);
			count1++;
			fscanf(file1, "%s %c", book1.title, &book1.available);
		}
		else {
			size = strlen(book2.title);
			fwrite(book2.title, size*sizeof(char), 1, output);
			fprintf(output, " ");
			fwrite(&book2.available, sizeof(char), 1, output);
			fprintf(output, "\n");
			length2 += size*sizeof(char)+sizeof(char)+2;
			fseek(file2, length2, SEEK_SET);
			count2++;
			fscanf(file2, "%s %c", book2.title, &book2.available);
		}
	}
}