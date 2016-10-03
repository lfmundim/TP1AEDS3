#include <stdio.h>
#include "books.h"
#include "files.h"
#include "sorting.h"
#include "shelves.h"

int main(){
	int num_books, mem_size, num_shelves, shelf_size, requests, i, unused_shelves;
	char bookName[51], shelfname[15];
	FILE *index, *shelf, *temp;


	scanf("%d %d %d %d %d", &num_books, &mem_size, &num_shelves, &shelf_size, &requests);

	unused_shelves=num_shelves-num_books/shelf_size; //para contar quantos # colocar no índice
	//preenche arquivo temporário com os livros na ordem de entrada
	temp = fopen("temp.bin", "wb");
	fillTempFile(temp, num_books);
	fclose(temp);

	//ordena o arquivo
	temp = fopen("temp.bin", "rb");
	externalSorting(temp, mem_size, num_books); //Merge sort externo
	fclose(temp);
	index = fopen("indice", "wb");
	temp = fopen("livros_ordenados", "rb");

	//Separa em estantes
	for(i = 0; i<num_shelves; i++){
		sprintf(shelfname, "estante%d", i);
		shelf = fopen(shelfname, "wb");
		if(i<num_shelves-unused_shelves)
			createShelf(shelf, temp, shelf_size, index);
		fclose(shelf);
	}
	for(i=unused_shelves; i>0; i--){ //preenche o índice das estantes vazias com #
		fprintf(index, "#\n");
	}
	fclose(index);
	index = fopen("indice", "rb");

	//Procura livros
	for(i=0; i<requests; i++){ //a cada livro requisitado, imprime imediatamente depois a resposta
		scanf(" %s", bookName);
		findBookShelf(bookName, index, num_shelves, shelf_size);//procura no índice onde o livro estaria
		rewind(index); //volta o ponteiro do arquivo índice para o começo para a procura do próximo livro
	}
	fclose(index);
	fclose(temp);

	return 0;
}
