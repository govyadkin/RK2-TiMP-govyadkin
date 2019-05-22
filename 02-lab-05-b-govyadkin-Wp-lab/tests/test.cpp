// Copyright 2019 govyadkin <mgovyadkin@gmail.com>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(BinarySearchTree, Contract)
{
    BinarySearchTree<int> a;
    EXPECT_EQ(a.root(), nullptr);
}

TEST(BinarySearchTree, Add)
{
    BinarySearchTree<int> a;
    a.Add(5);

    EXPECT_EQ(a.root()->Value, 5);

    a.Add(5);
    a.Add(6);
    a.Add(7);
    a.Add(3);
    a.Add(4);

    EXPECT_EQ(a.root()->Left->Right->Value, 4);
}

TEST(BinarySearchTree, Find)
{
    BinarySearchTree<int> a;
    a.Add(5);
    a.Add(6);
    a.Add(4);

    EXPECT_EQ(a.Find(5), a.root());
    EXPECT_EQ(a.Find(7), nullptr);
    EXPECT_EQ(a.Find(6), a.root()->Right);
    EXPECT_EQ(a.Find(4), a.root()->Left);
}

TEST(BinarySearchTree, Depth)
{
    BinarySearchTree<int> b;

    EXPECT_EQ(b.Depth(), 0);

    b.Add(5);

    EXPECT_EQ(b.Depth(), 1);

    b.Add(6);

    EXPECT_EQ(b.Depth(), 2);

    b.Add(7);
    b.Add(3);
    b.Add(4);

    EXPECT_EQ(b.Depth(), 3);
}

TEST(BinarySearchTree, Remove)
{
    BinarySearchTree<int> a;
    a.Add(5);

    a.Remove(a.root());

    ASSERT_EQ(a.root(), nullptr);

    a.Add(5);
    a.Add(6);
    a.Add(7);
    a.Add(3);
    a.Add(4);
    a.Remove(a.root());

    EXPECT_EQ(a.Depth(), 4);

    a.Add(1);
    a.Add(2);
    a.Add(0);
    a.Remove(a.root()->Left);

    ASSERT_EQ((a.root()->Left)->Value, 0);

    a.Add(5);
    a.Remove((a.root()->Right)->Right);

    EXPECT_EQ(a.Depth(), 4);

    a.Remove(a.root()->Right);

    EXPECT_EQ(a.Depth(), 3);

    a.Remove(a.root()->Left);
    a.Remove(a.root()->Left);

    EXPECT_EQ(a.Depth(), 3);

    a.Remove(a.root());
    a.Remove(a.root()->Right);

    EXPECT_EQ(a.Depth(), 1);
}

TEST(BinarySearchTree, TreeNode)
{
    TreeNode<int> a;
    a.Value = 5;
    TreeNode<int>* a1 = &a;

    EXPECT_EQ(IsBinarySearchTree(a1), true);

    TreeNode<int> b;
    b.Value = 6;
    a1->Right = &b;

    EXPECT_EQ(IsBinarySearchTree(a1), false);

    b.Parent = a1;

    EXPECT_EQ(IsBinarySearchTree(a1), true);

    TreeNode<int> c;
    c.Value = 6;
    a1->Left = &c;
    c.Parent = a1;

    EXPECT_EQ(IsBinarySearchTree(a1), false);

    c.Value = 4;

    EXPECT_EQ(IsBinarySearchTree(a1), true);
    EXPECT_EQ(IsBinarySearchTree(a1->Left), false);

    b.Value = 4;

    EXPECT_EQ(IsBinarySearchTree(a1), false);

    b.Value = 8;
    TreeNode<int> e;
    e.Value = 4;
    b.Left = &e;
    e.Parent = &b;

    EXPECT_EQ(IsBinarySearchTree(a1), false);

    e.Value = 6;
    TreeNode<int> f;
    f.Value = 4;
    b.Right = &f;
    f.Parent = &b;

    EXPECT_EQ(IsBinarySearchTree(a1), false);

    TreeNode<int>* d = nullptr;

    EXPECT_EQ(IsBinarySearchTree(d), true);
}
