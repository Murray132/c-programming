#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
First, count the frequency of each letter
 */

int get_largest_element(int * arr, int n){
  int largestIndex = 0;
  for (int j =1; j<n; j++){
    if(arr[j]>arr[largestIndex]){
      largestIndex = j;
    }
  }
  return largestIndex;
}

int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr," format for file input is not correct \n" );
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int array[26]={0};
  int c;
  while((c = fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      for (int i = 0; i<26; i++){
        int lettervalue = i+97;
	if(c == lettervalue){
	  array[i] = array[i]+1;
	}
      }
    }
  }

  int total = 0;
  for (int j=0;j<26;j++;){
    total = total + array[j];
  }
  if(total == 0){
    fprintf(stderr," there is no letter in this context \n" );
    return EXIT_FAILURE;
  }
  
  int most_common_letter = get_largest_element(array, 26);
  //printf("The most common is %d\n",most_common_letter);
  int answer;
  if(most_common_letter >= 4){
    answer = most_common_letter - 4;
    printf("%d\n",answer);
    return EXIT_SUCCESS;
  }
  else{
    answer = most_common_letter - 4 + 26;
    printf("%d\n",answer);
    return EXIT_SUCCESS;
  }
  
}
