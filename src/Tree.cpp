#include "Tree.h"

// Default Constructor
template <typename T> Tree<T>::Tree() {}
// Paramaterized Constructor
template <typename T> Tree<T>::Tree(const T data) { Insert(data, t_root); }
// Copy Constructor
template <typename T> Tree<T>::Tree(const Tree &copy) {
  std::vector<T> list = BreadthFirstTraverse(nullptr, copy.t_root);

  // Fill up tree in same order as source tree
  if (!list.empty()) {
    for (auto data : list)
      Insert(data, t_root);
  }
}
// Move Constructor
template <typename T>
Tree<T>::Tree(Tree &&move) noexcept : t_root(move.t_root) {
  move.t_root = nullptr;
}
// Deconstructor
template <typename T> Tree<T>::~Tree() { Purge(); }
// Copy Assignment Operator
template <typename T> Tree<T> &Tree<T>::operator=(const Tree &copy) {
  std::vector<T> list = BreadthFirstTraverse(nullptr, copy.t_root);

  // Fill up tree in same order as source tree
  if (!list.empty()) {
    for (auto data : list)
      Insert(data, t_root);
  }

  return *this;
}
// Move Assignment Operator
template <typename T> Tree<T> &Tree<T>::operator=(Tree &&move) noexcept {
  t_root = move.t_root;
  move.t_root = nullptr;

  return *this;
}
// Insert data into tree
template <typename T>
void Tree<T>::Insert(const T data, TreeNode<T> *tree_search) {

  // If tree is empty (doesn't enter recursion)
  if (tree_search == nullptr) {
    TreeNode<T> *newTreeNode = new TreeNode<T>(data); // Make new node with data
    t_root = newTreeNode; // Set tree root to new node
    return;
  }
  // If tree has one node (base case)
  if (tree_search->left_ptr == nullptr && tree_search->right_ptr == nullptr) {
    TreeNode<T> *newTreeNode = new TreeNode<T>(data); // Make new node with data

    if (data > tree_search->n_data)
      tree_search->right_ptr = newTreeNode;
    else
      tree_search->left_ptr = newTreeNode;

    return;
  }
  // If tree has only left subtree
  else if (tree_search->left_ptr != nullptr &&
           tree_search->right_ptr == nullptr) {

    if (data > tree_search->n_data) { // base case
      TreeNode<T> *newTreeNode = new TreeNode<T>(data);
      tree_search->right_ptr = newTreeNode;
    } else
      Insert(data, tree_search->left_ptr); // Continue search on the left
                                           // subtree
  }
  // If tree has only right subtree
  else if (tree_search->left_ptr == nullptr &&
           tree_search->right_ptr != nullptr) {

    if (data > tree_search->n_data)
      Insert(data,
             tree_search->right_ptr); // Continue search on the right subtree
    else {                            // base case
      TreeNode<T> *newTreeNode = new TreeNode<T>(data);
      tree_search->left_ptr = newTreeNode;
    }
  }
  // If tree has two subtrees
  else {
    if (data > tree_search->n_data)
      Insert(data,
             tree_search->right_ptr); // Continue search on the right subtree
    else
      Insert(data, tree_search->left_ptr); // Continue search on the left
                                           // subtree
  }

  return;
}
// Remove data from tree
template <typename T>
void Tree<T>::Delete(const T data, TreeNode<T> *tree_search,
                     TreeNode<T> *parent) {
  // If tree is empty
  if (tree_search == nullptr) {

    return;
  }
  // Find Element
  if (data > tree_search->n_data) {
    Delete(data, tree_search->right_ptr, tree_search);
  } else if (data < tree_search->n_data) {
    Delete(data, tree_search->left_ptr, tree_search);
  } else {
    // Element found, now Remove Element
    // If leaf node
    if (tree_search->left_ptr == nullptr && tree_search->right_ptr == nullptr) {
      if (parent == nullptr)
        parent = tree_search;

      if (parent->left_ptr == tree_search)
        parent->left_ptr = nullptr;
      else
        parent->right_ptr = nullptr;

      if (tree_search == t_root)
        t_root = nullptr;
      delete tree_search;
    }
    // If only left subtree
    else if (tree_search->left_ptr != nullptr &&
             tree_search->right_ptr == nullptr) {
      if (parent == nullptr)
        parent = tree_search;

      if (parent->left_ptr == tree_search)
        parent->left_ptr = tree_search->left_ptr;
      else if (parent->right_ptr == tree_search)
        parent->right_ptr = tree_search->left_ptr;
      else {
        t_root = tree_search->left_ptr;
      }

      delete tree_search;
    }
    // If only right subtree
    else if (tree_search->left_ptr == nullptr &&
             tree_search->right_ptr != nullptr) {
      if (parent == nullptr)
        parent = tree_search;

      if (parent->left_ptr == tree_search)
        parent->left_ptr = tree_search->right_ptr;
      else if (parent->right_ptr == tree_search)
        parent->right_ptr = tree_search->right_ptr;
      else {
        t_root = tree_search->left_ptr;
      }

      delete tree_search;
    }
    // If both subtrees
    else {
      // Point to root
      TreeNode<T> *temp = tree_search;
      parent = tree_search;

      // Go to leftmost node of right subtree
      tree_search = tree_search->right_ptr;
      while (tree_search->left_ptr != nullptr) {
        parent = tree_search;
        tree_search = tree_search->left_ptr;
      }

      // Copy data from leftmost node of right subtree into root
      temp->n_data = tree_search->n_data;

      // Delete leftmost node of right subtree
      Delete(tree_search->n_data, tree_search, parent);

      temp = nullptr;
    }
    tree_search = nullptr;
  }
}
// Returns height
template <typename T> int Tree<T>::Height(TreeNode<T> *tree_search) {
  if (tree_search == nullptr) {
    return -1;
  }

  int heightl = Height(tree_search->left_ptr);
  int heightr = Height(tree_search->right_ptr);

  if (heightl > heightr)
    return heightl + 1;
  else
    return heightr + 1;
}
// Delete all of the nodes in the list
template <typename T> void Tree<T>::Purge() noexcept {
  std::vector<T> list = BreadthFirstTraverse(nullptr, t_root);
  std::reverse(list.begin(), list.end());

  for (T val : list) {
    Delete(val, t_root);
  }
}
// InOrder Traversal-- Visit left subtree, visit root, visit right subtree
template <typename T>
void Tree<T>::InOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search) {
  if (tree_search == nullptr)
    return;

  InOrderTraverse(visit, tree_search->left_ptr);
  visit(tree_search->n_data);
  InOrderTraverse(visit, tree_search->right_ptr);
}
// PreOrder Traversal-- Visit root, visit left subtree, visit right subtree
template <typename T>
void Tree<T>::PreOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search) {
  if (tree_search == nullptr)
    return;

  visit(tree_search->n_data);
  PreOrderTraverse(visit, tree_search->left_ptr);
  PreOrderTraverse(visit, tree_search->right_ptr);
}
// PostOrder Traversal-- Visit left subtree, visit right subtree, visit root
template <typename T>
void Tree<T>::PostOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search) {
  if (tree_search == nullptr)
    return;

  PostOrderTraverse(visit, tree_search->left_ptr);
  PostOrderTraverse(visit, tree_search->right_ptr);
  visit(tree_search->n_data);
}
// Breadth-First Traversal-- Visit all nodes in level before proceeding to next
// level
template <typename T>
std::vector<T> Tree<T>::BreadthFirstTraverse(void (*visit)(T),
                                             TreeNode<T> *tree_search) {
  std::vector<TreeNode<T> *> queue{tree_search};
  std::vector<T> BFT{};

  if (tree_search == nullptr)
    return BFT;

  BreadthRecursion(BFT, queue, tree_search);

  if (visit != nullptr) {
    for (T data : BFT)
      visit(data);
  }

  return BFT;
}

template <typename T>
void Tree<T>::BreadthRecursion(std::vector<T> &BFT,
                               std::vector<TreeNode<T> *> &queue,
                               TreeNode<T> *tree_search) {
  if (queue.empty()) { // (Base Case)
    return;
  }
  if (tree_search->left_ptr != nullptr) // If left child, add it to queue
    queue.push_back(tree_search->left_ptr);
  if (tree_search->right_ptr != nullptr) // If right child, add it to queue
    queue.push_back(tree_search->right_ptr);

  BFT.push_back(
      tree_search->n_data);   // Add root to the BreadthFirstTraverse array
  queue.erase(queue.begin()); // Remove root from queue

  if (!queue.empty())
    BreadthRecursion(BFT, queue, queue[0]); // Recursive call starts from the
                                            // next queued node (the new root)
}
