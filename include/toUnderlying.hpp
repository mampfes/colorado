#pragma once

#include <type_traits>

template <typename T>
constexpr typename std::underlying_type<T>::type toUnderlying(T e) noexcept
{
    return static_cast<typename std::underlying_type<T>::type>(e);
}