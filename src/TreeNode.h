// Add documentation...

#pragma once
/*
#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H*/

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> class TreeNode {
private:
  T n_data;
  TreeNode<T> *left_ptr;
  TreeNode<T> *right_ptr;

  template <typename U> friend class Tree;

public:
  TreeNode();
  TreeNode(const TreeNode &copy);
  TreeNode(TreeNode &&move) noexcept;
  TreeNode(const T data);
  TreeNode(const T data, TreeNode<T> *left_ptr,
           TreeNode<T> *right_ptr); // 2nd Paramaterized constructor. Make sure
                                    // next and prev are adjacent
  ~TreeNode() = default;

  TreeNode<T> &operator=(const TreeNode &copy);
  TreeNode<T> &operator=(TreeNode &&move) noexcept;

  T &Value() noexcept;      // Returns address of the data value
  T Value() const noexcept; // Returns the data value
  void Value(const T data); // Sets the data value

  TreeNode<T> *Left() noexcept;                  // Doesn't return a const
  TreeNode<T> *Left() const noexcept;            // Returns a const
  TreeNode<T> *Right() noexcept;                 // Doesn't return a const
  TreeNode<T> *Right() const noexcept;           // Returns a const
  void Left(TreeNode<T> *const left) noexcept;   // Next ptr setter
  void Right(TreeNode<T> *const right) noexcept; // Previous ptr setter
};

// Default Constructor
template <typename T>
TreeNode<T>::TreeNode() : n_data(0), left_ptr(nullptr), right_ptr(nullptr) {}
// Paramaterized Constructor #1
template <typename T>
TreeNode<T>::TreeNode(const T data)
    : n_data(data), left_ptr(nullptr), right_ptr(nullptr) {}
// Copy Constructor
template <typename T>
TreeNode<T>::TreeNode(const TreeNode &copy)
    : n_data(copy.n_data), left_ptr(nullptr), right_ptr(nullptr) {}
// Move Constructor
template <typename T>
TreeNode<T>::TreeNode(TreeNode &&move) noexcept
    : n_data(move.n_data), left_ptr(nullptr), right_ptr(nullptr) {
  move.n_data(0);
  move->left_ptr(nullptr);
  move->right_ptr(nullptr);

  delete left_ptr;
  delete right_ptr;
}
// Paramaterized Constructor #2
template <typename T>
TreeNode<T>::TreeNode(const T data, TreeNode<T> *left, TreeNode<T> *right)
    : n_data(data), left_ptr(left), right_ptr(right) {}
// Copy Assignment Operator
template <typename T>
TreeNode<T> &TreeNode<T>::operator=(const TreeNode &copy) {
  n_data = copy.n_data;
  left_ptr(nullptr);
  right_ptr(nullptr);

  return *this;
}
// Move Assignment Operator
template <typename T>
TreeNode<T> &TreeNode<T>::operator=(TreeNode &&move) noexcept {
  n_data = move.n_data;
  left_ptr = nullptr;
  right_ptr = nullptr;

  move.n_data = 0;
  move->left_ptr = nullptr;
  move->right_ptr = nullptr;

  return *this;
}
// Get Address of Value
template <class T> T &TreeNode<T>::Value() noexcept { return n_data; }
// Get Value
template <class T> T TreeNode<T>::Value() const noexcept { return n_data; }
// Set Value
template <class T> void TreeNode<T>::Value(const T data) { n_data = data; }
// Next Pointer Getter, doesn't return const
template <typename T> TreeNode<T> *TreeNode<T>::Left() noexcept {
  return left_ptr;
}
// Next Pointer Getter, returns const
template <typename T> TreeNode<T> *TreeNode<T>::Left() const noexcept {
  return left_ptr;
}
// Previous Pointer Getter, doesn't return const
template <typename T> TreeNode<T> *TreeNode<T>::Right() noexcept {
  return right_ptr;
}
// Next Pointer Getter, returns const
template <typename T> TreeNode<T> *TreeNode<T>::Right() const noexcept {
  return right_ptr;
}
// Set Next Pointer
template <typename T> void TreeNode<T>::Left(TreeNode<T> *const left) noexcept {
  left_ptr = left;
}
// Set Previous Pointer
template <typename T>
void TreeNode<T>::Right(TreeNode<T> *const right) noexcept {
  right_ptr = right;
}

/*#endif // NODE_TEMPLATE_H*/
