#include <string>
#include <iostream>
#include <cstdint>
#include <cstring>
// #include "vector.hpp"

const short CAP = 16;
using ull = unsigned long long;

struct Data{
    char key[34];
    ull value;
    Data():key(""), value(0) {}
    Data(const char* k, ull v) : value(v) {
        strcpy(key,k);
    }
};


// #pragma once


template<typename T>
class Vector final{
private:
    T* arr{};
    size_t _size{};
    size_t _cap{};

public:

    Vector();
    Vector(size_t _size, T value);
    explicit Vector(size_t _size);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other) noexcept;

    ~Vector();
    T& operator[](size_t index) const;
    [[nodiscard]]size_t size() const noexcept;
    Vector<T>& operator=(const Vector& other);
    Vector<T>& operator=(Vector&& other) noexcept;
    [[nodiscard]] size_t capacity() const noexcept;
    void reserve(size_t newCap);
    void push_back(const T& value);
    constexpr void shrink_to_fit();
    [[nodiscard]]T* begin() const noexcept;
    [[nodiscard]]T* end() const noexcept;
};

template <typename T>
Vector<T>::Vector(size_t size){
    reserve(size);
     _size = size;
    for (size_t i = 0; i < _size; i++)
    {
        new(arr+i) T;
    }
    

}

template<typename T>
constexpr void Vector<T>::shrink_to_fit(){
    T* newarr = reinterpret_cast<T*>(new std::byte[_size*sizeof(T)]);

    for (size_t i = 0; i < _size; i++)
    {
        new(newarr+i) T(arr[i]);
    }
    for (size_t i = 0; i < _size; i++)
    {
        (arr+i)->~T();
    }
    delete[] reinterpret_cast<uint8_t*>(arr);
    _cap = _size;
    arr = newarr;
} 

template <typename T>
Vector<T>::Vector():_size(0),_cap(0) {
}

template<typename T>
Vector<T>::Vector(size_t size, T value): _size(size),_cap(size*2){
    arr = reinterpret_cast<T*>(new uint8_t[sizeof(T)*_cap]);
    for (size_t i = 0; i < _size; i++)
    {
        new (arr+i) T(value);
        arr[i] = value;
    }
    
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other)noexcept{
    _size = other._size;
    _cap = other._cap;
    arr = other.arr;

    other.arr = nullptr;
    other._size = 0;
    other._cap = 0;
    return *this;

}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){
    if (this==other)
    {
        return *this;
    }
    _size = other._size;
    _cap = other._cap;
    arr = new T[_cap];
    for(int i = 0; i < size; ++i) {
        arr[i] = other[i];
    }
    return *this;
    
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other){

    for (int i = 0; i < _size; i++)
    {
        arr[i] = other[i];
    }
    
}

template <typename T>
Vector<T>::~Vector(){
    for (size_t i = 0; i < _size; i++)
    {
        (arr+i)->~T();
    }
    delete[] reinterpret_cast<uint8_t*>(arr);
    _size = 0;
    _cap = 0;
    arr = nullptr;
    
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : _size(other._size), _cap(other._cap), arr(other.arr) {
    other.arr = nullptr;
    other._size = 0;
    other._cap = 0;
}

template <typename T>
void Vector<T>::push_back(const T& value){
    if(_size >= _cap){
        reserve(_cap*2);
    }
    new(arr+_size) T(value);//placement new
    ++_size;
}


template <typename T>
void Vector<T>::reserve(size_t newCap){
    if(newCap==0) ++newCap;
    if(newCap<=_cap) return;
    
    T* newarr = reinterpret_cast<T*>(new std::byte[newCap * sizeof(T)]);

    for (size_t i = 0; i < _size; i++)
    {
        new(newarr+i) T(arr[i]);
    }
    for (size_t i = 0; i < _size; i++)
    {
        (arr+i)->~T();
    }
    delete[] reinterpret_cast<uint8_t*>(arr);
    _cap = newCap;
    arr = newarr;
}

template <class T> 
T& Vector<T>::operator[](size_t index) const  {
    if(index >= _size) {
        throw std::logic_error("Cannot take Element from this index: index out of range");
    }

    return arr[index];
}

    
template<typename T>
size_t Vector<T>::capacity() const noexcept{
    return _cap;
}

template<typename T>
size_t Vector<T>::size() const noexcept{
    return _size;
}

template<typename T>
T* Vector<T>::begin() const noexcept{
    return arr;
}

template<typename T>
T* Vector<T>::end() const noexcept{
    return arr+_size;
}



void sortCounting(Vector<Data>& array, const uint16_t index){
    Vector<int> count(CAP,0);
    Vector<int> pos(CAP,0);
    Vector<Data> result(array.size());
    for(const auto&[key, value] : array){
        if(static_cast<int>(key[index])<97){
            ++count[static_cast<int>(key[index])-48];
        }else{
            ++count[static_cast<int>(key[index])-87];
        }
    }
    for (int i = 1; i < CAP; i++)
    {
        pos[i] = count[i-1] + pos[i-1];
    }
    for(int i = 0; i<array.size();i++){
        if(static_cast<int>(array[i].key[index])<97){
            result[pos[static_cast<int>(array[i].key[index])-48]++]=std::move(array[i]);
        }else{
            result[pos[static_cast<int>(array[i].key[index])-87]++]=std::move(array[i]);
        }

    }
    
    array = std::move(result);
}

void sortRadix(Vector<Data>& array){
    for (int i = CAP-1; i >= 0; i--)
    {
        sortCounting(array,i);
    }
    
}



int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Vector<Data> array;
    char key[34];
    ull value;
    // array.reserve(10000);
    while (std::cin>>key>>value)
    {
        Data newData = {key,value};
        array.push_back(newData);
    }
    array.shrink_to_fit();
    if (array.size()!=1)
    {
        sortRadix(array);
    }
    // sortRadix(array);
    for(const auto&[key, value]: array){
        std::cout<<key << "\t" << value << "\n";
    }

    return 0;
}