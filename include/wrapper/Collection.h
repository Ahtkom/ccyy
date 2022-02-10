#ifndef CCYY_COLLECTION_H_
#define CCYY_COLLECTION_H_

#include <memory>
#include <vector>

namespace ccyy {
namespace wrapper {

template<typename T>
class Collection
{
public:
    Collection() = default;
    virtual ~Collection() = default;

    T *operator[](std::size_t index);

    std::size_t size() const { return data_.size(); }

    void push_back(const T &);
    void push_back(T &&);
    void erase(std::size_t index);

    void updateByIndex(std::size_t index, const T &other);
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
void Collection<T>::erase(std::size_t index)
{
    data_.erase(data_.begin() + index);
}

template<typename T>
inline
void Collection<T>::updateByIndex(std::size_t index, const T &other)
{
    if (index < Collection<T>::size()) {
        data_[index] = std::make_unique<T>(other);
    }
}

template<typename T>
inline
void Collection<T>::updateByIndex(std::size_t index, T &&other)
{
    if (index < Collection<T>::size()) {
        data_[index] = std::unique_ptr<T>(new T(std::move(other)));
    }
}

} // namespace wrapper
} // namespace ccyy

#endif