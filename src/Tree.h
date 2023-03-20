// Add documentation...

#pragma once
/*#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H*/

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::move;

#include <algorithm>
#include <vector>

#include "Exception.h"
#include "TreeNode.h"

template <typename T> class Tree {
private:
  TreeNode<T> *t_root{};

public:
  Tree();
  Tree(const T data);
  Tree(const Tree &copy);
  Tree(Tree &&move) noexcept;
  ~Tree();

  Tree &operator=(const Tree &copy);
  Tree &operator=(Tree &&move) noexcept;

  void Insert(const T data, TreeNode<T> *tree_search);
  void Delete(const T data, TreeNode<T> *tree_search,
              TreeNode<T> *parent = nullptr);
  int Height(TreeNode<T> *tree_search);
  void Purge() noexcept;
  void InOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search);
  void PreOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search);
  void PostOrderTraverse(void (*visit)(T), TreeNode<T> *tree_search);
  // BreadthFirstTraverse return a vector of all tree nodes in BFT order (get
  // all nodes)
  std::vector<T> BreadthFirstTraverse(void (*visit)(T),
                                      TreeNode<T> *tree_search);
  void BreadthRecursion(std::vector<T> &BFT, std::vector<TreeNode<T> *> &queue,
                        TreeNode<T> *tree_search);

  TreeNode<T> *getRoot() { return t_root; };
};

/*#endif // LIST_TEMPLATE_H*/
