#pragma once
template<class K>
class TreeNode
{
    public:
        TreeNode(K key){
            this->key = key;
            this->value = 1;
            this->left = nullptr;
            this->right = nullptr;
        }
        TreeNode(const TreeNode& node){
            this->key = node.key;
            this->value = node.value;
            this->left = nullptr;
            this->right = nullptr;
        }
        ~TreeNode(){
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
        K key;
        int value;
        TreeNode * left;
        TreeNode * right;
};
