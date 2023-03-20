#include "Array.cpp"
#include "Hashmap.cpp"
#include "List.cpp"
#include "Queue.cpp"
#include "Tree.cpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std::chrono;

// Initialize timing variables

time_point<system_clock> start, end;
duration<double> diff{};

// Hash function supports int, char, string keys
template <typename K> int moduloHash(K key, int n) {
  struct overloads {
    int modulo(string key, int size) {
      int hashvalue{};

      for (char c : key) {
        hashvalue += (int)c;
      }
      return hashvalue % size;
    }

    int modulo(int key, int size) { return key % size; }

    int modulo(char key, int size) { return (int)key % size; }
  };

  overloads o;

  return (o.modulo(key, n));
}

// Compare Visit Function
template <typename T> void Compare(T data) {

  if (data == "unquenched.") {
    end = system_clock::now();
    diff = end - start;
    std::cout << "Search Complete -- found unquenched."
              << " in " << diff.count() << " seconds\n";
  }
}

void fill(std::vector<std::string> &vec) {
  std::ifstream myfile("../assets/frankenstein.txt");

  if (myfile.is_open()) {
    while (myfile) {
      std::string s;
      std::getline(myfile, s, ' ');
      vec.push_back(s);
    }
  } else {
    std::cout << "ERROR: file failed to open\n";
  }
}

int main() {

  // Fill vector words with each word of frankenstein.txt
  std::vector<std::string> words{};
  fill(words);

  // Fill Custom Array
  Array<std::string> a(words.size());
  int i{};
  start = system_clock::now();
  for (auto word : words) {
    a[i] = word;
    ++i;
  }
  end = system_clock::now();
  diff = end - start;

  std::cout << "Array Fill Complete -- inserted " << a.getLength()
            << " strings in " << diff.count() << " seconds\n";

  // Fill Custom Linked List
  List<std::string> l;
  start = system_clock::now();
  for (auto word : words) {
    l.Append(word);
  }
  end = system_clock::now();
  diff = end - start;

  std::cout << "List Fill Complete -- inserted " << l.Size() << " strings in "
            << diff.count() << " seconds\n";

  // Fill Custom Queue
  Queue<std::string> q;
  start = system_clock::now();
  for (auto word : words) {
    q.Enqueue(word);
  }
  end = system_clock::now();
  diff = end - start;

  std::cout << "Queue Fill Complete -- inserted " << q.getSize()
            << " strings in " << diff.count() << " seconds\n";

  // Fill BST
  Tree<std::string> t;
  start = system_clock::now();
  for (auto word : words) {
    t.Insert(word, t.getRoot());
  }
  end = system_clock::now();
  diff = end - start;

  std::cout << "Tree Fill Complete -- inserted "
            << (t.BreadthFirstTraverse(nullptr, t.getRoot())).size()
            << " strings in " << diff.count() << " seconds\n";

  i = 0;
  // Fill Hashmap
  Hashmap<std::string, std::string> h;
  start = system_clock::now();
  for (auto word : words) {
    h.Add("Key" + std::to_string(i), word);
    ++i;
  }

  end = system_clock::now();
  diff = end - start;

  std::cout << "Hashmap Fill Complete -- inserted " << h.getSize()
            << " strings in " << diff.count() << " seconds\n";

  std::cout << std::endl;

  std::string s_find{"unquenched."};
  // Search Custom Array
  start = system_clock::now();
  for (int i{}; i < a.getLength(); ++i) {
    if (a[i] == s_find) {
      end = system_clock::now();
      diff = end - start;
      std::cout << "Array Search Complete -- found " << s_find << " in "
                << diff.count() << " seconds\n";
      break;
    }
  }

  // Search Custom Linked List
  auto it = l.getHead();
  start = system_clock::now();
  for (auto word : words) {
    if (it->Value() == s_find) {
      end = system_clock::now();
      diff = end - start;
      std::cout << "List Search Complete -- found " << s_find << " in "
                << diff.count() << " seconds\n";
      break;
    }
    if (it->Next() != nullptr)
      it = it->Next();
    else
      break;
  }

  // Search Queue
  start = system_clock::now();
  for (auto word : words) {
    if (q.Peek() == s_find) {
      end = system_clock::now();
      diff = end - start;
      std::cout << "Queue Search Complete -- found " << s_find << " in "
                << diff.count() << " seconds\n";
      break;
    }

    q.Dequeue();
  }

  // Search BST
  start = system_clock::now();
  std::cout << "BST ";
  t.InOrderTraverse(Compare, t.getRoot());

  // Search Hashmap
  start = system_clock::now();
  std::cout << "Hashmap ";
  h.Traverse(Compare);
  return 0;
}
