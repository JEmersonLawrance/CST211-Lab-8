#pragma once
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#define LIST_SIZE 10

// merge
template <typename T> void merge(T arr[], int l, int m, int r) {
  int i{l}, j{m + 1}, k{l};
  T temp[LIST_SIZE];

  while (i <= m && j <= r) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      i++;
      k++;
    } else {
      temp[k] = arr[j];
      j++;
      k++;
    }
  }

  while (i <= m) {
    temp[k] = arr[i];
    i++;
    k++;
  }

  while (j <= r) {
    temp[k] = arr[j];
    j++;
    k++;
  }

  for (int p = l; p <= r; p++) {
    arr[p] = temp[p];
  }
}

// mergeSort
template <typename T> void mergeSort(T arr[], int l, int r) {
  if (l < r) {
    int m{(l + r) / 2};
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

// swap
template <typename T> void swap(T &a, T &b) {
  T temp{a};
  a = b;
  b = temp;
}

// partition
template <typename T> int partition(T arr[], int s, int e) {
  int pivot{arr[e]};
  int pIndex{s};

  for (int i{s}; i < (e - 1); ++i) {
    swap(arr[i], arr[pIndex]);
    pIndex++;
  }

  swap(arr[e], arr[pIndex]);
  return pIndex;
}
// quickSort
template <typename T> void quickSort(T arr[], int s, int e) {
  if (s < e) {
    int p{partition(arr, s, e)};
    quickSort(arr, s, p - 1);
    quickSort(arr, p + 1, e);
  }
}

// T is type of elements contained in list
template <typename T> class Sorts {
private:
  T *l_head; // this work?

public:
  // L is type of passed in list (vector, native array, custom array)
  template <typename L> Sorts(L &list); // Paramaterized Constructor

  void Print();                    // Print list
  T *getList() { return l_head; }; // Get List

  void BruteBubble();
  void FlagBubble();
  void Selection();
  void Insertion();
  void Shell();
  void Heap();  // iterative
  void Merge(); // recursive
  void Quick(); // recursive
};

template <typename T> template <typename L> Sorts<T>::Sorts(L &list) {
  l_head = &(list[0]);
}

template <typename T> void Sorts<T>::Print() {
  for (int i{}; i < LIST_SIZE; ++i) {
    std::cout << *(l_head + i) << " ";
  }
}

template <typename T> void Sorts<T>::BruteBubble() {
  for (int i{}; i < (LIST_SIZE - 1); ++i) {
    T *current{l_head};

    for (int j{}; j < (LIST_SIZE - i - 1); ++j) {
      if (*current > *(current + 1)) {
        T temp = *current;
        *current = *(current + 1);
        *(current + 1) = temp;
      }
      ++current;
    }
  }
}

template <typename T> void Sorts<T>::FlagBubble() {
  for (int i{}; i < (LIST_SIZE - 1); ++i) {
    T *current{l_head};

    for (int j{}, flag{};
         current + 1 < (l_head + (LIST_SIZE - i - 1)) || flag == 0; ++j) {
      if (*current > *(current + 1)) {
        T temp = *current;
        *current = *(current + 1);
        *(current + 1) = temp;
        flag = 1;
      }
      ++current;
    }
  }
}

template <typename T> void Sorts<T>::Selection() {
  for (int i{}; i < (LIST_SIZE - 1); ++i) {
    T *current{l_head + 1};
    T *largest{l_head};

    for (int j{}; current < (l_head + (LIST_SIZE - i - 1)); ++j) {
      if (*current > *largest) {
        largest = current;
      }
      ++current;
    }

    T temp{*current};
    *current = *largest;
    *largest = temp;
  }
}

template <typename T> void Sorts<T>::Insertion() {
  for (int sorted{1}; sorted < LIST_SIZE; ++sorted) {
    // Current at 1 element after sorted list
    // Sort Traverse at beginning of list
    T *current{l_head + sorted};
    T *sort_traverse{l_head};

    // Sort traverse travels up list until
    // Current is larger than a list element
    while (*current > *sort_traverse) {
      sort_traverse++;
    }

    // Shift unless current is greater than
    // sort_traverse
    if (*current <= *sort_traverse) {
      T *shift{sort_traverse};
      T left{*shift};
      T insert{*current};
      T right{*(shift + 1)};

      while (shift != current) {
        *(shift + 1) = left;
        left = right;
        ++shift;
        right = *(shift + 1);
      }
      *sort_traverse = insert;
    }
  }
}

template <typename T> void Sorts<T>::Shell() {
  int i{1};
  int gap{LIST_SIZE / 2};
  while (gap != 1) {
    gap = LIST_SIZE / (pow(2, i));
    ++i;

    for (int sorted{1}; sorted < (LIST_SIZE / gap); ++sorted) {
      // Current at 1 element after sorted list
      // Sort Traverse at beginning of list
      T *current{l_head + (gap * sorted)};
      T *sort_traverse{l_head};

      // Sort traverse travels up list until
      // Current is larger than a list element
      while (*current > *sort_traverse) {
        sort_traverse += gap;
      }
      // Shift unless current is greater than
      // sort_traverse
      if (*current <= *sort_traverse) {
        T *shift{sort_traverse};
        T left{*shift};
        T insert{*current};
        T right{*(shift + 1)};

        while (shift != current) {
          *(shift + 1) = left;
          left = right;
          ++shift;
          right = *(shift + 1);
        }
        *sort_traverse = insert;
      }
    }
  }
}

template <typename T> void Sorts<T>::Heap() {
  // Store unsorted list
  T *it{l_head};
  std::vector<T> unsorted{};
  while (it != l_head + LIST_SIZE) {
    unsorted.push_back(*it);
    ++it;
  }
  std::reverse(unsorted.begin(), unsorted.end());

  // Convert unsorted list to heap
  *l_head = unsorted.back();
  unsorted.pop_back();
  {
    int offset{1};
    while (offset < LIST_SIZE) {
      *(l_head + offset) = unsorted.back();
      unsorted.pop_back();
      // If inserted value > its parent,
      // Move it up in heap until heap
      // Property is satisfied
      int i{offset};
      while (*(l_head + i) > *(l_head + (i / 2)) && i != 0) {
        T swap{*(l_head + (i / 2))};
        *(l_head + (i / 2)) = *(l_head + i);
        *(l_head + i) = swap;
        i = i / 2;
      }
      ++offset;
    }
  }

  T *traverse = l_head;

  // Delete all nodes from heap, build sorted list
  // At opposite end of the list with deleted
  // Root values
  for (int size{LIST_SIZE}; size != 1;) {
    // Swap root node and last node
    T hold = *l_head;
    *l_head = *(l_head + (size - 1));
    *(l_head + (size - 1)) = hold;
    --size;

    /// Case: two items left unsorted
    if (size == 2) {
      if (*l_head > *(l_head + 1)) {
        T temp{*l_head};
        *l_head = *(l_head + 1);
        *(l_head + 1) = temp;
        return;
      } else {
        return;
      }
    }

    /// Case: more than two items left unsorted
    // Sort new root node down the list
    // So Heap Property is satisfied
    T *current{l_head + 0};
    T *l_child{l_head + 1};
    T *r_child{l_head + 2};

    int i{1};
    while (!(l_child >= (l_head + (size - 1)))) {

      if (l_child > (l_head + (size - 1))) {
        break;
      }
      if (r_child > (l_head + (size - 1))) {
        int i{-10000};
        r_child = &i;
      }
      // if neither left or right child > new val, or if both left and right
      // child == new val, break
      if (!(*l_child > *current || *r_child > *current) ||
          (*l_head == *current && *r_child == *current)) {
        break;
      }
      // if left child > right child
      else if (*l_child > *r_child || *l_child == *r_child) {
        T swap = *l_child;
        *l_child = *current;
        *current = swap;

        current = (current + i);
        i *= 2;
        l_child = (current + i);
        r_child = (current + i) + 1;
      }
      // if right child > left child
      else if (*r_child > *l_child) {
        T swap = *r_child;
        *r_child = *current;
        *current = swap;

        current = (current + i) + 1;
        i = (i * 2) + 1;
        l_child = (current + i);
        r_child = (current + i) + 1;
      }
    }
  }
}

template <typename T> void Sorts<T>::Merge() {
  mergeSort(l_head, 0, LIST_SIZE - 1);
}

template <typename T> void Sorts<T>::Quick() {
  quickSort(l_head, 0, LIST_SIZE - 1);
}
