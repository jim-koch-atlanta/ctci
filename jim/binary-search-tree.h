namespace ctci {
    namespace jim {
        template <typename T>
        class BinarySearchTreeNode {
        private:
            T value;
            BinarySearchTreeNode<T>* left;
            BinarySearchTreeNode<T>* right;

        public:
            BinarySearchTreeNode(T val)
            : value{val}
            , left{nullptr}
            , right{nullptr}
             { }

            ~BinarySearchTreeNode()
             {
                delete left;
                delete right;
             }

            // Inserts newValue into the subtree rooted at `node` and returns the
            // new subtree root (a fresh node when `node` is null). Reassign at the
            // caller: root = BinarySearchTreeNode<T>::insert(root, x);
            static BinarySearchTreeNode* insert(BinarySearchTreeNode* node, T newValue) {
                if (node == nullptr) {
                    return new BinarySearchTreeNode(newValue);
                }

                if (newValue <= node->value) {
                    node->left = insert(node->left, newValue);
                } else {
                    node->right = insert(node->right, newValue);
                }

                return node;
            }

            BinarySearchTreeNode* find(T value) {
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
            static BinarySearchTreeNode* findMin(BinarySearchTreeNode* node) {
                while (node != nullptr && node->left != nullptr) {
                    node = node->left;
                }
                return node;
            }

            // Removes `target` from the subtree rooted at `node` and returns the
            // new root of that subtree (which may differ, or be nullptr if the
            // subtree becomes empty). `delete` is a C++ keyword, so this is
            // `remove`; because the root can change, callers must reassign:
            //     root = BinarySearchTreeNode<T>::remove(root, x);
            static BinarySearchTreeNode* remove(BinarySearchTreeNode* node, T target) {
                if (node == nullptr) {
                    return nullptr; // not found
                }

                if (target < node->value) {
                    node->left = remove(node->left, target);
                } else if (target > node->value) {
                    node->right = remove(node->right, target);
                } else {
                    // Found the node to remove.
                    if (node->left == nullptr && node->right == nullptr) {
                        delete node;
                        return nullptr;
                    }
                    if (node->left == nullptr) {
                        BinarySearchTreeNode* child = node->right;
                        node->right = nullptr; // detach so the destructor won't free it
                        delete node;
                        return child;
                    }
                    if (node->right == nullptr) {
                        BinarySearchTreeNode* child = node->left;
                        node->left = nullptr;
                        delete node;
                        return child;
                    }
                    // Two children: overwrite with the in-order successor (smallest
                    // value in the right subtree), then delete that successor.
                    BinarySearchTreeNode* successor = findMin(node->right);
                    node->value = successor->value;
                    node->right = remove(node->right, successor->value);
                }

                return node;
            }
        };

        // Owns the root pointer and exposes a uniform instance-method API. The
        // node-level statics that reassign the root stay hidden as an
        // implementation detail.
        template <typename T>
        class BinarySearchTree {
        private:
            BinarySearchTreeNode<T>* root = nullptr;

        public:
            ~BinarySearchTree() {
                delete root; // node destructor recursively frees the whole tree
            }

            void insert(T value) {
                root = BinarySearchTreeNode<T>::insert(root, value);
            }

            void remove(T value) {
                root = BinarySearchTreeNode<T>::remove(root, value);
            }

            bool contains(T value) const {
                return root != nullptr && root->find(value) != nullptr;
            }
        };
    }
}