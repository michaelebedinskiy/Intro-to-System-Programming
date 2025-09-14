
#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
        struct Node {
            T m_data;
            Node* m_next = nullptr;
            explicit Node(const T& data, Node* next = nullptr)
                : m_data(data), m_next(next) {}
        };
        Node* m_head = nullptr;
        void deleteData();
    public:
        SortedList() = default;
        SortedList(const SortedList& other);
        SortedList& operator=(const SortedList& other);
        ~SortedList();
        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;
        void insert(const T& element);
        void remove(const ConstIterator& iterator);
        int length() const;

        template<class Condition>
        SortedList<T> filter(Condition c) const;

        template<class Action>
        SortedList<T> apply(Action a) const;
    };

    template <class T>
    SortedList<T>::SortedList(const SortedList& other) : m_head(nullptr) {
        try {
            Node* current = other.m_head;
            while (current) {
                insert(current->m_data);
                current = current->m_next;
            }
        } catch (...) {
            deleteData();
            throw;
        }
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList& other) {
        if (this == &other) {
            return *this;
        }
        SortedList<T> temp(other);
        deleteData();
        m_head = temp.m_head;
        temp.m_head = nullptr;
        return *this;
    }

    template <class T>
    template<class Condition>
    SortedList<T> SortedList<T>::filter(Condition c) const {
        SortedList<T> result;
        Node* current = m_head;
        while (current) {
            if (c(current->m_data)) {
                result.insert(current->m_data);
            }
            current = current->m_next;
        }
        return result;
    }

    template <class T>
    template<class Action>
    SortedList<T> SortedList<T>::apply(Action a) const {
        SortedList<T> result;
        Node* current = m_head;
        while (current) {
            result.insert(a(current->m_data));
            current = current->m_next;
        }
        return result;
    }

    template <class T>
    class SortedList<T>::ConstIterator {
        const Node* current;
        const SortedList* list;
    public:
        ConstIterator() = delete;

        ConstIterator(const Node* node, const SortedList* list) :
            current(node), list(list) {}

        ConstIterator(const ConstIterator& other) = default;

        ConstIterator& operator=(const ConstIterator& other) = default;

        ~ConstIterator() = default;

        ConstIterator& operator++();

        bool operator!=(const ConstIterator& other) const;

        const T& operator*() const;

        friend class SortedList<T>;
    };

    template <class T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(m_head, this);
    }

    template <class T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(nullptr, this);
    }

    template <class T>
    void SortedList<T>::insert(const T& element) {
        Node* newNode = new Node(element);

        if (!m_head || element > m_head->m_data) {
            newNode->m_next = m_head;
            m_head = newNode;
        } else {
            Node* current = m_head;
            while (current->m_next && current->m_next->m_data > element) {
                current = current->m_next;
            }
            newNode->m_next = current->m_next;
            current->m_next = newNode;
        }
    }

    template <class T>
    void SortedList<T>::remove(const SortedList::ConstIterator& iterator) {
        if (!iterator.current || iterator.list !=  this) {
            return;
        }
        const Node* toRemove = iterator.current;
        if (toRemove == m_head) {
            Node* temp = m_head;
            m_head = m_head->m_next;
            delete temp;
            return;
        }
        Node* current = m_head;
        while (current->m_next && current->m_next != toRemove) {
            current = current->m_next;
        }
        if (current->m_next) {
            Node* temp = current->m_next;
            current->m_next = current->m_next->m_next;
            delete temp;
        }
    }

    template <class T>
    int SortedList<T>::length() const {
        int counter = 0;
        Node* current = m_head;
        while (current) {
            counter++;
            current = current->m_next;
        }
        return counter;
    }

    template <class T>
    SortedList<T>::~SortedList() {
        deleteData();
    }

    template <class T>
    void SortedList<T>::deleteData() {
        Node* current = m_head;
        while (current) {
            Node* temp = current;
            current = current->m_next;
            delete temp;
        }
        m_head = nullptr;
    }

    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
        if (!current) {
            throw std::out_of_range("");
        }
        current = current->m_next;
        return *this;
    }

    template <class T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
        return current != other.current;
    }

    template <class T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        if (!current) {
            throw std::out_of_range("");
        }
        return current->m_data;
    }

}
