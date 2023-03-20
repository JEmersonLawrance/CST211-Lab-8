// Add documentation...

#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> class ListNode {
private:
  T n_data;
  ListNode<T> *next_ptr;
  ListNode<T> *prev_ptr;

  template <typename U> friend class List;
  template <typename U> friend class Tree;

public:
  ListNode();
  ListNode(const ListNode &copy);
  ListNode(ListNode &&move) noexcept;
  ListNode(const T data);
  ListNode(const T data, ListNode<T> *next,
           ListNode<T> *prev); // 2nd Paramaterized constructor. Make sure next
                               // and prev are adjacent
  ~ListNode() = default;

  ListNode<T> &operator=(const ListNode &copy);
  ListNode<T> &operator=(ListNode &&move) noexcept;

  T &Value() noexcept;      // Returns address of the data value
  T Value() const noexcept; // Returns the data value
  void Value(const T data); // Sets the data value

  ListNode<T> *Next() noexcept;                        // Doesn't return a const
  ListNode<T> *Next() const noexcept;                  // Returns a const
  ListNode<T> *Previous() noexcept;                    // Doesn't return a const
  ListNode<T> *Previous() const noexcept;              // Returns a const
  void Next(ListNode<T> *const next) noexcept;         // Next ptr setter
  void Previous(ListNode<T> *const previous) noexcept; // Previous ptr setter
};

// Default Constructor
template <typename T>
ListNode<T>::ListNode() : n_data(0), next_ptr(nullptr), prev_ptr(nullptr) {}
// Paramaterized Constructor #1
template <typename T>
ListNode<T>::ListNode(const T data)
    : n_data(data), next_ptr(nullptr), prev_ptr(nullptr) {}
// Copy Constructor
template <typename T>
ListNode<T>::ListNode(const ListNode &copy)
    : n_data(copy.n_data), next_ptr(nullptr), prev_ptr(nullptr) {}
// Move Constructor
template <typename T>
ListNode<T>::ListNode(ListNode &&move) noexcept
    : n_data(move.n_data), next_ptr(nullptr), prev_ptr(nullptr) {
  move.n_data(0);
  move->next_ptr(nullptr);
  move->prev_ptr(nullptr);

  delete next_ptr;
  delete prev_ptr;
}
// Paramaterized Constructor #2
template <typename T>
ListNode<T>::ListNode(const T data, ListNode<T> *next, ListNode<T> *prev)
    : n_data(data), next_ptr(next), prev_ptr(prev) {}
// Copy Assignment Operator
template <typename T>
ListNode<T> &ListNode<T>::operator=(const ListNode &copy) {
  n_data = copy.n_data;
  next_ptr(nullptr);
  prev_ptr(nullptr);

  return *this;
}
// Move Assignment Operator
template <typename T>
ListNode<T> &ListNode<T>::operator=(ListNode &&move) noexcept {
  n_data = move.n_data;
  next_ptr = nullptr;
  prev_ptr = nullptr;

  move.n_data = 0;
  move->next_ptr = nullptr;
  move->prev_ptr = nullptr;

  return *this;
}
// Get Address of Value
template <class T> T &ListNode<T>::Value() noexcept { return n_data; }
// Get Value
template <class T> T ListNode<T>::Value() const noexcept { return n_data; }
// Set Value
template <class T> void ListNode<T>::Value(const T data) { n_data = data; }
// Next Pointer Getter, doesn't return const
template <typename T> ListNode<T> *ListNode<T>::Next() noexcept {
  return next_ptr;
}
// Next Pointer Getter, returns const
template <typename T> ListNode<T> *ListNode<T>::Next() const noexcept {
  return next_ptr;
}
// Previous Pointer Getter, doesn't return const
template <typename T> ListNode<T> *ListNode<T>::Previous() noexcept {
  return prev_ptr;
}
// Next Pointer Getter, returns const
template <typename T> ListNode<T> *ListNode<T>::Previous() const noexcept {
  return prev_ptr;
}
// Set Next Pointer
template <typename T> void ListNode<T>::Next(ListNode<T> *const next) noexcept {
  next_ptr = next;
}
// Set Previous Pointer
template <typename T>
void ListNode<T>::Previous(ListNode<T> *const previous) noexcept {
  prev_ptr = previous;
}

#endif // NODE_TEMPLATE_H
