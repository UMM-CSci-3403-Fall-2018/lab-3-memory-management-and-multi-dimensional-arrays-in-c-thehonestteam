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

int* reduce(int size, int position, int* arr) {
  int* tmp = (int*) calloc(size - 1, sizeof(int));
  for (int i = 0; i < position; i++) {
    tmp[i] = arr[i];
  }
  for (int i = position; i < size; i++) {
    tmp[i] = arr[i + 1];
  }
  return tmp;
}

int get_uniq(int size, int* arr) {
  int counter = 0;
  for (int i = 1; i < size - 1; i++) {
    if ((arr[i] = arr[i + 1])) {
      arr = reduce(size, i, arr);
      counter++;
    }
  }
  return counter;
}
 
int resize(int size, int *arr) {
  int counter = 0;
  if (size >= 2) {
    counter += get_uniq(size, arr);
  }
  return size - counter;
}
 
int* array_merge(int num_array, int* sizes, int** values) {
  int* tmp = (int*) calloc(get_total_size(num_array, sizes), sizeof(int));
  int tmp_size = brutal_merge(tmp, num_array, sizes, values);
  mergesort(tmp_size, tmp);
  int new_size = resize(tmp_size,tmp);
  int* result = (int*) calloc(new_size + 1, sizeof(int));
  result[0] = new_size;
  for (int i = 0; i < new_size; i++) {
    result[i + 1] = tmp[i];
  }
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



