#include <iostream>
#include <stdexcept>
#include <deque>
#include <set>
#include <vector>

#include "../jim/binary-tree.h"

namespace ctci {
    namespace ch4 {
        using Node = ctci::jim::BinaryTreeNode<int>;

        std::deque<Node*> combine(std::deque<Node*> prefix, std::deque<Node*> seq) {
            std::deque<Node*> result = prefix;
            for (auto node : seq) {
                result.push_back(node);
            }

            return result;
        }

        std::deque<std::deque<Node*>> weaveSequences(
            std::deque<Node*> seq1,
            std::deque<Node*> seq2,
            std::deque<Node*> prefix
        ) {
            if (seq1.empty() && seq2.empty()) {
                return { prefix };
            }
            if (seq1.empty()) {
                return { combine(prefix, seq2) };
            }
            if (seq2.empty()) {
                return { combine(prefix, seq1) };
            }

            std::deque<Node*> prefixSeq1 = combine(prefix, { seq1.front() });
            auto shorter_seq1 = seq1;
            shorter_seq1.pop_front();
            std::deque<Node*> prefixSeq2 = combine(prefix, { seq2.front() });
            auto shorter_seq2 = seq2;
            shorter_seq2.pop_front();

            std::deque<std::deque<Node*>> resultsSeq1 = weaveSequences(shorter_seq1, seq2, prefixSeq1);
            std::deque<std::deque<Node*>> resultsSeq2 = weaveSequences(seq1, shorter_seq2, prefixSeq2);

            for (auto result : resultsSeq2) {
                resultsSeq1.emplace_back(result);
            }
            
            return resultsSeq1;
        }

        /**
         * Given a binary search tree with distinct elements, print all possibles array that could have led to this tree.
         * 
         * @param root The root node of the BST.
         * 
         * @return All possible arrays that could have led to the tree.
         */
        std::deque<std::deque<Node*>> getBstSequences(Node* root) {
            if (root == nullptr) {
                return std::deque<std::deque<Node*>>({{}});
            }

            // The array has to start with the root node. After that though, the
            // results of the left side and the right side need to be "weaved"
            // together.
            auto leftSeqs = getBstSequences(root->left);
            auto rightSeqs = getBstSequences(root->right);

            std::deque<std::deque<Node*>> results;
            for (auto leftSeq : leftSeqs) {
                for (auto rightSeq : rightSeqs) {
                    auto resultsWeaveSequence = weaveSequences(leftSeq, rightSeq, { root });
                    for (auto resultWeaveSequence : resultsWeaveSequence) {
                        results.push_back(resultWeaveSequence);
                    }
                }
            }

            return results;
        }

        int main(int argc, char** argv) {
            // Collapse the result into a set of value-sequences so we can compare
            // regardless of the order the sequences come back in.
            auto toSet = [](const std::deque<std::deque<Node*>>& seqs) {
                std::set<std::vector<int>> out;
                for (const auto& seq : seqs) {
                    std::vector<int> vals;
                    for (auto* n : seq) vals.push_back(n->value);
                    out.insert(vals);
                }
                return out;
            };

            // Single node: exactly one possible insertion sequence.
            {
                Node n5(5);
                std::set<std::vector<int>> expected = {{5}};
                if (toSet(getBstSequences(&n5)) != expected) throw std::runtime_error("Test failed.");
            }

            // Balanced 3-node BST: root first, then the two children in either order.
            //     2
            //    / \
            //   1   3
            {
                Node n2(2), n1(1), n3(3);
                n2.left = &n1; n2.right = &n3;
                std::set<std::vector<int>> expected = {
                    {2, 1, 3},
                    {2, 3, 1},
                };
                auto bstSequences = getBstSequences(&n2);
                if (toSet(bstSequences) != expected) throw std::runtime_error("Test failed.");
            }

            // 4-node BST: left subtree {2:(1,3)} weaves with right leaf {5}.
            //       4
            //      / \
            //     2   5
            //    / \
            //   1   3
            {
                Node n4(4), n2(2), n5(5), n1(1), n3(3);
                n4.left = &n2; n4.right = &n5;
                n2.left = &n1; n2.right = &n3;
                std::set<std::vector<int>> expected = {
                    {4, 5, 2, 1, 3}, {4, 2, 5, 1, 3}, {4, 2, 1, 5, 3}, {4, 2, 1, 3, 5},
                    {4, 5, 2, 3, 1}, {4, 2, 5, 3, 1}, {4, 2, 3, 5, 1}, {4, 2, 3, 1, 5},
                };

                auto bstSequences = getBstSequences(&n4);
                if (toSet(bstSequences) != expected) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
        
    }
}

int main(int argc, char** argv) {
    return ctci::ch4::main(argc, argv);
}