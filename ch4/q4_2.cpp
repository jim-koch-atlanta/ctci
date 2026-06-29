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

        void inOrder(const ctci::jim::BinaryTreeNode<int>* node, std::vector<int>& result) {
            if (node == nullptr) return;
            inOrder(node->left, result);
            result.push_back(node->value);
            inOrder(node->right, result);
        }

        ctci::jim::BinaryTreeNode<int>* buildBST(const std::vector<int>& sv) {
            return buildBST(sv, 0, sv.size() - 1);
        }

        int treeHeight(const ctci::jim::BinaryTreeNode<int>* node) {
            if (node == nullptr) return 0;
            return 1 + std::max(treeHeight(node->left), treeHeight(node->right));
        }

        int main(int argc, char** argv) {
            // In-order traversal of the BST should match the original sorted array.
            {
                std::vector<int> input = {1, 2, 3, 4, 5, 6, 7};
                auto* root = buildBST(input);
                std::vector<int> result;
                inOrder(root, result);
                if (result != input) throw std::runtime_error("Test failed.");
            }

            // Single element.
            {
                std::vector<int> input = {42};
                auto* root = buildBST(input);
                std::vector<int> result;
                inOrder(root, result);
                if (result != input) throw std::runtime_error("Test failed.");
            }

            // Even number of elements.
            {
                std::vector<int> input = {1, 2, 3, 4, 5, 6};
                auto* root = buildBST(input);
                std::vector<int> result;
                inOrder(root, result);
                if (result != input) throw std::runtime_error("Test failed.");
            }

            // Height should be minimal: ceil(log2(n+1)).
            {
                std::vector<int> input = {1, 2, 3, 4, 5, 6, 7};
                auto* root = buildBST(input);
                int height = treeHeight(root);
                int expectedMaxHeight = (int)ceil(log2(input.size() + 1));
                if (height > expectedMaxHeight) throw std::runtime_error("Test failed.");
            }

            // Print in-order for visual inspection.
            {
                std::vector<int> input = {1, 2, 3, 4, 5, 6, 7};
                auto* root = buildBST(input);
                std::vector<int> result;
                inOrder(root, result);
                std::cout << "In-order: ";
                for (int v : result) std::cout << v << " ";
                std::cout << "\n";
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}