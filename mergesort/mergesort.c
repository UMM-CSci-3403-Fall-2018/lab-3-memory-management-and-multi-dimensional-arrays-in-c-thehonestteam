#include <stdlib.h>
#include "mergesort.h"
#include <stdbool.h>

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

