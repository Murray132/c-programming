#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * curr = malloc(sizeof(*curr));
  curr -> array = NULL;
  curr -> sz = 0;
  curr -> unknown = 0;
  return curr;
  
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown = c ->unknown + 1;
    return;
  }
  int find = 0;

  for (size_t i =0; i< c->sz; i++) {
    char * temp = c->array[i]->str;
    if( strcmp(temp, name) == 0) {
      c->array[i]->counts = c->array[i]->counts + 1;
      find = 1;
    }
  }

  if ( find == 0) {
    c->array = realloc(c->array, (c->sz+1)*sizeof(*(c->array)));

    one_count_t * curr = malloc(sizeof(*curr));

    curr -> str = NULL;
    curr -> counts = 0;

    curr -> str = realloc( curr -> str, (strlen(name) + 1 )*sizeof(char));

    strcpy(curr->str, name);
    curr -> counts = 1;

    c->array[c->sz] = curr;
    c->sz = c->sz + 1;
  }
      
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    fprintf(outFile, "%s: %zd\n", c->array[i]->str, c->array[i]->counts );
  }
  if(c->unknown > 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i = 0; i< c->sz; i++){
    free(c->array[i]->str);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
