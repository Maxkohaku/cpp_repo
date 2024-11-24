#ifndef _COMMON_HPP_
#define _COMMON_HPP_
#include <iostream>
inline void LOG_IMPL() {
    std::cout << std::endl;
}

template <typename First, typename... Rest>
void LOG_IMPL(const First& first, const Rest&... rest) {
    std::cout << first;
    LOG_IMPL(rest...);  // 递归展开所有参数
}

#if DEBUG
    #define LOG_DEBUG(...) do { \
        std::cout << "[DEBUG] "; \
        LOG_IMPL(__VA_ARGS__); \
    } while (0)
#else
    #define LOG_DEBUG(...) ((void)0)
#endif

    #define LOG_INFO(...) do { \
        std::cout << "[INFO] "; \
        LOG_IMPL(__VA_ARGS__); \
    } while (0)

#endif /*_COMMON_HPP_*/