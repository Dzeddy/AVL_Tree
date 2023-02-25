// Copyright 2023 Dylan
//
// AVL_Tree implementation.

#include <iostream>
#include <string>
#include "AVL_Tree.h"
#include <regex>
#include <utility>
#include <sstream>
Node::Node(int k, std::string n) {
    key_ = k;
    name_ = std::move(n);
    left_ = right_ = nullptr;
    height_ = 1;
}
AVL_Tree::AVL_Tree() {
    root_ = nullptr;
}
Node::~Node() {
    this->left_ = nullptr;
    this->right_ = nullptr;
}
void AVL_Tree::insert(int key, const std::string& name) {
    // Constraints: UFID is 8 digits, names must only include letters and spaces.
    // If the input is invalid, the program will print "unsuccessful". If the input
    // is valid, the program will print "successful".
    // Regex to check if key_ is valid.
        if (search(root_, key) != nullptr) {
            std::cout << "unsuccessful" << std::endl;
            return;
        }

        // Regex to check if name_ is valid.
        std::regex name_regex("^[a-zA-Z ]*?$");
        if (!std::regex_match(name, name_regex)) {
            std::cout << "unsuccessful" << std::endl;
            return;
        }

    // If the input is valid, the program will print "successful".
    root_ = Insert(root_, key, name);

    // Update the height_ of the node. check for nullptrs
    computeHeightFromChildren(root_);
    std::cout << "successful" << std::endl;
}

Node* AVL_Tree::balance(Node *node) {
    if (node == nullptr) return nullptr;
    computeHeightFromChildren(node);
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->left_) < 0) {
            return leftRightRotate(node);
        } else {
            return rightRotate(node);
        }
    } else if (balance < -1) {
        if (getBalance(node->right_) > 0) {
            return rightLeftRotate(node);
        } else {
            return leftRotate(node);
        }
    }
    return node;
}

int AVL_Tree::height(Node* node) {
    if (node == nullptr) return 0;
    int left_height = height(node->left_);
    int right_height = height(node->right_);
    node->height_ = 1 + std::max(left_height, right_height);
    return node->height_;
}

int AVL_Tree::getBalance(Node *node) {
    if (node == nullptr) return 0;
    return height(node->left_) - height(node->right_);
}

Node* AVL_Tree::rightRotate(Node *node) {
    Node* newRoot = node->left_;
    node->left_ = newRoot->right_;
    newRoot->right_ = node;
    computeHeightFromChildren(node);
    computeHeightFromChildren(newRoot);
    return newRoot;
}

Node* AVL_Tree::leftRotate(Node *node) {
    Node* newRoot = node->right_;
    node->right_ = newRoot->left_;
    newRoot->left_ = node;
    computeHeightFromChildren(node);
    computeHeightFromChildren(newRoot);
    return newRoot;
}

Node* AVL_Tree::leftRightRotate(Node *node) {
    node->left_ = leftRotate(node->left_);
    return rightRotate(node);
}

Node* AVL_Tree::rightLeftRotate(Node *node) {
    node->right_ = rightRotate(node->right_);
    return leftRotate(node);
}

int AVL_Tree::computeHeightFromChildren(Node *node) {
    if (node == nullptr) return 0;
    node->height_ = 1 + std::max(node->left_ ? height(node->left_) : 0, node->right_ ? height(node->right_) : 0);
    return node->height_;
}

Node* AVL_Tree::Insert(Node *node, int key, std::string name) {
    // If the node is null, create a new node.
    if (node == nullptr) {
        return new Node(key, name);
    }

    // If the key_ is less than the node's key_, insert the key_ into the left_ subtree.
    if (key < node->key_) {
        node->left_ = Insert(node->left_, key, name);
    } else if (key > node->key_) {
        // If the key_ is greater than the node's key_, insert the key_ into the right_ subtree.
        node->right_ = Insert(node->right_, key, name);
    } else {
        // If the key_ is equal to the node's key_, return the node.
        return node;
    }

    // Update the height_ of the node.
    node->height_ = 1 + std::max(height(node->left_), height(node->right_));

    //balance the tree if necessary
    node = balance(node);

    // Return the node.
    return node;
}

/**
 *   - search for a student in a tree structure using the ID as input
 *
 * @param id The ID of the student to be searched for
 * @param root The root_ node of the tree structure
 *
 * @return void
 */
 void AVL_Tree::search(int key) {
     Node* temp = search(root_, key);
    if (temp == nullptr) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        std::cout << temp->name_ << std::endl;
    }
 }

 Node* AVL_Tree::search(Node *node, int key) {
    // If the node is null, print "unsuccessful".
    if (node == nullptr) {
        return nullptr;
    }

    // If the key_ is less than the node's key_, search the left_ subtree.
    if (key < node->key_) {
        search(node->left_, key);
    } else if (key > node->key_) {
        // If the key_ is greater than the node's key_, search the right_ subtree.
        search(node->right_, key);
    } else {
        // If the key_ is equal to the node's key_, print the name_ of the student.
        return node;
    }
 }

