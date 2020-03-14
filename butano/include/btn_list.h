#ifndef BTN_LIST_H
#define BTN_LIST_H

#include "btn_pool.h"
#include "btn_iterator.h"
#include "btn_algorithm.h"
#include "btn_list_fwd.h"

namespace btn
{

template<typename Type>
class ilist
{

protected:
    class node_type
    {

    public:
        node_type* prev = nullptr;
        node_type* next = nullptr;
    };

    class value_node_type : public node_type
    {

    public:
        Type value;

        template<typename... Args>
        value_node_type(Args&&... args) :
            value(forward<Args>(args)...)
        {
        }
    };

public:
    using value_type = Type;
    using size_type = int;
    using reference = Type&;
    using const_reference = const Type&;
    using pointer = Type*;
    using const_pointer = const Type*;

    class iterator
    {

    public:
        iterator& operator++()
        {
            BTN_ASSERT(_node, "Node is null");

            _node = _node->next;
            return *this;
        }

        iterator& operator--()
        {
            BTN_ASSERT(_node, "Node is null");

            _node = _node->prev;
            return *this;
        }

        [[nodiscard]] const_reference operator*() const
        {
            BTN_ASSERT(_node, "Node is null");

            return static_cast<const value_node_type*>(_node)->value;
        }

        [[nodiscard]] reference operator*()
        {
            BTN_ASSERT(_node, "Node is null");

            return static_cast<value_node_type*>(_node)->value;
        }

        const_pointer operator->() const
        {
            BTN_ASSERT(_node, "Node is null");

            return &static_cast<const value_node_type*>(_node)->value;
        }

        pointer operator->()
        {
            BTN_ASSERT(_node, "Node is null");

            return &static_cast<value_node_type*>(_node)->value;
        }

        [[nodiscard]] friend bool operator==(const iterator& a, const iterator& b)
        {
            return a._node == b._node;
        }

        [[nodiscard]] friend bool operator!=(const iterator& a, const iterator& b)
        {
            return ! (a == b);
        }

    private:
        friend class ilist;
        friend class const_iterator;

        node_type* _node = nullptr;

        explicit iterator(node_type* node) :
            _node(node)
        {
        }
    };

    class const_iterator
    {

    public:
        const_iterator(iterator it) :
            _node(it._node)
        {
        }

        const_iterator& operator++()
        {
            BTN_ASSERT(_node, "Node is null");

            _node = _node->next;
            return *this;
        }

        const_iterator& operator--()
        {
            BTN_ASSERT(_node, "Node is null");

            _node = _node->prev;
            return *this;
        }

        [[nodiscard]] const_reference operator*() const
        {
            BTN_ASSERT(_node, "Node is null");

            return static_cast<const value_node_type*>(_node)->value;
        }

        const_pointer operator->() const
        {
            BTN_ASSERT(_node, "Node is null");

            return &static_cast<const value_node_type*>(_node)->value;
        }

        [[nodiscard]] friend bool operator==(const const_iterator& a, const const_iterator& b)
        {
            return a._node == b._node;
        }

        [[nodiscard]] friend bool operator!=(const const_iterator& a, const const_iterator& b)
        {
            return ! (a == b);
        }

    private:
        friend class ilist;

        const node_type* _node = nullptr;

        explicit const_iterator(const node_type* node) :
            _node(node)
        {
        }
    };

    using reverse_iterator = btn::reverse_iterator<iterator>;
    using const_reverse_iterator = btn::reverse_iterator<const_iterator>;

    ilist(const ilist& other) = delete;

    ilist& operator=(const ilist& other)
    {
        if(this != &other)
        {
            BTN_ASSERT(other.size() <= max_size(), "Not enough space in list: ", max_size(), " - ", other.size());

            clear();
            _assign(other);
        }

        return *this;
    }

    ilist& operator=(ilist&& other)
    {
        if(this != &other)
        {
            BTN_ASSERT(other.size() <= max_size(), "Not enough space in list: ", max_size(), " - ", other.size());

            clear();
            _assign(move(other));
        }

        return *this;
    }

    [[nodiscard]] size_type size() const
    {
        return _ipool->size();
    }

    [[nodiscard]] size_type max_size() const
    {
        return _ipool->max_size();
    }

    [[nodiscard]] bool empty() const
    {
        return _ipool->empty();
    }

    [[nodiscard]] bool full() const
    {
        return _ipool->full();
    }

    [[nodiscard]] size_type available() const
    {
        return _ipool->available();
    }

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(_first_node.next);
    }

    [[nodiscard]] iterator begin()
    {
        return iterator(_first_node.next);
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator(&_last_node);
    }

    [[nodiscard]] iterator end()
    {
        return iterator(&_last_node);
    }

