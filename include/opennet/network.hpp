#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

namespace opennet {

using NodeId = std::uint32_t;
using Route = std::vector<NodeId>;

class Network {
public:
    // Add a node. Returns false when the node already exists.
    bool add_node(NodeId id);

    // Create a bidirectional link between two existing nodes.
    bool connect(NodeId left, NodeId right);

    // Find the shortest route using the links currently in the network.
    std::optional<Route> route(NodeId source, NodeId destination) const;

private:
    std::unordered_map<NodeId, std::vector<NodeId>> links_;
};

}  // namespace opennet
