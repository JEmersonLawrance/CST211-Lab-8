#include "Array.h"

// Paramaterized Constructor
template <typename T>
Array<T>::Array(int length, int start_index)
    : m_length(length), m_start_index(start_index) {
  if (length > 0)
    m_array = new T[length]{};
}

// Copy Constructor
template <typename T>
Array<T>::Array(const Array<T> &copy)
    : m_length(copy.m_length), m_start_index(copy.m_start_index) {
  if (copy.m_length > 0) {
    m_array = new T[copy.m_length]{};
    std::memmove(m_array, copy.m_array, copy.m_length * sizeof(T));
  }
}

// Move Constructor
template <typename T>
Array<T>::Array(Array<T> &&move) noexcept
    : m_length(move.m_length), m_start_index(move.m_start_index) {
  move.m_length = 0;
  move.m_start_index = 0;
  m_array = move.m_array;
  move.m_array = nullptr;
}

// Destructor
template <typename T> Array<T>::~Array() { delete[] m_array; }

// Copy Assignment Operator
template <typename T> Array<T> &Array<T>::operator=(const Array<T> &copy) {
  m_start_index = copy.m_start_index;
  m_length = copy.m_length;

  if (copy.m_length > 0) {
    m_array = new T[copy.m_length]{};
    std::memmove(m_array, copy.m_array, copy.m_length * sizeof(T));
  }

  return *this;
}

// Move Assignment Operator
template <typename T> Array<T> &Array<T>::operator=(Array<T> &&move) noexcept {
  m_start_index = move.m_start_index;
  m_length = move.m_length;
  move.m_start_index = 0;
  move.m_length = 0;
  m_array = move.m_array;
  move.m_array = nullptr;
  delete move.m_array;

  return *this;
}

// Subscript Operator
template <typename T> T &Array<T>::operator[](int index) {
  index -= m_start_index; // make index total distance from starting index

  if (index < 0 || index > (m_length - 1)) {
    T except{};
    return except;
  }

  return m_array[index];
}

// Get Start Index
template <typename T> const int Array<T>::getStartIndex() {
  return m_start_index;
}

// Set Start Index
template <typename T> void Array<T>::setStartIndex(const int start_index) {
  m_start_index = start_index;
}

// Get Length of Array
template <typename T> const int Array<T>::getLength() { return m_length; }

// Set Length of Array
template <typename T> void Array<T>::setLength(int length) {
  if (length < 0)
    return;

  T *temp = new T[length]{};

  if (m_array != nullptr) {

    if (m_length > length)
      std::memmove(temp, m_array, length * sizeof(T));
    else
      std::memmove(temp, m_array, m_length * sizeof(T));

    std::memset(m_array, 0, m_length * sizeof(T));
  }

  m_length = length;
  m_array = temp;
  temp = nullptr;
  delete temp;
}
