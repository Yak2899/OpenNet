# OpenNet

OpenNet is a small, dependency-free C++20 playground for exploring how an
internet could be built from first principles. It is intentionally a starter
project: the in-memory network in this repository is a clear place to add
packets, transports, discovery, and persistence without hiding the important
ideas behind a framework.

## Quick start

Requirements:

- CMake 3.20 or newer
- A compiler with C++20 support

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/opennet_demo
```

The demo prints the route found through a four-node network.

## Project layout

| Path | Purpose |
| --- | --- |
| `include/opennet/` | Public library headers |
| `src/network.cpp` | Routing implementation |
| `src/main.cpp` | Small executable example |
| `tests/` | Focused executable tests |
| `CMakeLists.txt` | Build and test entry point |

## Where to go next

The current `Network` class models only node registration, bidirectional links,
and shortest-path routing. Routing uses breadth-first search, which is a useful
first algorithm because every in-memory link currently has the same cost.
Suggested increments are:

1. Add a `Packet` type and a queue between neighbours.
2. Introduce a transport layer with delivery and retry rules.
3. Add a node-discovery protocol instead of manually connecting nodes.
4. Replace the in-memory links with a pluggable persistence or socket layer.

Keep each layer small and testable. New public concepts belong in
`include/opennet/`, their implementation belongs in `src/`, and behaviour
should be demonstrated by a test in `tests/`.
