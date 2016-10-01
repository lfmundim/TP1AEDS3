//
// Created by heimdallr on 25/09/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "books.h"

#define MAX_FILES 10000

int compare(const void * book1, const void * book2) { //função de comparação do nome dos livros para o qsort
	bookT *tempA = (bookT *)book1;
	bookT *tempB = (bookT *)book2;
	return strcmp(tempA->title, tempB->title);
}

void sorting(FILE *file1, FILE *file2, FILE *output);

void externalSorting(FILE *file, int memsize, int num_books){ //aplicação análoga ao MergeSort para ordenação externa
	long int i, j, k, count, last;
	size_t size;
	char straux[MAX_FILES];
	FILE *fileaux, *fileaux2, *fileaux3;
	bookT buffer, *book_array;

	last = num_books%memsize; //quantos livros ficam na última estante

	//particiona o arquivo em arquivos de tamanho M
	for(i=0, count=0; count<num_books; i++){
		sprintf(straux, "file%ld.bin", i);
		fileaux = fopen(straux, "wb");
		for(j=0; j<memsize; j++) {
			if(count==num_books)
                break;
			fscanf(file, "%s %c", buffer.title, &buffer.available);
			fprintf(fileaux, "%s %c\n", buffer.title, buffer.available);
			count++; //numero de arquivos total
		}
		fclose(fileaux);
	}
	//ordena internamente os i arquivos
	for(j=0; j<i; j++){
		if(j==i-1)
			size = (size_t)last;
		else
			size = (size_t)memsize;
		book_array = (bookT*)malloc(size*sizeof(bookT));
		sprintf(straux, "file%ld.bin", j);
		fileaux = fopen(straux, "r");

        //preenche o vetor de bookT a ser ordenado internamente com os livros do arquivo
		for(k=0; k<(int)size; k++) {
			fscanf(fileaux, "%s %c", book_array[k].title, &book_array[k].available);
		}
		fclose(fileaux);
		fileaux = fopen(straux, "wb");
		qsort(book_array, size, sizeof(bookT), compare); //ordena internamente

        //imprime o vetor ordenado no arquivo
        for(k=0; k<(int)size; k++){
			fprintf(fileaux, "%s %c\n", book_array[k].title, book_array[k].available);
		}
		fclose(fileaux);
		free(book_array);
	}

	//intercala os arquivos
	size = (size_t)(num_books/memsize+1); //conta numero de arquivos
	for(i=0; i<(int)size; i++){ //arquivos
		sprintf(straux, "file%ld.bin", size++);
		fileaux3 = fopen(straux, "wb");

		sprintf(straux, "file%ld.bin", i);
		fileaux = fopen(straux, "rb");
		sprintf(straux, "file%ld.bin", ++i);
		fileaux2 = fopen(straux, "rb");

        //ordena por intercalação
		sorting(fileaux, fileaux2, fileaux3);
		fclose(fileaux);
		fclose(fileaux2);
		fclose(fileaux3);
	}
	sprintf(straux, "mv file%ld.bin livros_ordenados", size-1);
	system(straux); //chamada do sistema para renomear o último arquivo file*.bin como o nome utilizado para um arquivo ordenado
	system("rm -f *.bin"); //chamada do sistema para remover todos os arquivos .bin criados temporáriamente

}

void sorting(FILE *file1, FILE *file2, FILE *output){
	//compara as primeiras duas linhas dos arquivos, passa a menor pra um arquivo output
	bookT book1, book2;
	int comp, length1=0, length2=0, count1=1, count2=1, flag1=0, flag2=0;
	size_t size=0;

	fscanf(file1, "%s %c", book1.title, &book1.available);
	fscanf(file2, "%s %c", book2.title, &book2.available);
	while(1) {
		comp = strcmp(book1.title, book2.title);
		if(feof(file1)==1){//se o primeiro arquivo acabar, "seta" um flag para ignora-lo no resto das intercalações
			comp = 1; //seta a comparação como >0 para funcionamento da função
			flag1 = 1;
		}
		if(feof(file2)==1){//se o segundo arquivo acabar, idem
			comp = -1;//seta a comparação como <0
			flag2 = 1;
		}
		if(flag1 == 1 && flag2 == 1){
			break; //se ambos os arquivos acabarem, quebra o while
		}
		if (comp < 0) {
			size = (size_t)strlen(book1.title);
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