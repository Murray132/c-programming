#include <stdio.h>
#include <stdlib.h>

size_t maxSeq (int * array, size_t n){

  size_t max = 0;
  size_t length = 0;
  if (n==0) {
    return length;
  }
  else if (n==1) {
   length = 1;
   return length;
  }
  max++;
  length++;
  for (int j=1; j<n; j++){
   
    if (array[j]>array[j-1]){
      length++;
    }
    else{
      if(max<length){
	max =length;
      }
      length =1;
    }
  }

  if (max < length){
    max = length;
  }

  return max;

}

