#include <iostream>
#include <deque>
#include <stdexcept>

#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {
        /**
         * Attempt to find "node" by breadth-first search, starting at "root".
         * 
         * @param root The root node for starting the search.
         * @param node The node to find.
         * 
         * @return true if found, false otherwise.
         */
        bool findNodeByBFS(
            ctci::jim::BinaryTreeNode<int>* root,
            ctci::jim::BinaryTreeNode<int>* node
        ) {
            if (root == nullptr) {
                return false;
            }

            std::deque<ctci::jim::BinaryTreeNode<int>*> nodesToVisit;
            nodesToVisit.emplace_back(root);

            while (!nodesToVisit.empty()) {
                auto currentNode = nodesToVisit.front();
                nodesToVisit.pop_front();

                if (currentNode != nullptr) {
                    if (currentNode == node) {
                        return true;
                    }

                    nodesToVisit.emplace_back(currentNode->left);
                    nodesToVisit.emplace_back(currentNode->right);
                }
            }

            return false;
        }

        /**
         * Find the first common ancestor of two nodes in a binary tree. Avoid storing additional nodes in a data structure.
         */
        ctci::jim::BinaryTreeNode<int>* getFirstCommonAncestor(
            ctci::jim::BinaryTreeNode<int>* root,
            ctci::jim::BinaryTreeNode<int>* node1,
            ctci::jim::BinaryTreeNode<int>* node2) {

            // If either node is the root, then root is the common ancestor.
            if ((root == node1) || (root == node2)) {
                return root;
            }

            bool isNode1Left = findNodeByBFS(root->left, node1);
            bool isNode2Left = findNodeByBFS(root->left, node2);

            // If one node is to the left and the other is to the right, root is the common ancestor.
            if (isNode1Left != isNode2Left) {
                return root;
            }
            else if (isNode1Left) {
                return getFirstCommonAncestor(root->left, node1, node2);
            } else {
                return getFirstCommonAncestor(root->right, node1, node2);
            }
        }

        /**
         * Search for **either** node at the same time. No BFS or queue needed.
         */
        ctci::jim::BinaryTreeNode<int>* getFirstCommonAncestorOptimized(
                ctci::jim::BinaryTreeNode<int>* root,
                ctci::jim::BinaryTreeNode<int>* node1,
                ctci::jim::BinaryTreeNode<int>* node2) {
            if (root == nullptr || root == node1 || root == node2) {
                return root;
            }

            auto* left  = getFirstCommonAncestorOptimized(root->left,  node1, node2);
            auto* right = getFirstCommonAncestorOptimized(root->right, node1, node2);

            // A target was found on each side -> this node is the split point.
            if (left != nullptr && right != nullptr) {
                return root;
            }
            
            // Otherwise bubble up whichever side found something (or nullptr).
            return (left != nullptr) ? left : right;
        }

        int main(int argc, char** argv) {
            using Node = ctci::jim::BinaryTreeNode<int>;

            //           1
            //         /   \
            //        2     3
            //       / \     \
            //      4   5     6
            //         / \
            //        7   8
            Node n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7), n8(8);
            n1.left = &n2; n1.right = &n3;
            n2.left = &n4; n2.right = &n5;
            n3.right = &n6;
            n5.left = &n7; n5.right = &n8;

            // Nodes in different subtrees of the root -> ancestor is the root.
            if (getFirstCommonAncestor(&n1, &n4, &n6) != &n1) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestor(&n1, &n7, &n6) != &n1) throw std::runtime_error("Test failed.");

            // Nodes sharing a mid-level ancestor.
            if (getFirstCommonAncestor(&n1, &n7, &n8) != &n5) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestor(&n1, &n4, &n7) != &n2) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestor(&n1, &n4, &n8) != &n2) throw std::runtime_error("Test failed.");

            // One node is an ancestor of the other -> that ancestor is the answer.
            if (getFirstCommonAncestor(&n1, &n2, &n5) != &n2) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestor(&n1, &n5, &n8) != &n5) throw std::runtime_error("Test failed.");

            // The root itself is one of the two nodes.
            if (getFirstCommonAncestor(&n1, &n1, &n7) != &n1) throw std::runtime_error("Test failed.");

            // Both arguments are the same node.
            if (getFirstCommonAncestor(&n1, &n5, &n5) != &n5) throw std::runtime_error("Test failed.");

            // Same cases, run against the optimized single-pass version.
            if (getFirstCommonAncestorOptimized(&n1, &n4, &n6) != &n1) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n7, &n6) != &n1) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n7, &n8) != &n5) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n4, &n7) != &n2) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n4, &n8) != &n2) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n2, &n5) != &n2) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n5, &n8) != &n5) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n1, &n7) != &n1) throw std::runtime_error("Test failed.");
            if (getFirstCommonAncestorOptimized(&n1, &n5, &n5) != &n5) throw std::runtime_error("Test failed.");

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}