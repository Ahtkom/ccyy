#ifndef CCYY_WRAPPER_COLLECTION_H_
#define CCYY_WRAPPER_COLLECTION_H_

#include <memory>
#include <vector>
#include <type_traits>
#include <assert.h>

namespace ccyy {
namespace wrapper {

/**
 * @brief Class template Collection: base class for NamedCollection.
 * 
 * @tparam T 
 */
template<typename T>
class Collection
{
public:
    Collection() = default;

    virtual ~Collection() = default;

    std::size_t size() const;

    virtual void reserve(std::size_t n);

    T *operator[](std::size_t index);

    const T *operator[](std::size_t index) const;

    void push_back(std::unique_ptr<T> &&ptr);

    // For derived class object
    template<typename D>
    void push_back(const D &other);

    // For derived class object
    template<typename D>
    void push_back(D &&other);

protected:
    virtual void eraseByIndex(std::size_t index);

    void updateByIndex(std::size_t index, std::unique_ptr<T> &&ptr);

    // For derived class object
    template<typename D>
    void updateByIndex(std::size_t index, const D &other);

    // For derived class object
    template<typename D>
    void updateByIndex(std::size_t index, D &&other);

protected:
    std::vector<std::unique_ptr<T>> data_;
};


template<typename T>
std::size_t Collection<T>::size() const
{
    return data_.size();
}

template<typename T>
void Collection<T>::reserve(std::size_t n)
{
    data_.reserve(n);
}

template<typename T>
T *Collection<T>::operator[](std::size_t index)
{
    return index < size() ? data_[index].get() : nullptr;
}

template<typename T>
const T *Collection<T>::operator[](std::size_t index) const
{
    return index < size() ? data_[index].get() : nullptr;
}

template<typename T>
void Collection<T>::push_back(std::unique_ptr<T> &&ptr)
{
    data_.push_back(std::move(ptr));
}

template<typename T>
template<typename D>
void Collection<T>::push_back(const D &object)
{
    static_assert(std::is_base_of<T, D>::value);
    static_assert(std::is_copy_constructible<D>::value);
    
    data_.push_back(std::make_unique<D>(object));
}

template<typename T>
template<typename D>
void Collection<T>::push_back(D &&other)
{
    static_assert(std::is_base_of<T, D>::value);
    static_assert(std::is_move_constructible<D>::value);

    data_.push_back(std::make_unique<D>(std::move(other)));
}

template<typename T>
void Collection<T>::eraseByIndex(std::size_t index)
{
    data_.erase(data_.begin() + index);
}

template<typename T>
template<typename D>
void Collection<T>::updateByIndex(std::size_t index, const D &other)
{
    static_assert(std::is_base_of<T, D>::value);
    static_assert(std::is_copy_constructible<D>::value);

    if (index < size()) {
        data_[index] = std::make_unique<D>(other);
    }
}

template<typename T>
template<typename D>
void Collection<T>::updateByIndex(std::size_t index, D &&other)
{
    static_assert(std::is_base_of<T, D>::value);
    static_assert(std::is_move_constructible<D>::value);

    if (index < size()) {
        data_[index] = std::make_unique<D>(std::move(other));
    }
}

template<typename T>
void Collection<T>::updateByIndex(std::size_t index, std::unique_ptr<T> &&ptr)
{
    if (index < size()) {
        data_[index] = std::move(ptr);
    }
}


} // namespace wrapper
} // namespace ccyy

#endif