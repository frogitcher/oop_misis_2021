#pragma once
//#include "map_iterator.h"
#include <cstdint>
#include <vector>

namespace KR383 {
    //template <typename KeyType, typename ValueType>
    
    template <typename KeyType, typename ValueType>
    class UserMap {
    public:
        UserMap() = default;
        UserMap(const UserMap <KeyType,ValueType>& other);
        ValueType& at(const KeyType& key);
        ValueType& operator[](const KeyType& key);


       /* UserMapIterator begin();
        UserMapIterator end();
        UserMapIterator find(const std::pair <KeyType, ValueType> );*/
    private:
        //friend UserMapIterator;
        std::vector <std::pair <KeyType,ValueType> > data;
    };
    template <typename KeyType, typename ValueType>
    UserMap<KeyType,ValueType>::UserMap(const UserMap <KeyType,ValueType>& other) {
        for (auto &pr : other) {
            data.push_back(pr);
        }
    }
    template <typename KeyType, typename ValueType>
    ValueType& UserMap<KeyType,ValueType>::at(const KeyType& key) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].key == key)
                return data[i].value;
        }
        data.push_back(std::pair <KeyType,ValueType>());
    }
    template <typename KeyType, typename ValueType>
    ValueType& UserMap<KeyType,ValueType>::operator[](const KeyType& key) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].key == key)
                return data[i].value;
        }
        data.push_back(std::pair <KeyType,ValueType>());
    }

}