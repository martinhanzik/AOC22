#include <vector>
#include <string>
#include <iostream>

int process_dir(std::vector<std::string>& data, size_t y, size_t x, int dy, int dx) {
    int count = 0;
    char start_size = data[y][x];
    size_t width = data[0].size();
    size_t height = data.size();
    while (y != 0 && y != height - 1 && x != 0 && x != width - 1) {
        x += dx;
        y += dy;
        char c = data[y][x];
        count++;
        if (c >= start_size) break;

    }
    return count;
}

int process(std::vector<std::string>& data, size_t y, size_t x) {
    int res = 1;
    res *= process_dir(data, y, x, 1, 0);
    res *= process_dir(data, y, x, -1, 0);
    res *= process_dir(data, y, x, 0, 1);
    res *= process_dir(data, y, x, 0, -1);
    return res;
}

int main() {
    std::vector<std::string> data;
    std::string s;
    while (std::getline(std::cin, s)) {
        data.push_back(s);
    }

    size_t width = data[0].size();
    size_t height = data.size();
    int max = 0;
    for (size_t y = 1; y < height - 1; y++) {
        for (size_t x = 1; x < width - 1; x++) {
            int score = process(data, y, x);
            if (score > max)
                max = score;
        }
    }
    printf("%d\n", max);
}
//}
//char process(std::vector<std::string>& data, std::vector<std::string>& visible, size_t y, size_t x, char last) {
//    char cur = data[y][x];
//    if (cur > last) {
//        visible[y][x] = '.';
//        last = cur;
//    }
//    if (cur == '9') return -1;
//    return last;
//}
//
//int main() {
//    std::vector<std::string> data;
//    std::string s;
//    while (std::getline(std::cin, s)) {
//        data.push_back(s);
//    }
//
//    std::vector<std::string> visible = data;
//    size_t width = data[0].size();
//    size_t height = data.size();
//
//    for (size_t y = 1; y < height - 1; y++) {
//        char last = data[y][0];
//        for (size_t x = 1; x < width - 1; x++) {
//            last = process(data, visible, y, x, last);
//            if (last == -1) break;
//        }
//
//        last = data[y][width - 1];
//        for (size_t x = width - 2; x > 0; x--) {
//            last = process(data, visible, y, x, last);
//            if (last == -1) break;
//        }
//    }
//
//    for (size_t x = 1; x < width - 1; x++) {
//        char last = data[0][x];
//        for (size_t y = 1; y < height - 1; y++) {
//            last = process(data, visible, y, x, last);
//            if (last == -1) break;
//        }
//
//        last = data[height - 1][x];
//        for (size_t y = height - 2; y > 0; y--) {
//            last = process(data, visible, y, x, last);
//            if (last == -1) break;
//        }
//    }
//    int sum = 0;
//    for (int y = 1; y < height - 1; y++) {
//        for (int x = 1; x < width - 1; x++) {
//            if (visible[y][x] == '.') sum++;
//        }
//    }
//    sum += 2 * (width + height - 2);
//    printf("%d\n", sum);
//}