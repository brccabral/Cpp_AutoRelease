#pragma once

#include <functional>
#include <ranges>

template<typename... Args>
class AutoReleaseVoid
{
public:

    AutoReleaseVoid(
            std::function<void(Args &&...args)> caller, std::function<void()> deleter,
            Args &&...args)
        : deleter_(std::move(deleter))
    {
        caller(std::forward<Args>(args)...);
    };

    AutoReleaseVoid() : AutoReleaseVoid(nullptr, nullptr, nullptr)
    {}

    AutoReleaseVoid(const AutoReleaseVoid &) = delete;
    AutoReleaseVoid &operator=(const AutoReleaseVoid &) = delete;
    AutoReleaseVoid(AutoReleaseVoid &&) = default;
    AutoReleaseVoid &operator=(AutoReleaseVoid &&) = default;

    ~AutoReleaseVoid()
    {
        if (deleter_)
        {
            deleter_();
        }
    }

private:

    std::function<void()> deleter_;
};

template<class T, T Invalid = {}>
class AutoReleaseBase
{
public:

    AutoReleaseBase() : AutoReleaseBase({}, nullptr)
    {}

    AutoReleaseBase(T obj, std::function<void(T &)> deleter) : obj_(obj), deleter_(deleter)
    {}

    ~AutoReleaseBase()
    {
        if (obj_ != Invalid && deleter_)
        {
            deleter_(obj_);
        }
    }

    AutoReleaseBase(const AutoReleaseBase &) = delete;
    AutoReleaseBase &operator=(const AutoReleaseBase &) = delete;

    AutoReleaseBase(AutoReleaseBase &&other) noexcept : AutoReleaseBase()
    {
        swap(other);
    };
    AutoReleaseBase &operator=(AutoReleaseBase &&other) noexcept
    {
        swap(other);
        return *this;
    }

    void swap(AutoReleaseBase &other) noexcept
    {
        std::ranges::swap(obj_, other.obj_);
        std::ranges::swap(deleter_, other.deleter_);
    }

    T get() const
    {
        return obj_;
    }

    constexpr explicit operator bool() const
    {
        return this->obj_ != Invalid;
    }

    constexpr bool operator==(const AutoReleaseBase &other) const
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
    T obj_;

private:

    std::function<void(T &)> deleter_;
};

// Wrapper with specialization
template<class T, T Invalid = {}>
class AutoRelease : public AutoReleaseBase<T, Invalid>
{
    using AutoReleaseBase<T, Invalid>::AutoReleaseBase;

public:

    // implicit conversion to T, conflicts with `bool`, therefore we need specialization for bool
    operator T() const
    {
        return this->obj_;
    }
};

// Specialization for bool
template<>
class AutoRelease<bool, false> : public AutoReleaseBase<bool>
{
    using AutoReleaseBase::AutoReleaseBase;

public:

    explicit operator bool() const
    {
        return this->obj_;
    }
};
