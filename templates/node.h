/**
 * This header file defines the template of a node class. 
 * 
 * @author Sean Droll
 */


/**
 * @class Node
 * @brief Represents a single node in a linked list
 * 
 * Provides functionality for accessing the value stored 
 * in the node and getting the next item in the linked list
 */
template <typename T>
class Node {
    private:
        T value;
        Node<T> *next;
    public:
        Node(T v);
        Node(T v, Node *next);
        T getValue() const;
        Node *getNext() const;
        void setNext(Node *n);
};


/**
 * @brief Constructs a node with a given value
 * @param v Value stored in Node
 */
template <typename T>
Node<T>::Node(T v) {
    value = v;
    next = nullptr;
}


/**
 * @brief Constructs a node with a given value and a pointer to the next node in the list
 * @param v Value stored in Node
 * @param *n pointer to next node in list
 */
template <typename T>
Node<T>::Node(T v, Node *n) {
    value = v;
    next = n;
}


/**
 * @brief  Retrieves the value stored in the node
 * @return The value stored in the rectangle
 */
template <typename T>
T Node<T>::getValue() const {
    return value;
}


/**
 * @brief Retrieves the pointer to the next node in the linked list
 * @return Pointer to next node in the linked list
 */
template <typename T> 
Node<T> *Node<T>::getNext() const {
    return next;
}


/**
 * @brief Sets the next node in the linked list
 * @param *n pointer to the node to set
 */
template <typename T>
void Node<T>::setNext(Node<T> *n) {
    next = n;
}
