#pragma once
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "Exception.h"

using std::list;
using std::pair;
using std::string;
using std::vector;

template <typename K, typename V> class veclistpair {
private:
  vector<list<pair<K, V>>> vlp{};
  int v_size{};

public:
  veclistpair(int size) : v_size{size} { vlp.resize(v_size); }

  veclistpair(const veclistpair &copy) : v_size{copy.v_size} {
    vlp.resize(v_size);
    for (int i{}; i < v_size; i++) {
      auto it = copy.vlp[i].begin();

      while (it != copy.vlp[i].end()) {
        vlp[i].emplace_back(*it);
        ++it;
      }
    }
  }

  veclistpair(veclistpair &&move) : v_size{move.v_size} {
    vlp.resize(v_size);
    for (int i{}; i < v_size; i++) {
      auto it = move.vlp[i].begin();

      while (it != move.vlp[i].end()) {
        vlp[i].emplace_back(*it);
        ++it;
      }
    }

    move.purge();
  }

  veclistpair &operator=(const veclistpair &copy) {
    v_size = copy.v_size;
    for (int i{}; i < v_size; i++) {
      auto it = copy.vlp[i].begin();

      while (it != copy.vlp[i].end()) {
        vlp[i].emplace_back(*it);
        ++it;
      }
    }

    return *this;
  }

  veclistpair &operator=(veclistpair &&move) {
    v_size = move.v_size;
    for (int i{}; i < v_size; i++) {
      auto it = move.vlp[i].begin();

      while (it != move.vlp[i].end()) {
        vlp[i].emplace_back(*it);
        ++it;
      }
    }

    move.purge();

    return *this;
  }

  bool operator==(const veclistpair &compare) {
    if (v_size != compare.v_size)
      return false;

    for (int i{}; i < size(); i++) {
      auto it = vlp[i].begin();
      auto it_cmp = compare.vlp[i].begin();

      while (it != vlp[i].end()) {
        if (it->first != it_cmp->first || it->second != it_cmp->second)
          return false;
        ++it;
      }
    }

    return true;
  }

  bool operator!=(const veclistpair &compare) {
    if (*this == compare)
      return false;

    return true;
  }

  list<pair<K, V>> &operator[](int index) { return vlp[index]; }

  int size() { return v_size; };

  void resize(int size) {
    v_size = size;
    vlp.resize(size);
  }

  void addpair(K key, V val, int index) {
    pair<K, V> temp(key, val);
    vlp[index].emplace_back(temp);
  }

  void removepair(string key) {
    for (int i{}; i < v_size; i++) {
      auto it = vlp[i].begin();

      while (it != vlp[i].end()) {
        if (it->first == key) {
          vlp[i].erase(it);
          return;
        }
        ++it;
      }
    }
  }

  int purge() {
    for (int i{}; i < v_size; i++) {

      while (!vlp[i].empty()) {
        vlp[i].pop_back();
      }
    }
    int temp = v_size;
    v_size = 0;
    return temp;
  }

  void print() {
    // print out all values of vlp
    // one list at a time, from front
    // of list to back
    for (int i{}; i < v_size; i++) {
      std::cout << "list " << i << ": ";

      auto it = vlp[i].begin();
      while (it != vlp[i].end()) {
        std::cout << "{" << it->first << ", " << it->second << "}, ";
        ++it;
      }

      std::cout << std::endl;
    }
  }

  pair<K, V> getpair(string key) {
    for (int i{}; i < v_size; i++) {
      auto it = vlp[i].begin();

      while (it != vlp[i].end()) {
        if (it->first == key) {
          return *it;
        }
        ++it;
      }
    }

    Exception e("ERROR: key does not exist");
    throw e;
    return {};
  }

  vector<pair<K, V>> getpairs() {
    vector<pair<K, V>> temp;

    for (int i{}; i < v_size; i++) {
      auto it = vlp[i].begin();

      while (it != vlp[i].end()) {
        temp.emplace_back(*it);
        ++it;
      }
    }

    return temp;
  }
};
