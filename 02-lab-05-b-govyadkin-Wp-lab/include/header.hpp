// Copyright 2019 govyadkin <mgovyadkin@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <functional>
#include <vector>
#include <cstddef>
#include <queue>

template <class T>
class BinarySearchTree
{
public:
    struct Node
    {
        Node* Parent = nullptr;
        Node* Left = nullptr;
        Node* Right = nullptr;
        T Value;

        size_t DepthN() const
        {
            size_t lenL = 1, lenR = 1;
            if (this->Left != nullptr)
            {
                lenL += this->Left->DepthN();
            }
            if (this->Right != nullptr)
            {
                lenR += this->Right->DepthN();
            }
            return (lenL > lenR) ? lenL : lenR;
        }
    };

private:
    Node* Root;

    void Del(Node* None)
    {
        if (None != nullptr)
        {
            if (None->Left != nullptr)
            {
                Del(None->Left);
                None->Left = nullptr;
            }
            if (None->Right != nullptr)
            {
                Del(None->Right);
                None->Right = nullptr;
            }
        }
        delete None;
    }

public:
    BinarySearchTree()
    {
        Root = nullptr;
    }

    ~BinarySearchTree()
    {
        Del(Root);
    }

    Node* root()
    {
        return Root;
    }

    void Add(const T& d)
    {
        if (Root != nullptr)
        {
            Node* it = Root;
            Node* it2 = it;
            while (it != nullptr)
            {
                if (d > it->Value)
                {
                    it2 = it;
                    it = it->Right;
                }else if (d < it->Value) {
                    it2 = it;
                    it = it->Left;
                }else {
                    return;
                }
            }
            if (d > it2->Value)
            {
                it2->Right = new Node;
                it2->Right->Value = d;
                it2->Right->Parent = it2;
            }else {
                it2->Left = new Node;
                it2->Left->Value = d;
                it2->Left->Parent = it2;
            }
        }else {
            Root = new Node;
            Root->Value = d;
        }
    }

    Node* Find(const T& d) const
    {
        Node* it = Root;
        while (it != nullptr)
        {
            if (d > it->Value)
            {
                it = it->Right;
            }else if (d < it->Value) {
                it = it->Left;
            }else {
                return it;
            }
        }
        return nullptr;
    }

    void Remove(Node* None)
    {
        if (None != nullptr)
        {
            if (None->Left != nullptr)
            {
                if (None->Right != nullptr)
                {
                    Node* it = None->Left;
                    while (it->Right != nullptr)
                    {
                        it = it->Right;
                    }
                    it->Right = None->Right;
                    it->Right->Parent = it;
                }
                if (None->Parent != nullptr)
                {
                    if (None->Parent->Right == None)
                    {
                        None->Parent->Right = None->Left;
                    }else {
                        None->Parent->Left = None->Left;
                    }
                }else {
                    (*this).Root = None->Left;
                }
                None->Left->Parent = None->Parent;
            }else if (None->Right != nullptr) {
                if (None->Parent != nullptr)
                {
                    if (None->Parent->Left == None)
                    {
                        None->Parent->Left = None->Right;
                    }else {
                        None->Parent->Right = None->Right;
                    }
                }else {
                    (*this).Root = None->Right;
                }
                None->Right->Parent = None->Parent;
            }else if (None->Parent != nullptr) {
                if (None->Parent->Left == None)
                {
                    None->Parent->Left = nullptr;
                }else {
                    None->Parent->Right = nullptr;
                }
            }else {
                (*this).Root = nullptr;
            }
            delete None;
            None = nullptr;
        }
    }
    size_t Depth() const
    {
        if (Root == nullptr)
        {
            return 0;
        }
        return Root->DepthN();
    }
};

template <class T>
std::ostream& operator<< (std::ostream& out, const BinarySearchTree<T>& tree)
{
   using Node = typename BinarySearchTree<T>::Node;
   if (tree == nullptr)
   {
       return out;
   }
   if (tree.root() == nullptr)
   {
       return out;
   }
   std::queue<Node> q;
   q.push(*(tree->root()));
   Node n;
   q.push(n);
   while (q.size() > 1)
   {
       if (q.front() == n)
       {
           out << std::endl;
           q.push(n);
           q.pop();
           continue;
       }
       if (q.front().Left != n)
       {
           q.push(q.front().Left);
       }
       if (q.front().Right != n)
       {
           q.push(q.front().Right);
       }
       out << q.front().Value << " ";
       q.pop();
   }
   return out;
}

template <class T>
struct TreeNode
{
    TreeNode* Parent = nullptr;
    TreeNode* Left = nullptr;
    TreeNode* Right = nullptr;
    T Value;
};

template <class T, class Comp = std::less<>>
bool Impuls(const TreeNode<T>* None, const T a, Comp sravn = Comp{})
{
    if (None == nullptr) return false;

    if (sravn(a, None->Value) ||
        Impuls(None->Left, a, sravn) ||
        Impuls(None->Right, a, sravn))
          return true;

    return false;
}

template <class T>
bool RecursiveTraversal(const TreeNode<T>* None)
{
    if (None == nullptr) return true;

    if (None->Left != nullptr &&
        (None->Left->Parent != None ||
        Impuls(None->Left, None->Value)))
            return false;

    if (None->Right != nullptr &&
        (None->Right->Parent != None ||
        Impuls(None->Right, None->Value, std::greater<>{})))
            return false;

    return (RecursiveTraversal(None->Left) &&
            RecursiveTraversal(None->Right));
}

template <class T>
bool IsBinarySearchTree(const TreeNode<T>* root)
{
    if (root == nullptr) return true;
    if (root->Parent != nullptr) return false;
    return RecursiveTraversal(root);
}

#endif // INCLUDE_HEADER_HPP_
