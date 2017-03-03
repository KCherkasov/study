#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BASE_CONTAINER_SIZE 4
#define GROW_FACTOR 2

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

size_t grow_string(CString* string) {
  if (string == NULL) {
    return RC_ERROR;
  }
  char* temp = NULL;
  size_t new_capacity = max(string->_capacity * GROW_FACTOR, BASE_CONTAINER_SIZE);
  if (!(temp = (char*)calloc(new_capacity, sizeof(char)))) {
    return RC_ERROR;
  }
  if (string->_buffer != NULL) {
    for (size_t i = 0; i < string->_capacity; ++i) {
      temp[i] = string->_buffer[i];
    }
    free(string->_buffer);
  }
  string->_capacity = new_capacity;
  string->_buffer = temp;
  return RC_OK;
}

size_t push_char(CString* string, char letter) {
  if (string->_size == string->_capacity) {
    if (grow_string(string) != RC_OK) {
      return RC_ERROR;
    }
  }
  string->_buffer[string->_size++] = letter;
  return RC_OK;
}

size_t clear_string(CString* string, bool free_memory) {
  string->_size = 0;
  if (free_memory == true) {
    string->_capacity = 0;
    free(string->_buffer);
    string->_buffer = NULL;
  }
  return RC_OK;
}

size_t lowercase_string(CString* string) {
  if (string == NULL) {
    return RC_ERROR;
  }
  char* letter = string->_buffer;
  while (*letter != 0) {
    if (*letter >= 'A' && *letter <= 'Z') {
      *letter += LOWERCASE_SHIFT;
    }
    ++letter;
  }
  return RC_OK;
}

size_t print_string(CString string) {
  if (string._buffer == NULL) {
    return RC_ERROR;
  }
  printf("%s\n", string._buffer);
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

size_t grow_list(CStringList* list) {
  if (list == NULL) {
    return RC_ERROR;
  }
  size_t new_capacity = max(list->_capacity * GROW_FACTOR, BASE_CONTAINER_SIZE);
  CString* temp = NULL;
  if (!(temp = (CString*)calloc(new_capacity, sizeof(CString)))) {
    return RC_ERROR;
  }
  if (list->_buffer != NULL) {
    for (size_t i = 0; i < list->_capacity; ++i) {
      free(temp[i]._buffer);
      temp[i]._buffer = list->_buffer[i]._buffer;
      temp[i]._size = list->_buffer[i]._size;
      temp[i]._capacity = list->_buffer[i]._capacity;
    }
    free(list->_buffer);
  }
  list->_buffer = temp;
  list->_capacity = new_capacity;
  return RC_OK;
}

size_t push_string(CStringList* list, CString string) {
  if (list->_size == list->_capacity) {
    if(grow_list(list) != RC_OK) {
      return RC_ERROR;
    }
  }
  free(list->_buffer[list->_size]._buffer);
  list->_buffer[list->_size]._buffer = NULL;
  if (!(list->_buffer[list->_size]._buffer = (char*)calloc(string._capacity, sizeof(char)))) {
    return RC_ERROR;
  }
  char* letter = string._buffer;
  char* inlist = list->_buffer[list->_size]._buffer;
  while (*letter != '\0') {
  	*inlist = *letter;
  	++letter;
  	++inlist;
  }
  list->_buffer[list->_size]._size = string._size;
  list->_buffer[list->_size]._capacity = string._capacity;
  ++list->_size;
  return RC_OK;
}

size_t clear_list(CStringList* list, bool free_memory) {
  if (list == NULL) {
    return RC_ERROR;
  }
  for (size_t i = 0; i < list->_size; ++i) {
    if (clear_string(&(list->_buffer[i]), free_memory) != RC_OK) {
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

size_t lowercase_list(CStringList* list) {
  if (list == NULL) {
    return RC_OK;
  }
  size_t i = 0;
  for (; i < list->_size; ++i) {
    if (lowercase_string(&(list->_buffer[i])) != RC_OK) {
      return i;
    }
  }
  return i;
}

size_t print_list(CStringList list) {
  if (list._size == 0 || list._buffer == NULL) {
    return RC_ERROR;
  }
  for (size_t i = 0; i < list._size; ++i) {
    if (print_string(list._buffer[i]) != RC_OK) {
      return RC_ERROR;
    }
  }
  return RC_OK;
}

//-- StringList structure end --//

size_t read_strings(CStringList* result) {
  if (result == NULL) {
    return 0;
  }
  char letter;
  CString string = { NULL, 0, 0 };
  while(scanf("%c", &letter) != EOF) {
  	//printf("%d\n", letter);
    if (letter == '\n' || letter == '\0') {
      if (push_char(&string, '\0') != RC_OK) {
        clear_string(&string, true);
        return 0;
      }
      if (push_string(result, string) != RC_OK) {
        clear_string(&string, true);
        return 0;
      }
      string._buffer = NULL;
      string._size = 0;
      string._capacity = 0;
    } else {
      if (push_char(&string, letter) != RC_OK) {
        clear_string(&string, true);
        return 0;
      }
    }
  }
  if (string._buffer != NULL) {
    if (push_string(result, string) != RC_OK) {
  	  clear_string(&string, true);
      return 0;
    }
  }
  return result->_size;
}

size_t process_strings(CStringList source, size_t count, CStringList* result) {
  if (source._size != count || result == NULL) {
    return 0;
  }
  clear_list(result, true);
  for(size_t i = 0; i < count; ++i) {
    push_string(result, source._buffer[i]);
  }
  return lowercase_list(result);
}

int main() {
  CStringList input = { NULL, 0, 0 };
  CStringList output = { NULL, 0, 0 };
  size_t count = read_strings(&input);
  if (count == 0) {
    errprint();
    return 0;
  }
  if (process_strings(input, count, &output) != count) {
    errprint();
    return 0;
  }
  if (print_list(output) != RC_OK) {
    errprint();
  }
  clear_list(&input, true);
  clear_list(&output, true);
  return 0;
}
