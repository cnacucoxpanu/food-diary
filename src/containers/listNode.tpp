#ifndef LISTNODE_TPP
#define LISTNODE_TPP

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    ListNode<T>* current = other.head;
    while (current != nullptr) {
        addToEnd(current->data);
        current = current->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            addToEnd(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
void LinkedList<T>::clear() {
    ListNode<T>* current = head;
    while (current != nullptr) {
        ListNode<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::addToEnd(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::addToFront(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template <typename T>
bool LinkedList<T>::removeByIndex(int index) {
    if (index < 0 || index >= size) return false;
    
    ListNode<T>* toDelete = nullptr;
    
    if (index == 0) {
        toDelete = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
    } else if (index == size - 1) {
        toDelete = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
    } else {
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        toDelete = current;
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
    }
    
    delete toDelete;
    size--;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(const T& value) {
    int index = find(value);
    return (index != -1) ? removeByIndex(index) : false;
}

template <typename T>
int LinkedList<T>::find(const T& value) const {
    int index = 0;
    for (auto it = begin(); it != end(); ++it, ++index) {
        if (*it == value) return index;
    }
    return -1;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    ListNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    ListNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Исправленная реализация оператора вывода
template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
    int counter = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        os << std::setw(3) << counter++ << ". " << *it << std::endl;
    }
    return os;
}

// Реализация ListNodeIterator
template <typename T>
ListNodeIterator<T>& ListNodeIterator<T>::operator++() {
    if (current) current = current->next;
    return *this;
}

template <typename T>
ListNodeIterator<T> ListNodeIterator<T>::operator++(int) {
    ListNodeIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
T& ListNodeIterator<T>::operator*() { 
    return current->data; 
}

template <typename T>
const T& ListNodeIterator<T>::operator*() const { 
    return current->data; 
}

template <typename T>
T* ListNodeIterator<T>::operator->() { 
    return &(current->data); 
}

template <typename T>
const T* ListNodeIterator<T>::operator->() const { 
    return &(current->data); 
}

template <typename T>
bool ListNodeIterator<T>::operator==(const ListNodeIterator& other) const { 
    return current == other.current; 
}

template <typename T>
bool ListNodeIterator<T>::operator!=(const ListNodeIterator& other) const { 
    return current != other.current; 
}

#endif