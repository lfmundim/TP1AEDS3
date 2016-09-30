//
// Created by heimdallr on 17/09/16.
//

#include <memory.h>
#include "books.h"

void includeBook(char* bookName, char availability, bookT* book){
	strcpy(book->title, bookName);
	book->available = availability;
}

