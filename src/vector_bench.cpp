#include <chrono>
#include <x86intrin.h>
#include "fixed_array.hpp"
#include <vector>

constexpr int ITERS = 2'000'000;

// warm up to stablilize the branch prediction & caches
template <typename Vector>
void warm_up(Vector& v){
    for (int i = 0; i < ITERS; ++i) {
        v.emplace_back(i);
    }
    v.clear();
}

template <typename Vector>
uint64_t bench(Vector &v){
    uint64_t start = __rdtsc();
    for (int i = 0; i < ITERS; ++i) {
        v.emplace_back(i);
    }
    uint64_t end = __rdtsc();
    v.clear();
    return end - start;
}

int main(){
    FixedArray<int, ITERS> fixed_array;
    std::vector<int> stl_vector;
    stl_vector.reserve(ITERS);
    
    warm_up(fixed_array);
    auto fa_cycles = bench(fixed_array);

    warm_up(stl_vector);
    auto stl_cycles = bench(stl_vector);

    std::printf("FixedArray cycles/insert: %.2f\n", static_cast<double>(fa_cycles) / ITERS);
    std::printf("STL vector cycles/insert: %.2f\n", static_cast<double>(stl_cycles) / ITERS);
}
