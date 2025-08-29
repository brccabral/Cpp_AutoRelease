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

private:

    T obj_;
    std::function<void(T &)> deleter_;
};
