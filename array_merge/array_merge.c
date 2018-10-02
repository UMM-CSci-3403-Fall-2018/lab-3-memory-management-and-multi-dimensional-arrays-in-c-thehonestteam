#include <stdlib.h>
#include "array_merge.h"
#include <stdbool.h>

void mergesort(int, int*);

int get_total_size(int num_arrays, int* sizes) {
  int total = 0;
  for (int i = 0; i < num_arrays; i++) {
    total += sizes[i];
  }
  return total;
}

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

 
int* resize(int size, int* arr) {
  int* tmp = (int*) calloc(size, sizeof(int));
  int counter = 0;
  for (int i = 0; i < size; i++) {
    if (size < 2) {
      tmp[counter] = arr[i];
      counter++;
      break;
    }  else if (arr[i] != arr[i + 1]) {
      tmp[counter] = arr[i];
      counter++;
    }
  }
  int* result = (int*) calloc(counter + 1, sizeof(int));
  result[0] = counter;
  for (int i = 0; i < counter; i++) {
    result[i + 1] = tmp[i];
  }
  free(tmp);
  return result;
}
 
int* array_merge(int num_array, int* sizes, int** values) {
  int* tmp = (int*) calloc(get_total_size(num_array, sizes), sizeof(int));
  int tmp_size = brutal_merge(tmp, num_array, sizes, values);
  mergesort(tmp_size, tmp);
  int* result = resize(tmp_size,tmp);
  free(tmp);
  return result;
}

//////////////////////////////////////////////////////////////////////
////////////      we add our sorting methods below    ////////////////


// takes an int and return if it is bigger than 2
bool needsSorting(int rangeSize) {
  return rangeSize >= 2;
}

// takes an int array as target, an int as start index, an int and middle point, and an int and the end index. Works as partition()
void mergeRanges(int *values, int startIndex, int midPoint, int endIndex) {
  int rangeSize = endIndex - startIndex;
  int *destination = (int*) calloc(rangeSize, sizeof(int));
  int firstIndex = startIndex;
  int secondIndex = midPoint;
  int copyIndex = 0;
  while (firstIndex < midPoint && secondIndex < endIndex) {
    if (values[firstIndex] < values[secondIndex]) {
      destination[copyIndex] = values[firstIndex];
      ++firstIndex;
    } else {
      destination[copyIndex] = values[secondIndex];
      ++secondIndex;
    }
    ++copyIndex;
  }
  while (firstIndex < midPoint) {
    destination[copyIndex] = values[firstIndex];
    ++copyIndex;
    ++firstIndex;
  }
  while (secondIndex < endIndex) {
    destination[copyIndex] = values[secondIndex];
    ++copyIndex;
    ++secondIndex;
  }
  for (int i = 0; i < rangeSize; ++i) {
    values[i + startIndex] = destination[i];
  }
  // free destination everytime the method ends
  free(destination);
}

// recursive function that takes an int array, an int as start index, and an int as the end index. Recursively devides the array to half and hands over to the MergeRanges function.
void mergesortRange(int *values, int startIndex, int endIndex) {
  int rangeSize = endIndex - startIndex;
  if (needsSorting(rangeSize)) {
    int midPoint = (startIndex + endIndex) / 2;
    mergesortRange(values, startIndex, midPoint);
    mergesortRange(values, midPoint, endIndex);
    mergeRanges(values, startIndex, midPoint, endIndex);
  }
}

// execution call to our mergesort function. It takes a int as size and an int array as our target
void mergesort(int size, int *values) {
  mergesortRange(values, 0, size);
}  



