#include <string>
#include <iostream>
#include <unordered_set>

int main() {
    std::string s;
    std::getline(std::cin, s);
    size_t i;
    char c1 = s[0];
    char c2 = s[1];
    char c3 = s[2];
    char c4;
    for (i = 13; i < s.size(); i++) {
        std::unordered_set<char> cset;
        cset.insert(s.begin() + (i - 13), s.begin() + i + 1);
//        printf("%d\n", cset.size());
        if (cset.size() == 14) break;

    }
    printf("%d\n", i + 1);
}
//int main() {
//    std::string s;
//    std::getline(std::cin, s);
//    size_t i;
//    char c1 = s[0];
//    char c2 = s[1];
//    char c3 = s[2];
//    char c4;
//    for (i = 3; i < s.size(); i++) {
//        c4 = s[i];
//        if (c1 != c2 && c1 != c3 && c1 != c4 && c2 != c3 && c2 != c4 && c3 != c4) break;
//        c1 = c2;
//        c2 = c3;
//        c3 = c4;
//    }
//    printf("%d\n", i + 1);
//}