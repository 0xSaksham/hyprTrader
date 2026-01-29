#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

template <typename T> class MemoryPool {
public:
  explicit MemoryPool(std::size_t size) {
    store_.reserve(size);

    for (std::size_t i = 0; i < size; ++i) {
      store_.push_back(T{});
      free_indices_.push_back(i);
    }
  }

  T *allocate() {
    if (free_indices_.empty()) {
      throw std::runtime_error("MemoryPool Exhausted!");
    }
    std::size_t index = free_indices_.back();
    free_indices_.pop_back();

    return &store_[index];
  }

  void deallocate(T *ptr) {
    std::ptrdiff_t index = ptr - &store_[0];
    if (index < 0 || static_cast<size_t>(index) >= store_.size()) {
      throw std::runtime_error("Pointer does not belong to this pool.");
    }

    free_indices_.push_back(static_cast<size_t>(index));
  }

private:
  std::vector<T> store_;
  std::vector<std::size_t> free_indices_;
};

#endif
