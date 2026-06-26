#include <algorithm>
#include <vector>

#include "./stack.h"
#include "./queue.h"

namespace ctci::jim {

template <typename T>
DirectedGraphNode<T>::DirectedGraphNode(T value) {
    this->value = value;
}

template <typename T>
void DirectedGraphNode<T>::addNeighbor(const DirectedGraphNode<T>& neighbor) {
    this->neighbors.push_back(&neighbor);
}

template <typename T>
DirectedGraph<T>::DirectedGraph() {
}

template <typename T>
void DirectedGraph<T>::addNode(const DirectedGraphNode<T>& node) {
    this->nodes.push_back(&node);
}

template <typename T>
void DirectedGraph<T>::removeNode(const DirectedGraphNode<T>& node) {

}

template <typename T>
int DirectedGraph<T>::getBfsDistance(const DirectedGraphNode<T>& S, const DirectedGraphNode<T>& E) {
    if (&S == &E) {
        return 0;
    }

    if (std::find(nodes.begin(), nodes.end(), &S) == this->nodes.end()) {
        return -1;
    }

    if (std::find(nodes.begin(), nodes.end(), &E) == this->nodes.end()) {
        return -1;
    }

    // List of nodes that have been visited already.
    std::vector<const DirectedGraphNode<T>*> visited;
    visited.push_back(&S);

    // List of nodes that need to be visited, along with their distance from S.
    ctci::jim::Queue<std::pair<const DirectedGraphNode<T>*, int>> toVisit;
    std::pair<const DirectedGraphNode<T>*, int> p(&S, 0);
    toVisit.add(p);

    while (!toVisit.isEmpty()) {
        auto current = toVisit.remove();
        auto currentNode = current.first;
        auto currentDistance = current.second;

        for (const DirectedGraphNode<T>* neighbor : currentNode->neighbors) {
            if (neighbor == &E) {
                return currentDistance + 1;
            }

            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);

                std::pair<const DirectedGraphNode<T>*, int> p(neighbor, currentDistance + 1);
                toVisit.add(p);
            }
        }
    }
    return -1;
}

template <typename T>
int DirectedGraph<T>::getDfsDistance(const DirectedGraphNode<T>& S, const DirectedGraphNode<T>& E) {
    if (&S == &E) {
        return 0;
    }

    if (std::find(nodes.begin(), nodes.end(), &S) == this->nodes.end()) {
        return -1;
    }

    if (std::find(nodes.begin(), nodes.end(), &E) == this->nodes.end()) {
        return -1;
    }

    // List of nodes that have been visited already.
    std::vector<const DirectedGraphNode<T>*> visited;
    visited.push_back(&S);

    // List of nodes that need to be visited, along with their distance from S.
    ctci::jim::Stack<std::pair<const DirectedGraphNode<T>*, int>> toVisit;
    std::pair<const DirectedGraphNode<T>*, int> p(&S, 0);
    toVisit.push(p);

    while (!toVisit.isEmpty()) {
        auto current = toVisit.pop();
        auto currentNode = current.first;
        auto currentDistance = current.second;

        for (const DirectedGraphNode<T>* neighbor : currentNode->neighbors) {
            if (neighbor == &E) {
                return currentDistance + 1;
            }

            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);

                std::pair<const DirectedGraphNode<T>*, int> p(neighbor, currentDistance + 1);
                toVisit.push(p);
            }
        }
    }
    return -1;
}

}
