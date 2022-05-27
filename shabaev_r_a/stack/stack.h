
//
// Created by Mac on 09/05/2022.
//

#ifndef PROJECT_STACK_H
#define PROJECT_STACK_H

#include <memory>
#include <initializer_list>



template<class T, class Allocator = std::allocator<T> >
class list{
private:
    struct BaseNode {
        BaseNode* prev = this;
        BaseNode* next = this;
    };

    struct Node : BaseNode {
        T value;

        Node() = default;
        Node(BaseNode* prev, BaseNode* next, const T& value) : BaseNode{prev, next}, value(value) {
        }
        Node(BaseNode* prev, BaseNode* next) : BaseNode{prev, next} {}
        ~Node() = default;
    };
private:
    template<bool is_const>
    class Iterator {
    private:
        using node_type = std::conditional_t<is_const, const BaseNode*, BaseNode*>;
        using Node_type = std::conditional_t<is_const, const Node*, Node*>;
        node_type ptr;

    public:

        node_type get_ptr() const {
            return ptr;
        }

        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = std::conditional_t<is_const, const T*, T*>;
        using reference = std::conditional_t<is_const, const T&, T&>;
        using value_type = std::conditional_t<is_const, const T, T>;

        Iterator() = default;

        ~Iterator() = default;

        Iterator(node_type base_node) : ptr(base_node) {}

        Iterator(const Iterator<false>& iterator) : ptr(iterator.get_ptr()) {

        }

        Iterator& operator=(const Iterator& iterator);

        reference operator*() {
            return static_cast<Node_type>(ptr)->value;
        };

        pointer operator->() {
            return &(static_cast<Node_type>(ptr)->value);
        }

        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy = *this;
            ptr = ptr->next;
            return copy;
        }

        Iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator copy = *this;
            ptr = ptr->prev;
            return copy;
        }

        bool operator!=(const Iterator& it) const {
            return ptr != it.get_ptr();
        }

        bool operator==(const Iterator& it) const {
            return ptr == it.get_ptr();
        }

    };
public:
    using alloc_traits=typename std::allocator_traits<Allocator>::template rebind_traits<Node>;
    using alloc_node = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer =  typename alloc_traits::pointer;
    using const_pointer = typename alloc_traits::const_pointer;
    using iterator = Iterator<0>;
    using const_iterator = Iterator<1>;
    using reverse_iterator=std::reverse_iterator<iterator>;
    using const_reverse_iterator=std::reverse_iterator<const_iterator>;



    explicit list( const Allocator& alloc =Allocator() );

    explicit  list( size_type count, const T& value,
                    const Allocator& alloc = Allocator());

    template< class InputIt >
    list( InputIt first, InputIt last,
          const Allocator& alloc = Allocator() );

    list( const list& other );

    list( const list& other, const Allocator& alloc );

    list( list&& other ) noexcept ;
    list( list&& other, const Allocator& alloc );

    list(std::initializer_list<T> init,
         const Allocator& alloc = Allocator() );

    ~list();

    list& operator=( const list& other );

    list& operator=( std::initializer_list<T> istack );

    list& operator=( list&& other ) noexcept ;

    allocator_type get_allocator() const noexcept;

    reference front();

    const_reference front() const;

    reference back();

    const_reference back() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rcbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator rcend() const noexcept;

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_type size() const noexcept;

    void clear() noexcept;
    iterator insert( const_iterator pos, const T& value );
    iterator insert( const_iterator pos, T&& value );
    iterator insert( const_iterator pos, size_type count, const T& value );
    template< class InputIt >
    iterator insert( const_iterator pos,
                     InputIt first, InputIt last );
    iterator insert( const_iterator pos, std::initializer_list<T> ilist );
    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args );

    iterator erase( const_iterator pos );
    iterator erase( const_iterator first, const_iterator last );

    void push_back( const T& value );
    void push_back( T&& value );
    template< class... Args >
    reference emplace_back( Args&&... args );
    void pop_back();
    void push_front( const T& value );
    void push_front( T&& value );
    template< class... Args >
    reference emplace_front( Args&&... args );
    void pop_front();

    void swap( list& other );

    void splice( const_iterator pos, list& other );
    void splice( const_iterator pos, list& other, const_iterator it );
    void splice( const_iterator pos, list& other,
                 const_iterator first, const_iterator last);

private:

    Allocator alloc;
    BaseNode* _first, *_last;
    size_type _size;
    alloc_node node_allocator=alloc;





};

template<class T, class Allocator>
template<bool is_const>
typename list<T, Allocator>::template Iterator<is_const> &list<T, Allocator>::Iterator<is_const>::operator=(const list::Iterator<is_const> &iterator) {
    ptr = iterator.get_ptr();
    return *this;
}


