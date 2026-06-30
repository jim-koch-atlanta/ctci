namespace ctci {
    namespace jim {
        template <typename T>
        class BinaryTreeNode {
        public:
            T value;
            BinaryTreeNode<T>* left;
            BinaryTreeNode<T>* right;

            BinaryTreeNode(T val)
            : value{val}
            , left{nullptr}
            , right{nullptr}
             { }
        };
    }
}