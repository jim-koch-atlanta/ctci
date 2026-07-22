#include <iostream>
#include <stdexcept>

#include "../jim/binary-search-tree-with-random.h"

namespace ctci {
    namespace ch4 {
        using Node = ctci::jim::BinarySearchTreeWithRandomNode<int>;
        using Tree = ctci::jim::BinarySearchTreeWithRandom<int>;

        int main(int argc, char** argv) {
            // contains() reflects inserts and removes.
            {
                Tree tree;
                for (int v : {5, 3, 8, 1, 4, 7, 9}) tree.insert(v);
                for (int v : {1, 3, 4, 5, 7, 8, 9})
                    if (!tree.contains(v)) throw std::runtime_error("Test failed.");
                if (tree.contains(6)) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 7) throw std::runtime_error("Test failed.");

                tree.remove(5);
                if (tree.contains(5)) throw std::runtime_error("Test failed.");
                if (!tree.contains(3) || !tree.contains(8)) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 6) throw std::runtime_error("Test failed.");
            }

            // random() on an empty tree returns nullptr.
            {
                Tree tree;
                if (tree.random() != nullptr) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 0) throw std::runtime_error("Test failed.");
            }

            // random() on a single-node tree returns a node.
            {
                Tree tree;
                tree.insert(42);
                if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 1) throw std::runtime_error("Test failed.");
            }

            // random() on a populated tree always returns a node (over many calls).
            {
                Tree tree;
                for (int v : {5, 3, 8, 1, 4, 7, 9}) tree.insert(v);
                if (tree.getTreeSize() != 7) throw std::runtime_error("Test failed.");
                for (int i = 0; i < 1000; i++) {
                    if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                }
            }

            // random() still works right after removing down to a single node.
            {
                Tree tree;
                tree.insert(5); tree.insert(3); tree.insert(8);
                tree.remove(3);
                tree.remove(8);
                if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 1) throw std::runtime_error("Test failed.");
            }

            // KNOWN ISSUE (to fix next): removing a value that is NOT in the tree
            // must be a no-op. If it corrupts the subtree-size bookkeeping, random()
            // breaks. This test encodes the correct behavior.
            {
                Tree tree;
                for (int v : {5, 3, 8}) tree.insert(v);
                tree.remove(100); // 100 is not present
                if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                if (tree.getTreeSize() != 3) throw std::runtime_error("Test failed.");
            }

            // Single-child removal (splice). Right chain 10 -> 20 -> 30; removing
            // 20 promotes its only child 30. The promoted subtree's size must stay
            // correct, or random() will route into the empty side and return null.
            {
                Tree tree;
                tree.insert(10); tree.insert(20); tree.insert(30);
                tree.remove(20);
                if (tree.getTreeSize() != 2) throw std::runtime_error("Test failed.");
                for (int i = 0; i < 500; i++) {
                    if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                }
            }

            // random() on an unbalanced tree with a left-only node. In {5, 3, 8, 1},
            // node 3 has a left child (1) but no right child. random() must handle
            // that without dereferencing a null right child.
            {
                Tree tree;
                for (int v : {5, 3, 8, 1}) tree.insert(v);
                for (int i = 0; i < 500; i++) {
                    if (tree.random() == nullptr) throw std::runtime_error("Test failed.");
                }
            }

            std::cout << "All tests passed.\n";
            return 0;
        }

    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}
