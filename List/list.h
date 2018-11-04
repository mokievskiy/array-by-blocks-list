#ifndef LIST_H
#define LIST_H

#include <cstdlib>

template<class T>
class Block {
private:
    T* _block;
    size_t _size;
    size_t _ind;
    
    Block<T> *prevs, *nexts;
public:
    Block(size_t size, size_t ind);
    ~Block();
    
    T& getElement(size_t index);
    int getSize() const;
    
    template <class K> friend class List;
};

template<class T>
class List {
private:
    static const size_t BLOCK_SIZE;
    Block<T> _start;
    
    void push (Block<T>* L, const T* x);
public:
    List();
    List(List &);
    List(T *, size_t);
    ~List();
    
    size_t Len () const;
    void PushAfter (Block<T>* L, size_t index);
    
    T& operator[](size_t index);
    
    template <class K> friend class Block;
};

///////////////////////////////////////

template<class T>
Block<T>::Block(size_t size, size_t ind) : prevs(NULL), nexts(NULL) {
    _size = size;
    _block = new T[size];
    _ind = ind;
}



template<class T>
T& Block<T>::getElement(size_t index) {
    return _block[index];
}

template<class T>
int Block<T>::getSize() const {
    return _size;
}

template<class T>
Block<T>::~Block() {
    delete[] _block;
}

/////////////////////////////////////////

template<class T>
T& List<T>::operator[](size_t index) {
 
    Block<T> *cur_block = _start;
    size_t pos = index % cur_block->getSize();
    size_t in1 = index / cur_block->getSize();
    
    while (cur_block->nexts != NULL && cur_block._ind <= in1) {
        cur_block = cur_block->nexts;
    }
    
    return cur_block->getElement(pos);
}

template<class T>
size_t List<T>::Len () const {
    Block<T> *tmp = _start.nexts;
    size_t n = 0;
    while (tmp != &_start) {
        tmp = tmp->nexts;
        n++;
    }
    return n;
}

template<class T>
void List<T>::push (Block <T> *L, const T* x) {
    Block<T> *R = L->nexts;
    Block<T> *NEW = new Block<T>;
    if (NEW == NULL) {throw "bad_alloc";}
    NEW->_size = BLOCK_SIZE;
    NEW->_block = x;
    L->nexts = NEW;
    NEW->prevs = L;
    NEW->nexts = R;
    R->prevs = NEW;
    size_t t, l;
    t = L->_ind;
    L->_ind = t - 1;
    NEW->_ind = t;
    
    l = Len();
    for (size_t i = t+1; i < l; i++) {
        R->_ind = i + 1;
        R = R->nexts;
    }
    return;
}
//////


//////


template<class T>
List<T>::List(List<T>& a) {
    Block<T>* next = a._start;
    _start = next;
    
    
    while (next->nexts) {
        //копирование блоков( не знаю как делать, думаю просто реализовать копирование списка через сверху написанный push)
    }
}

template<class T>
List<T>::List(T *arr, size_t n) {
    
}

template<class T>
const size_t List<T>::BLOCK_SIZE = 5;

template<class T>
List<T>::List() {
    _start.prevs = _start.nexts = &_start;
    List<T>::BLOCK_SIZE;
}

template<class T>
List<T>::~List() {
    Block<T>* nows = _start;
    while (nows != nullptr) {
        Block<T>* p = nows;
        nows = nows->nexts;
        
        delete p;
    }
}

#endif // LIST_H
