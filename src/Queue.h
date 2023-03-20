#pragma once
#include "Array.h"
#include "Exception.h"

template <typename T> class Queue {
private:
  Array<T> m_buffer; // Buffer holds 10 elements, starting index is 0
  int m_size{};
  T *front{};
  int front_index{};
  T *rear{};
  int rear_index{};

public:
  // Constructors
  Queue();                      // Default
  Queue(const Queue &copy);     // Copy
  Queue(Queue &&move) noexcept; // Move
  // Deconstructor
  ~Queue();

  // Overloaded Operators
  Queue &operator=(const Queue &copy);     // Copy
  Queue &operator=(Queue &&move) noexcept; // Move

  // Queue Operations
  void Enqueue(const T data); // Add to rear
  T Dequeue();                // Remove & return from front
  T Peek();                   // Return from font
  int getSize() const;        // Return m_size
  bool isEmpty() const;       // Bool if queue is empty or not
  bool isFull() const;        // Bool if queue is full or not
  void Print() const;         // Print queue to console

  // Throw Overflow/Underflow
  Exception throwUnderflow(); // If enqueue when queue is full
  Exception throwOverflow();  // If dequeue when queue is empty
  friend int main();
};
