#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int length = strlen(inputName);
  char * Outnameptr = malloc((length+8)*sizeof(*Outnameptr));
  char * ptr = Outnameptr;

  while(*inputName !='0'){
    *ptr = *inputName;
    ptr++;
    inputName++;
  }

  char * suffix = ".counts";
  while(*suffix != '0'){
    *ptr = *suffix;
    ptr++;
    suffix++;
  }
  *ptr = '\0';
  
  return Outnameptr;
}
