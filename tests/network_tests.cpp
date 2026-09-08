#include "opennet/network.hpp"

#include <cassert>

int main() {
    opennet::Network network;
    assert(network.add_node(1));
    assert(network.add_node(2));
    assert(network.add_node(3));
    assert(!network.add_node(1));

    assert(network.connect(1, 2));
    assert(network.connect(2, 3));
    assert(!network.connect(1, 2));
    assert(!network.connect(3, 99));

    const auto route = network.route(1, 3);
    assert(route);
    assert((*route == opennet::Route{1, 2, 3}));
    assert(!network.route(1, 99));

    opennet::Network disconnected;
    disconnected.add_node(10);
    disconnected.add_node(20);
    assert(!disconnected.route(10, 20));
}
