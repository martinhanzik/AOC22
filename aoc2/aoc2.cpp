#include <cstdio>

// rock A X
// paper B Y
// scissors C Z

// AX d 00 0
// AY w 01 1
// AZ l 02 2
// BX l 10 2
// BY d 11 0
// BZ w 12 1
// CX w 20 1
// CY l 21 2
// CZ d 22 0

int main() {
    int sum = 0;
    for (;;) {
        char c1, c2, outc;
        if (scanf("%c %c\n", &c1, &outc) != 2)
            break;
        printf("%c %c\n", c1, outc);
        c1 -= 'A';
        outc -= 'X';
//        printf("%d\n", c1);
//        printf("%d\n", c2);
        c2 = (outc + c1 + 2) % 3;
        printf("%d\n", c2);
        char res = ((c2 + 4 - c1) % 3) * 3;
//        printf("%d\n", res);
        res += c2 + 1;
//        printf("%d\n", res);
        sum += res;
    }
    printf("%d\n", sum);
}