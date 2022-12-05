#include <string>
#include <iostream>

int prio(char c) {
    if (c >= 'a') {
        return c - 'a' + 1;
    }
    return c - 'A' + 27;
}

int main() {
    std::string s1, s2, s3;
    int sum = 0;
    while (std::getline(std::cin, s1)) {
        std::getline(std::cin, s2);
        std::getline(std::cin, s3);

        std::vector<size_t> counts(52, 0);
        for (char i : s1) {
            size_t ci = prio(i) - 1;
            counts[ci] = 1;
        }
        for (char i : s2) {
            size_t ci = prio(i) - 1;
            if (counts[ci] == 1) counts[ci] = 2;
        }
        for (char i : s3) {
            size_t ci = prio(i) - 1;
            if (counts[ci] == 2) {
                sum += ci + 1;
                break;
            }
        }
    }
    std::cout << sum << std::endl;
}

//int main() {
//    std::string s;
//    int sum = 0;
//    while (std::getline(std::cin, s)) {
//        size_t len = s.length() / 2;
//        std::vector<size_t> counts(52, 0);
//        for (size_t i = 0; i < len; i++) {
//            char c = s[i];
//            counts[prio(c) - 1]++;
//        }
//        for (size_t i = 0; i < len; i++) {
//            char c = s[i + len];
//            int p = prio(c) - 1;
//            if (counts[p] > 0) {
//                sum += p + 1;
//                counts[p] = 0;
//                std::cout << c << ' ' << p << std::endl;
//            }
//        }
//    }
//    std::cout << sum << std::endl;
//}