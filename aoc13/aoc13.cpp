#include <string>
#include <sstream>
#include <iostream>

struct Item {
    bool list = false;
    int value = 0;
    std::vector<std::unique_ptr<Item>> items;

    Item* parent = nullptr;
    Item* next_sibling = nullptr;
};

std::vector<std::unique_ptr<Item>> parse_list(std::stringstream& ss) {
    std::vector<std::unique_ptr<Item>> items;
    ss.get(); // [

    while(true) {
        char c = ss.peek();
        if (c == ']') break;
        if (isdigit(c)) {
            int x;
            std::unique_ptr<Item> item = std::make_unique<Item>();
            ss >> item->value;

            if (!items.empty())
                items[items.size() - 1]->next_sibling = item.get();
            items.push_back(std::move(item));
        } else {
            std::unique_ptr<Item> item = std::make_unique<Item>();
            item->list = true;
            item->items = parse_list(ss);
            for (auto& child: item->items)
                child->parent = item.get();

            if (!items.empty())
                items[items.size() - 1]->next_sibling = item.get();
            items.push_back(std::move(item));

            ss.get(); // ]
        }
        if (ss.peek() == ',') ss.get();
    }

    return items;
}

std::unique_ptr<Item> parse(const std::string& s) {
    std::unique_ptr<Item> item = std::make_unique<Item>();
    item->list = true;

    std::stringstream ss(s);

    item->items = parse_list(ss);
    for (auto& child: item->items)
        child->parent = item.get();

    return item;
}

enum class Tristate {
    True,
    False,
    Continue
};

Tristate compare(Item* A, Item* B) {
    if (!A->list && !B->list) {
        if (A->value < B->value) return Tristate::True;
        if (A->value > B->value) return Tristate::False;
    }

    if (!A->list && B->list) {
        A->list = true;
        std::unique_ptr<Item> item = std::make_unique<Item>();
        item->value = A->value;
        A->items.push_back(std::move(item));
    }
    if (!B->list && A->list) {
        B->list = true;
        std::unique_ptr<Item> item = std::make_unique<Item>();
        item->value = B->value;
        B->items.push_back(std::move(item));
    }

    if (A->list && B->list) {
        for (int i = 0; i < std::min(A->items.size(), B->items.size()); i++) {
            Tristate res = compare(A->items[i].get(), B->items[i].get());
            if (res != Tristate::Continue) return res;
        }
        if (A->items.size() < B->items.size()) return Tristate::True;
        if (A->items.size() > B->items.size()) return Tristate::False;
    }

    return Tristate::Continue;
}

bool compare_pair(const std::pair<std::string, std::unique_ptr<Item>>& A, const std::pair<std::string, std::unique_ptr<Item>>& B) {
    return compare(A.second.get(), B.second.get()) == Tristate::True;
}

int main() {
    int i = 1, sum = 0;
    std::string a, b;
    std::vector<std::pair<std::string, std::unique_ptr<Item>>> items;
    while(std::getline(std::cin, a), std::getline(std::cin, b)) {
        std::cin.get();

        std::unique_ptr<Item> rootA = parse(a);
        std::unique_ptr<Item> rootB = parse(b);

        items.push_back(std::make_pair(a, std::move(rootA)));
        items.push_back(std::make_pair(b, std::move(rootB)));
    }

    items.push_back(std::make_pair("[[2]]", parse("[[2]]")));
    items.push_back(std::make_pair("[[6]]", parse("[[6]]")));

    std::sort(items.begin(), items.end(), compare_pair);

    int ia, ib;
    for (int i = 0; i < items.size(); i++) {
        const std::string& s = items[i].first;
        if (s == "[[2]]") ia = i + 1;
        if (s == "[[6]]") ib = i + 1;
    }
    printf("%d\n", ia * ib);
}
//
//int main() {
//    int i = 1, sum = 0;
//    std::string a, b;
//    while(std::getline(std::cin, a), std::getline(std::cin, b)) {
//        std::cin.get();
//
//        std::unique_ptr<Item> rootA = parse(a);
//        std::unique_ptr<Item> rootB = parse(b);
//
//        Item* A = rootA.get();
//        Item* B = rootB.get();
//
//        Tristate res = compare(A, B);
//        if (res == Tristate::True) {
//            printf("%d true\n", i);
//            sum +=i;
//        }
//
//        i++;
//    }
//    printf("%d\n", sum);
//}
