#ifndef LIST_H
#define LIST_H

#include <cstdlib>

template<typename T>
class Block {
private:
    T* _block;
    size_t _size;

    Block* prev, next;
public:
    Block(size_t size);

    T& getElement(size_t index);
    int getSize() const;
};

template<typename T>
class List {
private:
    static const size_t BLOCK_SIZE;
    Block<T>* _start;
public:
    List();

    T& operator[](size_t index);
    ~List();
};

#endif // LIST_H
