#include <concepts>
#include <iostream>
#include <list>
#include <vector>

template <typename T>
concept IterableWithFloats = std::floating_point<typename T::value_type> &&
                             std::ranges::forward_range<T>;

auto average(const IterableWithFloats auto &values) {
    typename std::iter_value_t<decltype(values)> sum = 0.0;
    for (const auto value : values) {
        sum += value;
    }
    return sum / values.size();
}

int main() {
    std::vector<float> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::list<double> values2 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::cout << average(values) << std::endl;
    std::cout << average(values2) << std::endl;
    return 0;
}
