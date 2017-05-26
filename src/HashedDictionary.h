#pragma once

#include "DictionaryInterface.h"
#include "HashedEntry.h"
#include <exception>
#include <unordered_map>
#include <vector>


#define DEFAULT_SIZE 101

/**
 *
 * This Hash table is of fixed max size 101
 */
template<class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType> **hashTable;  // Array of pointers to entries
    int itemCount;
    int hashTableSize; //Default value should be assigned to 101

    int getHashIndex(const KeyType &itemKey) const;

    void destroyDictionary();

public:
//TODO Implement the necessary functions.

    virtual ~HashedDictionary();

    HashedDictionary();

    bool isEmpty() const override;

    int getNumberOfItems() const override;

    bool add(const KeyType &searchKey, const ItemType &newItem) override;

    bool remove(const KeyType &searchKey) override;

    void clear() override;

    ItemType getItem(const KeyType &searchKey) const override;

    bool contains(const KeyType &searchKey) const override;

    void traverse(void (*visit)(ItemType &)) const override;

    std::vector<ItemType> toVector() const override;

    HashedEntry<KeyType, ItemType>& operator[](KeyType key);


};

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &key) const {
    return static_cast<int>(key % hashTableSize);
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
        : itemCount(0), hashTableSize(DEFAULT_SIZE) {
    hashTable = new HashedEntry<KeyType, ItemType> *[DEFAULT_SIZE];
    for (int i = 0; i < DEFAULT_SIZE; i++)
        hashTable[i] = nullptr;
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::destroyDictionary() {
    hashTable = new HashedEntry<KeyType, ItemType> *[DEFAULT_SIZE];
    itemCount = 0;
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary() {
    destroyDictionary();
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear() {
    destroyDictionary();
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const {
    return (itemCount == 0);
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const {
    return itemCount;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem) {
    HashedEntry<KeyType, ItemType> *addPtr = new HashedEntry<KeyType, ItemType>(searchKey, newItem);

    int itemHashIndex = getHashIndex(searchKey);

    if(hashTable[itemHashIndex] == nullptr) {
        hashTable[itemHashIndex] = addPtr;
        itemCount++;
    } else {
        addPtr->setNext(hashTable[itemHashIndex]);
        hashTable[itemHashIndex] = addPtr;
        itemCount++;
    }
    return true;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) {
    bool itemFound = false;

    int itemHashIndex = getHashIndex(searchKey);

    if(hashTable[itemHashIndex] != nullptr) {
        if(searchKey == hashTable[itemHashIndex]->getKey()) {
            HashedEntry <KeyType, ItemType> *removePtr = hashTable[itemHashIndex];
            hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
            delete removePtr;

            removePtr = nullptr;
            itemFound = true;
            itemCount--;
        } else {
            HashedEntry<KeyType, ItemType> *prevPtr = hashTable[itemHashIndex];
            HashedEntry<KeyType, ItemType> *curPtr = prevPtr->getNext();
            while((curPtr != nullptr) && !itemFound) {
                if(searchKey == curPtr->getKey()) {
                    prevPtr->setNext (curPtr->getNext());
                    delete curPtr;

                    curPtr = nullptr;
                    itemFound = true;
                } else {
                    prevPtr = curPtr;
                    curPtr = curPtr->getNext();
                }
            }
            itemCount--;
        }
    }
    return itemFound;
}

template<class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const {
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType> *curPtr = hashTable[itemHashIndex];
    while(curPtr != nullptr) {
        if(searchKey == curPtr->getKey()) {
            return curPtr->getItem();
        } else {
            curPtr = curPtr->getNext();
        }
    }
    throw std::exception();
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType &searchKey) const {
    int itemHashIndex = getHashIndex(searchKey);
    if(hashTable[itemHashIndex] != nullptr && hashTable[itemHashIndex]->getKey() == searchKey) {
        return true;
    }
    return false;
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void (*visit)(ItemType &)) const {
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            visit(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
}

template<class KeyType, class ItemType>
std::vector<ItemType> HashedDictionary<KeyType, ItemType>::toVector() const {
    std::vector<ItemType> returnVector;
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            returnVector.push_back(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
    return returnVector;
};

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>& HashedDictionary<KeyType, ItemType>::operator[](KeyType searchKey){
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[itemHashIndex];

    // Short circuit evaluation is important here
    while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey())) {
        chainPtr = chainPtr->getNext();
    } // end while

    if (chainPtr == nullptr)
        throw std::exception();

    return *chainPtr;
}
