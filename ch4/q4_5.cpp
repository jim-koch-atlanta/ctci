#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>
#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {

        bool isBST(
                ctci::jim::BinaryTreeNode<int>* node,
                std::optional<int> smallest = std::nullopt,
                std::optional<int> largest = std::nullopt) {

            if (node == nullptr) {
                return true;
            }

            if (smallest.has_value() && (node->value <= smallest)) {
                return false;
            }

            if (largest.has_value() && (node->value > largest)) {
                return false;
            }

            // When we go left, the value has to be smaller than the current node, but bigger than the current node's parent.
            if (!isBST(node->left, smallest, node->value)) {
                return false;
            }

            // When we go right, the value has to be larger than the current node, but smaller than the current node's parent.
            if (!isBST(node->right, node->value, largest)) {
                return false;
            }

            return true;
        }

        int main(int argc, char** argv) {
            using Node = ctci::jim::BinaryTreeNode<int>;

            // ---- Valid BSTs (should return true) ----

            // Single node.
            {
                Node n(5);
                if (!isBST(&n)) throw std::runtime_error("Test failed.");
            }

            // Perfect BST:
            //       4
            //      / \
            //     2   6
            //    /|   |\
            //   1 3   5 7
            {
                Node n1(1), n3(3), n5(5), n7(7), n2(2), n6(6), n4(4);
                n2.left = &n1; n2.right = &n3;
                n6.left = &n5; n6.right = &n7;
                n4.left = &n2; n4.right = &n6;
                if (!isBST(&n4)) throw std::runtime_error("Test failed.");
            }

            // Left-leaning valid BST.
            //     3
            //    /
            //   2
            //  /
            // 1
            {
                Node n1(1), n2(2), n3(3);
                n2.left = &n1;
                n3.left = &n2;
                if (!isBST(&n3)) throw std::runtime_error("Test failed.");
            }

            // Equality. BST is true for left <= parent < right.
            //       8
            //      / \
            //     6   10
            //    / \
            //   6   7
            //
            {
                Node n8(8), n6(6), n6b(6), n7(7), n10(10);
                n8.left = &n6; n8.right = &n10;
                n6.left = &n6b; n6.right = &n7;
                if (!isBST(&n8)) throw std::runtime_error("Test failed.");
            }

            // ---- Invalid BSTs (should return false) ----

            // Left child greater than root.
            {
                Node root(5), left(6);
                root.left = &left;
                if (isBST(&root)) throw std::runtime_error("Test failed.");
            }

            // Right child less than root.
            {
                Node root(5), right(3);
                root.right = &right;
                if (isBST(&root)) throw std::runtime_error("Test failed.");
            }

            // Ancestor-bound violation: 6 sits in the right subtree of 10
            // but is smaller than 10. Parent-only checks would wrongly pass this.
            //       10
            //      /  \
            //     5    15
            //         /  \
            //        6    20
            {
                Node n10(10), n5(5), n15(15), n6(6), n20(20);
                n10.left = &n5; n10.right = &n15;
                n15.left = &n6; n15.right = &n20;
                if (isBST(&n10)) throw std::runtime_error("Test failed.");
            }

            // Deep violation in the left subtree: 4 is larger than root 3.
            //       8
            //      / \
            //     3   10
            //    / \
            //   1   4  <- but this whole left subtree must be < 8; 4 is fine vs 8,
            //           actually make it violate: right child of 3 is 9 (>8).
            {
                Node n8(8), n3(3), n10(10), n1(1), n9(9);
                n8.left = &n3; n8.right = &n10;
                n3.left = &n1; n3.right = &n9; // 9 > 8, violates ancestor bound
                if (isBST(&n8)) throw std::runtime_error("Test failed.");
            }

            // Equality. BST is true for left <= parent < right.
            //       8
            //      / \
            //     6   10
            //    / \
            //   5   6
            //
            {
                Node n8(8), n5(5), n6(6), n6b(6), n10(10);
                n8.left = &n6; n8.right = &n10;
                n6.left = &n5; n6.right = &n6b;
                if (isBST(&n8)) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}