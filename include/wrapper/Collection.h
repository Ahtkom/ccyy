#ifndef CCYY_WRAPPER_COLLECTION_H_
#define CCYY_WRAPPER_COLLECTION_H_

#include <memory>
#include <vector>
#include <type_traits>
#include <cassert>

namespace ccyy {
namespace wrapper {

template<typename _B, typename _D>
using EnableIfIsBaseOf = std::enable_if_t<std::is_base_of_v<_B, _D>>;

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

    virtual void reserve(std::size_t n) { data_.reserve(n); }

    T *operator[](std::size_t index)
    {
      return index < size() ? data_[index].get() : nullptr;
    }

    const T *operator[](std::size_t index) const
    {
      return index < size() ? data_[index].get() : nullptr;
    }

    void push_back(std::unique_ptr<T> &&ptr)
    {
      data_.push_back(std::move(ptr));
    }

    template<typename D, typename = EnableIfIsBaseOf<T, D>>
    void push_back(D &&other)
    {
      data_.push_back(std::make_unique<D>(std::forward<D>(other)));
    }

  protected:
    virtual void eraseByIndex(std::size_t index)
    {
      data_.erase(data_.begin() + index);
    }

    void updateByIndex(std::size_t index, std::unique_ptr<T> &&ptr)
    {
      if (index < size()) {
        data_[index] = std::move(ptr);
      }
    }

    template<typename D, typename = EnableIfIsBaseOf<T, D>>
    void updateByIndex(std::size_t index, D &&other)
    {
      if (index < size()) {
        data_[index] = std::make_unique<D>(std::forward<D>(other));
      }
    }

  protected:
    std::vector<std::unique_ptr<T>> data_;
  };

} // namespace wrapper
} // namespace ccyy

#endif