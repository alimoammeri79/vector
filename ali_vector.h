//
// Created by Ali Moameri on 4/10/22.
//

#ifndef ALI_VECTOR_H
#define ALI_VECTOR_H

#include <cstddef>
#include <exception>
#include <algorithm>

namespace ali {
    template <class T> class vector {
    public:
        vector()
                : m_size{0}, m_capacity{0}, ptr{nullptr} {}

        explicit vector(const std::size_t& _size)
                : m_size{_size}, m_capacity{_size * 2} {
            ptr = m_alloc.allocate(m_capacity);
        }

        explicit vector(const std::size_t& _size, const T& value)
                : m_size{_size}, m_capacity{_size * 2} {
            ptr = m_alloc.allocate(m_capacity);
            for(std::size_t i{0}; i < m_size; ++i)
                ptr[i] = value;
        }

        vector(const std::initializer_list<T>& ls)
                : m_size{ls.size()}, m_capacity{ls.size() * 2} {
            ptr = m_alloc.allocate(m_capacity);
            std::copy(ls.begin(), ls.end(), ptr);
        }

        vector(const ali::vector<T>& rhs)
                :m_size{rhs.size()}, m_capacity{rhs.capacity()} {
            ptr = m_alloc.allocate(m_capacity);
            std::copy(rhs.ptr, rhs.ptr + rhs.size(), ptr);
        }

        vector(ali::vector<T>&& rhs) noexcept
                :m_size{rhs.size()}, m_capacity{rhs.capacity()} {
            ptr = m_alloc.allocate(m_capacity);
            std::copy(rhs.ptr, rhs.ptr + rhs.size(), ptr);
            rhs.clear();
            m_capacity = 0;
        }

        ~vector() { m_alloc.deallocate(ptr, m_capacity); }

        [[nodiscard]] constexpr std::size_t size() const noexcept { return m_size; }
        [[nodiscard]] constexpr std::size_t capacity() const noexcept { return m_capacity; }

        void clear() noexcept {
            delete[] ptr;
            ptr = nullptr;
            m_size = 0;
        }

        void push_back(const T& value) {
            std::size_t new_size{m_size + 1};
            if(new_size > m_capacity)
            {
                std::size_t new_capacity {new_size * 2};
                T* new_ptr{m_alloc.allocate(new_capacity)};
                std::copy(ptr, ptr + m_size, new_ptr);
                m_alloc.deallocate(ptr, m_capacity);
                m_capacity = new_capacity;
                ptr = new_ptr;
            }
            ptr[m_size++] = value;
        }


        void pop_back() {
            m_size = m_size > 0 ? m_size - 1 : m_size;
        }

        T& at(std::size_t index) {
            if (index < m_size)
                return ptr[index];
            else
                throw std::out_of_range("index out of range");
        }

        const T& at(std::size_t index) const {
            if (index < m_size)
                return ptr[index];
            else
                throw std::out_of_range("index out of range");
        }

        void shrink_to_fit() {
            if (m_size < m_capacity) {
                T* new_ptr{m_alloc.allocate(m_size)};
                std::copy(ptr, ptr + m_size, new_ptr);
                m_alloc.deallocate(ptr, m_capacity);
                ptr = new_ptr;
                m_capacity = m_size;
            }
        }

        void reserve(std::size_t capacity) {
            if (capacity > m_capacity) {
                T* new_ptr{m_alloc.allocate(capacity)};
                std::copy(ptr, ptr + m_size, new_ptr);
                m_alloc.deallocate(ptr, m_capacity);
                ptr = new_ptr;
                m_capacity = capacity;
            }
        }

        [[nodiscard]] bool empty() const { return size() == 0; }

        void swap(ali::vector<T>& rhs) {
            std::swap(m_size, rhs.m_size);
            std::swap(m_capacity, rhs.m_capacity);
            std::swap(m_alloc, rhs.m_alloc);
            std::swap(ptr, rhs.ptr);
        }

        T& operator[](const std::size_t& index) {
            if(index >= size())
                throw std::out_of_range("out of range index");
            else
                return ptr[index];
        }

        const T& operator[](const std::size_t& index) const {
            if(index >= size())
                throw std::out_of_range("out of range index");
            else
                return ptr[index];
        }

        ali::vector<T>& operator=(const ali::vector<T>& rhs) noexcept {
            m_size = rhs.size();
            T* new_ptr{m_alloc.allocate(rhs.capacity())};
            std::copy(rhs.ptr, rhs.ptr + rhs.size(), new_ptr);
            m_alloc.deallocate(ptr, m_capacity);
            m_capacity = rhs.capacity();
            ptr = new_ptr;
            return *this;
        }

        ali::vector<T>& operator=(ali::vector<T>&& rhs) noexcept {
            T* new_ptr{m_alloc.allocate(rhs.capacity())};
            std::copy(rhs.ptr, rhs.ptr + rhs.size(), new_ptr);
            m_alloc.deallocate(ptr, m_capacity);
            m_size = rhs.size();
            m_capacity = rhs.capacity();
            ptr = new_ptr;
            rhs.clear();
            return *this;
        }

        bool operator==(const vector &rhs) const {
            if (m_size != rhs.size())
                return false;
            for (std::size_t i{0}; i < m_size; ++i) {
                if (ptr[i] != rhs[i])
                    return false;
            }
            return true;
        }

    private:
        std::size_t m_size{0};
        std::size_t m_capacity{0};
        std::allocator<T> m_alloc;
        T* ptr{nullptr};
    };
}

#endif //ALI_VECTOR_H
