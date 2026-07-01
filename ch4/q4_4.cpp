#include <iostream>
#include <math.h>
#include <stdexcept>
#include <vector>
#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {

        int getHeight(ctci::jim::BinaryTreeNode<int>* node) {
            if (node == nullptr) {
                return 0;
            } else {
                auto heightLeft = getHeight(node->left);
                auto heightRight = getHeight(node->right);
                if (heightLeft == -1) {
                    return -1;
                }
                if (heightRight == -1) {
                    return -1;
                }
                if (abs(heightLeft - heightRight) > 1) {
                    return -1;
                }
                return (heightLeft > heightRight) ? (heightLeft + 1) : (heightRight + 1);
            }
        }

        bool isBalanced(ctci::jim::BinaryTreeNode<int>* node) {
            return getHeight(node) != -1;
        }

        int main(int argc, char** argv) {
            // Single node is balanced.
            {
                ctci::jim::BinaryTreeNode<int> root(42);
                if (!isBalanced(&root)) throw std::runtime_error("Test failed.");
            }

            // Perfect 3-level tree is balanced.
            {
                ctci::jim::BinaryTreeNode<int> n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7);
                n4.left = &n2; n4.right = &n6;
                n2.left = &n1; n2.right = &n3;
                n6.left = &n5; n6.right = &n7;
                if (!isBalanced(&n4)) throw std::runtime_error("Test failed.");
            }

            // Deep left chain (height 3 left, null right) is unbalanced.
            {
                ctci::jim::BinaryTreeNode<int> a(1), b(2), c(3);
                a.left = &b;
                b.left = &c;
                if (isBalanced(&a)) throw std::runtime_error("Test failed.");
            }

            // Left subtree height 3, right subtree height 1 — each subtree is
            // internally balanced, but the root is not.
            {
                ctci::jim::BinaryTreeNode<int> n1(1), n2(2), n3(3), n4(4), n5(5), n6(6);
                n5.left = &n6;
                n2.left = &n4;
                n2.right = &n5;
                n1.left = &n2;
                n1.right = &n3;
                if (isBalanced(&n1)) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}