#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

class DynamicArray {
private:
  int* data;
  int capacity;
  int length;

  void resize();

public:
  DynamicArray();
  ~DynamicArray();

  void push_back(int value);
  int size() const;
  int operator[](int index) const;
  void clear();
};

#endif