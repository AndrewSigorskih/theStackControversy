#pragma once
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <optional>

enum class Color { BLACK, RED };

// RBTree implementation inspired by https://github.com/Dynmi/RedBlackTree

namespace Containers
{
    struct _rbNode
    {
        _rbNode() : parent(nullptr), left(nullptr), right(nullptr), color(Color::RED) {}
        _rbNode(const _rbNode&) = delete;
        _rbNode& operator=(const _rbNode&) = delete;
        ~_rbNode();

        _rbNode* parent;
        _rbNode* left;
        _rbNode* right;
        ssize_t key;
        int data;
        Color color;
    };

    class rbTree
    {
    public:
        rbTree() : _root(nullptr), _size(0) {}
        rbTree(const rbTree&);
        rbTree& operator=(const rbTree&);
        ~rbTree();
        void insert(ssize_t, int);
        std::optional<int> pop(ssize_t);
		std::optional<const int*> search(ssize_t) const;

        size_t size() const;
        bool empty() const;
        void clear();
    private:
        void leftRotate(_rbNode*);	
		void rightRotate(_rbNode*);
		void removeNode(_rbNode*);
        void copy(const rbTree&);
    private:
        _rbNode* _root;
        size_t _size;
    };
}
