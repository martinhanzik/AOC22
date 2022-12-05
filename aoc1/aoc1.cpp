#include <iostream>
#include <vector>

int main() {
    std::vector<int> sums;
    int sum = 0;
    while(std::cin) {
        int x;
        std::cin >> x;
        sum += x;
        std::cin.get();
        std::cout << x << std::endl;
        if (std::cin.peek() == '\n') {
            sums.push_back(sum);
            sum = 0;
            std::cout << std::endl;
        }
    }
    std::sort(sums.begin(), sums.end());
    std::cout << sums.at(sums.size() - 1) + sums.at(sums.size() - 2) + sums.at(sums.size() - 3) << std::endl;
    return 0;
}
