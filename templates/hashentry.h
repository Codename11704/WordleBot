/**
 * This file contains functionality for a HashEntry class,
 * which is to be used to store an entry in a hash data structure
 * 
 * @author Sean Droll
 */

/**
 * @class HashEntry
 * @brief Stores a Key Value pair to be stored in a hash data structure
 * 
 * This class provides value for retrieving a key value pair
 */

#ifndef WORDLEBOT_TEMPLATES_HASHENTRY_H_
#define WORDLEBOT_TEMPLATES_HASHENTRY_H_

template <typename K, typename V>
class HashEntry {
    private:
        K key;
        V value;
    public:
        HashEntry(K k, V v);
        K getKey() const;
        V getValue() const;
        void setValue(V v);
};

/**
 * @brief Constructs a new HashEntry class
 * @param k key to be stored in entry
 * @param v value to be stored in entry
 */
template <typename K, typename V>
HashEntry<K, V>::HashEntry(K k, V v) {
    key = k;
    value = v;
}

/**
 * @brief retrieves the key stored in the entry
 * @return the key stored in the entry
 */
template <typename K, typename V>
K HashEntry<K, V>::getKey() const {
    return key;
}

/**
 * @brief retrieves the value stored in the entry
 * @return the value stored in the entry
 */
template <typename K, typename V>
V HashEntry<K, V>::getValue() const {
    return value;
}

/**
 * @brief sets the value stored in the entry
 * @param v the value to be stored
 */
template <typename K, typename V>
void HashEntry<K, V>::setValue(V v) {
    value = v;
}

#endif