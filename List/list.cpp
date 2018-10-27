#include "list.h"

template<typename T>
Block<T>::Block(size_t size) : prev(nullptr), next(nullptr) {
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
T& List<T>::operator[](size_t index) {
    int cur_pos = 0;
    Block<T> *cur_block = _start;

    while (cur_block->next != nullptr && cur_pos + cur_block->getSize() <= index) {
        cur_pos += cur_block->getSize();
        cur_block = cur_block->next;
    }

    index -= cur_pos;
    return cur_block->getElement(index);
}

template<typename T>
const size_t List<T>::BLOCK_SIZE = 500;

template<typename T>
List<T>::List() {
    _start = new Block<T>(List<T>::BLOCK_SIZE);
}

template<typename T>
List<T>::~List() {
    delete _start;
}