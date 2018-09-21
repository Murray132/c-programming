#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int * array, size_t n);

int main (void) {

  int array1[] = {-4,2,4};
  size_t ans1 = maxSeq(array1,3);
  if(ans1 != 3) {
    printf("Something is wrong");
     return EXIT_FAILURE;
  }

  
  int array2[] = {1,1,1,1,1,1};
  size_t ans2 = maxSeq(array2,6);
  if(ans2 != 1) {
    printf("Something is wrong");
     return EXIT_FAILURE;
  }
  
  
  int array3[] = {425, 59, -3, 77,0,36};
  size_t ans3 = maxSeq(array3,6);
  if(ans3 != 2) {
    printf("Something is wrong");
     return EXIT_FAILURE;
  }
  
  
  int array4[] = {};
  size_t ans4 = maxSeq(array4,0);
  if(ans4 != 0) {
    printf("Something is wrong");
     return EXIT_FAILURE;
  }

  
  return EXIT_SUCCESS;
}
