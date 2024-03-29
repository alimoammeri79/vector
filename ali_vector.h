//
// Created by Ali Moameri on 4/10/22.
//

#ifndef ALI_VECTOR_H
#define ALI_VECTOR_H

#include <cstddef>
#include <exception>
#include <algorithm>
#include <memory>

namespace ali {
    template <typename T> class vector {
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
                m_alloc.construct(ptr + i, value);
        }

        vector(const std::initializer_list<T>& ls)
                : m_size{ls.size()}, m_capacity{ls.size() * 2} {
            ptr = m_alloc.allocate(m_capacity);
            for(std::size_t i{0}; i < ls.size(); ++i)
                m_alloc.construct(ptr + i, *(ls.begin() + i));
        }

        vector(const ali::vector<T>& rhs)
                :m_size{rhs.size()}, m_capacity{rhs.capacity()} {
            ptr = m_alloc.allocate(m_capacity);
            for(std::size_t i{0}; i < rhs.size(); ++i)
                m_alloc.construct(ptr + i, rhs[i]);
        }

        vector(ali::vector<T>&& rhs) noexcept
                :m_size{rhs.size()}, m_capacity{rhs.capacity()} {
            ptr = m_alloc.allocate(m_capacity);
            for(std::size_t i{0}; i < rhs.size(); ++i)
                m_alloc.construct(ptr + i, rhs[i]);
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
            if(m_capacity == 0)
                reserve(8);
            else if(m_size == m_capacity)
                reserve(m_size * 2);
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
                for(std::size_t i{0}; i < m_size; ++i)
                    m_alloc.construct(new_ptr + i, ptr[i]);
                for(std::size_t i{0}; i < m_size; ++i)
                    m_alloc.destroy(ptr + i);
                m_alloc.deallocate(ptr, m_capacity);
                ptr = new_ptr;
                m_capacity = m_size;
            }
        }

        void reserve(std::size_t space) {
            if (space > m_capacity) {
                T* new_ptr{m_alloc.allocate(space)};

                for(std::size_t i{0}; i < m_size; ++i)
                    m_alloc.construct(new_ptr + i, ptr[i]);
                for(std::size_t i{0}; i < m_size; ++i)
                    m_alloc.destroy(ptr + i);

                m_alloc.deallocate(ptr, m_capacity);
                ptr = new_ptr;
                m_capacity = space;
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
            if(this == &rhs)
                return *this;

            if(rhs.size() <= m_capacity) {
                std::copy(rhs.ptr, rhs.ptr + rhs.size(), ptr);
                m_size = rhs.size();
                return *this;
            }

            T* new_ptr{m_alloc.allocate(rhs.size())};
            for(std::size_t i{0}; i < rhs.size(); ++i)
                m_alloc.construct(new_ptr + i, rhs[i]);
            for(std::size_t i{0}; i < m_size; ++i)
                m_alloc.destroy(ptr + i);
            m_alloc.deallocate(ptr, m_capacity);
            ptr = new_ptr;
            m_capacity = m_size = rhs.size();
            return *this;
        }

        ali::vector<T>& operator=(ali::vector<T>&& rhs) noexcept {
            if(this == &rhs)
                return *this;

            if(rhs.size() <= m_capacity) {
                std::copy(rhs.ptr, rhs.ptr + rhs.size(), ptr);
                m_size = rhs.size();
            } else {
                T* new_ptr{m_alloc.allocate(rhs.size())};
                for(std::size_t i{0}; i < rhs.size(); ++i)
                    m_alloc.construct(new_ptr + i, rhs[i]);
                for(std::size_t i{0}; i < m_size; ++i)
                    m_alloc.destroy(ptr + i);
                m_alloc.deallocate(ptr, m_capacity);
                ptr = new_ptr;
                m_capacity = m_size = rhs.size();
            }

            rhs.clear();
            rhs.m_capacity = 0;
            return *this;
        }

        bool operator==(const vector &rhs) const {
            if (size() != rhs.size())
                return false;
            for (std::size_t i{0}; i < size(); ++i) {
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
