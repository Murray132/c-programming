#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * splitpairs(char * str) {
  char * eqlsign = strchr(str, '='); // first apperence of equal sign
  *eqlsign = '\0'; // convert equal sign into null terminator
  char * value = eqlsign + 1 ;
  char * newline = strchr(value, '\n');
  if( newline != NULL) {
    *newline = '\0';
  }
  kvpair_t * p = malloc( (size_t) sizeof(*p) );
  p->key = str;
  p->value = value;
  return p;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME

  //opem the file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }
  //read the lines
  char * line = NULL;
  size_t sz = 0;
  kvpair_t * curr_pair = NULL;

  kvarray_t * kv_array = malloc( sizeof(*kv_array));//use "(size_t)"
  kv_array->size = 0;
  kv_array->array =NULL;

  while (getline(&line, &sz, f) >= 0) {
    curr_pair = splitpairs(line);
    kv_array->array = realloc(kv_array->array, (kv_array->size+1)*sizeof(*(kv_array->array)));
    kv_array->array[kv_array->size] = curr_pair;
    kv_array->size ++;
    line = NULL;
  }
  free(line);

  int result = fclose(f);
  if (result != 0) {
    return NULL;
  }
  return kv_array;
}



void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i =0; i<pairs->size; i++){
    free(pairs->array[i]->key);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * curr_pair;
  for (int i = 0; i< pairs->size; i++) {
    curr_pair = pairs->array[i];
    printf("key = '%s' value = '%s'\n", curr_pair->key, curr_pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t * curr_pair = NULL;
  for(int i = 0; i< pairs->size; i++) {
    curr_pair = pairs->array[i];
    if( !strcmp(curr_pair->key, key)) {
      return curr_pair->value;
    }
  }
  return NULL;
}