void AVL_Tree::inOrder(Node* inroot, bool& last) {
    if (inroot == nullptr) return;
    // inorder is left_, root_, right_
    inOrder(inroot->left_, last);
    if (!last) {
        std::cout << ", ";
    } else {
        last = false;
    }
    std::cout << inroot->name_;
    inOrder(inroot->right_, last);
}

 void AVL_Tree::inOrder(){
     bool first = true;
     inOrder(root_, first);
    std::cout << std::endl;
 }

void AVL_Tree::PreOrder(Node* inroot, bool &first) {
    if (inroot == nullptr) return;
    // preorder is root_, left_, right_
    if (!first) {
        std::cout << ", ";
    } else {
        first = false;
    }
    std::cout << inroot->name_;
    PreOrder(inroot->left_, first);
    PreOrder(inroot->right_, first);
}


 void AVL_Tree::preOrder(){
     bool first = true;
    PreOrder(root_, first);
    std::cout << std::endl;
 }

void AVL_Tree::PostOrder(Node *inroot, bool &first) {
    if (inroot == nullptr) return;
    // postorder is left_, right_, root_
    PostOrder(inroot->left_, first);
    PostOrder(inroot->right_, first);
    if (!first) {
        std::cout << ", ";
    } else {
        first = false;
    }
    std::cout << inroot->name_;
}
void AVL_Tree::searchName(const std::string& name) {
    std::queue<Node*> stack;
    SearchName(root_, name, stack);
    if(stack.empty()) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        while(!stack.empty()) {
            std::string curr = std::to_string(stack.front()->key_);
            //if length of key_ is less than 8, add 0s to the front of the key_
            while(curr.length() < 8) {
                curr = "0" + curr;
            }
            std::cout << curr;
            stack.pop();
            if(!stack.empty())
                std::cout<<"\n";
        }
        std::cout << std::endl;
    }
}

//searchname searches for a name_ in the tree and prints the key_. however, names are not sorted in the tree, so the tree must be traversed in order to find the name_. In addition, names are not unique, so the tree must be traversed until all instances of the name_ are found.
void AVL_Tree::SearchName(Node *node, const std::string& name, std::queue<Node*>& stack) {
    if (node == nullptr) {
        return;
    }
    if(node->name_ == name) {
        stack.push(node);
    }
    SearchName(node->left_, name, stack);
    SearchName(node->right_, name, stack);
}

void AVL_Tree::postOrder() {
     bool last = true;
    PostOrder(root_, last);
    std::cout << std::endl;
}
 void AVL_Tree::remove(int key) {
     root_ = Remove(root_, key);
 }
Node* AVL_Tree::Remove(Node* Groot, int key) {
    if(Groot){
        if(key < Groot->key_) Groot->left_ = Remove(Groot->left_, key);
        else if(key > Groot->key_) Groot->right_ = Remove(Groot->right_, key);
        else{
            if(Groot->left_ == nullptr && Groot->right_ == nullptr){
                delete Groot;
                Groot = nullptr;
                std::cout << "successful\n";
            }
            else if(Groot->left_ == nullptr){
                Node* temp = Groot;
                Groot = Groot->right_;
                Groot->height_ = 1;
                delete temp;
                std::cout << "successful\n";
            }
            else if(Groot->right_ == nullptr){
                Node* temp = Groot;
                Groot = Groot->left_;
                Groot->height_ = 1;
                delete temp;
                std::cout << "successful\n";
            }
            else{
                Node* temp = findMin(Groot->right_);
                Groot->key_ = temp->key_;
                Groot->name_ = temp->name_;
                Groot->right_ = Remove(Groot->right_, temp->key_);
            }

            // Update the height_ of the current node after deletion
            if (Groot == nullptr) return Groot;
            Groot->height_ = height(Groot);

            // balance the subtree rooted at the current node if necessary
            Groot = balance(Groot);
        }
    }
    else {
        std::cout << "unsuccessful\n";
    }
    return Groot;
}

 Node* AVL_Tree::findMin(Node* node) {
     while(node->left_ != nullptr) {
         node = node->left_;
     }
     return node;
 };

 void AVL_Tree::printLevelCount() {
     std::cout << height(root_) << std::endl;
 }

 void AVL_Tree::removeInOrder(int key) {
     RemoveInOrder(root_, key);
 }
/*
 *  remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
    If removal is successful, print “successful”.
    If the Nth GatorID does not exist within the tree, print “unsuccessful”.
 */
 void AVL_Tree::RemoveInOrder(Node *node, int key){
     std::stack<Node*> stack;
     int count = key;
     Node* temp = inOrder(node, stack, count);
    if(temp == nullptr) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    Remove(root_, temp->key_);
 }

 Node* AVL_Tree::inOrder(Node* inroot, std::stack<Node*> &stack, int count) {
     if(stack.size() > count && count != 0) {
         return stack.top();
     } else if(count == 0 && stack.size() == 1) {
         return stack.top();
     }
     if(inroot == nullptr) {
         return nullptr;
     }
     inOrder(inroot->left_, stack, count);
     if(stack.size() < count + 1) {
         stack.push(inroot);
     }
     inOrder(inroot->right_, stack, count);
 }

