#pragma once
#include "map_iterator.h"

namespace KR383 {
    //template <typename KeyType, typename ValueType>
    
    template <typename KeyType, typename ValueType>
    class UserMapIterator {
    public:
        UserMapIterator(const std::vector::iterator& new_iter);
        std::pair <KeyType,ValueType>& operator*();
    private:
        std::vector::iterator iter;
    };
    template <typename KeyType, typename ValueType>
    UserMapIterator(const std::vector::iterator& new_iter) {
        iter = new_iter;
    }

    template <typename KeyType, typename ValueType>
    std::pair <KeyType,ValueType>& UserMapIterator<KeyType,ValueType>::operator*() {
        return iter*;
    }


}