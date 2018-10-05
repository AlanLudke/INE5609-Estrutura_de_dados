/* Copyright [2018] <Alan Djon Lüdke>
 * doubly_linked_list.h
 */

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {
//! class DoublyLinkedList
template<typename T>
class DoublyLinkedList {
 public:
    //! Constructor method of DoublyLinkedList();
    DoublyLinkedList();  // construtor padrão
    //! Destructor method
    ~DoublyLinkedList();  // destrutor
    //! Wipe the list
    void clear();  // limpar lista
    //! Puts an element in the end of the list
    void push_back(const T& data);  // inserir no fim
    //! Puts an element in the beginning of the list
    void push_front(const T& data);  // inserir no início
    //! Puts an element in a specific index
    void insert(const T& data, std::size_t index);  // inserir na posição
      //! Puts an element neatly
    void insert_sorted(const T& data);  // inserir em ordem
    //! Returns the element of the index
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! Takes an specific element off by index
    T pop(std::size_t index);  // retirar da posição
    //! Takes the last element off
    T pop_back();  // retirar do fim
    //! Takes the first element off
    T pop_front();  // retirar do início
    //! Remove the first element
    void remove_front();  // remover 1
    //! Remove an specific element
    void remove(const T& data);  // remover específico
    //! Return if empty
    bool empty() const;  // lista vazia
    //! Returns if an specific element belongs to the list
    bool contains(const T& data) const;  // contém
    //! Returns the index of an element
    std::size_t find(const T& data) const;  // posição do dado
    //! Returns the size of the list
    std::size_t size() const;  // tamanho da lista

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
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {  // getter: prev
            return prev_;
        }
        const Node* prev() const {  // getter const: prev_
            return prev_;
        }
        void prev(Node* node) {  // setter: prev
            prev_ = node;
        }

        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};  // primeiro da lista
    Node* tail{nullptr};  // ultimo da lista
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
  if (empty()) {
    push_front(data);
  } else {
    insert(data, size_);
  }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {

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
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
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
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {

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
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
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
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
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
T structures::DoublyLinkedList<T>::pop_back() {
  return pop(size_-1);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
  Node *saiu;
  T volta;  // é ponteiro aqui?

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
void structures::DoublyLinkedList<T>::remove_front() {
  Node *saiu;

  if (empty()) {
    throw std::out_of_range("Lista vazia, não é possivel retirar!");
  } else {
    saiu = head;
    head = saiu->next();
    size_ = size_ - 1;
    delete saiu->data();
    delete saiu;
  }
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    auto index = find(data);
    if (index != size()) {
        pop(index);
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
  return find(data) != size();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
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
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}

#endif
