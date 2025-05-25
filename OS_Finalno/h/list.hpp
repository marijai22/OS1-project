#ifndef _LIST_HPP
#define _LIST_HPP
#include "../h/memallocator.hpp"
#include "../lib/mem.h"


template<typename T>
class List
{
private:
    struct Elem{
        T* data;
        Elem* next;

        Elem(T *data, Elem *next): data(data), next(next){}
        /*void *operator new(size_t size) { return __mem_alloc(size); }
        void operator delete(void *p) {__mem_free(p);}*/
       void *operator new(size_t size) { return MemoryAllocator::getInstance().allocate(size); }
        void operator delete(void *p) { MemoryAllocator::getInstance().deallocate(p); }
    };

    Elem *head, *tail;
    int size;


public:
    List() :head(0),tail(0), size(0) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T *data){
        Elem *elem = new Elem(data, head);
        head = elem;
        if(!tail) {tail = head;}
        size++;
    }

    void addLast(T *data){
        Elem *elem = new Elem(data, 0);
        if(tail){
            tail->next = elem;
            tail = elem;
        }else
        {
            head = tail = elem;
        }
        size++;
    }

    T *removeFirst()
    {
        if(!head) {return 0;}

        Elem *elem = head;
        head = head->next;
        if(!head) {tail = nullptr;}

        T *ret = elem->data;
        size--;
        delete elem;
        return ret;
    }


    T *peekFirst(){
        if(!head) {return 0;}
        return head->data;
    }


    T *removeLast()
    {
        if(!head) {return 0;}

        Elem *prev = 0;
        for(Elem *curr = head; curr && curr!=tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if(prev) {prev->next = 0;}
        else{head = 0;}
        tail = prev;

        T *ret = elem->data;
        delete elem;
        size--;
        return ret;
    }


    T *peekLast(){
        if(!tail) {return 0;}
        return tail->data;
    }

    int getSize(){
        return size;
    }

};

#endif