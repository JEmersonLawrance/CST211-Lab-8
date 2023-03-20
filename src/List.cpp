#include "List.h"

// Default Constructor
template <typename T>
List<T>::List() : l_head(nullptr), l_tail(nullptr), l_count(0) {}
// Paramaterized Constructor
template <typename T> List<T>::List(const T data) : l_count(1) {
  ListNode<T> *newListNode = new ListNode<T>(data);
  l_head = newListNode;
  l_tail = newListNode;
}
// Copy Constructor
template <typename T> List<T>::List(const List &copy) : l_count(copy.l_count) {
  // Copy list is empty
  if (copy.l_head == nullptr) {
    l_head = nullptr;
    l_tail = nullptr;
  }
  // Copy list has 1 node
  else if (copy.l_head->next_ptr == nullptr) {
    ListNode<T> *newListNode = new ListNode<T>(copy.l_head->n_data);
    l_head = newListNode;
    l_tail = newListNode;
  }
  // Copy list has more than 1 node
  else {
    ListNode<T> *traverse = copy.l_head;
    ListNode<T> *newHead = new ListNode<T>(traverse->n_data);
    l_head = newHead;
    l_tail = newHead;
    traverse = traverse->next_ptr;
    while (traverse != nullptr) {
      ListNode<T> *newListNode = new ListNode<T>(traverse->n_data);
      newListNode->Previous(l_tail);
      l_tail->next_ptr = newListNode;
      traverse = traverse->next_ptr;
      l_tail = l_tail->next_ptr;
    }
  }
}
// Move Constructor
template <typename T>
List<T>::List(List &&move) noexcept : l_count(move.l_count) {
  if (move.l_head->next_ptr == nullptr) {
    l_head = move.l_head;
    l_tail = move.l_tail;
  }

  move.l_head = nullptr;
  move.l_tail = nullptr;
  delete l_head;
  delete l_tail;
}
// Deconstructor
template <typename T> List<T>::~List() {
  ListNode<T> *current = l_head;
  ListNode<T> *prev = l_head;
  while (prev != nullptr) {
    current = current->next_ptr;
    delete prev;
    prev = current;
  }
}
// Copy Assignment Operator
template <typename T> List<T> &List<T>::operator=(const List &copy) {
  l_count = copy.l_count;
  // Copy list is empty
  if (copy.l_head == nullptr) {
    l_head = nullptr;
    l_tail = nullptr;
  }
  // Copy list has 1 node
  else if (copy.l_head->next_ptr == nullptr) {
    ListNode<T> *newListNode = new ListNode<T>(copy.l_head->n_data);
    l_head = newListNode;
    l_tail = newListNode;
  }
  // Copy list has more than 1 node
  else {
    ListNode<T> *traverse = copy.l_head;
    ListNode<T> *newHead = new ListNode<T>(traverse->n_data);
    l_head = newHead;
    l_tail = newHead;
    traverse = traverse->next_ptr;
    while (traverse != nullptr) {
      ListNode<T> *newListNode = new ListNode<T>(traverse->n_data);
      newListNode->Previous(l_tail);
      l_tail->next_ptr = newListNode;
      traverse = traverse->next_ptr;
      l_tail = l_tail->next_ptr;
    }
  }

  return *this;
}
// Move Assignment Operator
template <typename T> List<T> &List<T>::operator=(List &&move) noexcept {
  l_count = move.l_count;
  l_head = move.l_head;
  l_tail = move.l_tail;

  move.l_tail = nullptr;
  move.l_head = nullptr;

  return *this;
}
// Conversion Operator (Boolean), True if list is empty, otherwise False
template <typename T> List<T>::operator bool() const {
  if (l_head == nullptr)
    return true;

  return false;
}
// Put T data at the end of the list
template <typename T> void List<T>::Append(const T data) {
  // If list is empty
  if (l_head == nullptr) {
    ListNode<T> *newListNode = new ListNode<T>(data);
    l_head = newListNode;
    l_tail = newListNode;
  }
  // If list is not empty
  else {
    ListNode<T> *newListNode = new ListNode<T>(data);
    newListNode->prev_ptr = l_tail;
    l_tail->next_ptr = newListNode;
    l_tail = newListNode;
  }
  l_count++;
}
// Put T data at the beginning of the list
template <typename T> void List<T>::Prepend(const T data) {
  // If list is empty
  if (l_head == nullptr) {
    ListNode<T> *newListNode = new ListNode<T>(data);
    l_head = newListNode;
    l_tail = newListNode;
  }
  // If list is not empty
  else {
    ListNode<T> *newListNode = new ListNode<T>(data);
    newListNode->next_ptr = l_head;
    l_head->prev_ptr = newListNode;
    l_head = newListNode;
  }
}
// Remove the last node of the list
template <typename T> void List<T>::RemoveLast() {
  if (l_tail->prev_ptr != nullptr) {
    l_tail = l_tail->prev_ptr;
    delete l_tail->next_ptr;
    l_tail->next_ptr = nullptr;
  } else {
    delete l_tail;
    l_tail = nullptr;
    l_head = nullptr;
  }
}
// Remove the first node of the list
template <typename T> void List<T>::RemoveFirst() {
  if (l_head->next_ptr != nullptr) {
    l_head = l_head->next_ptr;
    delete l_head->prev_ptr;
    l_head->prev_ptr = nullptr;
  } else {
    delete l_head;
    l_tail = nullptr;
    l_head = nullptr;
  }
}
// Remove the first node that equals T data while traversing list
template <typename T> void List<T>::Extract(const T data) {
  // If list is empty
  if (l_head == nullptr) {
    Exception e("list is empty");
    throw e;
    return;
  }
  // If l_head is data
  else if (l_head->n_data == data) {
    this->RemoveFirst();
    return;
  }
  // If l_tail is data
  else if (l_tail->n_data == data) {
    this->RemoveLast();
    return;
  }
  // If middle is data
  ListNode<T> *traverse = l_head;
  ListNode<T> *prev = l_head;

  while (traverse != nullptr) {
    traverse = traverse->next_ptr;
    if (prev->n_data == data) {
      prev = prev->prev_ptr;
      delete prev->next_ptr;
      prev->next_ptr = traverse;
      traverse->prev_ptr = prev;
      return;
    }
    prev = traverse;
  }

  // If no data
  Exception e("Data does not exist in list");
  throw e;
  return;
}

