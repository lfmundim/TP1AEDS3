//
// Created by heimdallr on 17/09/16.
//

#include <stdio.h>
#include <memory.h>
#include "shelves.h"

void createShelf(FILE *shelf, FILE *books, int shelfsize, FILE *index){
	int i;
	bookT book;
	fscanf(books, "%s %c", book.title, &book.available);
	for(i=0; i<shelfsize; i++){
		if(i==0)
			fwrite(book.title, strlen(book.title)*sizeof(char), 1, index);
		else if(i==shelfsize-1) {
			fprintf(index, " ");
			fwrite(book.title, strlen(book.title) * sizeof(char), 1, index);
			fprintf(index, "\n");
		}
		fwrite(book.title, strlen(book.title)*sizeof(char), 1, shelf);
		fprintf(shelf, " ");
		fwrite(&book.available, sizeof(char), 1, shelf);
		fprintf(shelf, "\n");
		if(i!=shelfsize-1)
			fscanf(books, "%s %c", book.title, &book.available);
		if(book.available==EOF)
			break;
	}
}