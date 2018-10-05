/* Copyright [2018] <Alan Djon Lüdke>
 * circular_list.h
 */
//  there are some problems to solve
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {

//! classe CircularList
template<typename T>
class CircularList {
 public:
  //! Constructor method of CircularList();
  CircularList();

  //! Destructor method
  ~CircularList();

  //! Wipe the list
  void clear();

  //! Puts an element in the end of the list
  void push_back(const T& data);

  //! Puts an element in the beginning of the list
  void push_front(const T& data);

  //! Puts an element in a specific index
  void insert(const T& data, std::size_t index);

  //! Puts an element neatly
  void insert_sorted(const T& data);

  //! Returns the element of the index
  T& at(std::size_t index);

  //! Returns the const element of the index
  const T& at(std::size_t index) const;

  //! Takes an specific element off by index
  T pop(std::size_t index);

  //! Takes the last element off
  T pop_back();

  //! Takes the first element off
  T pop_front();

  //! Remove an specific element
  void remove(const T& data);

  //! Return if empty
  bool empty() const;

  //! Returns if an specific element belongs to the list
  bool contains(const T& data) const;

  //! Returns the index of an element
  std::size_t find(const T& data) const;

  //! Returns the size of the list
  std::size_t size() const;

 private:
  class Node {
   public:
    explicit Node(const T& data):
      data_{data}
    {}

    Node(const T& data, Node* next):
      data_{data},
      next_{next}
    {}

    Node(const T& data, Node* next, bool sentinel):
      data_{data},
      next_{next},
      isSentinel_{isSentinel}
    {}

    T& data() {
      return data_;
    }

    const T& data() const {
      return data_;
    }

    Node* next() {
      return next_;
    }

    const Node* next() const {
      return next_;
    }

    void next(Node* node) {
      next_ = node;
    }

    bool isSentinel() {
      return isSentinel_;
    }

    const bool isSentinel() const {
      return isSentinel_;
    }

    void isSentinel(bool isSentinel) {
      isSentinel_ = isSentinel;
    }

   private:
    T data_;
    Node* next_{nullptr};
    bool isSentinel_;
  };

  Node* head{nullptr};
  std::size_t size_{0u};
};

}  // namespace structures


template<typename T>
structures::CircularList<T>::CircularList() {}

template<typename T>
structures::CircularList<T>::~CircularList() {
  clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
  if (empty()) {
    push_front(data);
  } else {
    insert(data, size_);
  }
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
  Node *novo = new Node(data);

  if (novo == nullptr) {
    throw std::out_of_range("Nodo não alocado!");
  } else {
    novo->next(head);
    head = novo;
    size_ = size_ + 1;
  }
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
  Node *novo, *anterior;

  if (index > size_) {
    throw std::out_of_range("Erro no index!!");
  } else {
    if (index == 0) {
      return push_front(data);
    } else {
      novo = new Node(data);
      if (novo == nullptr) {
        throw std::out_of_range("Nodo não alocado!");
      } else {
        anterior = head;
        for (int i = 0; i < index - 1; i++) {
          anterior = anterior->next();
        }
        novo->next(anterior->next());
        anterior->next(novo);
        size_++;
      }
    }
  }
}

template <typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
  if (empty()) {
    push_back(data);
    return;
  }

  auto it = head;
  int index = 0;

  while (it->data() < data) {
    it = it->next();
    index++;

    if (it == nullptr) {
      push_back(data);
      return;
    }
  }
  insert(data, index);
}

template <typename T>
T& structures::CircularList<T>::at(std::size_t index) {
  if (index >= size()) {
    throw std::out_of_range("Index out of bounds.");
  }
  auto it = head;
  for (int i = 0; i < index; i++) {
    it = it->next();
  }
  return it->data();
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
  Node *anterior, *eliminar;
  T volta;
  if (empty() || index >= size_ || index < 0) {
    throw std::out_of_range("Erro no index!!");
  } else {
    if (index == 0) {
      return pop_front();
    } else {
      anterior = head;
      for (int i = 0; i < index - 1; i++) {
        anterior = anterior->next();
      }
      eliminar = anterior->next();
      volta = eliminar->data();
      anterior->next(eliminar->next());
      size_--;
      delete eliminar;
      return volta;
    }
  }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
  return pop(size_-1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
  Node *saiu;
  T volta;

  if (empty()) {
    throw std::out_of_range("Lista vazia, não é possivel retirar!");
  } else {
    saiu = head;
    volta = saiu->data();
    head = saiu->next();
    size_ = size_ - 1;
    delete saiu;
    return volta;
  }
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
  auto index = find(data);
  if (index != size()) {
    pop(index);
  }
}

template<typename T>
bool structures::CircularList<T>::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
  return find(data) != size();
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
  auto temp = head;
  int i = 0;
  while (temp != nullptr) {
    if (temp->data() == data) {
      return i;
    }
    i++;
    temp = temp->next();
  }
  return i;
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
  return size_;
}

#endif
