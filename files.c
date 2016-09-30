//
// Created by heimdallr on 20/09/16.
//

#include <memory.h>
#include "files.h"
#include "books.h"

void fillTempFile(FILE *temp, int num_books){
	int i, size;
	bookT book;

	for(i=0; i<num_books; i++){
		scanf("%s %c", book.title, &book.available);
		size = strlen(book.title);
		fwrite(book.title, size*sizeof(char), 1, temp);
		//fprintf(temp, "%s", book.title);
		fprintf(temp, " ");
		fwrite(&book.available, sizeof(char), 1, temp);
		//fprintf(temp, "%c", book.available);
		fprintf(temp, "\n");
	}
}

void readTempFile(FILE *temp, int num_books){
	int i;
	bookT buffer;

	rewind(temp);

	for(i=0; i<num_books; i++){
		fscanf(temp, "%s %c", buffer.title, &buffer.available);
		printf("%s\n", buffer.title);
	}
}