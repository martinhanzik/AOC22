#include <vector>

struct Pos {
    int64_t x, y;
};
struct Item {
    Pos sensor, beacon;
    int64_t dist;
};

std::vector<Item> items_demo = {
        {{2,  18}, {-2, 15}},
        {{9,  16}, {10, 16}},
        {{13, 2},  {15, 3}},
        {{12, 14}, {10, 16}},
        {{10, 20}, {10, 16}},
        {{14, 17}, {10, 16}},
        {{8,  7},  {2,  10}},
        {{2,  0},  {2,  10}},
        {{0,  11}, {2,  10}},
        {{20, 14}, {25, 17}},
        {{17, 20}, {21, 22}},
        {{16, 7},  {15, 3}},
        {{14, 3},  {15, 3}},
        {{20, 1},  {15, 3}},
};

std::vector<Item> items_full = {
        {{3890859, 2762958}, {4037927, 2985317}},
        {{671793,  1531646}, {351996,  1184837}},
        {{3699203, 3052069}, {4037927, 2985317}},
        {{3969720, 629205},  {4285415, 81270}},
        {{41343,   57178},   {351996,  1184837}},
        {{2135702, 1658955}, {1295288, 2000000}},
        {{24022,   1500343}, {351996,  1184837}},
        {{3040604, 3457552}, {2994959, 4070511}},
        {{357905,  3997215}, {-101509, 3502675}},
        {{117943,  3670308}, {-101509, 3502675}},
        {{841852,  702520},  {351996,  1184837}},
        {{3425318, 3984088}, {2994959, 4070511}},
        {{3825628, 3589947}, {4299658, 3299020}},
        {{2745170, 139176},  {4285415, 81270}},
        {{878421,  2039332}, {1295288, 2000000}},
        {{1736736, 811875},  {1295288, 2000000}},
        {{180028,  2627284}, {-101509, 3502675}},
        {{3957016, 2468479}, {3640739, 2511853}},
        {{3227780, 2760865}, {3640739, 2511853}},
        {{1083678, 2357766}, {1295288, 2000000}},
        {{1336681, 2182469}, {1295288, 2000000}},
        {{3332913, 1556848}, {3640739, 2511853}},
        {{3663725, 2525708}, {3640739, 2511853}},
        {{2570900, 2419316}, {3640739, 2511853}},
        {{1879148, 3584980}, {2994959, 4070511}},
        {{3949871, 2889309}, {4037927, 2985317}}
};

bool compare(const Item& A, const Item& B) {
    return A.sensor.y < B.sensor.y;
}

int main() {
//    auto& items = items_demo;
    auto& items = items_full;

    int64_t xmax = std::numeric_limits<int64_t>::max();
    int64_t xmin = std::numeric_limits<int64_t>::min();

    for (auto& item: items) {
        item.dist = abs(item.sensor.x - item.beacon.x) + abs(item.sensor.y - item.beacon.y);
        xmax = std::max(std::max(xmax, item.sensor.x + item.dist), item.beacon.x + item.dist);
        xmin = std::min(std::min(xmin, item.sensor.x - item.dist), item.beacon.x - item.dist);
    }
    int64_t ymax = 20;
    ymax = 4000000;

    xmin = std::max(0ll, xmin);
    xmax = std::min(ymax, xmax);

    std::sort(items.begin(), items.end(), compare);

    for (int64_t y = 0; y <= ymax; y++) {
        if (y % 10000 == 0) printf("y: %d\n", y);
        for (int64_t x = 0; x <= xmax; x++) {
            bool can_be_beacon = true;
            for (const auto& item: items) {
                if (abs(item.sensor.x - x) + abs(item.sensor.y - y) <= item.dist) {
                    x = item.sensor.x + item.dist - abs(item.sensor.y - y);
                    x = std::min(x, xmax);
                    can_be_beacon = false;
                    break;
                }
            }
            if (can_be_beacon) {
                printf("%d %d, %d\n", x, y, x * 4000000 + y);

//                for (const auto& item: items) {
//                    printf("%d %d\n", item.dist, abs(item.sensor.x - x) + abs(item.sensor.y - y));
//                }
//                return 0;
            }
        }
    }
}
//int main() {
//    auto& items = items_full;
//
//    int xmax = INT_MIN, xmin = INT_MAX;
//
//    for (auto& item: items) {
//        item.dist = abs(item.sensor.x - item.beacon.x) + abs(item.sensor.y - item.beacon.y);
//        xmax = std::max(std::max(xmax, item.sensor.x + item.dist), item.beacon.x + item.dist);
//        xmin = std::min(std::min(xmin, item.sensor.x - item.dist), item.beacon.x - item.dist);
//    }
//
//    int ytarget = 10;
//    ytarget = 2000000;
//
//    int count = 0;
//    for (int x = xmin; x <= xmax; x++) {
//        bool can_be_beacon = true;
//        bool is_beacon = false;
//        for (const auto& item: items) {
//            if (abs(item.sensor.x - x) + abs(item.sensor.y - ytarget) <= item.dist) {
//                can_be_beacon = false;
//            }
//            if (item.beacon.x == x && item.beacon.y == ytarget)
//                is_beacon = true;
//        }
//        if (!can_be_beacon && !is_beacon)
//            count++;
//    }
//
//    printf("%d\n", count);
//}
