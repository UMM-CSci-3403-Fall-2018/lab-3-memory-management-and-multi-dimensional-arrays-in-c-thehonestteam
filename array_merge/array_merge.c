#include <stdlib.h>
#include "array_merge.h"
#include <stdbool.h>

// compare function for using qsort
int compare(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

// takes a number of total arrays and an int array of sizes, return the total size of their subarrays.
int get_total_size(int num_arrays, int* sizes) {
  int total = 0;
  for (int i = 0; i < num_arrays; i++) {
    total += sizes[i];
  }
  return total;
}

// takes an empty array and variables of a target array, merge all elements of the target array into the empty array.
int brutal_merge(int* result, int num_array, int* sizes, int** values) {
  int counter = 0;
  for (int i = 0; i < num_array; i++) {
    int* tmp = values[i];
    for (int j = 0; j < sizes[i]; j++) {
      result[counter] = tmp[j];
      counter++;
    }
  }
  return counter;
}

// takes an int as size and a SORTED int array. return a new array without duplicated elements. 
int* resize(int size, int* arr) {
  int* tmp = (int*) calloc(size, sizeof(int));
  int counter = 0;
  if (size == 0) {
  } else if (size >= 1) {
    tmp[0] = arr[0];
    counter++;
  }
  if (size >= 2) {
    for (int i = 1; i < size; i++) {
      if (arr[i] != arr[i - 1]) {
	tmp[counter] = arr[i];
	counter++;
      }
    }
  }
  int* result = (int*) calloc(counter + 1, sizeof(int));
  result[0] = counter;
  for (int i = 0; i < counter; i++) {
    result[i + 1] = tmp[i];
  }
  // free memory of tmp if return result 
  free(tmp);
  return result;
}

// execution function
// takes a number of arrays, an int array of sizes, and an array of arrays.
// merges the arrays into one array that has the first element as its size.
int* array_merge(int num_array, int* sizes, int** values) {
  int* tmp = (int*) calloc(get_total_size(num_array, sizes), sizeof(int));
  int tmp_size = brutal_merge(tmp, num_array, sizes, values);
  qsort(tmp, tmp_size, sizeof(int), compare);
  int* result = resize(tmp_size,tmp);
  // free memory of tmp
  free(tmp);
  return result;
}




