/**
 * This files contains an implementation of a linked list with functionality for a generic type
 * 
 * @author Sean Droll
 */

#include <stdexcept>
#include <string>
#include "node.h"

/**
 * @class LinkedList
 * @brief This class represents a simple LinkedList with generic typing
 * 
 * Linkedlist provides functionality to insert, retrieve,
 * and remove values from a linked list
 */
template <typename T>
class LinkedList {
    private:
        Node<T> *head;
        int listSize;
    public:
        LinkedList() : head(nullptr), listSize(0) {};
        ~LinkedList();
        void put(T value);
        T pop();
        void insert(int index, T value);
        T get(int index);
        T remove(int index);
        int size();
};

/**
 * @brief Deconstructs a linked list and each node contained in it
 */
template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = head;
    while(current != nullptr) {
        Node<T> *next = current->getNext();
        delete current;
        current = next;
    }
}

/**
 * @brief Places a node at position 0 of the linked list
 */
template <typename T>
void LinkedList<T>::put(T v) {
    head = new Node(v, head);
    listSize++;
}

/**
 * @brief retrieves and removes node at position 0 of the linked list
 * @return The value stored at index 0 of the linked list
 * @throw Index out of range exception
 */
template <typename T>
T LinkedList<T>::pop() {
    if(listSize == 0) {
        throw std::out_of_range("Cannot pop from an empty list");
    }
    Node<T> *item = head;
    head = head->getNext();
    T val = item->getValue();
    delete item;
    listSize--;
    return val;
}

/**
 * @brief stores a value at the given index in a linked list
 * @param index the index in which to insert the value
 * @param v the value to store
 * @throw index out of bounds exception
 */
template <typename T>
void LinkedList<T>::insert(int index, T v) {
    if(index < 0 || index > listSize) {
        throw std::out_of_range("Index " + std::to_string(index) + " out of bounds for list size " + std::to_string(listSize));
    }
    if(index == 0) {
        head = new Node(v, head);
        listSize++;
        return;
    }
    Node<T> *current = head;
    for(int i = 1; i < index; i++) {
        current = current->getNext();
    }
    current->setNext(new Node(v, current->getNext()));
    listSize++;
}

/**
 * @brief retrieves a value at a given index
 * @param index the index in which to retrieve the value
 * @return value stored at that index
 */
template <typename T>
T LinkedList<T>::get(int index) {
    if(index < 0 || index >= listSize) {
        throw std::out_of_range("Index " + std::to_string(index) + " out of bounds for list size " + std::to_string(listSize));
    }
    Node<T> *current = head;
    for(int i = 0; i < index; i++) {
        current = current->getNext();
    }
    return current->getValue();
}

/**
 * @brief retrieves and removes a value from a given index
 * @param index the index in which to remove the value
 * @return the value stored at the given index
 */
template <typename T>
T LinkedList<T>::remove(int index) {
    if(index < 0 || index >= listSize) {
        throw std::out_of_range("Index " + std::to_string(index) + " out of bounds for list size " + std::to_string(listSize));
    }
    if(index == 0) {
        Node<T> *item = head;
        head = head->getNext();
        T val = item->getValue();
        delete item;
        listSize--;
        return val;
    }
    Node<T> *prev = head;
    Node<T> *current = head->getNext();
    for(int i = 1; i < index; i++) {
        prev = current;
        current = current->getNext();
    }
    Node<T> *item = current;
    prev->setNext(current->getNext());
    T val = item->getValue();
    delete item;
    listSize--;
    return val;
}

/**
 * @brief retrieves the size of the LinkedList
 * @return the size of the list
 */
template <typename T>
int LinkedList<T>::size() {
    return listSize;
}

