#pragma once

#include <random>
#include <stdexcept>
#include <vector>

inline std::size_t get_random_number(std::size_t from, std::size_t to)
{
    static std::mt19937 rnd(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(from, to);
    return dist(rnd);
}

template <class T>
class randomized_queue
{
private:
    std::vector<T> m_data;

    template <class Iterator>
    class randomized_queue_iterator
    {
    private:
        Iterator m_iter;
        std::vector<std::size_t> m_permutation;
        std::size_t m_position = 0;

        void check_index()
        {
            if (m_position + 1 > m_permutation.size()) {
                throw std::out_of_range("Iterator out of range");
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;

        randomized_queue_iterator() = default;
        randomized_queue_iterator(Iterator iter, std::size_t size_permutation)
            : m_iter(iter)
            , m_permutation(size_permutation)
            , m_position(0)
        {
            for (std::size_t i = 0; i < size_permutation; ++i) {
                m_permutation[i] = i;
            }
            for (std::size_t i = 0; i < size_permutation; ++i) {
                std::swap(m_permutation[i], m_permutation[get_random_number(i, size_permutation - 1)]);
            }
        }
        randomized_queue_iterator & operator++()
        {
            check_index();
            ++m_position;
            return *this;
        }
        randomized_queue_iterator operator++(int)
        {
            check_index();
            auto tmp = *this;
            ++m_position;
            return tmp;
        }
        reference operator*() const
        {
            return *(m_iter + m_permutation[m_position]);
        }
        pointer operator->() const
        {
            return &*(m_iter + m_permutation[m_position]);
        }
        bool operator==(const randomized_queue_iterator & other) const
        {
            return m_iter + m_position == other.m_iter + other.m_position;
        }
        bool operator!=(const randomized_queue_iterator & other) const
        {
            return !(this->operator==(other));
        }
    };
    using iterator = randomized_queue_iterator<typename std::vector<T>::iterator>;
    using const_iterator = randomized_queue_iterator<typename std::vector<T>::const_iterator>;

public:
    randomized_queue() = default;
    std::size_t size() const
    {
        return m_data.size();
    }
    bool empty() const
    {
        return m_data.empty();
    }
    void enqueue(T & element)
    {
        m_data.push_back(element);
    }
    void enqueue(const T & element)
    {
        m_data.push_back(element);
    }
    void enqueue(T && element)
    {
        m_data.push_back(std::move(element));
    }
    const T & sample() const
    {
        return m_data[get_random_number(0, size() - 1)]; // random
    }
    T dequeue()
    {
        if (empty()) {
            throw std::out_of_range("Trying to dequeue from empty queue");
        }
        std::size_t index = get_random_number(0, size() - 1); // random
        std::swap(m_data[index], m_data[size() - 1]);
        auto result = std::move(m_data[size() - 1]);
        m_data.pop_back();
        return result;
    }
    iterator begin()
    {
        return iterator(m_data.begin(), size());
    }
    iterator end()
    {
        return iterator(m_data.end(), size());
    }
    const_iterator begin() const
    {
        return const_iterator(m_data.begin(), size());
    }
    const_iterator end() const
    {
        return const_iterator(m_data.end(), size());
    }
    const_iterator cbegin()
    {
        return const_iterator(m_data.begin(), size());
    }
    const_iterator cend()
    {
        return const_iterator(m_data.end(), size());
    }
};
