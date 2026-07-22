#include <random>
#include <tuple>

namespace ctci {
    namespace jim {
        template <typename T>
        class BinarySearchTreeWithRandomNode {

        template <typename U> friend class BinarySearchTreeWithRandom;

        private:
            T value;
            int subtreeSize;
            BinarySearchTreeWithRandomNode<T>* left;
            BinarySearchTreeWithRandomNode<T>* right;

        public:
            BinarySearchTreeWithRandomNode(T val)
            : value{val}
            , subtreeSize{1}
            , left{nullptr}
            , right{nullptr}
             { }

            ~BinarySearchTreeWithRandomNode()
             {
                delete left;
                delete right;
             }

            // Inserts newValue into the subtree rooted at `node` and returns the
            // new subtree root (a fresh node when `node` is null). Reassign at the
            // caller: root = BinarySearchTreeWithRandomNode<T>::insert(root, x);
            static BinarySearchTreeWithRandomNode* insert(BinarySearchTreeWithRandomNode* node, T newValue) {
                if (node == nullptr) {
                    return new BinarySearchTreeWithRandomNode(newValue);
                }

                node->subtreeSize++;

                if (newValue <= node->value) {
                    node->left = insert(node->left, newValue);
                } else {
                    node->right = insert(node->right, newValue);
                }

                return node;
            }

            BinarySearchTreeWithRandomNode* find(T value) {
                if (this->value == value) {
                    return this;
                }

                if (value < this->value) {
                    if (this->left != nullptr) {
                        return this->left->find(value);
                    }
                    return nullptr;
                }

                if (this->value < value) {
                    if (this->right != nullptr) {
                        return this->right->find(value);
                    }
                    return nullptr;
                }

                return nullptr;
            }

            // Leftmost node in a subtree = smallest value (the in-order successor
            // when called on a node's right child).
            static BinarySearchTreeWithRandomNode* findMin(BinarySearchTreeWithRandomNode* node) {
                while (node != nullptr && node->left != nullptr) {
                    node = node->left;
                }
                return node;
            }

            // Removes `target` from the subtree rooted at `node` and returns the
            // new root of that subtree (which may differ, or be nullptr if the
            // subtree becomes empty). `delete` is a C++ keyword, so this is
            // `remove`; because the root can change, callers must reassign:
            //     root = BinarySearchTreeWithRandomNode<T>::remove(root, x);
            static std::tuple<BinarySearchTreeWithRandomNode*, bool> remove(BinarySearchTreeWithRandomNode* node, T target) {
                if (node == nullptr) {
                    return { nullptr, false }; // not found
                }

                if (target < node->value) {
                    auto [ resultNode, resultBool ] = remove(node->left, target);
                    node->left = resultNode;
                    if (resultBool) { node->subtreeSize--; } // Reduce the tree size if the node was found.
                    return { node, resultBool };
                } else if (target > node->value) {
                    auto [ resultNode, resultBool ] = remove(node->right, target);
                    node->right = resultNode;
                    if (resultBool) { node->subtreeSize--; } // Reduce the tree size if the node was found.
                    return { node, resultBool };
                } else {
                    // Found the node to remove.
                    if (node->left == nullptr && node->right == nullptr) {
                        delete node;
                        return { nullptr, true };
                    }

                    if (node->left == nullptr) {
                        BinarySearchTreeWithRandomNode* child = node->right;
                        node->right = nullptr; // detach so the destructor won't free it
                        delete node;

                        // child->subtreeSize--; **Don't** decrement the child's subtree size. Its size didn't change.
                        return { child, true };
                    }
                    if (node->right == nullptr) {
                        BinarySearchTreeWithRandomNode* child = node->left;
                        node->left = nullptr;
                        delete node;

                        // child->subtreeSize--; **Don't** decrement the child's subtree size. Its size didn't change.
                        return { child, true };
                    }
                    // Two children: overwrite with the in-order successor (smallest
                    // value in the right subtree), then delete that successor.
                    BinarySearchTreeWithRandomNode* successor = findMin(node->right);
                    node->value = successor->value;

                    auto [ resultNode, resultBool ] = remove(node->right, successor->value);
                    node->right = resultNode;
                    if (resultBool) { node->subtreeSize--; } // Reduce the tree size if the node was found.

                    return { node, resultBool };
                }
            }

            /**
             * Returns a random number in the range of [1, max] inclusive.
             */
            static int getRandomNumber(int max) {
                // 1. Seed the random number engine with hardware entropy
                // Do as static, since it can be slow.
                static std::random_device rd;

                // 2. Initialize the Mersenne Twister pseudo-random generator.
                // Do as static, since it can be slow.
                static std::mt19937 gen(rd());

                // 3. Define the inclusive range [1, max]
                std::uniform_int_distribution<int> distr(1, max);

                // 4. Generate the random number
                int random_num = distr(gen);

                return random_num;
            }

            /**
             * Returns a random node from node's subtree. All nodes have
             * equal probability of being selected.
             */
            static BinarySearchTreeWithRandomNode* random(BinarySearchTreeWithRandomNode* node) {
                if (node == nullptr) {
                    return nullptr;
                }

                int rand = getRandomNumber(node->subtreeSize);
                if (rand == 1) {
                    return node;
                }

                if ((node->right == nullptr) || (rand < (node->subtreeSize - node->right->subtreeSize + 1))) {
                    return random(node->left);
                }

                return random(node->right);
            }
        };

        // Owns the root pointer and exposes a uniform instance-method API. The
        // node-level statics that reassign the root stay hidden as an
        // implementation detail.
        template <typename T>
        class BinarySearchTreeWithRandom {
        private:
            BinarySearchTreeWithRandomNode<T>* root = nullptr;

        public:
            ~BinarySearchTreeWithRandom() {
                delete root; // node destructor recursively frees the whole tree
            }

            void insert(T value) {
                root = BinarySearchTreeWithRandomNode<T>::insert(root, value);
            }

            void remove(T value) {
                auto [ newRoot, boolResult ] = BinarySearchTreeWithRandomNode<T>::remove(root, value);
                root = newRoot;
            }

            bool contains(T value) const {
                return root != nullptr && root->find(value) != nullptr;
            }

            BinarySearchTreeWithRandomNode<T>* random() const {
                return BinarySearchTreeWithRandomNode<T>::random(root);
            }

            int getTreeSize() const {
                return (root == nullptr) ? 0 : root->subtreeSize;
            }
        };
    }
}