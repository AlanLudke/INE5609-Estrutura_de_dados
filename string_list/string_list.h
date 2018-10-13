/* Copyright [2018] <Alan Djon Lüdke>
 * string_list.cpp
 */

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {

//! class ArrayList
template<typename T>
class ArrayList {
 public:
    //! Constructor method of ArrayList();
    ArrayList();

    //! Constructor method with max_size as parameter;
    explicit ArrayList(std::size_t max_size);

    //! Destructor method
    ~ArrayList();

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

    //! Takes an specific element off by index
    T pop(std::size_t index);

    //! Takes the last element off
    T pop_back();

    //! Takes the first element off
    T pop_front();

    //! Remove an specific element
    void remove(const T& data);

    //! Return if full
    bool full() const;

    //! Return if empty
    bool empty() const;

    //! Returns if an specific element belongs to the list
    bool contains(const T& data) const;

    //! Returns the index of an element
    std::size_t find(const T& data) const;

    //! Returns the size of the list
    std::size_t size() const;

    //! Returns the max size of the list
    std::size_t max_size() const;

    //! Returns the element of the index
    // it needs to verify if the index is valid
    T& at(std::size_t index);

    //! Returns the element of the index
    // it doesn't need to verify if the index is valid
    T& operator[](std::size_t index);

    //! Returns the element of the index - constant
    // it needs to verify if the index is valid
    const T& at(std::size_t index) const;

    //! Returns the element of the index - constant
    // it doesn't need to verify if the index is valid
    const T& operator[](std::size_t index) const;

 private:
    //! Default max size of the list
    static const auto DEFAULT_MAX = 10u;
    //! pointer to the contents
    T* contents;
    //! actual size of the list
    std::size_t size_;
    //! max size of our list
    std::size_t max_size_;
};

//! ArrayListString is an spelization of the class ArrayList()
class ArrayListString : public ArrayList<char *> {
 public:
    //! Constructor method of ArrayListString();
    ArrayListString() : ArrayList() {}

    //! Constructor method with max_size as parameter;
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}

    //! Destructor method
    ~ArrayListString();

    //! Wipe the list
    void clear();

    //! Puts an element in the end of the list
    void push_back(const char *data);

    //! Puts an element in the beginning of the list
    void push_front(const char *data);

    //! Puts an element in a specific index
    void insert(const char *data, std::size_t index);

    //! Puts an element neatly
    void insert_sorted(const char *data);

    //! Takes an specific element off by index
    char *pop(std::size_t index);

    //! Takes the last element off
    char *pop_back();

    //! Takes the first element off
    char *pop_front();

    //! Remove an specific element
    void remove(const char *data);

    //! Returns if an specific element belongs to the list
    bool contains(const char *data);

    //! Returns the index of an element
    std::size_t find(const char *data);
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

structures::ArrayListString::~ArrayListString() {
    clear();
}

void structures::ArrayListString::clear() {
    ArrayList::clear();
}

void structures::ArrayListString::push_back(const char *data) {
    ArrayListString::insert(data, ArrayList::size());
}

void structures::ArrayListString::push_front(const char *data) {
    insert(data, 0);
}

void structures::ArrayListString::insert(const char *data,
std::size_t index) {
    if (strlen(data) > 10000) {
        throw std::out_of_range("String muito grande!");
    } else {
        // takes the size of *data and put in 'len'
        std::size_t len = strlen(data);

        // alocates memory with the size of data;
        char *datanew = new char[len + 1];

        // copy the content of *data to datanew
        snprintf(datanew, len + 1, "%s", data);

        // insert the pointer in the list
        ArrayList::insert(datanew, index);
    }
}

void structures::ArrayListString::insert_sorted(const char *data) {
     if (strlen(data) > 10000) {
        throw std::out_of_range("String muito grande!");
    } else {
        std::size_t i;
        for (i = 0; i < ArrayList::size(); i++) {
           if (strcmp(ArrayList::at(i), data) > 0) {  // a>b
               break;
            }
        }
        ArrayListString::insert(data, i);
    }
}

char* structures::ArrayListString::pop(std::size_t index) {
    char* temp = ArrayList::pop(index);

    return temp;
}

char* structures::ArrayListString::pop_back() {
    return pop(ArrayList::size() - 1);
}

char* structures::ArrayListString::pop_front() {
    return pop(0);
}

void structures::ArrayListString::remove(const char *data) {
    std::size_t i;

    for (i = 0; i < ArrayList::size(); i++) {
        if (strcmp(ArrayList::at(i), data) == 0) {  // a=b
              break;
        }
    }
    pop(i);
}

bool structures::ArrayListString::contains(const char *data) {
    return (find(data) != ArrayList::size());
}


std::size_t structures::ArrayListString::find(const char *data) {
    std::size_t index;
    for (index = 0; index < ArrayList::size(); index++) {
        if (strcmp(ArrayList::at(index), data) == 0) {
            break;
        }
    }
    return index;
}

#endif
