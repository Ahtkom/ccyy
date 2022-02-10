#ifndef CCYY_NAMEDCOLLECTION_H_
#define CCYY_NAMEDCOLLECTION_H_

#include "./Collection.h"

#include <algorithm>
#include <vector>
#include <string>

namespace ccyy {
namespace wrapper {

/**
 * @brief Class template NamedCollection: a container for objects based on
 * vector, offering quick access and operations on their names.
 * 
 * @note The name must be unique, not as the type T object.
 * 
 * @tparam T 
 */
template<typename T>
class NamedCollection : public Collection<T>
{
public:
    NamedCollection() = default;
    ~NamedCollection() = default;

    using Collection<T>::operator[];
    T *operator[](std::string name);

    std::string getName(std::size_t index) const;
    void printNames() const;

    void push_back(const T &, const std::string &name);
    void push_back(T &&, const std::string &name);
    void erase(std::size_t index);
    void eraseByName(const std::string &name);

    /// Return -1 if the given name was not found.
    int findByName(const std::string &name) const;
    bool existsName(const std::string &name) const;

    void renameByIndex(std::size_t index, const std::string &nameNew);
    void renameByName(const std::string &name, const std::string &nameNew);

    void updateByName(const std::string &name, const T &other);
    void updateByName(const std::string &name, T &&other);

private:
    std::vector<std::string> names_;
};


template<typename T>
T *NamedCollection<T>::operator[](std::string name)
{
    int index = findByName(name);
    return index != -1 ? operator[](static_cast<std::size_t>(index)) : nullptr;
}

template<typename T>
inline
std::string NamedCollection<T>::getName(std::size_t index) const
{
    return index < Collection<T>::size() ? names_[index] : "Overflow!";
}

template<typename T>
void NamedCollection<T>::printNames() const
{
    for (std::size_t i = 0; i != Collection<T>::size(); ++i) {
        printf("%-4d%s\n", i, names_[i].c_str());
    }
}

template<typename T>
void NamedCollection<T>::push_back(const T &other, const std::string &name)
{
    if (!existsName(name)) {
        names_.push_back(name);
        Collection<T>::push_back(other);
    }
}

template<typename T>
void NamedCollection<T>::push_back(T &&other, const std::string &name)
{
    if (!existsName(name)) {
        names_.push_back(name);
        Collection<T>::push_back(std::move(other));
    }
}

template<typename T>
void NamedCollection<T>::erase(std::size_t index)
{
    names_.erase(names_.begin() + index);
    Collection<T>::erase(index);
}

template<typename T>
int NamedCollection<T>::findByName(const std::string &name) const
{
    auto iter = std::find(names_.cbegin(), names_.cend(), name);
    return iter == names_.end() ? -1 : (iter - names_.begin());
}

template<typename T>
inline
bool NamedCollection<T>::existsName(const std::string &name) const
{
    return findByName(name) != -1;
}

template<typename T>
void NamedCollection<T>::renameByIndex(std::size_t index, const std::string &nameNew)
{
    if (index < Collection<T>::size()) {
        names_[index] = nameNew;
    }
}

template<typename T>
void NamedCollection<T>::renameByName(const std::string &name, const std::string &nameNew)
{
    int index = findByName(name);
    if (index != -1) {
        renameByIndex(static_cast<std::size_t>(index), nameNew);
    } 
}

template<typename T>
void NamedCollection<T>::updateByName(const std::string &name, const T &other)
{
    int index = findByName(name);
    if (index != -1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index), other);
    }
}

template<typename T>
void NamedCollection<T>::updateByName(const std::string &name, T &&other)
{
    int index = findByName(name);
    if (index != -1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index), std::move(other));
    }
}


} // namespace wrapper
} // namespace ccyy

#endif