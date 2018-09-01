/* Copyright [2018] <Alan Djon Lüdke>
 * array_list.cpp
 */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

//! classe ArrayList
template<typename T>
class ArrayList {
 public:
    //! metodo construtor vazio
    ArrayList();

    //! metodo construtor com o tamanho como parametro
    explicit ArrayList(std::size_t max_size);

    //! metodo destrutor
    ~ArrayList();

    //! limpa a lista
    void clear();

    //! insere um elemento no final da fila
    void push_back(const T& data);

    //! insere um elemento no começo da fila
    void push_front(const T& data);

    //! insere um elemento em um determinado index da fila
    void insert(const T& data, std::size_t index);

    //! insere um elemento na ordem
    void insert_sorted(const T& data);

    //! retira um elemento em um determinado index da fila
    T pop(std::size_t index);

    //! retira um elemento do final da fila
    T pop_back();

    //! retira um elemento do começo da fila
    T pop_front();

    //! remove um elemento
    void remove(const T& data);

    //! retorna se a lista esta cheia
    bool full() const;

    //! retorna se a lista esta vazia
    bool empty() const;

    //! retorna se o elemento está na lista
    bool contains(const T& data) const;

    //! encontra a posicao da primeira vez que encontra o elemento
    std::size_t find(const T& data) const;

    //! retorna o tamanho da lista
    std::size_t size() const;

    //! retorna a quantidade maxima de elementos da lista
    std::size_t max_size() const;

    //! retorna o elemento do 'index' precisa verificar se é valido
    T& at(std::size_t index);

    //! retorna o elemento do 'index' NAO precisa verificar se é valido
    T& operator[](std::size_t index);

    //! Polymorph for const object
    const T& at(std::size_t index) const;

    //! Polymorph for const object
    const T& operator[](std::size_t index) const;

 private:
    static const auto DEFAULT_MAX = 10u;
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
};

}  //  namespace structures


template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("A fila esta cheia!");
    } else {
        contents[size_] = data;
        size_++;
    }
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

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        int i;
        for (i = 0; i < size_ && contents[i] < data; i++) {}
        insert(data, i);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("A fila esta vazia!");
    } else if (index >= this->size_ || index < 0) {
        throw std::out_of_range("Invalid index");
    }
    auto data = contents[index];

    for (int i = index; i < size_-1; i++) {
        contents[i] = contents[i+1];
    }
    size_ = size_ - 1;
    return data;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size_-1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    bool found = false;
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data && found == false) {
            found = true;
            pop(i);
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    if (size_ == max_size_) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    return find(data) != size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < this->size_; i++) {
        if (data == this->contents[i]) {
            return i;
        }
    }
    return this->size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (size_ < index || index < 0) {
        throw std::out_of_range("Index out of bounds.");
    } else {
        return this->operator[](index);
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (size_ < index || index < 0) {
        throw std::out_of_range("Index out of bounds.");
    } else {
        return operator[](index);
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

#endif

