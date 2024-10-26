#include "DynamicArray.h"
#include <string.h>

void DynamicArray::resize() {
  capacity *= 2;
  int* newData = new int[capacity];
  memcpy(newData, data, length * sizeof(int));
  delete[] data;
  data = newData;
}

DynamicArray::DynamicArray() : capacity(1), length(0) {
  data = new int[capacity];
}

DynamicArray::~DynamicArray() {
  delete[] data;
}

void DynamicArray::push_back(int value) {
  if (length == capacity) {
    resize();
  }
  data[length++] = value;
}

int DynamicArray::size() const {
  return length;
}

int DynamicArray::operator[](int index) const {
  if (index < 0 || index >= length) {
    return -1;
  }
  return data[index];
}

void DynamicArray::clear() {
  delete[] data;
  data = new int[1];
  capacity = 1;
  length = 0;
}