#include <stdio.h>
#include <stdlib.h>


unsigned power (unsigned x, unsigned y);
int main(void) {
  
  unsigned a1 = power(11,2);
  if(a1 != 121){
    return EXIT_FAILURE;
  }

  unsigned a2 =power(0,0);
  if(a2 != 1) {
    return EXIT_FAILURE;
  }
  
  unsigned a3 = power(-1,1);
  if(a3 != 4294967295){
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
