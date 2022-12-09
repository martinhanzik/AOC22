#include <cstdio>
#include <iostream>
#include <set>

struct Pos {
    int x = 0;
    int y = 0;
};

void render(const std::vector<Pos>& knots) {
    int minx = 1000;
    int maxx = -1000;
    int miny = 1000;
    int maxy = -1000;
    for (int i = 0; i < 10; i++) {
        int x = knots[i].x;
        int y = knots[i].y;
        minx = std::min(minx, x);
        maxx = std::max(maxx, x);
        miny = std::min(miny, y);
        maxy = std::max(maxy, y);
    }

    for (int y = maxy; y >= miny; y--) {
        for (int x = minx; x <= maxx; x++) {
            bool printed = false;
            for (int k = 0; k < 10; k++) {
                if (knots[k].x == x && knots[k].y == y) {
                    std::cout << k;
                    printed = true;
                    break;
                }
            }
            if (printed) continue;
            if (x == 0 && y == 0)
                std::cout << 's';
            else
                std::cout << '.';
        }
        std::cout << std::endl;
    }
}

int main() {
    std::set<std::pair<int, int>> positions;
    std::vector<Pos> knots;
    knots.resize(11);
    char dir;
    int steps;
    while (scanf("%c %d\n", &dir, &steps) == 2) {
        printf("%c %d\n", dir, steps);
        for (int i = 0; i < steps; i++) {
            printf("step %d\n", i);
            int dx = dir == 'R' ? 1 : (dir == 'L' ? -1 : 0);
            int dy = dir == 'U' ? 1 : (dir == 'D' ? -1 : 0);
            for (int k = 0; k < 10; k++) {
//                printf("dx %d dy %d\n", dx, dy);
                int& hx = knots[k].x;
                int& hy = knots[k].y;
                int& tx = knots[k + 1].x;
                int& ty = knots[k + 1].y;
                int otx = tx;
                int oty = ty;

                int nhx = hx + dx;
                int nhy = hy + dy;

                int ntx = tx;
                int nty = ty;

                int xdiff = abs(nhx - tx);
                int ydiff = abs(nhy - ty);
                int diffsum = xdiff + ydiff;
                if (diffsum == 2) {
                    if (nhx == tx && abs(nhy - ty) == 2) {
                        nty += dy;
                    } else if (nhy == ty && abs(nhx - tx) == 2) {
                        ntx += dx;
                    }
                }
                if (diffsum == 3) {
                    if (xdiff == 1) {
                        ntx = nhx;
                        nty = (ty + nhy) / 2;
                    } else {
                        nty = nhy;
                        ntx = (tx + nhx) / 2;
                    }
                }
                if (diffsum == 4) {
                    ntx = (tx + nhx) / 2;
                    nty = (ty + nhy) / 2;
                }
                hx = nhx;
                hy = nhy;
                dx = ntx - otx;
                dy = nty - oty;
            }
            positions.insert(std::make_pair(knots[9].x, knots[9].y));
            render(knots);
            std::cout << std::endl;
        }
    }

    printf("%d\n", positions.size());
}
//int main() {
//    std::set<std::pair<int, int>> positions;
//    char dir;
//    int steps;
//    int tx = 0;
//    int ty = 0;
//    int hx = 0;
//    int hy = 0;
//    while (scanf("%c %d\n", &dir, &steps) == 2) {
//        int dx = dir == 'R' ? 1 : (dir == 'L' ? -1 : 0);
//        int dy = dir == 'U' ? 1 : (dir == 'D' ? -1 : 0);
//        for (int i = 0; i < steps; i++) {
//
//            int nhx = hx + dx;
//            int nhy = hy + dy;
//
//            int xdiff = abs(nhx - tx);
//            int ydiff = abs(nhy - ty);
//            int diffsum = xdiff + ydiff;
//            if (diffsum == 2) {
//                if (nhx == tx && abs(nhy - ty) == 2) {
//                    ty += dy;
//                } else if (nhy == ty && abs(nhx - tx) == 2) {
//                    tx += dx;
//                }
//            }
//            if (diffsum == 3) {
//                if (xdiff == 1) {
//                    tx = nhx;
//                    ty = (ty + nhy) / 2;
//                } else {
//                    ty = nhy;
//                    tx = (tx + nhx) / 2;
//                }
//            }
//
//            hx = nhx;
//            hy = nhy;
//            positions.insert(std::make_pair(tx, ty));
//        }
//    }
//
//    printf("%d\n", positions.size());
//}