#include <string>
#include <iostream>
#include <set>
#include <unordered_map>

struct Dir {
    Dir* parent = nullptr;
    int size = 0;
    std::unordered_map<std::string, std::unique_ptr<Dir>> dirs;
    std::unordered_map<std::string, int> files;
};

void walk(Dir* dir, int& sum, std::vector<int>& sizes) {
    int total_size = dir->size;
    for (auto& [name, child]: dir->dirs) {
        walk(child.get(), sum, sizes);
        total_size += child->size;
    }
    if (total_size < 100000)
        sum += total_size;
    dir->size = total_size;
    sizes.push_back(total_size);
}

int main() {
    Dir root;
    Dir* workdir = &root;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line[2] == 'c') { // cd
            std::string path = line.substr(5);
            if (path[0] == '/') {
                workdir = &root;
            } else if (path[0] == '.') {
                workdir = workdir->parent;
            } else {
                if (workdir->dirs.count(path)) {
                    workdir = workdir->dirs[path].get();
                } else {
                    abort();
//                    std::unique_ptr<Dir> dir = std::make_unique<Dir>();
//                    dir->parent = workdir;
//                    workdir->dirs[path] = std::move(dir);
//                    workdir = dir.get();
                }
            }
        } else { // ls
            while (true) {
                int peek = std::cin.peek();
                if (peek == EOF || peek == '$') break;
                std::getline(std::cin, line);
                if (line[0] == 'd') { //dir
                    std::string path = line.substr(4);
                    std::unique_ptr<Dir> dir = std::make_unique<Dir>();
                    dir->parent = workdir;
                    workdir->dirs[path] = std::move(dir);
                } else { //file
                    size_t idx;
                    int size = std::stoi(line, &idx);
                    std::string name = line.substr(idx + 1);
                    workdir->files[name] = size;
                    workdir->size += size;
                }
            }
        }
    }
    int sum = 0;
    std::vector<int> sizes;
    walk(&root, sum, sizes);
    printf("%d\n", sum);
    std::sort(sizes.begin(), sizes.end());
    int tofree = root.size - 40000000;
    for (int i = 0; i < sizes.size(); i++) {
        if (sizes[i] >= tofree) {
            printf("%d\n", sizes[i]);
            break;
        }
    }
}