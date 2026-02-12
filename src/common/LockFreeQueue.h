#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <cstddef>
#include <optional>
#include <vector>

template <typename T> class LockFreeQueue {
public:
  explicit LockFreeQueue(size_t size) : buffer_(size), head_(0), tail_(0) {}

  // Producer (Gateway Thread)
  bool push(const T &value) {
    const size_t current_head = head_.load(std::memory_order_relaxed);
    const size_t next_head = (current_head + 1) % buffer_.size();

    if (next_head == tail_.load(std::memory_order_acquire))
      return false; // Full

    buffer_[current_head] = value;
    head_.store(next_head, std::memory_order_release);
    return true;
  }

  std::optional<T> pop() {
    const size_t current_tail = tail_.load(std::memory_order_relaxed);
    if (current_tail == head_.load(std::memory_order_acquire))
      return std::nullopt;

    T value = buffer_[current_tail];
    tail_.store((current_tail + 1) % buffer_.size(), std::memory_order_release);
    return value;
  }

private:
  std::vector<T> buffer_;
  // alignas(64) prevents "False Sharing" between CPU cores
  alignas(64) std::atomic<size_t> head_;
  alignas(64) std::atomic<size_t> tail_;
};

#endif
