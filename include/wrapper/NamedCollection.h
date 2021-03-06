#ifndef CCYY_WRAPPER_NAMEDCOLLECTION_H_
#define CCYY_WRAPPER_NAMEDCOLLECTION_H_

#include <util/IllegalArgumentException.h>
#include <wrapper/Collection.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

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
template <typename T> class NamedCollection : public Collection<T> {
public:
  using Collection<T>::operator[];

  NamedCollection() = default;

  ~NamedCollection() override = default;

  std::string getName(std::size_t index) const {
    return index < Collection<T>::size() ? names_[index] : "";
  }

  T *operator[](std::string name) {
    if (int index = findIndexByName(name) + 1) {
      return operator[](static_cast<std::size_t>(index - 1));
    }
    return nullptr;
  }

  const T *operator[](std::string name) const {
    if (int index = findIndexByName(name) + 1) {
      return operator[](static_cast<std::size_t>(index - 1));
    }
    return nullptr;
  }

  void push_back(std::unique_ptr<T> &&ptr, const std::string &name) {
    nameCheck(name, __PRETTY_FUNCTION__);
    if (!existsName(name)) {
      Collection<T>::push_back(std::move(ptr));
      names_.push_back(name);
    }
  }

  template <typename D, typename = EnableIfIsBaseOf<T, D>>
  void push_back(D &&other, const std::string &name) {
    nameCheck(name, __PRETTY_FUNCTION__);
    if (!existsName(name)) {
      Collection<T>::push_back(std::forward<D>(other));
      names_.push_back(name);
    }
  }

  void updateByName(const std::string &name, std::unique_ptr<T> &&ptr) {
    if (int index = findIndexByName(name) + 1) {
      Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1),
                                   std::move(ptr));
    }
  }

  template <typename D, typename = EnableIfIsBaseOf<T, D>>
  void updateByName(const std::string &name, D &&other) {
    if (int index = findIndexByName(name) + 1) {
      Collection<T>::updateByIndex(static_cast<std::size_t>(index - 1),
                                   std::forward<D>(other));
    }
  }

  void reserve(std::size_t n) override {
    Collection<T>::reserve(n);
    names_.reserve(n);
  }

  void eraseByName(const std::string &name) {
    if (int index = findIndexByName(name) + 1) {
      eraseByIndex(static_cast<std::size_t>(index - 1));
    }
  }

  bool existsName(const std::string &name) const {
    return findIndexByName(name) != -1;
  }

  void rename(const std::string &name, const std::string &nameNew) {
    if (int index = findIndexByName(name) + 1) {
      renameByIndex(static_cast<std::size_t>(index - 1), nameNew);
    }
  }

  /**
   * @brief A string repr of names.
   */
  std::string toString() const {
    std::ostringstream s;
    s << *this;
    return s.str();
  }

protected:
  void eraseByIndex(std::size_t index) override {
    Collection<T>::eraseByIndex(index);
    names_.erase(names_.begin() + index);
  }

  // Return -1 if the given name was not found.
  int findIndexByName(const std::string &name) const {
    auto iter = std::find(names_.cbegin(), names_.cend(), name);
    return iter == names_.end() ? -1 : (iter - names_.begin());
  }

  void renameByIndex(std::size_t index, const std::string &nameNew) {
    nameCheck(nameNew, __PRETTY_FUNCTION__);
    if (index < Collection<T>::size()) {
      names_[index] = nameNew;
    }
  }

  void nameCheck(const std::string &name, const std::string &caller) {
    if (name.empty()) {
      throw util::IllegalArgumentException(
          caller, "Name in NamedCollection cannot be empty!");
    }
  }

private:
  std::vector<std::string> names_;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const NamedCollection<T> &nc) {
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