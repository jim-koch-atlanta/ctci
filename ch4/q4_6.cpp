#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

namespace ctci {
    namespace ch4 {

        template <typename T>
        class BstNode {
        public:
            T value;
            BstNode<T>* parent;
            BstNode<T>* left;
            BstNode<T>* right;

            BstNode(T val)
            : value{val}
            , parent{nullptr}
            , left{nullptr}
            , right{nullptr}
             { }
        };

        BstNode<int>* getInOrderSuccessor(BstNode<int>* node) {
            // Tree with no nodes.
            if (node == nullptr) {
                return nullptr;
            }

            // If this node has a right child, that is the successor.
            if (node->right != nullptr) {
                BstNode<int>* current = node->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
                return current;
            }

            BstNode<int>* current = node;
            // We need to traverse **up** the tree until the current node is the left child of its parent.
            while (current != nullptr) {
                if ((current->parent != nullptr) && (current->parent->left == current)) {
                    return current->parent;
                }
                current = current->parent;
            }

            return current;
        }

        int main(int argc, char** argv) {
            using Node = ctci::ch4::BstNode<int>;

            // ---- Valid BSTs (should return true) ----

            // Single node.
            {
                Node n(5);
                if (getInOrderSuccessor(&n) != nullptr) throw std::runtime_error("Test failed.");
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
                n1.parent = &n2; n3.parent = &n2;
                n5.parent = &n6; n7.parent = &n6;
                n2.parent = &n4; n6.parent = &n4;
                if (getInOrderSuccessor(&n1) != &n2) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n2) != &n3) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n3) != &n4) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n4) != &n5) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n5) != &n6) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n6) != &n7) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n7) != nullptr) throw std::runtime_error("Test failed.");
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
                n1.parent = &n2;
                n2.parent = &n3;
                if (getInOrderSuccessor(&n1) != &n2) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n2) != &n3) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n3) != nullptr) throw std::runtime_error("Test failed.");
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
                n6.parent = &n8; n10.parent = &n8;
                n6b.parent = &n6; n7.parent = &n6;
                if (getInOrderSuccessor(&n6b) != &n6) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n6) != &n7) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n7) != &n8) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n8) != &n10) throw std::runtime_error("Test failed.");
                if (getInOrderSuccessor(&n10) != nullptr) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}