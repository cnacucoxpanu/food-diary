#ifndef LISTNODE_H
#define LISTNODE_H

#include <stdexcept>
#include <iomanip>

template <typename T>
class ListNodeIterator;

template <typename T>
class ListNode {
public:
    T data;
    ListNode<T>* next;
    ListNode<T>* prev;
    
    ListNode() : next(nullptr), prev(nullptr) {}
    ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    ListNode(const ListNode& other) : data(other.data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    
    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }
    void clear();
    
    void addToEnd(const T& value);
    void addToFront(const T& value);
    
    bool removeByIndex(int index);
    bool remove(const T& value);
    
    int find(const T& value) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    
    ListNodeIterator<T> begin() { return ListNodeIterator<T>(head); }
    ListNodeIterator<T> end() { return ListNodeIterator<T>(nullptr); }
    ListNodeIterator<T> begin() const { return ListNodeIterator<T>(head); }
    ListNodeIterator<T> end() const { return ListNodeIterator<T>(nullptr); }
    
    // Исправленный friend declaration
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& list);
};

template <typename T>
class ListNodeIterator {
private:
    ListNode<T>* current;

public:
    ListNodeIterator(ListNode<T>* node) : current(node) {}
    
    ListNodeIterator& operator++();
    ListNodeIterator operator++(int);
    
    T& operator*();
    const T& operator*() const;
    
    T* operator->();
    const T* operator->() const;
    
    bool operator==(const ListNodeIterator& other) const;
    bool operator!=(const ListNodeIterator& other) const;
    
    operator ListNode<T>*() const { return current; }
};

#include "../src/containers/listNode.tpp"

#endif