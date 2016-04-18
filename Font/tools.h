#ifndef TOOLS_H
#define TOOLS_H


namespace Tools {
template<typename T>
std::pair<T, T> minmax(const std::vector<T> &points, std::function<bool(const T&, const T&)> comparator) {
    return {
        *std::min_element(std::begin(points), std::end(points), comparator),
        *std::max_element(std::begin(points), std::end(points), comparator)
    };
}
}

#endif // TOOLS_H
