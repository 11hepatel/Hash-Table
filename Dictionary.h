
 /*Instructions:
 * Implement the MyUnorderedMap class, which should implement a hash table of MyPair objects.
 * You can choose a type of in-table closed hashing for collision management, 
 * and chose how to manage delete (e.g., tombstones).
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "MyPair.h"


template <typename K, typename V>
class Dictionary
{
    public:
        // Should only update, but not insert
        // Should throw std::out_of_range exception
        virtual V & at(const K &key) = 0;
    
        // Updates or inserts
        virtual V & operator[](const K &key) = 0;

        virtual bool empty() const = 0;

        virtual int size() const = 0;

        virtual void clear() = 0;

        virtual void insert(const MyPair<K, V> &init_pair) = 0;

        // The version that removes by key
        virtual void erase(const K &key) = 0;

        // Not exactly like the std:: version, but similar.
        virtual MyPair<K, V> * find(const K &key) const = 0; 

        // Not actually std:: (see h file)
        virtual void print() const = 0;
        
        virtual int count(const K &key) const = 0;
};

#endif

