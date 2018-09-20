/* Copyright [2018] <Alan Djon Lüdke>
 * linked_queue.h
 */

#include <cstdint>
#include <stdexcept>  // C++ Exceptions
#include <cstring>


namespace structures {
//! class LinkedQueue
template<typename T>
class LinkedQueue {
 public:
  //! Constructor method of LinkedStack();
  LinkedQueue();
  //! Destructor method
  ~LinkedQueue();
  //! Wipe the list
  void clear();  // limpar
  //! Puts an element in the stack
  void enqueue(const T& data);  // enfilerar
  //! Takes an element off
  T dequeue();  // desenfilerar
  //! Return the first element
  T& front() const;  // primeiro dado
  //! Return the last element
  T& back() const;  // último dado
  //! Return if empty
  bool empty() const;  // fila vazia
  //! Returns the size of the queue
  std::size_t size() const;  // tamanho

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

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
  clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
  Node *novo = new Node(data);

  if (novo == nullptr) {
    throw std::out_of_range("Nodo não alocado!");
  } else {
    if (empty()) {
      novo->next(nullptr);
      head = novo;
      tail = novo;
    } else {
      novo->next(nullptr);
      tail->next(novo);
      tail = novo;
    }
    size_++;
  }
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
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
T& structures::LinkedQueue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Não há elementos!!");
  } else {
    return head->data();
  }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Não há elementos!!");
  } else {
    return tail->data();
  }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
