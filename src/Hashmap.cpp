#include "Hashmap.h"

template <typename K, typename V> Hashmap<K, V>::Hashmap() {
  h_hashfunc = moduloHash;
}
template <typename K, typename V> Hashmap<K, V>::Hashmap(K key, V val) {
  Add(key, val);
  h_size++;
}
template <typename K, typename V>
Hashmap<K, V>::Hashmap(const Hashmap &copy)
    : hashnodes{copy.hashnodes}, h_size(copy.h_size), h_hashfunc(moduloHash) {}

template <typename K, typename V>
Hashmap<K, V>::Hashmap(Hashmap &&move) noexcept
    : hashnodes{std::move(move.hashnodes)}, h_size(move.h_size),
      h_hashfunc(moduloHash) {
  move.h_size = 0;
}

template <typename K, typename V>
Hashmap<K, V> &Hashmap<K, V>::operator=(const Hashmap &copy) {
  hashnodes = copy.hashnodes;

  return *this;
}
template <typename K, typename V>
Hashmap<K, V> &Hashmap<K, V>::operator=(Hashmap &&move) {
  hashnodes = std::move(move.hashnodes);

  move.h_size = 0;
  return *this;
}

template <typename K, typename V>
bool Hashmap<K, V>::operator==(const Hashmap &compare) {
  if (hashnodes == compare.hashnodes)
    return true;

  return false;
}

template <typename K, typename V>
bool Hashmap<K, V>::operator!=(const Hashmap &compare) {
  if (hashnodes != compare.hashnodes)
    return true;

  return false;
}

// Read & Write (Write not working)
template <typename K, typename V> V &Hashmap<K, V>::operator[](const K &key) {
  int index = h_hashfunc(key, hashnodes.size());

  if (hashnodes[index].empty()) {
    Exception e("ERROR: key does not exist in Hashmap");
    throw e;
  }

  auto it = hashnodes[index].begin();

  while (it != hashnodes[index].end()) {
    if (it->first == key) {
      return it->second;
    }
    std::cout << "Key: " << it->first << "\nValue: " << it->second << std::endl;
    ++it;
  }

  Exception e("ERROR: key does not exist in Hashmap");
  throw e;
}

template <typename K, typename V>
void Hashmap<K, V>::Add(const K &key, const V &value) {
  int index = h_hashfunc(key, hashnodes.size());

  hashnodes.addpair(key, value, index);
  h_size++;

  if (atCapacity())
    reHash();
}

template <typename K, typename V>
void Hashmap<K, V>::setHash(int (*hashfn)(K key, int size)) {
  h_hashfunc = hashfn;

  reHash();
}

template <typename K, typename V> bool Hashmap<K, V>::atCapacity() {
  // true if # of hashmap elements >= size of hashnode buffer
  float percent_full = ((float)h_size / (float)hashnodes.size());
  if (percent_full >= 0.75) {
    return true;
  }
  return false;
}

template <typename K, typename V> void Hashmap<K, V>::reHash() {
  vector<pair<K, V>> temp = hashnodes.getpairs();

  int prev_size = hashnodes.purge();

  hashnodes.resize(prev_size);

  float percent_full = ((float)h_size / (float)hashnodes.size());
  if (percent_full >= 0.75)
    hashnodes.resize(hashnodes.size() * 2);

  h_size = 0;
  for (int i{}; i < temp.size(); i++) {
    Add(temp[i].first, temp[i].second);
  }
}

template <typename K, typename V> void Hashmap<K, V>::Remove(const K &key) {
  hashnodes.removepair(key);
  h_size--;
}

template <typename K, typename V>
void Hashmap<K, V>::Traverse(void (*visit)(V value)) {
  vector<pair<K, V>> temp = hashnodes.getpairs();

  for (int i{}; i < temp.size(); i++) {
    visit(temp[i].second);
  }
}

template <typename K, typename V> bool Hashmap<K, V>::empty() {
  if (h_size == 0)
    return true;

  return false;
}

template <typename K, typename V> void Hashmap<K, V>::print() {
  hashnodes.print();
}
