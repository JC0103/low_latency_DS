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
    template<class... Args>
    T& emplace_back(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>) {
        if (size_ >= N) [[unlikely]]
            _builtin_trap();   // overflow, terminate fast, no exception
        
        T* slot = std::launder(data() + size_);
        new (slot) T(std::forward<Args>(args)...); // placement new
        return *slot, ++size_, *slot;
    }

    void push_back(const T & v){ emplace_back(v); }
    void push_back(T && v){emplace_back(std::move(v));}
    void pop_back() noexcept { std::destory_at(data() + --size_);}
    void clear() noexcept { std::destroy(data(), data() + size_); size_ = 0;}

    // raw pointer to contiguous storage
    constexpr T* data() noexcept {return std::launder(reinterpret_cast<T*>(storage_));}
    constexpr const T* data() const noexcept {return std::launder(reinterpret_cast<const T*>(storage_));}

private:
    alignas(T) std::byte storage_[sizeof(T) * N] {}; // in object buffer
    size_type size_{0};
};

#endif /* FIXED_ARRAY_H */
