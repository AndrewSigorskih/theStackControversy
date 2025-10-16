#include "RBTreeContainer.hpp"

namespace Containers
{
    _rbNode::~_rbNode()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

    rbTree::rbTree(const rbTree& other)
    {
        if (other.empty())
            return;

        this->copy(other);
    }

    rbTree& rbTree::operator=(const rbTree& other)
    {
        if (this != &other)
        {
            if (!this->empty())
                this->clear();
            this->copy(other);
        }
        return *this;
    }

    rbTree::~rbTree()
    {
        if (_root != nullptr)
            delete _root;
    }

    void rbTree::insert(ssize_t key, int val)
    {
        auto node = new _rbNode;
        node->key = key;
        node->data = val;

        if (_root == nullptr) {
            _size++;
            _root = node;
            node->color = Color::BLACK;
            return;
        }

        _rbNode* curr = _root;
        while (true)
        {
            if (key == curr->key)
            {
                curr->data = val;
                return;
            } else if (key < curr->key) {
                if (curr->left)
                    curr = curr->left;
                else
                    break;
            } else {
                if (curr->right)
                    curr = curr->right;
                else
                    break;
            }
        }
        _size++;
        node->parent = curr;
        if (key < curr->key)
            curr->left = node;
        else
            curr->right = node;

        while ((curr->color == Color::RED) && (curr->parent != nullptr))
        {
            bool isRight = (curr == curr->parent->right);
            _rbNode* uncle;
            if (isRight)
                uncle = curr->parent->left;
            else
                uncle = curr->parent->right;
            if (uncle == nullptr)
            {
                curr->color = Color::BLACK;
                curr->parent->color = Color::RED;
                if (uncle == curr->parent->right)
                {
                    this->rightRotate(curr->parent);
                } else {
                    this->leftRotate(curr->parent);
                }
                break;
            } else if (uncle->color == Color::RED) {
                curr->color = Color::BLACK;
                uncle->color = Color::BLACK;
                curr->parent->color = Color::RED;
                curr = curr->parent;
            } else {
                curr->color = Color::BLACK;
                curr->parent->color = Color::RED;
                if (isRight)
                {
                    if (node == curr->left)
                    {
                        this->rightRotate(curr);
                        curr = node;
                    }
                    this->leftRotate(curr->parent);
                } else {
                    if (node == curr->right)
                    {
                        this->leftRotate(curr);
                        curr = node;
                    }
                    this->rightRotate(curr->parent);
                }
            }

            _root->color = Color::BLACK;
        }
    }

    std::optional<int> rbTree::pop(ssize_t key)
    {
        if (this->empty())
            return std::nullopt;

        auto curr = _root;
        while (true)
        {
            if (!curr)
                return std::nullopt;
            if (curr->key == key)
            {
                break;
            } else if (key > curr->key) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        
        auto result = std::make_optional<int>(curr->data);
        this->removeNode(curr);
        if (_size > 0)
            _size--;
        return result;
    }

    std::optional<const int*> rbTree::search(ssize_t key) const
    {
        if (this->empty())
            return std::nullopt;

        auto curr = _root;
        while (true)
        {
            if (!curr)
                return std::nullopt;
            if (curr->key == key)
            {
                break;
            } else if (key > curr->key) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        
        return std::make_optional<const int*>(&(curr->data));
    }

    size_t rbTree::size() const
    {
        return _size;
    }

    bool rbTree::empty() const
    {
        return (_size == 0);
    }

    void rbTree::clear()
    {
        if (_root != nullptr)
        {
            delete _root;
            _root = nullptr;
        }
        _size = 0;
    }

    void rbTree::leftRotate(_rbNode* node)
    {
        if (node->right == nullptr)
            throw std::runtime_error("Broken or malformed rbTree structure, cannot perform left rotation!");
        
        auto temp = node->right;
        node->right = temp->left;
        if (temp->left != nullptr)
            temp->left->parent = node;
        temp->left = node;
        temp->parent = node->parent;
        node->parent = temp;

        if (node == _root)
        {
            _root = temp;
            return;
        }

        if (node == temp->parent->left)
        {
            temp->parent->left = temp;
        } else {
            temp->parent->right = temp;
        }
    }

    void rbTree::rightRotate(_rbNode* node)
    {
        if (node->left == nullptr)
            throw std::runtime_error("Broken or malformed rbTree structure, cannot perform right rotation!");
        
        auto temp = node->left;
        node->left = temp->right;
        if (temp->right != nullptr)
            temp->right->parent = node;
        temp->right = node;
        temp->parent = node->parent;
        node->parent = temp;

        if (node == _root)
        {
            _root = temp;
            return;
        }

        if (node == temp->parent->left)
        {
            temp->parent->left = temp;
        } else {
            temp->parent->right = temp;
        }
    }

    void rbTree::removeNode(_rbNode* node)
    {
        if (node->color == Color::RED)
        {
            if ((node->left != nullptr) && (node->right != nullptr))
            {
                auto successor = node->right;
                while (successor->left != nullptr)
                    successor = successor->left;
                node->key = successor->key;
                node->data = successor->data;
                this->removeNode(successor);
            } else if (node->left != nullptr) {
                node->key = node->left->key;
                node->data = node->left->data;
                node->color = node->left->color;
                this->removeNode(node->left);
            } else if (node->right != nullptr){
                node->key = node->right->key;
                node->data = node->right->data;
                node->color = node->right->color;
                this->removeNode(node->right);
            } else {
                if (node->parent == nullptr)
                {  // deleting root
                    this->clear();
                    return;
                }
                if (node == node->parent->left)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
                delete node;
            }
        } else {
            if ((node->left != nullptr) && (node->right != nullptr))
            {
                auto successor = node->right;
                while (successor->left != nullptr)
                    successor = successor->left;
                node->key = successor->key;
                node->data = successor->data;
                this->removeNode(successor);
            } else if (node->left != nullptr) {
                node->key = node->left->key;
                node->data = node->left->data;
                this->removeNode(node->left);
            } else if (node->right != nullptr){
                node->key = node->right->key;
                node->data = node->right->data;
                this->removeNode(node->right);
            } else {
                if (node->parent == nullptr)
                {  // deleting root
                    this->clear();
                    return;
                }

                if (node == node->parent->left)
                {
                    node->parent->left = nullptr;
                    if ((node->parent->right != nullptr) && (node->parent->right->color == Color::RED))
                    {
                        node->parent->right->color = Color::BLACK;
                        leftRotate(node->parent);
                    }
                } else {
                    node->parent->right = nullptr;
                    if ((node->parent->left != nullptr) && (node->parent->left->color == Color::RED))
                    {
                        node->parent->left->color = Color::BLACK;
                        rightRotate(node->parent);
                    }
                }

                if ((node->parent->left == nullptr)
                     && (node->parent->right == nullptr)
                     && (node->parent->parent != nullptr))
                {
                    rightRotate(node->parent->parent);
                }

                delete node;
            }
        }
    }

    void rbTree::copy(const rbTree& other)
    {
        std::vector<const _rbNode*> remaining;
        remaining.reserve(other._size);

        const auto* cur = other._root;
        while (cur != nullptr)
        {
            this->insert(cur->key, cur->data);
            if (cur->right != nullptr)
                remaining.push_back(cur->right);
            
            if (cur->left != nullptr)
            {
                cur = cur->left;
            } else if (remaining.empty()) {
                break;
            } else {
                cur = remaining.back();
                remaining.pop_back();
            }
        }
    }
}
