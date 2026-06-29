#include <iostream>
#include <math.h>
#include <stdexcept>
#include <vector>
#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {

        ctci::jim::BinaryTreeNode<int>* buildBST(const std::vector<int>& sv, int minIndex, int maxIndex) {
            if (minIndex > maxIndex) {
                return nullptr;
            }

            int mid = (minIndex + maxIndex) / 2;
            ctci::jim::BinaryTreeNode<int>* root = new ctci::jim::BinaryTreeNode<int>(sv[mid]);
            root->left = buildBST(sv, minIndex, mid - 1);
            root->right = buildBST(sv, mid + 1, maxIndex);

            return root;
        }

        ctci::jim::BinaryTreeNode<int>* buildBST(const std::vector<int>& sv) {
            return buildBST(sv, 0, sv.size() - 1);
        }

        void createDepthCharts(const ctci::jim::BinaryTreeNode<int>* node, std::vector<std::vector<int>>& result, int depth) {
            if (node == nullptr) return;
            if (result.size() <= (size_t)depth) {
                result.push_back(std::vector<int>());
            }
            result[depth].push_back(node->value);
            createDepthCharts(node->left, result, depth + 1);
            createDepthCharts(node->right, result, depth + 1);
        }

        void createDepthCharts(const ctci::jim::BinaryTreeNode<int>* node, std::vector<std::vector<int>>& result) {
            return createDepthCharts(node, result, 0);
        }

        int main(int argc, char** argv) {
            // Single node: one level containing the root.
            {
                ctci::jim::BinaryTreeNode<int> root(42);
                std::vector<std::vector<int>> result;
                createDepthCharts(&root, result);
                if (result.size() != 1) throw std::runtime_error("Test failed.");
                if (result[0] != std::vector<int>{42}) throw std::runtime_error("Test failed.");
            }

            // Perfect 7-node BST: three levels.
            // buildBST([1..7]) produces root=4, left subtree root=2, right subtree root=6.
            {
                auto* root = buildBST({1, 2, 3, 4, 5, 6, 7});
                std::vector<std::vector<int>> result;
                createDepthCharts(root, result);
                if (result.size() != 3) throw std::runtime_error("Test failed.");
                if (result[0] != std::vector<int>{4}) throw std::runtime_error("Test failed.");
                if (result[1] != std::vector<int>{2, 6}) throw std::runtime_error("Test failed.");
                if (result[2] != std::vector<int>{1, 3, 5, 7}) throw std::runtime_error("Test failed.");
            }

            // Two nodes: root and one left child.
            {
                ctci::jim::BinaryTreeNode<int> root(10);
                ctci::jim::BinaryTreeNode<int> left(5);
                root.left = &left;
                std::vector<std::vector<int>> result;
                createDepthCharts(&root, result);
                if (result.size() != 2) throw std::runtime_error("Test failed.");
                if (result[0] != std::vector<int>{10}) throw std::runtime_error("Test failed.");
                if (result[1] != std::vector<int>{5}) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}