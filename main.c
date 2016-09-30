#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "books.h"
#include "files.h"
#include "sorting.h"

int main(){
	int num_books, mem_size, num_shelves, shelf_size, requests, i, j, k, num, count;
	char bookName[51], availability, shelfname[9];
	bookT *books;
	FILE *index, *shelves, *temp;

	scanf("%d %d %d %d %d", &num_books, &mem_size, &num_shelves, &shelf_size, &requests);

	temp = fopen("temp.bin", "wb");
	fillTempFile(temp, num_books);
	fclose(temp);
	temp = fopen("temp.bin", "rb");
	externalSorting(temp, mem_size, num_books);
	fclose(temp);
//	temp = fopen("temp.bin", "rb");
//	readTempFile(temp, num_books);
//	fclose(temp);

	return 0;
}