#include <stdexcept>
#include <string>
#include <vector>

namespace ctci {
    namespace jim {
        template <typename T>
        class DirectedGraphNode {

        public:
            std::vector<const DirectedGraphNode<T>*> neighbors;
            T value;

            DirectedGraphNode(T value);

            void addNeighbor(const DirectedGraphNode<T>& neighbor);
        };

        template <typename T>
        class DirectedGraph {

        public:
            std::vector<const DirectedGraphNode<T>*> nodes;

            DirectedGraph();

            void addNode(const DirectedGraphNode<T>& node);

            void removeNode(const DirectedGraphNode<T>& node);

            /**
             * Breadth-first search to find the distance from node S to node E.
             *
             * @returns The distance in steps. -1 if not connected.
             */
            int getBfsDistance(const DirectedGraphNode<T>& S, const DirectedGraphNode<T>& E);

            /**
             * Depth-first search to find the distance from node S to node E.
             *
             * @returns The distance in steps. -1 if not connected.
             */
            int getDfsDistance(const DirectedGraphNode<T>& S, const DirectedGraphNode<T>& E);
        };
   }
}

#include "directed-graph.tpp"