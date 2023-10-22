#include <string>

#include "fluxsort/fluxsort.hpp"

extern "C" {
    // #include "fluxsort/quadsort.h"
    #include "fluxsort/fluxsort.h"
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