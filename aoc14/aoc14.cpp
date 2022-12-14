#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

struct Pos {
    int x, y;
};

void print(const std::vector<std::string>& data) {
    int w = data[0].size() + 4;
    for (int i = 0; i < data.size(); i++) {
        std::cout << std::setfill(' ') << std::setw(3) << i << ' ';
        std::cout << data[i] << std::endl;
    }
    std::cout << std::string(w, '-') << std::endl;
    std::cout << std::endl;
}

int main() {
    std::vector<std::vector<Pos>> lines;
    std::string s;
    int minx = 1000000;
    int miny = 1000000;
    int maxx = 0;
    int maxy = 0;
    while (std::getline(std::cin, s)) {
        std::stringstream ss(s);
        std::vector<Pos> line;
        while (ss) {
            int x, y;
            ss >> x;
            ss.get();
            ss >> y;
            line.push_back({x, y});
            minx = std::min(minx, x);
            maxx = std::max(maxx, x);
            miny = std::min(miny, y);
            maxy = std::max(maxy, y);

            if (ss.peek() == ' ') {
                ss.get();
                ss.get();
                ss.get();
                ss.get();
            } else if (!ss)
                break;
        }
        lines.push_back(line);
    }

    maxy += 1;
    minx -= maxy;
    maxx += maxy;


    std::vector<std::string> data;
    data.resize(maxy + 1);

    for (int y = 0; y <= maxy; y++) {
        data[y].resize(maxx - minx + 1, ' ');
    }

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size() - 1; j++) {
            Pos cur = lines[i][j];
            Pos to = lines[i][j + 1];
            int xdiff = to.x - cur.x;
            xdiff /= abs(xdiff);
            int ydiff = to.y - cur.y;
            ydiff /= abs(ydiff);

            while (cur.x != to.x || cur.y != to.y) {
                data[cur.y][cur.x - minx] = '#';
                printf("%d, %d\n", cur.x - minx, cur.y);

                cur.x += xdiff;
                cur.y += ydiff;
            }
            data[cur.y][cur.x - minx] = '#';
            printf("%d, %d\n", cur.x - minx, cur.y);
        }
    }

    print(data);
    bool done = false;
    int rested = 0;
    while(data[0][500 - minx] != '+') {
        int sx = 500 - minx;
        int sy = 0;

        while(true) {
            if (data[sy + 1][sx] == ' ') {
                sy++;
            } else if (data[sy + 1][sx - 1] == ' ') {
                sy++;
                sx--;
            } else if (data[sy + 1][sx + 1] == ' ') {
                sy++;
                sx++;
            } else {
                break;
            }

            if (sy == maxy) {
                break;
            }
        }

        data[sy][sx] = '+';
        rested++;
//        print(data);
    }
    printf("%d\n", rested);

}
//
//int main() {
//    std::vector<std::vector<Pos>> lines;
//    std::string s;
//    int minx = 1000000;
//    int miny = 1000000;
//    int maxx = 0;
//    int maxy = 0;
//    while (std::getline(std::cin, s)) {
//        std::stringstream ss(s);
//        std::vector<Pos> line;
//        while (ss) {
//            int x, y;
//            ss >> x;
//            ss.get();
//            ss >> y;
//            line.push_back({x, y});
//            minx = std::min(minx, x);
//            maxx = std::max(maxx, x);
//            miny = std::min(miny, y);
//            maxy = std::max(maxy, y);
//
//            if (ss.peek() == ' ') {
//                ss.get();
//                ss.get();
//                ss.get();
//                ss.get();
//            } else if (!ss)
//                break;
//        }
//        lines.push_back(line);
//    }
//
//    minx--;
//    maxx++;
//
//    std::vector<std::string> data;
//    data.resize(maxy + 1);
//
//    for (int y = 0; y <= maxy; y++) {
//        data[y].resize(maxx - minx + 1, ' ');
//    }
//
//    for (int i = 0; i < lines.size(); i++) {
//        for (int j = 0; j < lines[i].size() - 1; j++) {
//            Pos cur = lines[i][j];
//            Pos to = lines[i][j + 1];
//            int xdiff = to.x - cur.x;
//            xdiff /= abs(xdiff);
//            int ydiff = to.y - cur.y;
//            ydiff /= abs(ydiff);
//
//            while (cur.x != to.x || cur.y != to.y) {
//                data[cur.y][cur.x - minx] = '#';
//                printf("%d, %d\n", cur.x - minx, cur.y);
//
//                cur.x += xdiff;
//                cur.y += ydiff;
//            }
//            data[cur.y][cur.x - minx] = '#';
//            printf("%d, %d\n", cur.x - minx, cur.y);
//        }
//    }
//
//    print(data);
//    bool done = false;
//    int rested = 0;
//    while(data[0][500 - minx] != '+') {
//        int sx = 500 - minx;
//        int sy = 0;
//
//        while(true) {
//            if (data[sy + 1][sx] == ' ') {
//                sy++;
//            } else if (data[sy + 1][sx - 1] == ' ') {
//                sy++;
//                sx--;
//            } else if (data[sy + 1][sx + 1] == ' ') {
//                sy++;
//                sx++;
//            } else {
//                break;
//            }
//
//            if (sy == maxy) {
//                done = true;
//                break;
//            }
//        }
//        if (done) {
//            break;
//        }
//
//        data[sy][sx] = '+';
//        rested++;
//        print(data);
//    }
//    printf("%d\n", rested);
//
//}
