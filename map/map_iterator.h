#pragma once
#include "map_iterator.h"

namespace KR383 {
    //template <typename KeyType, typename ValueType>
    
    template <typename KeyType, typename ValueType>
    class UserMapIterator {
    public:
        UserMapIterator(const vector<pair<KeyType,ValueType>>& new_data,const ptrdiff_t& id);
        std::pair <KeyType,ValueType>& operator*();
    private:
        vector<pair<KeyType,ValueType>>* data;
        ptrdiff_t id;
    };
    template <typename KeyType, typename ValueType>
    UserMapIterator(const vector<pair<KeyType,ValueType>>& new_data, const ptrdiff_t new_id) {
        id = new_id
    }

    template <typename KeyType, typename ValueType>
    std::pair <KeyType,ValueType>& UserMapIterator<KeyType,ValueType>::operator*() {
        return 
    }


}