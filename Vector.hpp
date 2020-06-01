#pragma once

#include<cassert>

template <typename T> class MyVector {
  T * vector;
  long size_;
  long capacity;

  public:
  MyVector() {
    vector = new T[100];
    size_ = 0;
    capacity = 100;
  }

  MyVector(int n) {
    vector = new T[n];
    size_ = 0;
    capacity = n;
  }

  T& operator[](long pos) {
    return vector[pos];
  }

  T get_elem(long i) const {
    assert(i < size_);
    return vector[i];
  }

  void realloc() { 
      MyVector buf = *this;
      vector = new T[2*capacity];
      capacity = 2*capacity;
      size_ = capacity;
      for(int i = 0; i < size_; ++i) {
        vector[i] = buf.get_elem(i);
      }
      delete[] buf.vector;
  }

  void push_back(const T& elem) {
    if(size_ < capacity) {
      vector[size_] = elem;
      ++size_;
    }

    else {
      realloc();
      push_back(elem);
      ++size_;
    }
  }

  T pop_back() {
    if(size == 0) {
      std::cout << "Using pop on empty vector\n";
      std::abort();
    }

    else {
      --size;
      return vector[size];
    }
  }

  long size() const{
    return size_;
  }

  ~MyVector() {
    delete[] vector;
  }
};
