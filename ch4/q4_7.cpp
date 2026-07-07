#include <algorithm>
#include <format>
#include <iostream>
#include <list>
#include <optional>
#include <ranges>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ctci {
    namespace ch4 {
        class Example {
            public:
                std::string projects;
                std::string dependencies;
        };

        std::list<Example> examples = {
            {"projects: a, b, c, d, e, f", "dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)"},
            {"projects: a, b, c", "dependencies: (b, a), (c, a), (b, c)"},
        };

        template <typename T>
        class DagNode {
        public:
            T value;
            std::vector<DagNode<T>*> dependents;
            std::vector<DagNode<T>*> prereqs;

            DagNode(T val)
            : value{val}
             { }
        };

        template <typename T>
        class DagGraph {
        public:
            std::unordered_map<T, DagNode<T>*> nodes;
        };

        std::vector<char> parseProjects(std::string_view line) {
            if (line.starts_with("projects: ")) {
                line.remove_prefix(std::string_view("projects: ").size());
            } else {
                throw std::runtime_error(std::format("Line does not start with prefix."));
            }

            std::vector<char> items;
            for (auto&& part : line | std::views::split(std::string_view{", "})) {
                items.emplace_back(part[0]);
            }

            return items;
        }

        std::vector<std::pair<char, char>> parseDependencies(std::string line) {
            if (line.starts_with("dependencies: ")) {
                line = line.substr(std::string_view("dependencies: ").size());
            } else {
                throw std::runtime_error(std::format("Line does not start with prefix."));
            }

            std::vector<std::pair<char, char>> items;
            static const std::regex pattern{R"(\(([a-zA-Z]), ([a-zA-Z])\))"};
            for (std::sregex_iterator it{line.begin(), line.end(), pattern}, end; it != end; ++it)
                items.emplace_back((*it)[1].str()[0], (*it)[2].str()[0]);            
            return items;
        }

        DagGraph<char> createGraphFromExample(Example example) {
            auto projects = parseProjects(example.projects);
            auto dependencies = parseDependencies(example.dependencies);

            DagGraph<char> graph;
            for (auto project : projects) {
                DagNode<char>* node = new DagNode<char>(project);
                graph.nodes.emplace(project, node);
            }

            for (auto [prerequisite, dependent] : dependencies) {
                graph.nodes.at(prerequisite)->dependents.emplace_back(graph.nodes.at(dependent));
                graph.nodes.at(dependent)->prereqs.emplace_back(graph.nodes.at(prerequisite));
            }

            return graph;
        }

        void getBuildOrder(const DagGraph<char>& graph) {
            // We'll start with the list of nodes with no dependents, and we'll
            // do a depth-first search from there.
            std::stack<DagNode<char>*> toVisit;

            // We can visit a node when if it doesn't have any unvisited prereqs.
            std::vector<DagNode<char>*> visited;

            // Get the list of projects that have no dependents.
            for (auto& [name, node] : graph.nodes) {
                if (node->dependents.empty()) {
                    toVisit.push(node);
                }
            }
            // Nodes currently on the stack, waiting for their prereqs. A prereq
            // that is itself still "in progress" means we've looped back on our
            // own path -> a cycle -> no valid build order.
            std::unordered_set<DagNode<char>*> inProgress;

            // Do a depth-first search.
            while (!toVisit.empty()) {
                DagNode<char>* node = toVisit.top();

                // A stale duplicate that was already finalized on an earlier pass.
                if (std::ranges::find(visited, node) != visited.end()) {
                    toVisit.pop();
                    continue;
                }

                inProgress.insert(node);

                bool allPrereqsVisited = true;
                for (auto prereq : node->prereqs) {
                    if (std::ranges::find(visited, prereq) != visited.end()) {
                        continue; // prereq already built
                    }
                    if (inProgress.contains(prereq)) {
                        throw std::runtime_error("Cycle detected: no valid build order.");
                    }
                    allPrereqsVisited = false;
                    toVisit.push(prereq);
                }

                if (allPrereqsVisited) {
                    visited.emplace_back(node);
                    inProgress.erase(node);
                    toVisit.pop();
                }
            }

            for (auto node : visited) {
                std::cout << node->value << " ";
            }
            std::cout << std::endl;
        }

        // Kahn's algorithm: repeatedly take any node whose prereqs are all built,
        // then relax its dependents. If we can't place every node, there's a cycle.
        std::vector<char> getBuildOrderSimplified(const DagGraph<char>& graph) {
            // How many not-yet-built prereqs each node still has.
            std::unordered_map<DagNode<char>*, int> remaining;
            std::queue<DagNode<char>*> ready;

            for (auto& [name, node] : graph.nodes) {
                remaining[node] = node->prereqs.size();
                if (node->prereqs.empty()) {
                    ready.push(node);
                }
            }

            std::vector<char> order;
            while (!ready.empty()) {
                DagNode<char>* node = ready.front();
                ready.pop();
                order.push_back(node->value);

                for (DagNode<char>* dependent : node->dependents) {
                    if (--remaining[dependent] == 0) {
                        ready.push(dependent);
                    }
                }
            }

            if (order.size() != graph.nodes.size()) {
                throw std::runtime_error("Cycle detected: no valid build order.");
            }

            return order;
        }

        int main(int argc, char** argv) {

            for (auto example : examples) {
                DagGraph<char> graph = createGraphFromExample(example);
                getBuildOrder(graph);
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}