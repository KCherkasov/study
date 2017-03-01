#include <stdio.h>
#include <stdlib.h>

#define BASE_CONTAINER_SIZE 4;
#define GROW_FACTOR 2;

#define true 0
#define false 1

#define RC_OK 0
#define RC_ERROR 1

#define LOWERCASE_SHIFT 32

void errprint() {
  printf("[error]");
}

size_t max(size_t lhs, size_t rhs) {
  if (lhs >= rhs) {
    return lhs;
  } else {
    return rhs;
  }
}

//-- String structure --//

struct cstring {
  char* _buffer;
  size_t _size;
  size_t _capacity;
};

typedef struct cstring CString;

size_t grow(CString* string) {
  if (string == NULL) {
    return RC_ERROR;
  }
  char* temp = NULL;
  size_t new_capacity = max(string->_capacity * GROW_FACTOR, BASE_CONTAINER_SIZE);
  if (!(temp = calloc(new_size, sizeof(char)))) {
    return RC_ERROR;
  }
  for (size_t i = 0; i < string->_capacity; ++i) {
    temp[i] = string->_buffer[i];
  }
  string->_capacity = new_capacity;
  free(string->_buffer);
  string->_buffer = temp;
  return RC_OK;
}

size_t push(CString* string, char letter) {
  if (string->_size == string->_capacity) {
    if (grow(string) != RC_OK) {
      return RC_ERROR;
    }
  }
  string->_buffer[_size++] = letter;
  return RC_OK;
}

size_t clear(CString* string, bool free_memory = true) {
  string->_size = 0;
  if (free_memory == true) {
    string->_capacity = 0;
    free(string->_buffer);
    string->_buffer = NULL;
  }
  return RC_OK;
}

size_t lowercase(CString* string) {
  if (string == NULL) {
    return RC_ERROR;
  }
  char* letter = string->_buffer;
  while (*letter != 0) {
    if (*letter > 'A' && *letter < 'Z') {
      *letter += LOWERCASE_SHIFT;
    }
    ++letter;
  }
  return RC_OK;
}

//-- String structure end --//

//-- StringList structure --//

struct cstringlist {
  CString* _buffer;
  size_t _size;
  size_t _capacity;
};

typedef struct cstringlist CStringList;

size_t grow(CStringList* list) {
  if (list == NULL) {
    return RC_ERROR;
  }
  size_t new_capacity = max(list->_capacity * GROW_FACTOR, BASE_CONTAINER_SIZE);
  CString* temp = NULL;
  if (!(temp = (CString*)calloc(new_capacity, sizeof(CString)))) {
    return RC_ERROR;
  }
  for (size_t i = 0; i < list->_capacity; ++i) {
    free(temp[i]._buffer);
    temp[i]._buffer = list->_buffer[i]._buffer;
    temp[i]._size = list->_buffer[i]._size;
    temp[i]._capacity = list->buffer[i]._capacity;
  }
  free(list->_buffer);
  list->_buffer = temp;
  list->_capacity = new_capacity;
  return RC_OK;
}

size_t push(CStringList* list, CString string) {
  if (list->_size == list->_capacity) {
    if(grow(list) != RC_OK) {
      return RC_ERROR;
    }
  }
  free(list->_buffer[list->_size]._buffer);
  list->_buffer[list->_size]._buffer = string._buffer;
  list->_buffer[list->_size]._size = string._size;
  list->_buffer[list->_size]._capacity = string._capacity;
  ++list->_size;
  return RC_OK;
}

size_t clear(CStringList* list, bool free_memory = true) {
  if (list == NULL) {
    return RC_ERROR;
  }
  for (size_t i = 0; i < list->_size; ++i) {
    if (clear(list->_buffer[i], free_memory) != RC_OK) {
      return RC_ERROR;
    }
  }
  list->_size = 0;
  if (free_memory == true) {
    free(list->_buffer);
    list->_buffer = NULL;
    list->_capacity = 0;
  }
  return RC_OK;
}

size_t lowercase(CStringList* list) {
  if (list == NULL) {
    return RC_ERROR;
  }
  return RC_OK;
}

size_t print(CStringList* list) {
  if (list == NULL) {
    return RC_ERROR;
  }
  return RC_OK;
}

//-- StringList structure end --//

size_t read_strings(char*** result) {
  size_t count = 0;
  
  return count;
}

size_t process_strings(char** source, size_t count, char*** result) {
  size_t response = 0;
  
  return response;
}

int main() {
  char** input, output;
  size_t count = read_strings(&input);
  if (count == 0) {
    errprint();
    return 0;
  }
  if (process_strings(input, count, &output) == count) {
    errprint();
  }
  return 0;
}
