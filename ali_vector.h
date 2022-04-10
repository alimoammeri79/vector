/*
 * Created by ali on 4/10/22.
 *
 * todo:
 *  begin()
 *  cbegin()
 *  end()
 *  cend()
 *  front()
 *  back()
 *  empty()
 *  insert() 
*/

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

        explicit vector(const std::size_t& _size, const T& value = T{})
                : m_size{_size}, m_capacity{_size * 2}, ptr{ new T[m_capacity] } {
                    for(std::size_t i{0}; i < m_size; ++i)
                        ptr[i] = value;
                }

        vector(const std::initializer_list<T>& ls)
                : m_size{ls.size()}, m_capacity{ls.size() * 2}, ptr{ new T[ls.size()] } {
            std::copy(ls.begin(), ls.end(), ptr);
        }

        vector(const ali::vector<T>& rhs)
                :m_size{rhs.size()}, m_capacity{rhs.capacity()}, ptr{new T[rhs.capacity()]} {
            std::copy(rhs.ptr, rhs.ptr + size(), ptr);
        }

        vector(ali::vector<T>&& rhs) noexcept
                :m_size{rhs.size()}, m_capacity{rhs.capacity()}, ptr{new T[rhs.capacity()]} {
            std::copy(rhs.ptr, rhs.ptr + size(), ptr);
            rhs.clear();
        }

        ~vector() { delete[] ptr; }

        [[nodiscard]] std::size_t size() const noexcept { return m_size; }
        [[nodiscard]] std::size_t capacity() const noexcept { return m_capacity; }
        void clear() noexcept {
            delete[] ptr;
            ptr = nullptr;
            m_size = 0;
        }

        void push_back(const T& value) {
            std::size_t new_size{m_size + 1};
            if(new_size > capacity())
            {
                m_capacity = new_size * 2;
                T* new_ptr {new T[m_capacity] {T()}};
                std::copy(ptr, ptr + size(), new_ptr);
                delete[] ptr;
                ptr = new_ptr;
            }
            ptr[m_size++] = value;
        }


        void pop_back() {
            m_size = m_size > 0 ? m_size - 1 : m_size;
        }

        T& at(std::size_t index) {
            if (index < size())
                return ptr[index];
            else
                throw std::out_of_range("index out of range");
        }

        const T& at(std::size_t index) const {
            if (index < size())
                return ptr[index];
            else
                throw std::out_of_range("index out of range");
        }

        void shrink_to_fit() {
            if (size() < capacity()) {
                T* new_arr = new T[size()];
                std::copy(ptr, ptr + size(), new_arr);
                delete[] ptr;
                ptr = new_arr;
                m_capacity = size();
            }
        }

        void reserve(std::size_t capacity) {
            if (capacity > m_capacity) {
                T* new_arr = new T[capacity];
                std::copy(ptr, ptr + m_size, new_arr);
                delete[] ptr;
                ptr = new_arr;
                m_capacity = capacity;
            }
        }

        bool empty() const { return size() == 0; }

        void swap(ali::vector<T>& rhs) {
            std::swap(m_size, rhs.m_size);
            std::swap(m_capacity, rhs.m_capacity);
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
            if(*this != rhs)
            {
                m_size = rhs.size();
                m_capacity = rhs.capacity();
                T* new_ptr{new T[m_capacity]};
                std::copy(rhs.ptr, rhs.ptr + rhs.size(), new_ptr);
                delete[] ptr;
                ptr = new_ptr;
            }
            return *this;
        }

        ali::vector<T>& operator=(ali::vector<T>&& rhs) noexcept {
            m_size = rhs.size();
            m_capacity = rhs.capacity();
            ptr = new T[rhs.capacity()] ;
            std::copy(rhs.ptr, rhs.ptr + size(), ptr);
            rhs.clear();
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
        T* ptr{nullptr};
    };
}

#endif //VECTOR_ALI_VECTOR_H

