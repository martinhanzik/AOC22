#include <vector>
#include <string>
#include <iostream>
#include <queue>

struct Pos {
    int x, y, steps;
};

void bfs(std::vector<std::string>& dirs, size_t x, size_t y, size_t w, size_t h, size_t startx, size_t starty, std::vector<std::vector<int>>& steps) {
    if (x < 0 || y < 0 || x >= w || x >= h)
        return;

    bfs(dirs, x+1, y+0, w, h, startx, starty, steps);
}

int main() {
    std::string line;
    std::vector<std::string> data;
    while (std::getline(std::cin, line)) {
        data.push_back(line);
    }
    size_t w = data[0].size();
    size_t h = data.size();

    int startx, starty, endx, endy;

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            char c = data[y][x];
            if (c == 'S') {
                startx = x;
                starty = y;
                data[y][x] = 'a';
            } else if (c == 'E') {
                endx = x;
                endy = y;
                data[y][x] = 'z';
            }
        }
    }

    std::vector<std::string> dirs(h);
    std::vector<std::vector<int>> steps(h);
    for (size_t i = 0; i < h; i++) {
        dirs[i].resize(w);
        steps[i].resize(w, 1000000);
    }

    std::queue<Pos> Q;
    Q.push({endx, endy, 0});
    while (!Q.empty()) {
        Pos item = Q.front();
        Q.pop();
        int x = item.x;
        int y = item.y;
        int S = item.steps;
        char c = data[y][x];
        printf("%c at (%d, %d) in %d steps\n", c, x, y, S);

        if (x < 0 || y < 0 || x >= w || y >= h)
            continue;

        if (steps[y][x] > S) {
            steps[y][x] = S;
        } else {
            continue;
        }

        if (data[y+0][x+1] >= c - 1) Q.push({x+1, y+0, S+1});
        if (data[y+0][x-1] >= c - 1) Q.push({x-1, y+0, S+1});
        if (data[y+1][x+0] >= c - 1) Q.push({x+0, y+1, S+1});
        if (data[y-1][x+0] >= c - 1) Q.push({x+0, y-1, S+1});
    }

    printf("%d\n", steps[starty][startx]);
    int min = 1000000;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (data[y][x] == 'a' && steps[y][x] < min) {
                min = steps[y][x];
            }
        }
    }
    printf("%d\n", min);
}