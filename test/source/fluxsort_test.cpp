#include <random>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

#include "fluxsort/fluxsort.hpp"
#include "ut.hpp"

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

auto main() -> int
{
    using namespace boost::ut;

    using a = std::tuple<int, float>;
    using b = std::tuple<int, double>;

    std::uniform_int_distribution<int> uniform_int(1, 100);
    std::uniform_real_distribution<double> uniform_real(-1, 1);
    std::default_random_engine rd{};

    auto print = [](auto const& vec) {
        for (auto v : vec) { std::cout << "[" << std::get<0>(v) << ", " << std::get<1>(v) << "] "; }
        std::cout << "\n";
    };

    auto generate_b = [&](int n) {
        std::vector<b> bs; bs.reserve(n);
        for (auto i = 0; i < n; ++i) {
            bs.emplace_back(uniform_int(rd), uniform_real(rd));
        }
        return bs;
    };

    std::cout << "sizeof(b): " << sizeof(b) << ", sizeof(long double): " << sizeof(long double) << "\n";

    for (auto i = 0; i < 1000; ++i) {
        auto const n = std::uniform_int_distribution<int>(1000, 10'000)(rd);
        auto vec = generate_b(n);

        for (auto j = 0; j < 10; ++j) {
            flux::sort(vec, [](auto t) { return std::get<1>(t); });
        }
    }


    // auto constexpr n{2'000'000};
    // // std::vector<a> as(n);
    // auto as_ = std::make_unique<a[]>(n);
    // std::span<a> as(as_.get(), n);
    // std::generate(as.begin(), as.end(), [&](){ return a{ uniform_int(rd), uniform_real(rd) }; });
    // // std::cout << "before: "; print(as);
    // flux::sort(as, [](auto t) { return std::get<1>(t); });
    // // std::cout << "after: "; print(as);

    // // std::vector<b> bs(n);
    // auto bs_ = std::make_unique<a[]>(n);
    // std::span<a> bs(bs_.get(), n);
    // std::generate(bs.begin(), bs.end(), [&](){ return b{ uniform_int(rd), uniform_real(rd) }; });
    // // std::cout << "before: "; print(bs);
    // flux::sort(bs, [](auto t) { return std::get<1>(t); });
    // // std::cout << "after: "; print(bs);
}
