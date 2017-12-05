#include "stl/BinTree.h"
#include "gtest/gtest.h"

// test initialization
TEST(tree_test, test_root_val){
    float rootVal = 5;
    Tree<float> tree(rootVal);
    float returned = tree.getRoot();
    ASSERT_EQ(returned, rootVal);
}

// test inserting and deleting
TEST(tree_test, test_insert_and_delete){
    Tree<float> tree(0);

    tree.insertChildAt(0, 1);
    tree.insertChildAt(0, 2);
    ASSERT_EQ(tree.getNumLeaves(), 3);
    ASSERT_EQ(tree.getVal(1), 2);
    ASSERT_EQ(tree.getVal(2), 1);

    float leftChild = tree.getLeftChildVal(0);
    float rightChild = tree.getRightChildVal(0);
    ASSERT_EQ(leftChild, 2);
    ASSERT_EQ(rightChild, 1);

    tree.insertChildAt(1, 3);
    leftChild = tree.getLeftChildVal(1);
    rightChild = tree.getRightChildVal(1);
    ASSERT_EQ(leftChild, 3);

    unsigned short leftChildIndex = tree.getLeftChildIndex(1);
    unsigned short rightChildIndex = tree.getRightChildIndex(1);
    unsigned short parentIndex1 = tree.getParentIndex(leftChildIndex);
    unsigned short parentIndex2 = tree.getParentIndex(rightChildIndex);
    ASSERT_EQ(parentIndex1, parentIndex2);
    ASSERT_EQ(parentIndex1, (unsigned short)1);

    ASSERT_EQ(tree.getNumLeaves(), (unsigned short)4);

    tree.clear();
    ASSERT_EQ(tree.getNumLeaves(), (unsigned short)0);
}
