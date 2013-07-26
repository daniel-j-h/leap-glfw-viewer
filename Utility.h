#pragma once


#define likely(x)   __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)


template <typename T, std::size_t N>
constexpr std::size_t safe_sizeof(T (&)[N]) {
  return N;
}