// Insert (T data) after first node that equals (T after)
template <typename T> void List<T>::InsertAfter(const T data, const T after) {
  // If list is empty
  if (l_head == nullptr) {
    Exception e("List is empty");
    throw e;
    return;
  }
  // If head is data
  if (l_head->n_data == after) {
    if (l_head->next_ptr == nullptr) {
      this->Append(data);
      return;
    }
    ListNode<T> *temp = l_head->next_ptr;
    ListNode<T> *newListNode = new ListNode<T>(data, temp, l_head);
    l_head->next_ptr = newListNode;
    temp->prev_ptr = newListNode;
  }

  // If tail is data
  if (l_tail->n_data == after) {
    this->Append(data);
  }

  // If data in middle
  ListNode<T> *traverse = l_head;

  while (traverse != nullptr) {
    if (traverse->n_data == after) {
      ListNode<T> *temp = traverse->next_ptr;
      ListNode<T> *newListNode = new ListNode<T>(data, temp, traverse);
      traverse->next_ptr = newListNode;
      temp->prev_ptr = newListNode;
      return;
    }
    traverse = traverse->next_ptr;
  }
  // If no data
  Exception e2("Data does not exist in list");
  throw e2;
  return;
}
// Insert (T data) before first node that equals (T before)
template <typename T> void List<T>::InsertBefore(const T data, const T before) {
  // If list is empty
  if (l_head == nullptr) {
    Exception e("List is empty");
    throw e;
    return;
  }
  // If tail is data
  if (l_tail->n_data == before) {
    if (l_head->next_ptr == nullptr) {
      this->Prepend(data);
      return;
    }
    ListNode<T> *temp = l_tail->prev_ptr;
    ListNode<T> *newListNode = new ListNode<T>(data, l_tail, temp);
    l_tail->prev_ptr = newListNode;
    temp->next_ptr = newListNode;
  }

  // If head is data
  if (l_head->n_data == before) {
    this->Prepend(data);
    return;
  }

  // If data in middle
  ListNode<T> *traverse = l_head;

  while (traverse != nullptr) {
    if (traverse->n_data == before) {
      ListNode<T> *temp = traverse->prev_ptr;
      ListNode<T> *newListNode = new ListNode<T>(data, traverse, temp);
      traverse->prev_ptr = newListNode;
      temp->next_ptr = newListNode;
      return;
    }
    traverse = traverse->next_ptr;
  }
  // If no data
  Exception e2("Data does not exist in list");
  throw e2;
  return;
}
// Delete all of the nodes in the list
template <typename T> void List<T>::Purge() noexcept {
  ListNode<T> *current = l_head;
  ListNode<T> *prev = l_head;
  while (prev != nullptr) {
    current = current->next_ptr;
    delete prev;
    prev = current;
  }

  l_head = nullptr;
  l_tail = nullptr;
}
// Return the address of the last element
template <typename T> T &List<T>::Last() {
  if (l_tail == nullptr) {
    Exception e("l_tail was nullptr");
    throw e;
  }

  return l_tail->n_data;
}
// Return the value of the last element
template <typename T> T List<T>::Last() const {
  if (l_tail == nullptr) {
    Exception e("l_tail was nullptr");
    throw e;
  }

  return l_tail->n_data;
}
// Return the address of the first element
template <typename T> T &List<T>::First() {
  if (l_tail == nullptr) {
    Exception e("l_tail was nullptr");
    throw e;
  }

  return l_head->n_data;
}
// Return the value of the first element
template <typename T> T List<T>::First() const {
  if (l_tail == nullptr) {
    Exception e("l_tail was nullptr");
    throw e;
  }

  return l_head->n_data;
}
// Return the pointer to the head of the list
template <typename T> ListNode<T> *List<T>::getHead() { return l_head; }
// Return the pointer to the tail of the list
template <typename T> ListNode<T> *List<T>::getTail() { return l_tail; }
// True if list is empty, otherwise F
template <typename T> bool List<T>::isEmpty() const noexcept {
  if (l_head == nullptr)
    return true;

  return false;
}
// Return the size of the list
template <typename T> size_t List<T>::Size() const noexcept { return l_count; }
// Compare if two lists are equal
template <typename T>
bool List<T>::operator==(const List<T> &rhs) const noexcept {
  ListNode<T> *traverse1 = l_head;
  ListNode<T> *traverse2 = rhs.l_head;

  while (traverse1->next_ptr != nullptr && traverse2->next_ptr != nullptr) {
    if (traverse1->n_data != traverse2->n_data)
      return false;
  }

  return true;
}
