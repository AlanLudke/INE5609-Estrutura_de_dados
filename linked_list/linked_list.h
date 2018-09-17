/* Copyright [2018] <Alan Djon Lüdke>
 * linked_list.cpp
 */

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {

//! class LinkedList
template<typename T>
class LinkedList {
 public:
    //! Constructor method of LinkedList();
    LinkedList();  // construtor padrão
    //! Destructor method
    ~LinkedList();  // destrutor
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
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
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
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::LinkedList<T>::LinkedList() {}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
  clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
  if (empty()) {
    push_front(data);
  } else {
    insert(data, size_);
  }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
/*
Verifica a possibilidade de alocac¸ao de um elemento; ˜
O proximo deste novo elemento passa ser o primeiro da ´
lista;
A cabec¸a de lista passa a apontar para o novo elemento.
*/

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
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
  Node *novo, *anterior;  // auxiliares

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
void structures::LinkedList<T>::insert_sorted(const T& data) {
  // If list is empty, just push
        if (empty()) {
            push_back(data);
            return;
        }

        auto it = head;
        int index = 0;

        while (it->data() < data) {
            it = it->next();
            index++;

            // If reach the last object, push on last pos
            if (it == nullptr) {
                push_back(data);
                return;
            }
        }

        insert(data, index);
}

template <typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
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
T structures::LinkedList<T>::pop(std::size_t index) {
  Node *anterior, *eliminar;  //  auxiliares
  T volta;  //  errado T*
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
      delete[] eliminar;
      return volta;
    }
  }
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
  return pop(size_-1);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
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
void structures::LinkedList<T>::remove_front() {
  Node *saiu;

  if (empty()) {
    throw std::out_of_range("Lista vazia, não é possivel retirar!");
  } else {
    saiu = head;
    head = saiu->next();
    size_ = size_ - 1;
    delete saiu->data();
    delete[] saiu;
  }
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    auto index = find(data);
    if (index != size()) {
        pop(index);
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
  if(size_ == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
  return find(data) != size();
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
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
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

#endif
