#ifndef FIXED_ARRAY_H
#define FIXED_ARRAY_H

# include <new>
# include <cstddef>
# include <utility>
# include <type_traits>
# include <memory>

template <typename T, std::size_t N>
class FixedArray {
public:
    using value_type = T;
    using size_type = std::size_t;
    
    constexpr static size_type capacity_v = N;

    // Constructor & Destructor
    constexpr FixedArray() noexcept = default;
    ~FixedArray() noexcept{clear();}

    // non-copyable
    FixedArray(const FixedArray&) = delete;
    FixedArray& operator=(const FixedArray&) = delete;

    // element access
    constexpr T& operator[](size_type index) noexcept {return data_[index];}
    constexpr const T& operator[](size_type index) const noexcept {return data_[index];}

    // size / capacity
    constexpr size_type size() const noexcept {return size_;}
    constexpr size_type capacity() const noexcept {return N;}
    constexpr bool empty() const noexcept {return size_ == 0;}

    // modifiers
    te
};

#endif /* FIXED_ARRAY_H */
