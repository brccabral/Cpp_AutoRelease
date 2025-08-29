#pragma once

#include <functional>
#include <ranges>

template<class T, T Invalid = {}>
class AutoRelease
{
public:

    AutoRelease() : AutoRelease({}, nullptr)
    {}

    AutoRelease(T obj, std::function<void(T &)> deleter) : obj_(obj), deleter_(deleter)
    {}

    ~AutoRelease()
    {
        if (obj_ != Invalid && deleter_)
        {
            deleter_(obj_);
        }
    }

    AutoRelease(const AutoRelease &) = delete;
    AutoRelease &operator=(const AutoRelease &) = delete;

    AutoRelease(AutoRelease &&other) noexcept : AutoRelease()
    {
        swap(other);
    };
    AutoRelease &operator=(AutoRelease &&other) noexcept
    {
        swap(other);
        return *this;
    }

    void swap(AutoRelease &other) noexcept
    {
        std::ranges::swap(obj_, other.obj_);
        std::ranges::swap(deleter_, other.deleter_);
    }

    T get() const
    {
        return obj_;
    }

    explicit operator T() const
    {
        return obj_;
    }

    constexpr explicit operator bool() const
    {
        return obj_ != Invalid;
    }

    constexpr bool operator==(const AutoRelease &other) const
    {
        return obj_ == other.obj_;
    }

    constexpr bool operator==(std::nullptr_t) const
    {
        return !*this;
    }

    constexpr bool operator==(std::nullopt_t) const
    {
        return !*this;
    }

    constexpr T operator*() const
    {
        return obj_;
    }

    constexpr const T *operator->() const
    {
        return &obj_;
    }

protected:

    T &get()
    {
        return obj_;
    }

private:

    T obj_;
    std::function<void(T &)> deleter_;
};
