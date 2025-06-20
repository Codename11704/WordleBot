#pragma once

#include <cstdarg>
#include <stdexcept>

template <typename T>
class Tuple {
private:
    T *data_;
    int size_;

public:
    Tuple(int count, ...);
    ~Tuple();
    int size() const;
    const T& operator[](int index) const;
    Tuple<T> slice(int start) const;

private:
    Tuple(int size, T* Source);
};

template <typename T>
Tuple<T>::Tuple(int count, ...) {
    va_list args;
    va_start(args, count);
    this->data_ = new T[count];
    for(int i = 0; i < count; i++) {
        this->data_[i] = va_arg(args, T);
    }
    this->size_ = count;
}

template <typename T>
Tuple<T>::Tuple(int size, T* source) {
    size_ = size;
    data_ = new T[size_];
    for(int i = 0; i < size_; ++i) {
        data_[i] = source[i];
    }
}

template <typename T>
Tuple<T>::~Tuple() {
    delete[] this->data_;
}

template <typename T>
const T& Tuple<T>::operator[](int index) const {
    if(index < 0 || index >= this->size_) {
        throw std::runtime_error("Index out of bounds exception");
    }
    return data_[index];
}

template <typename T>
int Tuple<T>::size() const {
    return this->size_;
}

template <typename T>
Tuple<T> Tuple<T>::slice(int start) const {
    if (start < 0 || start >= size_) {
        throw std::out_of_range("Invalid slice start");
    }
    return Tuple<T>(size_ - start, data_ + start);
}
