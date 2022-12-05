#include <string>
#include <vector>
#include <iostream>

//    [D]
//[N] [C]
//[Z] [M] [P]
// 1   2   3
//
//move 1 from 2 to 1
//move 3 from 1 to 3
//move 2 from 2 to 1
//move 1 from 1 to 2

int main() {
    std::vector<std::vector<char>> data;
    while(true) {
        std::string line;
        std::getline(std::cin, line);
        if (line[1] == '1') {
            break;
        }

        for (int i = 0; i < (line.length() + 1) / 4; i++) {
            char c = line[i * 4 + 1];
            if (c != ' ') {
                if (i + 1 > data.size()) {
                    data.resize(i + 1);
                }
                data[i].push_back(c);
            }
        }
    }
    int cols = data.size();
    for (int i = 0; i < cols; i++)
        std::reverse(data[i].begin(), data[i].end());

    while (std::cin.get() != '\n');

    int count, from, to;
    while(scanf("move %d from %d to %d\n", &count, &from, &to) == 3) {
        std::cout << count << from << to << std::endl;
        to--;
        from--;
        for (int i = 0; i < count; i++) {
            data[to].push_back(data[from].at(data[from].size() - count + i));
        }
        for (int i = 0; i < count; i++) {
            data[from].pop_back();
        }
    }

    for (int i = 0; i < cols; i++) {
        std::cout << data[i].back();
    }
    std::cout << std::endl;


}