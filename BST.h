//
// Created by ohess on 3/22/24.
//

#ifndef BST_H
#define BST_H

#include <algorithm>
#include <iostream>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* smaller = nullptr;
        Node* larger = nullptr;
    };

    Node* root;

public:
    BST() {
        root = nullptr;
    }

    void display() {
        if (!root) {
            std::cout << "List empty" << std::endl;
            return;
        }
        displayRecurse(root);
    }

    void insertValue(T value) {
        Node* node = new Node;
        node->data = value;
        if (!root) {
            root = node;
            return;
        }

        Node* tempRoot = root;

        while (true) {
            // If new data equals data already in the tree, exit
            if (node->data == tempRoot->data) {
                return;
            }
            // If new data is larger
            if (node->data > tempRoot->data) {
                if (tempRoot->larger == nullptr) {
                    tempRoot->larger = node;
                    return;
                }
                tempRoot = tempRoot->larger;
            }
            // If new data is smaller
            else {
                if (tempRoot->smaller == nullptr) {
                    tempRoot->smaller = node;
                    return;
                }
                tempRoot = tempRoot->smaller;
            }
        }
    }

    bool contains(T value) {
        if (!root) {
            return false;
        }
        Node* tempRoot = root;
        while (true) {
            if (tempRoot->data == value) {
                return true;
            }
            if (tempRoot->smaller && tempRoot->data > value) {
                tempRoot = tempRoot->smaller;
            } else if (tempRoot->larger && tempRoot->data < value) {
                tempRoot = tempRoot->larger;
            } else {
                return false;
            }
        }
    }
    void remove(T value) {
        if (!root) {
            return;
        }
        if (root->data == value) {
            Node* temp = nullptr;
            // No children
            if (!(root->smaller || root.larger)) {
                delete root;
                root = nullptr;
            }
            // Single child
            else if (XOR(root->smaller, root->larger)) {
                if (root->smaller) {
                    temp = root->smaller;
                } else {
                    temp = root->larger;
                }
                delete root;
                root = temp;
            }
            // Both Children
            else {

            }
            return;

        }
        remove(value, root);
    }

    T findMin() {
        return findMin(root)->data;
    }

    T findMax() {
        return findMax(root)->data;
    }

private:
    void remove(T value, Node* tempRoot) {
        Node* tempForDelete = nullptr;
        while (true) {
            if (!tempRoot) {
                return;
            }

            // Found in smaller
            if (tempRoot->smaller && tempRoot->smaller->data == value) {
                // No children
                if (!tempRoot->smaller->smaller && !tempRoot->smaller->larger) {
                    delete tempRoot->smaller;
                    tempRoot->smaller = nullptr;
                }
                // One child
                else if (XOR(tempRoot->smaller->smaller, tempRoot->smaller->larger)) {
                    if (tempRoot->smaller->smaller) {
                        tempForDelete = tempRoot->smaller;
                        tempRoot->smaller = tempRoot->smaller->smaller;
                        delete tempForDelete;
                    } else {
                        tempForDelete = tempRoot->smaller;
                        tempRoot->smaller = tempRoot->smaller->larger;
                        delete tempForDelete;
                    }
                }
                // Both children
                else {
                    T minValue = findMin(tempRoot->smaller->larger)->data;
                    tempRoot->smaller->data = minValue;
                    remove(minValue, tempRoot->smaller->larger);
                }
                return;
            }

            // Found in larger
            if (tempRoot->larger && tempRoot->larger->data == value) {
                // No children
                if (!tempRoot->larger->smaller && !tempRoot->larger->larger) {
                    delete tempRoot->larger;
                    tempRoot->larger = nullptr;
                }
                // One child
                else if (XOR(tempRoot->larger->smaller, tempRoot->larger->larger)) {
                    if (tempRoot->larger->smaller) {
                        tempForDelete = tempRoot->larger;
                        tempRoot->larger = tempRoot->larger->smaller;
                        delete tempForDelete;
                    } else {
                        tempForDelete = tempRoot->larger;
                        tempRoot->larger = tempRoot->larger->larger;
                        delete tempForDelete;
                    }
                }
                // Both children
                else {
                    T minValue = findMin(tempRoot->larger->larger)->data;
                    tempRoot->larger->data = minValue;
                    remove(minValue, tempRoot->larger->larger);
                }
                return;
            }


            // Too Small
            if (tempRoot->data < value) {
                tempRoot = tempRoot->larger;
                continue;
            }
            // Too big
            if (tempRoot->data > value) {
                tempRoot = tempRoot->smaller;
                continue;
            }
        }
    }

    void displayRecurse(Node* node) {
        // Display BST in order
        if (node->smaller)
            displayRecurse(node->smaller);
        std::cout << node->data << " " << std::endl;
        if (node->larger)
            displayRecurse(node->larger);
    }

    Node* findMin(Node* root) {
        if (!root->smaller) {
            return root;
        }
        return findMin(root->smaller);
    }

    Node* findMax(Node* root) {
        if (!root->larger) {
            return root;
        }
        return findMax(root->larger);
    }

    bool XOR (bool b1, bool b2) {
        return b1 != b2;
    }
};
#endif //BST_H
