#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string_view>

void notMain() {
    auto start = std::chrono::high_resolution_clock::now();

    std::string thing1 = "MZZZ0__";
    std::string thing2 = "MZZZZabsdjasbhdasdiasidbhasdsabdhsa";
    for (int i = 0; i < 100000000; i++) {
        thing1.erase(thing1.find_last_not_of('_') + 1);
        thing2.erase(thing2.find_last_not_of('_') + 1);
        std::string thing3 = thing2.substr(thing2.empty() ? 0 : 1, thing2.empty() ? 0 : 3);
        thing3 = thing3.substr(i % thing3.size());
        std::string thing4 = thing3.substr(i % thing3.size());
    }
    std::cout << (thing1 < thing2 ? "True" : "False") << " " << thing1 << " " << thing2;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nElapsed time: " << elapsed.count() << "s\n";
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::string alex = "Alex";
    std::string_view alexView(alex);
    if (alexView.find("J") == std::string::npos) {
        std::cout << "haha" << std::endl;
    } else {
        std::cout << "noo" << std::endl;
    }

    std::string thing1 = "MZZZ0__";
    std::string thing2 = "MZZZZabsdjasbhdasdiasidbhasdsabdhsa";
    for (int i = 0; i < 100000000; i++) {
        thing1.erase(thing1.find_last_not_of('_') + 1);
        thing2.erase(thing2.find_last_not_of('_') + 1);
        // std::string_view thing3(thing2);
        auto thing3 = std::string_view(thing2).substr(thing2.empty() ? 0 : 1, thing2.empty() ? 0 : 3);
        thing3 = thing3.substr(i % thing3.size());
        std::string_view thing4 = thing3.substr(i % thing3.size());
    }
    std::cout << (thing1 < thing2 ? "True" : "False") << " " << thing1 << " " << thing2;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nElapsed time: " << elapsed.count() << "s\n";

    notMain();

    return 0;
}
