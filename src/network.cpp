#include "opennet/network.hpp"

#include <algorithm>
#include <queue>
#include <unordered_map>

namespace opennet {

bool Network::add_node(NodeId id) {
    return links_.emplace(id, std::vector<NodeId>{}).second;
}

bool Network::connect(NodeId left, NodeId right) {
    if (left == right || !links_.contains(left) || !links_.contains(right)) {
        return false;
    }

    auto& left_links = links_.at(left);
    auto& right_links = links_.at(right);
    if (std::find(left_links.begin(), left_links.end(), right) != left_links.end()) {
        return false;
    }

    left_links.push_back(right);
    right_links.push_back(left);
    return true;
}

std::optional<Route> Network::route(NodeId source, NodeId destination) const {
    if (!links_.contains(source) || !links_.contains(destination)) {
        return std::nullopt;
    }

    // Every link has the same cost, so breadth-first search finds the
    // shortest route. `previous` records how each node was reached.
    std::queue<NodeId> pending;
    std::unordered_map<NodeId, NodeId> previous;
    pending.push(source);
    previous.emplace(source, source);

    while (!pending.empty()) {
        const auto current = pending.front();
        pending.pop();
        if (current == destination) {
            Route result;
            for (auto node = destination;; node = previous.at(node)) {
                result.push_back(node);
                if (node == source) {
                    break;
                }
            }
            std::reverse(result.begin(), result.end());
            return result;
        }

        for (const auto neighbour : links_.at(current)) {
            if (!previous.contains(neighbour)) {
                previous.emplace(neighbour, current);
                pending.push(neighbour);
            }
        }
    }

    return std::nullopt;
}

}  // namespace opennet
