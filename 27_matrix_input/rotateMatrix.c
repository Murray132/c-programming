#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10]){
  //int range = 9; 
  for (int i=0; i<5;i++){
    for (int j=i;j<9-i;j++){
      char temp = matrix[i][j];
      matrix[i][j] = matrix[9-j][i];
      matrix[9-j][i]=matrix[9-i][9-j];
      matrix[9-i][9-j]=matrix[j][9-i];
      matrix[j][9-i]= temp;
    }
  }
}

int main(int argc, char** argv){
  if(argc != 2){
    fprintf(stderr, "Usage : Wrong amount of Arguments\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1],"r");
  if(f == NULL){
    fprintf(stderr,"Usage : Couldn't open file\n");
    return EXIT_FAILURE;
  }

  int c = fgetc(f);
  if(c == EOF){
    fprintf(stderr, "Usage : Empty File\n");
    return EXIT_FAILURE;
  }
  char input_matrix[10][10];
  int row = 0;
  int column=0;

  while( c! = EOF){

    if(row >9){// first check whether the input matrix has more than 10 rows
      fprintf(stderr,"Usage: Exceed maximal number of rows ");
    }

    if(column == 10){
      column = 0; // when reach the end of the row, set column index to be 0 and start the next row
      row++;

      if(c != '\n'){
	fprintf(stderr, "Usage: Missing newline command at the end of the row\n");
	return EXIT_FAILURE;
      }
    }

    else{ // check if the row has less than 10 characters
      if(c == '\n'){
	fprintf(stderr, "Usage: the row have less than 10 characters");
	return EXIT_FAILURE;
      }

      input_matrix[row][column]=c;
      column++;
    }
    c = fgetc(f);// advance the file
  }

  fclose(f);// close the file

  if(row < 10){
    printf(stderr, "Usage: insufficent number of rows\n");
    return EXIT_FAILURE;
  }

  rotate(input_matrix);

  for(int i=0;i<10;i++){
    for (int j =0;j<10;j++){
      printf("%c",input_matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}

  

      


      

      