    [[nodiscard]] const_iterator cbegin() const
    {
        return const_iterator(_first_node.next);
    }

    [[nodiscard]] const_iterator cend() const
    {
        return const_iterator(&_last_node);
    }

    [[nodiscard]] const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    [[nodiscard]] reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    [[nodiscard]] const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    [[nodiscard]] reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    [[nodiscard]] const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(cend());
    }

    [[nodiscard]] const_reverse_iterator crend() const
    {
        return const_reverse_iterator(cbegin());
    }

    [[nodiscard]] const_reference front() const
    {
        BTN_ASSERT(! empty(), "List is empty");

        return static_cast<const value_node_type*>(_first_node.next)->value;
    }

    [[nodiscard]] reference front()
    {
        BTN_ASSERT(! empty(), "List is empty");

        return static_cast<value_node_type*>(_first_node.next)->value;
    }

    [[nodiscard]] const_reference back() const
    {
        BTN_ASSERT(! empty(), "List is empty");

        return static_cast<const value_node_type*>(_last_node.prev)->value;
    }

    [[nodiscard]] reference back()
    {
        BTN_ASSERT(! empty(), "List is empty");

        return static_cast<value_node_type*>(_last_node.prev)->value;
    }

    void push_front(const_reference value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(value);
        _insert(begin(), new_node);
    }

    void push_front(value_type&& value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(move(value));
        _insert(begin(), new_node);
    }

    template<typename... Args>
    void emplace_front(Args&&... args)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(forward<Args>(args)...);
        _insert(begin(), new_node);
    }

    void push_back(const_reference value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(value);
        _insert(end(), new_node);
    }

    void push_back(value_type&& value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(move(value));
        _insert(end(), new_node);
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(forward<Args>(args)...);
        _insert(end(), new_node);
    }

    void pop_front()
    {
        BTN_ASSERT(! empty(), "List is empty");

        _erase(begin());
    }

    void pop_back()
    {
        BTN_ASSERT(! empty(), "List is empty");

        iterator it = end();
        --it;
        _erase(it);
    }

    iterator insert(const_iterator position, const_reference value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(value);
        _insert(const_cast<iterator>(position), new_node);
        return iterator(&new_node);
    }

    iterator insert(const_iterator position, value_type&& value)
    {
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(move(value));
        _insert(const_cast<iterator>(position), new_node);
        return iterator(&new_node);
    }

    template<typename... Args>
    iterator emplace(const_iterator position, Args&&... args)
    {
        BTN_ASSERT(position >= begin() && position <= end(), "Invalid position");
        BTN_ASSERT(! full(), "List is full");

        node_type& new_node = _ipool->create(forward<Args>(args)...);
        _insert(const_cast<iterator>(position), new_node);
        return iterator(&new_node);
    }

    iterator erase(const_iterator position)
    {
        BTN_ASSERT(! empty(), "List is empty");

        iterator non_const_position = const_cast<iterator>(position);
        iterator next = non_const_position;
        ++next;
        _erase(non_const_position);
        return next;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        auto erase_first = const_cast<iterator>(first);
        auto erase_last = const_cast<iterator>(last);
        iterator erase_it = erase_first;

        while(erase_it != erase_last)
        {
            iterator next = erase_it;
            ++next;
            _erase(erase_it);
            erase_it = next;
        }

        return erase_it;
    }

    friend void erase(ilist& list, const_reference value)
    {
        iterator it = list.begin();
        iterator last = list.end();

        while(it != last)
        {
            if(*it == value)
            {
                iterator next = it;
                ++next;
                list._erase(it);
                it = next;
            }
            else
            {
                ++it;
            }
        }
    }

    template<class Pred>
    friend void erase_if(ilist& list, const Pred& pred)
    {
        iterator it = list.begin();
        iterator last = list.end();

        while(it != last)
        {
            if(pred(*it))
            {
                iterator next = it;
                ++next;
                list._erase(it);
                it = next;
            }
            else
            {
                ++it;
            }
        }
    }

    void assign(size_type count, const_reference value)
    {
        BTN_ASSERT(count >= 0 && count <= max_size(), "Invalid count: ", count, " - ", max_size());

        iterator last = end();
        clear();

        for(size_type index = 0; index < count; ++index)
        {
            node_type& new_node = _ipool->create(value);
            _insert(last, new_node);
        }
    }

    template<typename Iterator>
    void assign(const Iterator& first, const Iterator& last)
    {
        iterator input_last = end();
        clear();

        for(Iterator it = first; it != last; ++it)
        {
            BTN_ASSERT(! full(), "List is full");

            node_type& new_node = _ipool->create(*it);
            _insert(input_last, new_node);
        }
    }

    void swap(ilist& other)
    {
        if(this != &other)
        {
            BTN_ASSERT(size() <= other.max_size(), "Invalid size: ", size(), " - ", other.max_size());
            BTN_ASSERT(max_size() <= other.size(), "Invalid max size: ", max_size(), " - ", other.size());

            ilist* min_list;
            ilist* max_list;

            if(size() < other.size())
            {
                min_list = *this;
                max_list = &other;
            }
            else
            {
                min_list = *other;
                max_list = &this;
            }

            iterator min_iterator = min_list->begin();
            iterator min_end = min_list->end();
            iterator max_iterator = max_list->begin();
            iterator max_end = max_list->end();

            while(min_iterator != min_end)
            {
                btn::swap(*min_iterator, *max_iterator);
                ++min_iterator;
                ++max_iterator;
            }

            while(max_iterator != max_end)
            {
                node_type& min_new_node = min_list->_ipool->create(move(*max_iterator));
                min_list->_insert(min_end, min_new_node);

                iterator max_next = max_iterator;
                ++max_next;
                max_list->_erase(max_iterator);
                max_iterator = max_next;
            }
        }
    }

    friend void swap(ilist& a, ilist& b)
    {
        a.swap(b);
    }

    void clear()
    {
        iterator it = begin();
        iterator last = end();

        while(it != last)
        {
            node_type* node = it._node;
            ++it;
            _ipool->destroy(static_cast<value_node_type&>(*node));
        }

        _first_node.next = &_last_node;
        _last_node.prev = &_first_node;
    }

    [[nodiscard]] friend bool operator==(const ilist& a, const ilist& b)
    {
        if(a.size() != b.size())
        {
            return false;
        }

        return equal(a.begin(), a.end(), b.begin());
    }

    [[nodiscard]] friend bool operator!=(const ilist& a, const ilist& b)
    {
        return ! (a == b);
    }

    [[nodiscard]] friend bool operator<(const ilist& a, const ilist& b)
    {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    [[nodiscard]] friend bool operator>(const ilist& a, const ilist& b)
    {
        return b < a;
    }

    [[nodiscard]] friend bool operator<=(const ilist& a, const ilist& b)
    {
        return ! (a > b);
    }

    [[nodiscard]] friend bool operator>=(const ilist& a, const ilist& b)
    {
        return ! (a < b);
    }

protected:
    ipool<value_node_type>* _ipool;
    node_type _first_node;
    node_type _last_node;

    explicit ilist(ipool<value_node_type>& ipool) :
        _ipool(&ipool)
    {
        _first_node.next = &_last_node;
        _last_node.prev = &_first_node;
    }

    void _assign(const ilist& other)
    {
        iterator last = end();

        for(const_reference value : other)
        {
            node_type& new_node = _ipool->create(move(value));
            _insert(last, new_node);
        }
    }

    void _assign(ilist&& other)
    {
        iterator last = end();

        for(reference value : other)
        {
            node_type& new_node = _ipool->create(move(value));
            _insert(last, new_node);
        }

        other.clear();
    }

    void _insert(iterator position, node_type& new_node)
    {
        node_type* position_node = position._node;
        node_type* prev_node = position_node->prev;
        prev_node->next = &new_node;
        new_node.prev = prev_node;
        new_node.next = position_node;
        position_node->prev = &new_node;
    }

    void _erase(iterator position)
    {
        node_type* position_node = position._node;
        node_type* prev_node = position_node->prev;
        node_type* next_node = position_node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        _ipool->destroy(static_cast<value_node_type&>(*position_node));
    }
};


template<typename Type, int MaxSize>
class list : public ilist<Type>
{
    static_assert(MaxSize > 0);

public:
    using value_type = Type;
    using size_type = int;
    using reference = Type&;
    using const_reference = const Type&;
    using pointer = Type*;
    using const_pointer = const Type*;
    using iterator = typename ilist<Type>::iterator;
    using const_iterator = typename ilist<Type>::const_iterator;
    using reverse_iterator = typename ilist<Type>::reverse_iterator;
    using const_reverse_iterator = typename ilist<Type>::const_reverse_iterator;

    list() :
        ilist<Type>(_pool)
    {
    }

    list(const list& other) :
        list()
    {
        this->_assign(other);
    }

    list& operator=(const list& other)
    {
        if(this != &other)
        {
            this->clear();
            this->_assign(other);
        }

        return *this;
    }

    list(list&& other) :
        list()
    {
        this->_assign(move(other));
    }

    list& operator=(list&& other)
    {
        if(this != &other)
        {
            this->clear();
            this->_assign(move(other));
        }

        return *this;
    }

    ~list()
    {
        this->clear();
    }

private:
    pool<typename ilist<Type>::value_node_type, MaxSize> _pool;
};

}

#endif