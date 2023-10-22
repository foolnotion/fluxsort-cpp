#pragma once

#include <string>
#include <type_traits>

#include "fluxsort/fluxsort_export.hpp"

namespace quad {
    auto sort(void *, size_t, size_t, std::add_pointer_t<int(void const*, void const*)>) -> void;
} // namespace quad

namespace flux {
    auto sort(void *, size_t, size_t, std::add_pointer_t<int(void const*, void const*)>) -> void;
} // namespace flux
