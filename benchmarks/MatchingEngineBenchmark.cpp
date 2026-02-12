#include "common/LockFreeQueue.h"
#include "engine/OrderBook.cpp"
#include <benchmark/benchmark.h>
#include <cstdint>

static void BM_OrderMatching(benchmark::State &state) {
  OrderBook book;

  // Prefilling some orders for liquidity
  for (int i = 0; i < 100; ++i) {
    Order o{static_cast<uint32_t>(i), 100.0, 10, false}; // Sells at 100
    book.processOrder(&o);
  }

  // Benchmark the time it takes to match incoming order
  for (auto _ : state) {
    Order buyOrder{999, 100.0, 10, true};
    book.processOrder(&buyOrder);
    benchmark::DoNotOptimize(buyOrder);
  }
}

BENCHMARK(BM_OrderMatching);

BENCHMARK_MAIN();
