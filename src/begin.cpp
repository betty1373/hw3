#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

template<typename Container>
void printContainter(const Container& values) {
    for (auto v : values)
        std::cout << v << ' ';
    std::cout << std::endl;
}

template<typename Container>
void sort(Container& values) {
    std::cout << "size = " << std::size(values) << std::endl;
    std::cout << (std::empty(values) ? "empty!" : "not empty!") << std::endl;
    std::sort(std::begin(values), std::end(values));
}

std::ostream& operator<<(std::ostream& os, const std::pair<const int, std::string>& pair) {
    os << pair.first << " <-> " << pair.second << '\n';
    return os;
}

int main() {
    int c_array[] = {3, 1, 4, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3};
    printContainter(c_array);

    std::vector<char> vector = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    printContainter(vector);

    std::map<int, std::string> map = {
        {0, {}},
        {1, {'a'}},
        {2, {"ab"}},
        {3, {"abc"}}
    };
    printContainter(map);

    sort(c_array);
    printContainter(c_array);
    sort(vector);
    printContainter(vector);

    // compile error
    // sort(map);
    // printContainter(map);

    return 0;
}