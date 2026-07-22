#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {
        using Node = ctci::jim::BinaryTreeNode<int>;

        /**
         * For the given node, counts the number of paths within its
         * tree that sum to the specified value. The path does not need
         * to start or end at the given node or at a leaf.
         * 
         * O(n^2) time, O(1) space
         */
        int numberOfPathsThatSumToValueNoSpace(Node* node, int value, bool includesNode = false) {
            if (node == nullptr) {
                return 0;
            }

            int isThisNodeAPath = (node->value == value) ? 1 : 0;

            int numberOfPaths =
                numberOfPathsThatSumToValueNoSpace(node->left, value - node->value, true) +
                numberOfPathsThatSumToValueNoSpace(node->right, value - node->value, true) +
                isThisNodeAPath;

            if (includesNode == false) {
                numberOfPaths +=
                    numberOfPathsThatSumToValueNoSpace(node->left, value, false) +
                    numberOfPathsThatSumToValueNoSpace(node->right, value, false);
            }

            return numberOfPaths;
        }

        int numberOfPathsThatSumToValueNoSpace(Node* node, int value) {
            return numberOfPathsThatSumToValueNoSpace(node, value, false);
        }

        /**
         * For the given node, counts the number of paths within its
         * tree that sum to the specified value. The path does not need
         * to start or end at the given node or at a leaf.
         * 
         * O(n) time, O(n) space
         */
        int numberOfPathsThatSumToValueHashmap(Node* node, int target, int runningSum, std::unordered_map<int, int>& prefixCounts) {
            if (node == nullptr) {
                return 0;
            }

            runningSum += node->value;
            int pathsEndingHereThatSumToTarget = prefixCounts[runningSum - target];
            prefixCounts[runningSum]++;
            int leftCount = numberOfPathsThatSumToValueHashmap(node->left, target, runningSum, prefixCounts);
            int rightCount = numberOfPathsThatSumToValueHashmap(node->right, target, runningSum, prefixCounts);
            prefixCounts[runningSum]--;

            return pathsEndingHereThatSumToTarget + leftCount + rightCount;
        }

        int numberOfPathsThatSumToValueHashmap(Node* node, int target) {
            // For a given target value, the number of paths that sum to that target.
            std::unordered_map<int, int> prefixCounts;
            prefixCounts[0] = 1;

            int numberOfPaths = numberOfPathsThatSumToValueHashmap(node, target, 0, prefixCounts);
            return numberOfPaths;
        }


        using NumberOfPathsThatSumToValueFunc = int (*)(Node*, int);

        int testImplementation(NumberOfPathsThatSumToValueFunc numberOfPathsThatSumToValue) {
            // Handles nullptr.
            {
                if (numberOfPathsThatSumToValue(nullptr, 1) != 0) throw std::runtime_error("Test failed");
            }

            // If the root node is the desired value.
            {
                //      1
                //     / \
                //    2   3
                //   / \ / \
                //  4  5 6  7
                Node n1(1);
                Node n2(2);
                Node n3(3);
                Node n4(4);
                Node n5(5);
                Node n6(6);
                Node n7(7);
                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n5;
                n3.left = &n6;
                n3.right = &n7;

                if (numberOfPathsThatSumToValue(&n1, 1) != 1) throw std::runtime_error("Test failed");
            }

            // If a full path tree-to-leaf is the desired value.
            {
                //      1
                //     / \
                //    2   3
                //   / \ / \
                //  4  5 6  7
                Node n1(1);
                Node n2(2);
                Node n3(3);
                Node n4(4);
                Node n5(5);
                Node n6(6);
                Node n7(7);
                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n5;
                n3.left = &n6;
                n3.right = &n7;

                // 1 -> 3 -> 7
                if (numberOfPathsThatSumToValue(&n1, 11) != 1) throw std::runtime_error("Test failed");
            }

            // If multiple full paths tree-to-leaf are the desired values.
            {
                //      1
                //     / \
                //    2   3
                //   / \ / \
                //  4  6 5  7
                Node n1(1);
                Node n2(2);
                Node n3(3);
                Node n4(4);
                Node n5(5);
                Node n6(6);
                Node n7(7);
                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n6; // Swapped
                n3.left = &n5;  // Swapped
                n3.right = &n7;

                // 1 -> 2 -> 6
                // 1 -> 3 -> 5
                if (numberOfPathsThatSumToValue(&n1, 9) != 2) throw std::runtime_error("Test failed");
            }

            // If root to left-most leaf is a path,
            // and root's right subtree has another path.
            {
                //      1
                //     / \
                //    2   3
                //   / \ / \
                //  4  5 6  7
                Node n1(1);
                Node n2(2);
                Node n3(3);
                Node n4(4);
                Node n5(5);
                Node n6(6);
                Node n7(7);
                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n5;
                n3.left = &n6;
                n3.right = &n7;

                // 1 -> 2 -> 4
                // 2 -> 5
                // 7
                if (numberOfPathsThatSumToValue(&n1, 7) != 3) throw std::runtime_error("Test failed");
            }

            // If there are negative values in the path.
            {
                //      1
                //     / \
                //   -1   1
                //   / \ / \
                // -1  1 -1 1
                Node n1(1);

                Node n2(-1);
                Node n3(1);

                Node n4(-1);
                Node n5(1);                
                Node n6(-1);
                Node n7(1);

                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n5;
                n3.left = &n6;
                n3.right = &n7;

                // 1 -> -1 -> -1
                // -1
                // -1
                // -1
                if (numberOfPathsThatSumToValue(&n1, -1) != 4) throw std::runtime_error("Test failed");
            }

            // If there are **no paths**
            {
                //      1
                //     / \
                //   -1   1
                //   / \ / \
                // -1  1 -1 1
                Node n1(1);

                Node n2(-1);
                Node n3(1);

                Node n4(-1);
                Node n5(1);                
                Node n6(-1);
                Node n7(1);

                n1.left = &n2;
                n1.right = &n3;
                n2.left = &n4;
                n2.right = &n5;
                n3.left = &n6;
                n3.right = &n7;

                if (numberOfPathsThatSumToValue(&n1, 4) != 0) throw std::runtime_error("Test failed");
            }

            return 0;
        }

        int main(int argc, char** argv) {
            testImplementation(numberOfPathsThatSumToValueNoSpace);
            testImplementation(numberOfPathsThatSumToValueHashmap);

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}
