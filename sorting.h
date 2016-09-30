//
// Created by heimdallr on 25/09/16.
//

#ifndef AEDS3_TP1_SORTING_H
#define AEDS3_TP1_SORTING_H

#include <stdio.h>

int compare(const void * book1, const void * book2);

void externalSorting(FILE *file, int memsize, int num_books);

void sorting(FILE *file1, FILE *file2, FILE *output, int memsize);

#endif //AEDS3_TP1_SORTING_H
