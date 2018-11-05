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
    size_t getSize() const;
    size_t getIndex() const;
    
    template <class K> friend class List;
};

template<class T>
class List {
private:
    static const size_t BLOCK_SIZE;
    Block<T> _start;
    
public:
    List();
    List(List &);
    List(T *, size_t);
    ~List();
    
    size_t Len () const;
    void PushAfter (Block<T>* L, T* x);
    void PushAfterI (size_t i, T* x);
    void PushBegin (Block<T>* K);
    void PushEnd (Block<T>* K);
    
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
size_t Block<T>::getIndex() const {
	return _ind;
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
void List<T>::PushAfter (Block <T> *L, const T* x) {
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

template <class T>
void List<T>::PushAfterI (size_t i, const T* x) {
	Block<T>* tmp;
	tmp = _start->nexts;
	while (tmp->_ind != i) {
		tmp = tmp->nexts;
	}
	PushAfter(tmp, x);
	return;
}

//////
template<class T>
void List<T>:: PushEnd(const T* x) {
	PushAfter(_start.prevs, x);
}

template<class T>
void List<T>:: PushBegin(const t* x) {
	PushAfter(&_start, x);
}

//////


template<class T>
List<T>::List(List<T>& a) {
    Block<T>* next = a._start;
    _start = next;
    
    
    while (next->nexts) {
        //??????????? ??????( ?? ???? ??? ??????, ????? ?????? ??????????? ??????????? ?????? ????? ?????? ?????????? push)
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
