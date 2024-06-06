#include <iostream>
#include <string>
#include <cstdint>

using ull = unsigned long long;
const short CAP = 16;


auto f = [](){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();


struct Data{
    std::string key;
    ull value;
};


class MyVector final{
    private:
    size_t _cap;
    size_t _size;
    Data* arr;
    public:
    MyVector():_cap(1),_size(0),arr(new Data[_cap]){}
    MyVector(const MyVector& other):_size(other._size),_cap(other._cap),arr(new Data[_cap]){
        for (size_t i = 0; i < _size; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    MyVector(size_t size):_size(size),_cap(size),arr(new Data[_cap]){}
    MyVector(MyVector&& other) noexcept :_cap(other._cap),_size(other._size),arr(other.arr){
        other.arr = nullptr;
        other._size = 0;
        other._cap = 0;
    }
    MyVector& operator=(const MyVector& other){
        if (this==&other)
        {
            return *this;
        }
        _size = other._size;
        _cap = other._cap;
        arr = new Data[_cap];
        for (size_t i = 0; i < _size; i++)
        {
            arr[i] = other.arr[i];
        }
        return *this;
    }
    MyVector& operator=(MyVector&& other){
        _size=other._size;
        _cap = other._cap;
        arr = other.arr;
        other.arr = nullptr;
        other._size = 0;
        other._cap = 0;
        return *this;
    }
    void push_back(const Data& other){
        if (_size==_cap)
        {
            reserve(_cap*2);
        }
        arr[_size++] = other;
        
    }
    void reserve(size_t new_cap){
        if(new_cap <= _cap){ return ;};
        Data* new_arr = new Data[new_cap];
        for (size_t i = 0; i < _size; i++)
        {
            new_arr[i] = arr[i];
        }
        _cap = new_cap;
        arr = new_arr;
    }
    size_t size() const noexcept{ 
        return _size;
    }
    size_t capacity() const noexcept{
        return _cap;
    }
    ~MyVector(){
        delete[] arr;
    }
    Data& operator[](size_t index)const noexcept{
        return *(arr+index);
    } 
    Data* begin() const noexcept{
        return arr;
    }
    Data* end() const noexcept{
        return arr+_size;
    }
};




void sortCounting(MyVector& array, const uint16_t index){
    int count[CAP] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int pos[CAP] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    MyVector result(array.size());
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
    for (size_t i = 0; i < array.size(); i++)
    {
        array[i] = result[i]; 
    }
    
}

void sortRadix(MyVector& array){
    for (int i = CAP-1; i >= 0; i--)
    {
        sortCounting(array,i);
    }
    
}



int main(){
    MyVector array;
    std::string key;
    ull value;
    array.reserve(1000000);
    while (std::cin>>key>>value)
    {
        Data newData{key,value};
        array.push_back(newData);
    }
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