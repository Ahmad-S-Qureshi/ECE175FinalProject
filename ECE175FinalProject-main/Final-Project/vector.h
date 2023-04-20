#include <stdio.h>
#include <stdlib.h>
#include "linkedListFunctions.h"
// I don't know why, but it breaks when using test
// after making Vector *test but not when making
// Vector test and using &test when calling functions

typedef struct vector{
  LinkedListData *content;
  int size;
} Vector;

//make, destroy, append, delete, insert, pointer, resize

void vector_create(Vector *v, int size);
void vector_destroy(Vector *v);
void vector_resize(Vector *v, int newSize);
int* vector_at(Vector *v, int index); //gives pointer, not actual value
void vector_insert(Vector *v, int index, int value);
void vector_append(Vector *v, int value);
void vector_delete(Vector *v, int index);


void vector_create(Vector *v, int size){
  v->content = (LinkedListData*)malloc(size * sizeof(LinkedListData));
  v->size = size;
  int i;
  for (i=0; i<size; ++i){
    initializeData(v->content[i]);
  }
}
void vector_destroy(Vector *v){
  if (v->content == NULL){
    return;
  }
  free(v->content);
  v->content = NULL;
  v->size = 0;
}
void vector_resize(Vector *v, int newSize){
  if (v->content == NULL){
    return;
  }
  v->content = (LinkedListData*)realloc(v->content, newSize*sizeof(LinkedListData));
  int i;
  for (i = v->size; i < newSize; ++i){ //initialize any new values
    v->content[i] = 0;
  }
  v->size = newSize;
}
int* vector_at(Vector *v, int index){
  if (v->content == NULL){
    return NULL;
  }
  return &(v->content[index]);
}
void vector_insert(Vector *v, int index, int value){
  if (v->content == NULL){
    return;
  }
  vector_resize(v, v->size + 1);
  int i;
  for (i = v->size - 1; i > index; --i){
    v->content[i] = v->content[i-1];
  }
  v->content[index] = value;
}
void vector_delete(Vector *v, int index){
  if (v->content == NULL){
    return;
  }
  int i;
  for (i = index; i > (v->size - 2); --i){
    v->content[i] = v->content[i+1];
  }
  vector_resize(v, v->size);
}
void vector_append(Vector *v, int value){
  if (v->content == NULL){
    return;
  }
  vector_resize(v,v->size + 1);
  v->content[v->size-1] = value;
}