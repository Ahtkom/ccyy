#ifndef CCYY_WRAPPER_NAMEDCOLLECTION_H_
#define CCYY_WRAPPER_NAMEDCOLLECTION_H_

#include <wrapper/Collection.h>

#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

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

    ~NamedCollection() = default;

    using Collection<T>::operator[];

    T *operator[](std::string name);

    std::string toString() const;

    std::string getName(std::size_t index) const;

    bool existsName(const std::string &name) const;
    
    void rename(const std::string &name, const std::string &nameNew);

    void push_back(std::unique_ptr<T> &&ptr, const std::string &name);

    void updateByName(const std::string &name, std::unique_ptr<T> &&ptr);

    void eraseByName(const std::string &name);

    /// @deprecated Use push_back(std::unique_ptr<T> &&, const std::string &)
    void push_back(const T &other, const std::string &name);
    
    /// @deprecated Use push_back(std::unique_ptr<T> &&, const std::string &)
    void push_back(T &&other, const std::string &name);
    
    /// @deprecated Use updateByName(const std::string &, std::unique_ptr<T> &&)
    void updateByName(const std::string &name, const T &other);
    
    /// @deprecated Use updateByName(const std::string &, std::unique_ptr<T> &&)
    void updateByName(const std::string &name, T &&other);

protected:
    /// Return -1 if the given name was not found.
    int findIndexByName(const std::string &name) const;

    void renameByIndex(std::size_t index, const std::string &nameNew);

    void eraseByIndex(std::size_t index);

private:
    std::vector<std::string> names_;
};


template<typename T>
T *NamedCollection<T>::operator[](std::string name)
{
    if (int index = findIndexByName(name) + 1) {
        return operator[](static_cast<std::size_t>(index - 1));
    }
    return nullptr;
}

template<typename T>
inline
std::string NamedCollection<T>::toString() const
{
    std::ostringstream s;
    s << *this;
    return s.str();
}

template<typename T>
inline
std::string NamedCollection<T>::getName(std::size_t index) const
{
    return index < Collection<T>::size() ? names_[index] : "Overflow!";
}

template<typename T>
inline
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
void NamedCollection<T>::push_back(std::unique_ptr<T> &&ptr, const std::string &name)
{
    if (!existsName(name)) {
        names_.push_back(name);
        Collection<T>::push_back(std::move(ptr));
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
void NamedCollection<T>::updateByName(const std::string &name, const T &other)
{
    if (int index = findIndexByName(name) + 1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1), other);
    }
}

template<typename T>
void NamedCollection<T>::updateByName(const std::string &name, T &&other)
{
    if (int index = findIndexByName(name) + 1) {
        Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1), std::move(other));
    }
}

template<typename T>
int NamedCollection<T>::findIndexByName(const std::string &name) const
{
    auto iter = std::find(names_.cbegin(), names_.cend(), name);
    return iter == names_.end() ? -1 : (iter - names_.begin());
}

template<typename T>
void NamedCollection<T>::eraseByIndex(std::size_t index)
{
    names_.erase(names_.begin() + index);
    Collection<T>::eraseByIndex(index);
}

template<typename T>
void NamedCollection<T>::renameByIndex(std::size_t index, const std::string &nameNew)
{
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