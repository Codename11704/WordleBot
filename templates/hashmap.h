/**
 * This file contains an implementation for a HashMap class
 * with functionality for generic types. Behavior is undefinded if the 
 * provided hash function or equal function are not functional
 * 
 * @author Sean Droll
 */

#include "hashentry.h"
#include "linkedlist.h"

const int INITIAL_CAPACITY = 16;
const double THRESHOLD = .75;
const int RESIZE_SCALAR = 2;

/**
 * @class HashMap
 * @brief Stores key value pairs with efficient lookup
 * 
 * Hashmap provides a way to store, retrieve,
 * and remove key value pairs with efficient lookup times
 * given the provided hash function is efficient
 */
template <typename K, typename V>
class HashMap {
    private:
        HashEntry<K, V> **arr;
        int capacity;
        int utilization;
        HashEntry<K, V> *tombstone;
        int (* hash)(K k);
        bool (*equals)(K k1, K k2);
        void resize();
        int probe(int index);
    public:
        HashMap(int (* hash)(K k), bool (*equals)(K k1, K k2));
        ~HashMap();
        void put(K k, V v);
        V get(K k);
        V remove(K k);
        int size();
};

/**
 * @brief Constructs a hashmap of default length. Behavior is undefined if the hash function or equals function does not work.
 * @param h hash function to hash the key and provide an index for the entry
 * @param eq returns true if both keys are equal
 */
template <typename K, typename V>
HashMap<K, V>::HashMap(int (* h)(K k), bool (*eq)(K k1, K k2)) {
    capacity = INITIAL_CAPACITY;
    utilization = 0;
    tombstone = reinterpret_cast<HashEntry*>(-1);
    arr = new HashEntry<K, V>*[capacity]();
    hash = h;
    equals = eq;
}

/**
 * @brief Deconstructs the hashmap and all nodes contained in it
 */
template <typename K, typename V>
HashMap<K, V>::~HashMap() {
    for(int i = 0; i < capacity; i++) {
        if(arr[i] == nullptr) continue;
        delete arr[i];
    }
    delete[] arr;
}

/**
 * @brief Stores a Key Value pair in the hashmap
 * @param k key to be stored
 * @param v value to be stored
 */
template <typename K, typename V>
void HashMap<K, V>::put(K k, V v) {
    int index = hash(k) % capacity;
    HashEntry<K, V> *node = new HashEntry(k, v);
    while(arr[index] != nullptr) {
        if(equals(arr[index]->getKey(), k)) {
            arr[index]->setValue(v);
            return;
        }
        index = probe(index) % capacity;
    }
    utilization++;
    arr[index] = node;
    if((((double) utilization) / ((double) capacity)) >= THRESHOLD) resize();
}

/**
 * @brief Retrieves a value based on the given key
 * @param k the key in which to find the matching value pair
 * @return the matching value
 */
template <typename K, typename V>
V HashMap<K, V>::get(K k) {
    int index = hash(k) % capacity;
    while(arr[index] != nullptr && !equals(k, arr[index]->getKey())) {
        index = probe(index) % capacity;
    }
    if(arr[index] == nullptr) return V();
    return arr[index]->getValue();
}

/**
 * @brief Removes a value from the hashtable
 * @param k the key in which to remove the value from
 * @return the matching value
 */
template <typename K, typename V>
V HashMap<K, V>::remove(K k) {
    int index = hash(k) % capacity;
    while(arr[index] != nullptr && !equals(k, arr[index]->getKey())) {
        index = probe(index) % capacity;
    }
    if(arr[index] == nullptr) return V();
    V val = arr[index]->getValue();
    delete arr[index];
    arr[index] = tombstone;
    utilization--;
    return val;
}

/**
 * @brief retrieves the current utilization in the hashtable
 * @return the number of key value pairs stored in the table
 */
template <typename K, typename V>
int HashMap<K, V>::size() {
    return utilization;
}

/**
 * @brief resizes the hashtable based off RESIZE_SCALAR
 */
template <typename K, typename V>
void HashMap<K, V>::resize() {
    int new_capacity = capacity*RESIZE_SCALAR;
    HashEntry<K, V> **new_arr = new HashEntry<K, V>*[new_capacity]();
    for(int i = 0; i < capacity; i++) {
        if(arr[i] == nullptr || arr[i] == tombstone) continue;
        int index = hash(arr[i]->getKey()) % new_capacity;
        while(new_arr[index] != nullptr) {
            index = probe(index) % new_capacity;
        }
        new_arr[index] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    capacity = new_capacity;
}

/**
 * @brief probes the hashtable for a new index
 * @return a new index based off the old index
 */
template <typename K, typename V>
int HashMap<K, V>::probe(int index) {
    return (index*index);
}