template<class T, class Allocator>
list<T, Allocator>::list(const Allocator &_alloc): _size(0),  alloc(_alloc){
    _first=alloc_traits::allocate(node_allocator, 1);
    _last=alloc_traits::allocate(node_allocator, 1);
    alloc_traits::construct(node_allocator, static_cast<Node*>(_first), nullptr, _last);
    alloc_traits::construct(node_allocator,static_cast<Node*>(_last), _first, nullptr);
}

template<class T, class Allocator>
list<T, Allocator>::list(list::size_type count, const T &value, const Allocator &alloc):list(alloc) {
    try{
        while(count--){
            push_back(value);
        }
    }catch(...) {
        clear();
        throw;
    }
}

template<class T, class Allocator>
template<class InputIt>
list<T, Allocator>::list(InputIt first, InputIt last, const Allocator &alloc):list(alloc) {
    try{
        while(first!=last){
            push_back(*front());
        }
    }
    catch(...){
        clear();
        throw;
    }
}

template<class T, class Allocator>
list<T, Allocator>::list(const list &other):list(
        list<T, Allocator>::alloc_traits::select_on_container_copy_construction(other.get_allocator())
) {
    try{
        for(const auto &i:other){
            push_back(i);
        }
    }catch(...){
        clear();
        throw;
    }
}

template<class T, class Allocator>
list<T, Allocator>::list(const list &other, const Allocator &alloc):list(alloc) {
    try{
        for(const auto &i:other){
            push_back(i);
        }
    }catch(...){
        clear();
        throw;
    }
}

template<class T, class Allocator>
list<T, Allocator>::list(std::initializer_list<T> init, const Allocator &alloc):list(alloc) {
    try{
        for(const auto &i:init){
            push_back(i);
        }
    }catch(...){
        clear();
        throw;
    }
}

template<class T, class Allocator>
list<T, Allocator>::~list() {
    clear();
}



template<class T, class Allocator>
list<T, Allocator>::list(list &&other) noexcept: list(
        list<T, Allocator>::alloc_traits::select_on_container_copy_construction(other.get_allocator())
){
    swap( other);

}

template<class T, class Allocator>
list<T, Allocator>::list(list &&other, const Allocator &alloc): list(alloc)  {
    if(alloc == other.get_allocator()){
        swap(&other);
    }
    else{
        try{
            for(const auto &i:other){
                push_back(i);
            }
        }catch(...){
            clear();
            throw;
        }

    }

}

template<class T, class Allocator>
list<T, Allocator> &list<T, Allocator>::operator=(const list &other) {
    list<T, Allocator> it(other);
    swap(it);
    return *this;
}

template<class T, class Allocator>
list<T, Allocator> &list<T, Allocator>::operator=(std::initializer_list<T> istack) {
    list<T, Allocator> it(istack);
    swap(it);
    return *this;
}

template<class T, class Allocator>
list<T, Allocator> &list<T, Allocator>::operator=(list &&other)  noexcept {
    swap(other);
    return *this;
}

template<class T, class Allocator>
typename list<T, Allocator>::allocator_type list<T, Allocator>::get_allocator() const noexcept {
    return alloc;
}

template<class T, class Allocator>
typename list<T, Allocator>::reference list<T, Allocator>::front() {
    return _first->value;
}




template<class T, class Allocator>
typename list<T, Allocator>::const_reference list<T, Allocator>::front() const {
    return _first->value;
}

template<class T, class Allocator>
typename list<T, Allocator>::reference list<T, Allocator>::back() {
    return _last->value;
}

template<class T, class Allocator>
typename list<T, Allocator>::const_reference list<T, Allocator>::back() const {
    return _last->value;
}

template<class T, class Allocator>
bool list<T, Allocator>::empty() const noexcept {
    return _size == 0;
}

template<class T, class Allocator>
typename list<T, Allocator>::size_type list<T, Allocator>::size() const noexcept {
    return _size;
}

template<class T, class Allocator>
void list<T, Allocator>::clear() noexcept {
    while(begin()!=end()){
        erase(begin());
    }
    if(_first != nullptr){
        alloc_traits::destroy(node_allocator, static_cast<Node*>(_first));
        alloc_traits::deallocate(node_allocator,static_cast<Node*>(_first), 1);
    }
}

template<class T, class Allocator>
void list<T, Allocator>::push_back(const T &value) {
    insert(end(), value);
}

template<class T, class Allocator>
void list<T, Allocator>::push_back(T &&value) {
    insert(end(), std::forward(value));
}

template<class T, class Allocator>
template<class... Args>
typename list<T, Allocator>::reference list<T, Allocator>::emplace_back(Args &&... args) {
    return emplace(end(), std::forward(args...));
}

template<class T, class Allocator>
void list<T, Allocator>::pop_back() {
    erase(rbegin());
}

