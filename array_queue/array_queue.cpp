/* Copyright [2018] <Alan Djon Lüdke>
 * array_queue.cpp
 */
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! metodo construtor vazio
    ArrayQueue();

    //! metodo construtor com parametro de tamanho
    explicit ArrayQueue(std::size_t max);

    //! metodo destrutor
    ~ArrayQueue();

    //! metodo enfileirar
    void enqueue(const T& data);

    //! metodo desenfileirar
    T dequeue();

    //! metodo que retorna o final da fila
    T& back();

    //! metodo limpar a fila
    void clear();

    //! metodo que retorna o tamanho atual da fila
    std::size_t size();

    //! metodo que retorna o tamanho total da fila
    std::size_t max_size();

    //! retorna se vazio
    bool empty();

    //! retorna se cheio
    bool full();

 private:
    static const auto DEFAULT_SIZE = 10u;
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
};

}  //  namespace structures

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    ArrayQueue(DEFAULT_SIZE);
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("A fila esta cheia!");
    } else {
        size_++;
        contents[size_-1] = data;
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("A fila esta vazia!");
    } else {
        T data = contents[0];
        size_--;
        for (int i = 0; i < size_ ; i++) {
            contents[i] = contents[i + 1];
        }
        return data;
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("A fila esta vazia!");
    } else {
        return contents[size_-1];
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == max_size_) {
        return true;
    } else {
        return false;
    }
}

#endif
