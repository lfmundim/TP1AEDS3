//
// Created by heimdallr on 17/09/16.
//

#ifndef AEDS3_TP1_BOOKS_H
#define AEDS3_TP1_BOOKS_H

typedef struct bookT{
	char title[51]; //título do livro + \0
	char available; //1 se o livro está disponível, 0 caso contrário
}bookT;

void includeBook(char* bookName, char availability, bookT* book);

#endif //AEDS3_TP1_BOOKS_H
