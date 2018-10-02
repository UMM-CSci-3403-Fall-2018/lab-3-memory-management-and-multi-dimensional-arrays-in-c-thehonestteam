#include <stdlib.h>
#include "array_merge.h"
//#include "mergesort.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int num_arrays = 10;
  int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int* a[] = { a0, a0, a0, a0, a0, a0, a0, a0, a0, a0 };

  int* result = array_merge(num_arrays, sizes, a);
  int printing = result[0];
  free(result);

  printf("%d\n", printing);

  
}
