// Add documentation...

#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::move;

#include "Exception.h"
#include "ListNode.h"

template <typename T> class List {
private:
  ListNode<T> *l_head; // Pointer to the head of the list
  ListNode<T> *l_tail; // Pointer to the tail of the list
  int l_count;         // Number of nodes in the list
public:
  List();
  List(const T data);
  List(const List &copy);
  List(List &&move) noexcept;
  ~List();

  List &operator=(const List &copy);
  List &operator=(List &&move) noexcept;
  explicit operator bool() const;

  void Append(const T data);
  void Prepend(const T data);
  void RemoveLast();
  void RemoveFirst();
  void Extract(const T data);
  void InsertAfter(const T data, const T after);
  void InsertBefore(const T data, const T before);
  void Purge() noexcept;

  T &Last();
  T Last() const;
  T &First();
  T First() const;

  ListNode<T> *getHead();
  ListNode<T> *getTail();
  bool isEmpty() const noexcept;
  size_t Size() const noexcept;
  bool operator==(const List<T> &rhs) const noexcept;
};
#endif // LIST_TEMPLATE_H
