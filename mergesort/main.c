#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

// declare the mergesort method
void mergesort(int, int*);

// set up a main to run valgrind test, because it is only for the valgrind test we didn't fulfill the entire array.
int main(int argc, char* argv[]) {
  int *arr =(int*) calloc(10, sizeof(int));
  arr[0] = 3;
  arr[1] = 4;
  mergesort(10, arr);
  for(int i = 0; i < 3; i++) {
    printf("%d ", arr[i]);
  }
  free(arr);
  printf("\n");
  
}
