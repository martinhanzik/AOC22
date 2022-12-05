#include <cstdio>
#include <utility>

int main() {
    int a1, a2, b1, b2;
    int count = 0;
    while(scanf("%d-%d,%d-%d\n", &a1, &a2, &b1, &b2) == 4) {
        if (a1 > b1 || (a1 == b1 && a2 > b2)) {
            std::swap(a1, b1);
            std::swap(a2, b2);
        }
        if (b1 <= a2) count += 1;
    }
    printf("%d\n", count);
}
//int main() {
//    int a1, a2, b1, b2;
//    int count = 0;
//    while(scanf("%d-%d,%d-%d\n", &a1, &a2, &b1, &b2) == 4) {
//        if (a1 <= b1 && a2 >= b2) {
//            count += 1;
//            printf("%d-%d,%d-%d\n", a1, a2, b1, b2);
//            continue;
//        }
//        if (b1 <= a1 && b2 >= a2) {
//            count += 1;
//            printf("%d-%d,%d-%d\n", a1, a2, b1, b2);
//        }
//    }
//    printf("%d\n", count);
//}