#pragma once
#include <list>
#include <utility>
#include <vector>

#include "vectorlistpair.h"

using std::list;
using std::pair;
using std::vector;

// Forward Declaration of Hash Function
template <typename K> int moduloHash(K key, int n);

template <typename K, typename V> class Hashmap {
private:
  veclistpair<K, V> hashnodes{(16)};         // Hashmap buffer
  int (*h_hashfunc)(K, int) = moduloHash<K>; // Hashing Algorithm
  int h_size{0}; // Number of elements in Hashmap (NOT size of  Hashnode buffer)

  bool atCapacity();

public:
  // Canonical Constructors
  Hashmap();
  Hashmap(K key, V val);
  Hashmap(const Hashmap &copy);
  Hashmap(Hashmap &&move) noexcept;

  // Operations
  Hashmap<K, V> &operator=(const Hashmap &copy);
  Hashmap<K, V> &operator=(Hashmap &&move);
  bool operator==(const Hashmap &compare);
  bool operator!=(const Hashmap &compare);
  V const &operator[](const K &key) const;
  V &operator[](const K &key); // Subscript with Key, return corresponding Val
  void Add(const K &key, const V &value);       // Add value to Val at Key
  void setHash(int (*hashfn)(K key, int size)); // Set the Hash Function, rehash
  void reHash();
  void Remove(const K &key);             // Remove Hashnode at Key
  void Traverse(void (*visit)(V value)); // Pass Val to visit for all hashnodes

  bool empty();
  void print();
  int getSize() { return h_size; }
};
