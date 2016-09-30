#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "books.h"
#include "files.h"
#include "sorting.h"
#include "shelves.h"

//TODO Busca binária

int main(){
	int num_books, mem_size, num_shelves, shelf_size, requests, i, j, k, num, count, unused_shelves;
	char bookName[51], availability, shelfname[15];
	bookT *books;
	FILE *index, *shelf, *temp;


	scanf("%d %d %d %d %d", &num_books, &mem_size, &num_shelves, &shelf_size, &requests);

	unused_shelves=num_shelves-num_books/shelf_size;

	temp = fopen("temp.bin", "wb");
	fillTempFile(temp, num_books);
	fclose(temp);
	temp = fopen("temp.bin", "rb");
	externalSorting(temp, mem_size, num_books);
	fclose(temp);
	index = fopen("indice", "wb");
	temp = fopen("livros_ordenados", "rb");
	for(i = 0; i<num_shelves; i++){
		sprintf(shelfname, "estante%d", i);
		shelf = fopen(shelfname, "wb");
		if(i<num_shelves-unused_shelves)
			createShelf(shelf, temp, shelf_size, index);
		else
			shelf = fopen(shelfname, "wb");
		fclose(shelf);
	}
	for(i=unused_shelves; i>0; i--){
		fprintf(index, "#\n");
	}
	fclose(index);
	fclose(temp);

	return 0;
}