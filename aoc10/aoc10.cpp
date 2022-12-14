#include <iostream>
#include <string>

int main() {
    std::string s;
    int cycle = 1;
    int x = 1;
    std::string res(240, '.');
    while (std::getline(std::cin, s)) {
        if (s[0] == 'n') {
            if (abs((cycle % 40) - 1 - x) <= 1) {
                res[cycle - 1] = '#';
            }
            cycle++;
        } else {
            int nx = std::stol(s.substr(5));
            if (abs((cycle % 40) - 1 - x) <= 1) {
                res[cycle - 1] = '#';
            }
            cycle++;
            if (abs((cycle % 40) - 1 - x) <= 1) {
                res[cycle - 1] = '#';
            }
            cycle++;

            x += nx;
        }
    }
    for(int i = 0; i < 6; i++) {
        printf("%s\n", res.substr(i * 40, 40).c_str());
    }
}

//int main() {
//    std::string s;
//    int cycle = 1;
//    int sum = 0;
//    int x = 1;
//    int nx = 0;
//    while (std::getline(std::cin, s)) {
//        int oldcycle = cycle;
//        if (s[0] == 'n') {
//            cycle++;
//            nx = 0;
//
//            if ((cycle + 20) % 40 == 0) {
//                sum += cycle * x;
//                printf("sum %d %d\n", cycle * x, sum);
//            }
//        } else {
//            nx = std::stol(s.substr(5));
//            cycle += 2;
//            if ((oldcycle + 20) % 40 > (cycle + 20) % 40) {
//                if (cycle % 20 == 0) {
//                    sum += cycle * (x + nx);
//                    printf("sum %d %d\n", cycle * (x + nx), sum);
//                } else {
//                    sum += (cycle - 1) * x;
//                    printf("sum %d %d\n", cycle * x, sum);
//                }
//            }
//        }
//        x += nx;
//        printf("%d %d\n", cycle, x);
//    }
//    printf("%d\n", sum);
//}