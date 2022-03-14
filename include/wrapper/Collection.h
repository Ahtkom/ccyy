#ifndef CCYY_WRAPPER_COLLECTION_H_
#define CCYY_WRAPPER_COLLECTION_H_

#include <memory>
#include <vector>

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

    std::size_t size() const { return data_.size(); }

    T *operator[](std::size_t index);

    void push_back(std::unique_ptr<T> &&ptr);

    /// @deprecated Use push_back(std::unique_ptr<T> &&)
    void push_back(const T &other);

    /// @deprecated Use push_back(std::unique_ptr<T> &&)
    void push_back(T &&other);

protected:
    void eraseByIndex(std::size_t index);

    void updateByIndex(std::size_t index, std::unique_ptr<T> &&ptr);

    /// @deprecated Use updateByIndex(std::size_t, std::unique_ptr<T> &&)
    void updateByIndex(std::size_t index, const T &other);

    /// @deprecated Use updateByIndex(std::size_t, std::unique_ptr<T> &&)
    void updateByIndex(std::size_t index, T &&other);

protected:
    std::vector<std::unique_ptr<T>> data_;
};


template<typename T>
inline
T *Collection<T>::operator[](std::size_t index)
{
    return index < size() ? data_[index].get() : nullptr;
}

template<typename T>
inline
void Collection<T>::push_back(const T &object)
{
    data_.push_back(std::make_unique<T>(object));
}

template<typename T>
inline
void Collection<T>::push_back(T &&object)
{
    data_.push_back(std::unique_ptr<T>(new T(std::move(object))));
}

template<typename T>
inline
void Collection<T>::push_back(std::unique_ptr<T> &&ptr)
{
    data_.push_back(std::move(ptr));
}

template<typename T>
inline
void Collection<T>::eraseByIndex(std::size_t index)
{
    data_.erase(data_.begin() + index);
}

template<typename T>
inline
void Collection<T>::updateByIndex(std::size_t index, const T &other)
{
    if (index < size()) {
        data_[index] = std::make_unique<T>(other);
    }
}

template<typename T>
inline
void Collection<T>::updateByIndex(std::size_t index, T &&other)
{
    if (index < size()) {
        data_[index] = std::unique_ptr<T>(new T(std::move(other)));
    }
}

template<typename T>
inline
void Collection<T>::updateByIndex(std::size_t index, std::unique_ptr<T> &&ptr)
{
    if (index < size()) {
        data_[index] = std::move(ptr);
    }
}


} // namespace wrapper
} // namespace ccyy

#endif