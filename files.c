//
// Created by heimdallr on 20/09/16.
//

#include <memory.h>
#include "files.h"
#include "books.h"

void fillTempFile(FILE *temp, int num_books){ //preenche um arquivo temporário com os livros na ordem de entrada
	int i;
	size_t size;
	bookT book;

	for(i=0; i<num_books; i++){
		scanf("%s %c", book.title, &book.available);
		size = strlen(book.title);
		fwrite(book.title, size*sizeof(char), 1, temp);
		fprintf(temp, " ");
		fwrite(&book.available, sizeof(char), 1, temp);
		fprintf(temp, "\n");
	}
}