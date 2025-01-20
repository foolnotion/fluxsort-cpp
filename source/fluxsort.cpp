#include <concepts>
#include <string>
#include <type_traits>

#include "fluxsort/fluxsort.hpp"

extern "C" {
    // #include "fluxsort/quadsort.h"
    #include "fluxsort/blitsort.h"
    #include "fluxsort/fluxsort.h"
}

namespace blit {
auto FLUXSORT_EXPORT sort(void *array, size_t nmemb, size_t size, std::add_pointer_t<int(void const*, void const*)> cmp) -> void {
    blitsort(array, nmemb, size, cmp);
}
}

namespace quad {
auto FLUXSORT_EXPORT sort(void *array, size_t nmemb, size_t size, std::add_pointer_t<int(void const*, void const*)> cmp) -> void {
    quadsort(array, nmemb, size, cmp);
}
}

namespace flux {
auto FLUXSORT_EXPORT sort(void *array, size_t nmemb, size_t size, std::add_pointer_t<int(void const*, void const*)> cmp) -> void {
    fluxsort(array, nmemb, size, cmp);
}
}