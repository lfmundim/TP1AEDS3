//
// Created by heimdallr on 17/09/16.
//

#include <memory.h>
#include <stdio.h>
#include "books.h"

void findBook(char* book_name, int shelf_num, int shelfsize);

void findBookShelf(char* book_name, FILE *index, int num_shelves, int shelfsize){
	char aux[51];
	int i, cmp, flag_smaller=0, flag_bigger=0;

	for(i=0; i<num_shelves; i++){
		//vê se o livro ficaria na estante i atual
		//TODO fscanf bugado??
		fscanf(index, "%s ", aux);
		cmp = strcmp(aux, book_name);
		//livro vem antes do lido
		if(cmp>=0)
			flag_smaller=1;

		fscanf(index, " %s", aux);
		cmp = strcmp(aux, book_name);
		//livro vem depois do lido
		if(cmp<=0)
			flag_bigger=1;

		//nome do livro viria antes do primeiro da primeira estante
		if(i==0 && flag_smaller == 1){
			printf("livro nao encontrado\n");
			break;
		}
		//nome do livro esta na estante atual
		if(flag_bigger==0 && flag_smaller==0)
			findBook(book_name, i, shelfsize);
		//nome do livro viria depois do último da última estante
		if(i==num_shelves-1 && flag_bigger==1){
			printf("livro nao encontrado\n");
			break;
		}
	}
}

void findBook(char* book_name, int shelf_num, int shelfSize){
	FILE* shelf;
	int i, cmp, pos;
	char available, aux[51], shelf_name[15];

	sprintf(shelf_name, "estante%d", shelf_num);

	shelf = fopen(shelf_name, "rb");

	for(i=0; i<shelfSize; i++){
		fscanf(shelf, " %s %c", aux, &available);
		cmp = strcmp(book_name, aux);
		if(cmp<0){
			printf("livro nao encontrado\n");
			break;
		}
		if(cmp==0){
			if(available==48){
				printf("emprestado\n");
				break;
			}
			if(available==49){
				pos = ftell(shelf)/sizeof(bookT);
				printf("disponivel na posicao %d na estante %d\n", pos, shelf_num);
				break;
			}
		}
	}

}