template<class T, class Allocator>
void list<T, Allocator>::push_front(T &&value) {
    insert(begin(), std::forward(value));
}

template<class T, class Allocator>
void list<T, Allocator>::push_front(const T &value) {
    insert(begin(), value);
}

template<class T, class Allocator>
template<class... Args>
typename list<T, Allocator>::reference list<T, Allocator>::emplace_front(Args &&... args) {
    return emplace(begin(), std::forward(args...));
}

template<class T, class Allocator>
void list<T, Allocator>::swap(list &other) {
    std::swap(_size, other._size);
    std::swap(_first, other._last);
    std::swap(_last, other._last);
}

template<class T, class Allocator>
void list<T, Allocator>::pop_front() {
    erase(begin());
}



template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(list::const_iterator pos, const T &value) {
    auto it=alloc_traits::allocate(node_allocator, 1);
    alloc_traits::construct(node_allocator, it, const_cast<BaseNode*>(pos.get_ptr()->prev),
                            const_cast<BaseNode*>(pos.get_ptr()), value);
    const_cast<BaseNode*>(pos.get_ptr()->prev)->next=it;
    const_cast<BaseNode*>(pos.get_ptr())->prev=it;
    _size++;
    return it;
}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(list::const_iterator pos, T &&value) {
    auto it=alloc_traits::allocate(node_allocator, 1);
    alloc_traits::construct(node_allocator, it, const_cast<BaseNode*>(pos->prev), const_cast<BaseNode*>(pos), std::forward(value));
    const_cast<BaseNode*>(pos.get_ptr()->prev)->next=it;
    const_cast<BaseNode*>(pos.get_ptr())->prev=it;
    _size++;
    return it;

}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(list::const_iterator pos, list::size_type count, const T &value) {
    if(count == 0) return pos;
    auto it= insert(pos, value);
    --count;
    while(count--){
        insert(pos, value);
    }
    return it;

}

template<class T, class Allocator>
template<class InputIt>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(list::const_iterator pos, InputIt first, InputIt last) {
    if(first==last) return pos;
    auto it = insert(pos, *first);
    while(first!=last){
        insert(pos, *first);
        ++first;
    }
    return it;
}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(list::const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
}

template<class T, class Allocator>
template<class... Args>
typename list<T, Allocator>::iterator list<T, Allocator>::emplace(list::const_iterator pos, Args &&... args) {
    T it(args...);
    return insert(pos, move(it));
}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(list::const_iterator pos) {
    auto it=const_cast<BaseNode*>(pos.get_ptr());
    it->next->prev=pos.get_ptr()->prev;
    it->prev->next=pos.get_ptr()->next;
    auto res=it->next;
    alloc_traits::destroy(node_allocator, static_cast<Node*>(it));
    alloc_traits::deallocate(node_allocator, static_cast<Node*>(it), 1);
    return res;
}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(list::const_iterator first, list::const_iterator last) {
    while(first!=last){
        auto it=first++;
        erase(it);
    }
}

template<class T, class Allocator>
void list<T, Allocator>::splice(list::const_iterator pos, list &other) {
    splice(pos, other, other.begin(), other.end());
}

template<class T, class Allocator>
void list<T, Allocator>::splice(list::const_iterator pos, list &other, list::const_iterator it) {
    splice(pos, other, it, other.end());
}

template<class T, class Allocator>
void list<T, Allocator>::splice(list::const_iterator pos, list &other, list::const_iterator first,
                                list::const_iterator last) {
    auto prelast=last.get_ptr()->prev;
    auto prepos=pos.get_ptr()->prev;
    const_cast<BaseNode*>(first.get_ptr())->prev->next=const_cast<BaseNode*>(last.get_ptr());
    const_cast<BaseNode*>(last.get_ptr())->prev=const_cast<BaseNode*>(first.get_ptr()->prev);
    prelast->next=prepos->next;
    prepos->next->prev=prelast;
    prepos->next=const_cast<BaseNode*>(first.get_ptr());
    const_cast<BaseNode*>(first.get_ptr())->prev=prepos;

}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::begin() noexcept {
    return iterator(_first->next);
}

template<class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::begin() const noexcept {
    return const_iterator(_first->next);
}

template<class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::cbegin() const noexcept {
    return const_iterator(_first->next);
}

template<class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::end() noexcept {
    return iterator(_last);
}

template<class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::end() const noexcept {
    return const_iterator(_last);
}

template<class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::cend() const noexcept {
    return const_iterator(_last);
}

template<class T, class Allocator>
typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin() noexcept {
    return reverse_iterator(end());
}

template<class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rcbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<class T, class Allocator>
typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rend() noexcept {
    return reverse_iterator(begin());
}

template<class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template<class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rcend() const noexcept {
    return const_reverse_iterator(begin());
}


#endif //PROJECT_STACK_H