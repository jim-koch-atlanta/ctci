#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

#include "../jim/directed-graph.h"

namespace ctci {
    namespace ch4 {

        int main(int argc, char** argv) {
            // Linear chain: a->b->c->d->e->f->g, distance a to g = 6.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b'), c('c'), d('d'),
                                                   e('e'), f('f'), g('g');
                a.addNeighbor(b); b.addNeighbor(c); c.addNeighbor(d);
                d.addNeighbor(e); e.addNeighbor(f); f.addNeighbor(g);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b); graph.addNode(c); graph.addNode(d);
                graph.addNode(e); graph.addNode(f); graph.addNode(g);
                if (graph.getBfsDistance(a, g) != 6) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, g) != 6) throw std::runtime_error("Test failed.");
            }

            // Direct neighbor: distance = 1.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b');
                a.addNeighbor(b);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b);
                if (graph.getBfsDistance(a, b) != 1) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, b) != 1) throw std::runtime_error("Test failed.");
            }

            // Same node: distance = 0.
            {
                ctci::jim::DirectedGraphNode<char> a('a');
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a);
                if (graph.getBfsDistance(a, a) != 0) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, a) != 0) throw std::runtime_error("Test failed.");
            }

            // No path (directed): b->a doesn't mean a->b.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b');
                b.addNeighbor(a);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b);
                if (graph.getBfsDistance(a, b) != -1) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, b) != -1) throw std::runtime_error("Test failed.");
            }

            // Disconnected graph: no path between components.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b'), c('c'), d('d');
                a.addNeighbor(b);
                c.addNeighbor(d);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b); graph.addNode(c); graph.addNode(d);
                if (graph.getBfsDistance(a, d) != -1) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, d) != -1) throw std::runtime_error("Test failed.");
            }

            // BFS finds shortest path; DFS may find a longer one.
            // Graph: a->b->e (short, 2), a->c->d->e (long, 3).
            // DFS pushes b then c; c is on top so DFS explores a->c->d->e first.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b'), c('c'), d('d'), e('e');
                a.addNeighbor(b); b.addNeighbor(e);
                a.addNeighbor(c); c.addNeighbor(d); d.addNeighbor(e);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b); graph.addNode(c);
                graph.addNode(d); graph.addNode(e);
                if (graph.getBfsDistance(a, e) != 2) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, e) != 3) throw std::runtime_error("Test failed.");
            }

            // Node not in graph: returns -1.
            {
                ctci::jim::DirectedGraphNode<char> a('a'), b('b'), c('c');
                a.addNeighbor(b);
                ctci::jim::DirectedGraph<char> graph;
                graph.addNode(a); graph.addNode(b);
                if (graph.getBfsDistance(a, c) != -1) throw std::runtime_error("Test failed.");
                if (graph.getDfsDistance(a, c) != -1) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}