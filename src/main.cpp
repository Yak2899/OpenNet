#include "opennet/network.hpp"

#include <iostream>

int main() {
    opennet::Network network;
    for (const auto node : {1U, 2U, 3U, 4U}) {
        network.add_node(node);
    }
    network.connect(1, 2);
    network.connect(2, 3);
    network.connect(3, 4);

    const auto path = network.route(1, 4);
    if (!path) {
        std::cerr << "No route found\n";
        return 1;
    }

    std::cout << "Route:";
    for (const auto node : *path) {
        std::cout << ' ' << node;
    }
    std::cout << '\n';
}
