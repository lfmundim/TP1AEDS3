//
// Created by heimdallr on 17/09/16.
//

#ifndef AEDS3_TP1_SHELVES_H
#define AEDS3_TP1_SHELVES_H

#include "books.h"

typedef struct shelfT{
	bookT* first, last; //apontadores para o primeiro e último livros da estante
	int size; //tamanho da prateleira
	char empty; //1 se vazia, 0 se possui livros
}shelfT;

void createShelf(FILE *shelf, FILE *books, int shelfsize, FILE *index);

#endif //AEDS3_TP1_SHELVES_H
