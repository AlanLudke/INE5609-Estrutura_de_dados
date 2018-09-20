/* Copyright [2018] <Alan Djon Lüdke>
 * array_stack.h
 */
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! classe arraystack
class ArrayStack {
 public:
    //! metodo construtor vazio
    ArrayStack();

    //! metodo construtor estipulando tamanho max para alocação
    explicit ArrayStack(std::size_t max);

    //! destrutor
    ~ArrayStack();

    //! empilha
    void push(const T& data);

    //! desempilha
    T pop();

    //! topo da pilha
    T& top();

    //! limpa
    void clear();

    //! tamanho da pilha
    std::size_t size();

    //! tamanho max da pilha
    std::size_t max_size();

    //! retorna se vazio
    bool empty();

    //! retorna se cheio
    bool full();

 private:
    static const auto DEFAULT_SIZE = 10u;
    T* contents;
    int top_;
    std::size_t max_size_;
};
}  //  namespace structures

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
	ArrayStack(DEFAULT_SIZE);
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
	max_size_ = max;
	contents = new T[max_size_];
	top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
	delete[] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
	if(full()) {
		throw std::out_of_range("A pilha esta cheia!");
	} else {
		top_++;
		contents[top_] = data;
	}
}

template<typename T>
T structures::ArrayStack<T>::pop() {
	if(empty()) {
		throw std::out_of_range("A pilha esta vazia!");
	} else {
		T data = contents[top_];
		top_--;
		return data;
	}
}

template<typename T>
T& structures::ArrayStack<T>::top() {
	if(empty()) {
		throw std::out_of_range("A pilha esta vazia!");
	} else {
		return contents[top_];
	}
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_+1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    if (top_ == -1) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    if (top_ == max_size_ - 1) {
        return true;
    } else {
        return false;
    }
}

#endif
