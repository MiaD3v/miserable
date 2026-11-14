#include <cstdlib>
#include <print>

#define PANIC(...) do {                                                        \
    std::print(stderr, "PANIC: ");                                             \
    std::print(stderr, __VA_ARGS__);                                           \
    std::print(stderr, "\n");                                                  \
    std::abort();                                                              \
} while (0)

