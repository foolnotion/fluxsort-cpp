# fluxsort-cpp

Thin C++ wrapper of https://github.com/scandum/fluxsort with CMake support.
The API remains the same but the C++ methods are renamed to `flux::sort()` and `quad::sort()`. Nicer wrappers are planned in the future.

## Usage

In `CMakeLists.txt`:
```cmake
find_package(fluxsort REQUIRED)
...
target_link_libraries(yourlibrary fluxsort::fluxsort)
```

In C++ code:
```cpp
#include <fluxsort/fluxsort.hpp>

// the sorting methods are in namespaces flux (for fluxsort) and quad (for quadsort)
auto cmp = [](auto a, auto b) {
    auto fa = *static_cast<int const*>(a);
    auto fb = *static_cast<int const*>(b);
    return (fa > fb) - (fa < fb);
};

vector<int> vec{ 1, 2, 3, 4 };
flux::sort(vec.data(), vec.size(), sizeof(int), cmp);
```
