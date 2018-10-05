/* Copyright [2018] <Alan Djon Lüdke>
 * binary_tree.h
 */

#include "array_list.h"

namespace structures {
//! class BinaryTree
template<typename T>
class BinaryTree {
 public:
  //! Destructor method
  ~BinaryTree();

  //! Puts an element in the tree
  void insert(const T& data);

  //! Takes an element off the tree
  void remove(const T& data);

  //! Returns if an specific element belongs to the tree
  bool contains(const T& data) const;

  //! Returns if empty
  bool empty() const;

  //! Returns the actual size
  std::size_t size() const;

  //! ..
  ArrayList<T> pre_order() const;

  //! ..
  ArrayList<T> in_order() const;

  //! ...
  ArrayList<T> post_order() const;

 private:
  struct Node {
    explicit Node(const T& data);

    T data;
    Node* left;
    Node* right;

    void insert(const T& data_);

    bool remove(const T& data_);

    bool contains(const T& data_) const;

    void pre_order(ArrayList<T>& v) const;

    void in_order(ArrayList<T>& v) const;

    void post_order(ArrayList<T>& v) const;
  };

  Node* root;
  std::size_t size_;
};

}  //  namespace structures

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("A fila esta cheia!");
    } else if (index >= max_size_ || index < 0 || index > size_) {
        throw std::out_of_range("index invalido!");
    } else {
        for (int i = size_; i > index; i--) {
            contents[i] = contents[i-1];
        }
        contents[index] = data;
        size_ += 1;
    }
}
