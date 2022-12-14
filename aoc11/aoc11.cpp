#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <numeric>
//Monkey 0:
//  Starting items: 79, 98
//  Operation: new = old * 19
//  Test: divisible by 23
//    If true: throw to monkey 2
//    If false: throw to monkey 3

enum class Operation {
    MultiplySelf,
    Multiply,
    Add
};

struct Monkey {
    std::queue<uint64_t> items;
    Operation operation;
    uint64_t operation_param;
    uint64_t test;
    uint64_t true_target;
    uint64_t false_target;
    uint64_t inspected = 0;
};

int main() {
    int id;
    std::vector<Monkey> monkeys;
    int lcm = 1;
    while(scanf("Monkey %d:\n", &id) == 1) {
        Monkey m;
        std::string s;
        std::getline(std::cin, s);
        std::stringstream ss(s.substr(16));
        int item;
        while (ss >> item) {
            m.items.push(item);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }

        // operation
        std::getline(std::cin, s);
        s = s.substr(23);
        if (s[0] == '+') {
            m.operation = Operation::Add;
            m.operation_param = std::stoi(s.substr(2));
        }
        else if (s[0] == '*' && s[2] == 'o') {
            m.operation = Operation::MultiplySelf;
        } else {
            m.operation = Operation::Multiply;
            m.operation_param = std::stoi(s.substr(2));
        }

        // test
        std::getline(std::cin, s);
        m.test = std::stoi(s.substr(21));
        lcm = std::lcm(lcm, m.test);
        // true
        std::getline(std::cin, s);
        m.true_target = std::stoi(s.substr(29));
        // false
        std::getline(std::cin, s);
        m.false_target = std::stoi(s.substr(30));

        monkeys.push_back(m);
        std::getline(std::cin, s);
    }

    for (int r = 0; r < 10000; r++) {
        for (int mi = 0; mi < monkeys.size(); mi++) {
            Monkey& m = monkeys[mi];
            while(!m.items.empty()) {
                uint64_t item = m.items.front();
                m.items.pop();
                switch (m.operation) {
                    case Operation::MultiplySelf:
                        item *= item;
                        break;
                    case Operation::Multiply:
                        item *= m.operation_param;
                        break;
                    case Operation::Add:
                        item += m.operation_param;
                        break;
                }
//                item /= 3;
                item %= lcm;
                if (item % m.test == 0) {
                    monkeys[m.true_target].items.push(item);
                } else {
                    monkeys[m.false_target].items.push(item);
                }
                m.inspected++;
            }
        }
    }
    std::vector<uint64_t> inspected;
    for (int m = 0; m < monkeys.size(); m++) {
        inspected.push_back(monkeys[m].inspected);
    }
    std::sort(inspected.begin(), inspected.end());
    printf("%lld\n", inspected[inspected.size() - 1] * inspected[inspected.size() - 2]);
}