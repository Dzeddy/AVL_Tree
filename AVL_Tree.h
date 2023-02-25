#ifndef DSAPROJ1_AVL_TREE_H
#define DSAPROJ1_AVL_TREE_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>

class Node {
public:
    // Constructor for Node class
    Node(int k, std::string n);
private:
    // Declare AVL_Tree class as friend class to give it access to private members
    friend class AVL_Tree;
    int key_;
    std::string name_;
    Node* left_;
    Node* right_;
    int height_;
    ~Node();
};

class AVL_Tree {
public:
    // Constructor for AVL_Tree class
    AVL_Tree();
    /**
     * insert function
     *
     * Adds a node object with the specified key_ (ID) and name_ into the binary search tree.
     * If necessary, the function will balance the tree to maintain its integrity.
     *
     * @param key: ID of the node to be inserted, must be a 8-digit number and unique.
     * @param name: name_ of the node to be inserted, must contain only alphabets from [a-z, A-Z, and spaces].
     *
     * @return void
     *
     * The function returns "successful" if the insertion was successful, otherwise "unsuccessful".
     * If either the ID or the NAME does not meet the specified constraints, the function will print "unsuccessful" and return.
     */
    void insert(int key, const std::string& name);
    void preOrder();
    void postOrder();
    void inOrder();
    /**
     * search function
     *
     * search for a student in a tree structure using the ID as input
     *
     * @param id The ID of the student to be searched for
     * @param root The root_ node of the tree structure
     *
     * @return void
     */
    void search(int key);
    Node* search(Node* node, int key);
    /**
     * remove function
     *
     * Finds and removes the account with the specified ID from the AVL tree.
     * If the deletion is successful, prints “successful”.
     * If the ID does not exist within the tree, prints “unsuccessful”.
     * If the deleted node has two children, the function will prioritize replacing it with its inorder successor.
     *
     * @param key: ID of the node to be deleted, must be a 8-digit number and exist within the tree.
     *
     * @return void
     *
     * The function will balance the tree if necessary to maintain its integrity.
     */
    void remove(int key);
    void searchName(const std::string& name);
    /*
     * printLevelCount
     *
     * Prints the number of levels that exist in the tree.
     * Prints 0 if the head of the tree is null. For example, the tree in Fig. 1 has 4 levels.
     */
    void printLevelCount();
    void removeInOrder(int key);

private:
    void SearchName(Node* node, const std::string& name, std::queue<Node*>& stack);
    Node* balance(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    Node* leftRightRotate(Node* node);
    Node* rightLeftRotate(Node* node);
    int computeHeightFromChildren(Node* node);
    int height(Node* node);
    int getBalance(Node* node);
    Node* Insert(Node* node, int key, std::string name);
    void inOrder(Node* inroot, bool& last);
    Node* inOrder(Node* inroot, std::stack<Node*>& stack, int count);
    Node* Remove(Node* Groot, int key);
    void RemoveInOrder(Node* node, int key);
    void PreOrder(Node* inroot, bool& last);
    void PostOrder(Node* inroot, bool& last);
    void BruteForceHeight(Node* node);
    Node* root_;
    Node* findMin(Node* node);
};

#endif  // DSAPROJ1_AVL_TREE_H
