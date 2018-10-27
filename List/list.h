#ifndef LIST_H
#define LIST_H

#include <cstdlib>

template<typename T>
class Block {
private:
    T* _block;
    size_t _size;

    Block<T> *prevs, *nexts;
public:
    Block(size_t size);

    T& getElement(size_t index);
    int getSize() const;

    ~Block();
};

template<typename T>
class List {
private:
    static const size_t BLOCK_SIZE;
    Block<T>* _start;
public:
    List();
    List(List &copy);

    T& operator[](size_t index);

    ~List();
};

template<typename T>
Block<T>::Block(size_t size) : prevs(nullptr), nexts(nullptr) {
    _size = size;
    _block = new T[size];
}

template<typename T>
T& Block<T>::getElement(size_t index) {
    return _block[index];
}

template<typename T>
int Block<T>::getSize() const {
    return _size;
}

template<typename T>
Block<T>::~Block() {
    delete[] _block;
}

template<typename T>
T& List<T>::operator[](size_t index) {
    int cur_pos = 0;
    Block<T> *cur_block = _start;

    while (cur_block->nexts != nullptr && cur_pos + cur_block->getSize() <= index) {
        cur_pos += cur_block->getSize();
        cur_block = cur_block->nexts;
    }

    index -= cur_pos;
    return cur_block->getElement(index);
}

template<typename T>
List<T>::List(List<T>& copy) {
    Block<T>* nexts = copy._start;
    _start = Block<T>(nexts);


    while (nexts->nexts) {
        // реализовать копирование блоков
    }
}

template<typename T>
const size_t List<T>::BLOCK_SIZE = 500;

template<typename T>
List<T>::List() {
    _start = new Block<T>(List<T>::BLOCK_SIZE);
}

template<typename T>
List<T>::~List() {
    Block<T>* nows = _start;
    while (nows != nullptr) {
        Block<T>* p = nows;
        nows = nows->nexts;

        delete p;
    }
}

#endif // LIST_H
