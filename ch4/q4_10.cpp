#include <iostream>
#include <stdexcept>
#include <deque>
#include <set>
#include <vector>

#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {
        using Node = ctci::jim::BinaryTreeNode<int>;

        bool matchTree(Node* n1, Node* n2) {
            if (n1 == nullptr && n2 == nullptr) {
                return true;
            }

            if (n1 == nullptr || n2 == nullptr) {
                return false;
            }

            return ((n1->value == n2->value) &&
                    (matchTree(n1->left, n2->left)) && 
                    (matchTree(n1->right, n2->right)));
        }

        /**
         * Given the root node t1 of binary tree T1, and the root node t2 of binary tree T2,
         * determine "if T2 is a subtree of T1".
         * 
         * T2 is a subtree of T1 if there is a node n in T1 such that the subtree of T1
         * "is identical to T2". So it's about them **looking** the same. It's not just that
         * T2's root is a node within T1.
         * 
         * @param t1 The root node of binary tree T1.
         * @param t2 The root node of binary tree T2.
         * 
         * @return True of T2 is a subtree of T1. Otherwise return false.
         */
        bool isSubtree(Node* t1, Node* t2) {
            // If t2 is an empty tree, it's a subtree.
            if (t2 == nullptr) {
                return true;
            }

            // If t1 is an empty tree, it's not possible to contain a non-empty subtree.
            if (t1 == nullptr) {
                return false;
            }

            if ((t1->value == t2->value) && matchTree(t1, t2)) {
                return true;
            }


            return (isSubtree(t1->left, t2) || isSubtree(t1->right, t2));
        }

        int main(int argc, char** argv) {
            // T1:
            //          5
            //         / \
            //        3   8
            //       / \   \
            //      1   4   9
            Node t5(5), t3(3), t8(8), t1(1), t4(4), t9(9);
            t5.left = &t3; t5.right = &t8;
            t3.left = &t1; t3.right = &t4;
            t8.right = &t9;

            // Empty T2 counts as a subtree of anything.
            if (isSubtree(&t5, nullptr) != true) throw std::runtime_error("Test failed.");

            // A single matching leaf.
            {
                Node s9(9);
                if (isSubtree(&t5, &s9) != true) throw std::runtime_error("Test failed.");
            }

            // A full matching subtree rooted at 3.
            {
                Node s3(3), s1(1), s4(4);
                s3.left = &s1; s3.right = &s4;
                if (isSubtree(&t5, &s3) != true) throw std::runtime_error("Test failed.");
            }

            // Matching subtree rooted at 8 (9 as the *right* child).
            {
                Node s8(8), s9(9);
                s8.right = &s9;
                if (isSubtree(&t5, &s8) != true) throw std::runtime_error("Test failed.");
            }

            // The whole tree matches itself (separate node instances, same shape/values).
            {
                Node u5(5), u3(3), u8(8), u1(1), u4(4), u9(9);
                u5.left = &u3; u5.right = &u8;
                u3.left = &u1; u3.right = &u4;
                u8.right = &u9;
                if (isSubtree(&t5, &u5) != true) throw std::runtime_error("Test failed.");
            }

            // Right root value, wrong structure: 3 with only a left child.
            {
                Node s3(3), s1(1);
                s3.left = &s1;
                if (isSubtree(&t5, &s3) != false) throw std::runtime_error("Test failed.");
            }

            // Structure differs by side: 8 with 9 as the *left* child (T1 has it on the right).
            {
                Node s8(8), s9(9);
                s8.left = &s9;
                if (isSubtree(&t5, &s8) != false) throw std::runtime_error("Test failed.");
            }

            // Value not present anywhere.
            {
                Node s7(7);
                if (isSubtree(&t5, &s7) != false) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}