#ifndef CCYY_WRAPPER_NAMEDCOLLECTION_H_
#define CCYY_WRAPPER_NAMEDCOLLECTION_H_

#include <wrapper/Collection.h>
#include <util/IllegalArgumentException.h>

#include <sstream>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

namespace ccyy {
namespace wrapper {

/**
 * @brief Class template NamedCollection: a container for objects based
 *        on vector, offering quick access and operations on their names.
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

    ~NamedCollection() override = default;

    // For name looking-ups.
    using Collection<T>::operator[];

    /**
     * @brief A string repr of names.
     */
    std::string toString() const;

    std::string getName(std::size_t index) const;

    T *operator[](std::string name);

    const T *operator[](std::string name) const;

    void push_back(std::unique_ptr<T> &&ptr, const std::string &name);

    // For derived class object
    template<typename D>
    void push_back(const D &other, const std::string &name);
    
    // For derived class object
    template<typename D>
    void push_back(D &&other, const std::string &name);

    void updateByName(const std::string &name, std::unique_ptr<T> &&ptr);

    // For derived class object
    template<typename D>
    void updateByName(const std::string &name, const D &other);
    
    // For derived class object
    template<typename D>
    void updateByName(const std::string &name, D &&other);

    void reserve(std::size_t n) override;
    
    void eraseByName(const std::string &name);

    bool existsName(const std::string &name) const;
    
    void rename(const std::string &name, const std::string &nameNew);

protected:
    void eraseByIndex(std::size_t index) override;

    // Return -1 if the given name was not found.
    int findIndexByName(const std::string &name) const;

    void renameByIndex(std::size_t index, const std::string &nameNew);

private:
    std::vector<std::string> names_;

};


template<typename T>
std::string NamedCollection<T>::toString() const
{
    std::ostringstream s;
    s << *this;
    return s.str();
}

template<typename T>
std::string NamedCollection<T>::getName(std::size_t index) const
{
    return index < Collection<T>::size() ? names_[index] : "";
}

template<typename T>
T *NamedCollection<T>::operator[](std::string name)
{
    if (int index = findIndexByName(name) + 1) {
        return operator[](static_cast<std::size_t>(index - 1));
    }
    return nullptr;
}

template<typename T>
const T *NamedCollection<T>::operator[](std::string name) const
{
    if (int index = findIndexByName(name) + 1) {
        return operator[](static_cast<std::size_t>(index - 1));
    }
    return nullptr;
}

template<typename T>
void NamedCollection<T>::push_back(std::unique_ptr<T> &&ptr, const std::string &name)
{
    if (name.empty()) {
        throw util::IllegalArgumentException(__PRETTY_FUNCTION__,
            "Name in NamedCollection cannot be empty!");
    }
    if (!existsName(name)) {
        Collection<T>::push_back(std::move(ptr));
        names_.push_back(name);
    }
}

template<typename T>
template<typename D>
void NamedCollection<T>::push_back(const D &other, const std::string &name)
{
    if (name.empty()) {
        throw util::IllegalArgumentException(__PRETTY_FUNCTION__,
            "Name in NamedCollection cannot be empty!");
    }
    if (!existsName(name)) {
        Collection<T>::push_back(other);
        names_.push_back(name);
    }
}

template<typename T>
template<typename D>
void NamedCollection<T>::push_back(D &&other, const std::string &name)
{
    if (name.empty()) {
        throw util::IllegalArgumentException(__PRETTY_FUNCTION__,
            "Name in NamedCollection cannot be empty!");
    }
    if (!existsName(name)) {
        Collection<T>::push_back(std::move(other));
        names_.push_back(name);
    }
}

template<typename T>
void NamedCollection<T>::updateByName(const std::string &name, std::unique_ptr<T> &&ptr)
{
    if (int index = findIndexByName(name) + 1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1), std::move(ptr));
    }
}

template<typename T>
template<typename D>
void NamedCollection<T>::updateByName(const std::string &name, const D &other)
{
    if (int index = findIndexByName(name) + 1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1), other);
    }
}

template<typename T>
template<typename D>
void NamedCollection<T>::updateByName(const std::string &name, D &&other)
{
    if (int index = findIndexByName(name) + 1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1), std::move(other));
    }
}

template<typename T>
void NamedCollection<T>::reserve(std::size_t n)
{
    Collection<T>::reserve(n);
    names_.reserve(n);
}

template<typename T>
void NamedCollection<T>::eraseByName(const std::string &name)
{
    if (int index = findIndexByName(name) + 1) {
        eraseByIndex(static_cast<std::size_t>(index - 1));
    }
}

template<typename T>
bool NamedCollection<T>::existsName(const std::string &name) const
{
    return findIndexByName(name) != -1;
}

template<typename T>
void NamedCollection<T>::rename(const std::string &name, const std::string &nameNew)
{
    if (int index = findIndexByName(name) + 1) {
        renameByIndex(static_cast<std::size_t>(index - 1), nameNew);
    }
}

template<typename T>
void NamedCollection<T>::eraseByIndex(std::size_t index)
{
    Collection<T>::eraseByIndex(index);
    names_.erase(names_.begin() + index);
}

template<typename T>
int NamedCollection<T>::findIndexByName(const std::string &name) const
{
    auto iter = std::find(names_.cbegin(), names_.cend(), name);
    return iter == names_.end() ? -1 : (iter - names_.begin());
}

template<typename T>
void NamedCollection<T>::renameByIndex(std::size_t index, const std::string &nameNew)
{
    if (nameNew.empty()) {
        throw util::IllegalArgumentException(__PRETTY_FUNCTION__,
            "Name in NamedCollection cannot be empty!");
    }
    if (index < Collection<T>::size()) {
        names_[index] = nameNew;
    }
}


template<typename T>
std::ostream &operator<<(std::ostream &os, const NamedCollection<T> &nc)
{
    int maxLength = log10(nc.size()) + 3;
    for (std::size_t i = 0; i != nc.size(); ++i) {
        os.width(maxLength);
        os << std::left << i << nc.getName(i) << "\n";
    }
    return os;
}

} // namespace wrapper
} // namespace ccyy

#endif