#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void rotate(char matrix[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = i; j < 10; j++){

      char temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix [j][i] = temp;
      
    }
  }

  for (int k = 0; k < 10; k++) {
    for (int l = 0; l < 5; l++) {
      char temp1 = matrix[k][l];
      matrix[k][l] = matrix[k][9-l];
      matrix[k][9-l] = temp1;
    }
  }
    
    



  





}
  
