#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int* sort();


int main(int argc, char* argv[]) {
  int *arr =(int*) calloc(10, sizeof(int));
  arr[0] = 3;
  arr[1] = 4;
  sort(arr);
  for(int i = 0; i < 3; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  
}
