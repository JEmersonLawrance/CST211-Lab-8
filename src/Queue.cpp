#include "Queue.h"
#include <iostream>

// Constructors
template <typename T> Queue<T>::Queue() : m_size(0) { // Default
  m_buffer.setLength(75000);
}
template <typename T>
Queue<T>::Queue(const Queue &copy)
    : m_buffer(copy.m_buffer), m_size(copy.m_size),
      front_index(copy.front_index), rear_index(copy.rear_index) { // Copy
  // If source queue is empty, do not enter
  if (copy.front != nullptr) {
    front = &(m_buffer[0]);         // Front pointer to first element in buffer
    rear = &(m_buffer[m_size - 1]); // Rear pointer to last element in buffer
  }
}
template <typename T>
Queue<T>::Queue(Queue &&move) noexcept
    : m_buffer(move.m_buffer), front(move.front), rear(move.rear),
      m_size(move.m_size), front_index(move.front_index),
      rear_index(move.rear_index) { // Move
  m_buffer.setLength(10);
  move.m_buffer.m_array = nullptr;
  move.m_buffer.m_start_index = 0;
  move.m_buffer.m_length = 0;
  move.m_size = 0;
  move.front_index = 0;
  move.rear_index = 0;
  move.front = nullptr;
  move.rear = nullptr;
}
// Deconstructor
template <typename T> Queue<T>::~Queue() {
  front = nullptr;
  rear = nullptr;
}

// Overloaded Operators
template <typename T> Queue<T> &Queue<T>::operator=(const Queue &copy) { // Copy
  m_buffer = copy.m_buffer;
  m_size = copy.m_size;
  front_index = copy.front_index;
  rear_index = copy.rear_index;
  front = nullptr;
  rear = nullptr;

  if (copy.front != nullptr) {
    front = &(m_buffer[0]); // Front pointer to first element in buffer
    rear = &(m_buffer[m_buffer.m_length -
                      1]); // Rear pointer to last element in buffer
  }

  return *this;
}
template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&move) noexcept { // Move
  m_buffer = move.m_buffer;
  m_size = move.m_size;
  front = move.front;
  rear = move.rear;
  front_index = move.front_index;
  rear_index = move.rear_index;
  move.m_buffer.m_array = nullptr;
  move.m_buffer.m_start_index = 0;
  move.m_buffer.m_length = 0;
  move.m_size = 0;
  move.front = nullptr;
  move.rear = nullptr;

  return *this;
}

// Queue Operations
template <typename T> void Queue<T>::Enqueue(const T data) { // Add to rear
  // Queue is full
  if (m_size == m_buffer.getLength()) {
    throw throwOverflow();
    return;
  }
  m_size++;
  // Queue is empty
  if (front == nullptr) {
    front = &m_buffer[0];
    rear = &m_buffer[0];
    *front = data;
  }
  // Else (not empty or full)
  else {
    rear_index = ((rear_index + 1) % m_buffer.m_length);
    rear = m_buffer.m_array + rear_index;

    *rear = data;
  }
}
template <typename T> T Queue<T>::Dequeue() { // Remove & return from front
  // Queue is empty
  if (front == nullptr) {
    throw throwUnderflow();
    return {};
  }
  T temp = *front;
  // Queue has one element
  if (front == rear) {
    front = nullptr;
    rear = nullptr;
    front_index = 0;
    rear_index = 0;
    m_size--;
    return temp;
  }
  // Else (not empty, num elements > 1)
  else {
    *front = {};
    front_index = ((front_index + 1) % m_buffer.m_length);
    front = m_buffer.m_array + front_index;

    m_size--;
    return temp;
  }
}
template <typename T> T Queue<T>::Peek() { // Return from front
  return *front;
}
template <typename T> int Queue<T>::getSize() const { // Return m_size
  return m_size;
}
template <typename T>
bool Queue<T>::isEmpty() const { // Bool if queue is empty or not
  return (front == nullptr);
}
template <typename T>
bool Queue<T>::isFull() const { // Bool if queue is full or not
  return (m_size == 10);
}
template <typename T> void Queue<T>::Print() const { // Print queue to console
  T *temp = front;
  int temp_index = front_index;
  for (int i{}; i < m_size; i++) {
    std::cout << *temp << " ";
    temp_index = ((temp_index + 1) % m_buffer.m_length);
    temp = m_buffer.m_array + temp_index;
  }
}

// Throw Overflow/Underflow
template <typename T>
Exception Queue<T>::throwUnderflow() { // If enqueue when queue is full
  Exception e("ERROR: Underflow");
  return e;
}
template <typename T>
Exception Queue<T>::throwOverflow() { // If dequeue when queue is empty
  Exception e("ERROR: Overflow");
  return e;
}
