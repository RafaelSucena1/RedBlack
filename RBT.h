#include "BST.h"

using namespace std;

template<typename comparable>
class RBT : public BST<comparable> {

public:
    /**
     * inserts a node and verifies/fixes
     * Red Black properties
     * @param value
     * @return
     */
    RBT insert(comparable value) {
        node<comparable> *currentNode = BST<comparable>::insert(value);
        /**
         * if the value was already in tree
         */
        if (!currentNode)
            return *this;

        /**
         * inserted node is always red
         */
        currentNode->isRed = true;

        /**
         * fix Red Black Tree properties
         */
        return fixupInsertRB(currentNode);
    }


    node<comparable> *errorNode;

    /**
     * removes a node and verifies/fixes
     * the Red Black properties
     * @param value
     * @return
     */
    RBT remove(comparable value) {
        node<comparable> *currentNode = BST<comparable>::remove(value);
        /**
         * fix Red Black Tree properties
         */
        return fixupRemoveRB(currentNode);

    }

    /**
     * verifies all Red Black properties
     */
    bool testRB() {
        if (this->root->isRed)
            return false;

        if (!ifNodeIsRedBothChildrenAreBlack(this->root))
            return false;

        if (!sameNumberOfBlackNodes())
            return false;

        return true;
    }

private:

    RBT fixupInsertRB(node<comparable> *currentNode) {
        while (!isBlack(currentNode->parent)) {
            node<comparable> *parent = currentNode->parent;

            if (parent->parent->left == parent) {
                node<comparable> *uncle = parent->parent->right;

                if (!isBlack(uncle)) {
                    parent->isRed = false;
                    uncle->isRed = false;
                    parent->parent->isRed = true;
                    currentNode = parent->parent;

                } else {
                    if (currentNode == parent->right) {
                        currentNode = parent;
                        this->rotateLeft(currentNode);
                    }
                    parent = currentNode->parent;
                    parent->isRed = false;
                    parent->parent->isRed = true;
                    this->rotateRight(parent->parent);
                }

            } else {
                node<comparable> *uncle = parent->parent->left;

                if (!isBlack(uncle)) {
                    parent->isRed = false;
                    uncle->isRed = false;
                    parent->parent->isRed = true;
                    currentNode = parent->parent;
                } else {

                    if (currentNode == parent->left) {
                        currentNode = parent;
                        this->rotateRight(currentNode);
                    }
                    parent = currentNode->parent;
                    parent->isRed = false;
                    parent->parent->isRed = true;
                    this->rotateLeft(parent->parent);
                }
            }
        }
        this->root->isRed = false;
        return *this;
    }

    RBT fixupRemoveRB(node<comparable> *currentNode) {
        while(currentNode != this->root && !currentNode->isRed){
            node<comparable>* parent = currentNode->parent;
            if(currentNode == parent->left){
                node<comparable> *uncle = parent->right;
                if(uncle->isRed){
                    uncle->isRed = false;
                    parent->isRed = true;
                    this->rotateLeft(parent);
                    uncle = parent->right;
                }
                if(!uncle->left->isRed && !uncle->right->isRed){
                    uncle->isRed = true;
                    currentNode = parent;
                } else {
                    if(!uncle->right->isRed){
                        uncle->left->isRed = false;
                        uncle->isRed = true;
                        this->rotateRight(uncle);
                        uncle = parent->right;
                    }
                    uncle->isRed  = parent->isRed;
                    parent->isRed = false;
                    uncle->right->isRed = false;
                    this->rotateLeft(parent);
                    this->root = currentNode;
                }
            } else {
                node<comparable> *uncle = parent->left;
                if(uncle->isRed){
                    uncle->isRed = false;
                    parent->isRed = true;
                    this->rotateRight(parent);
                    uncle = parent->left;
                }
                if(!uncle->left->isRed && !uncle->left->isRed){
                    uncle->isRed = true;
                    currentNode = parent;
                } else {
                    if(!uncle->left->isRed){
                        uncle->right->isRed = false;
                        uncle->isRed = true;
                        this->rotateLeft(uncle);
                        uncle = parent->left;
                    }
                    uncle->isRed  = parent->isRed;
                    parent->isRed = false;
                    uncle->left->isRed = false;
                    this->rotateRight(parent);
                    this->root = currentNode;
                }
            }
        }
        currentNode->isRed = false;
    }

    /**
     * checks if node is black
     * null nodes are black
     * @param currentNode
     * @return
     */
    bool isBlack(node<comparable> *currentNode) {
        if (!currentNode)
            return true;

        return !currentNode->isRed;
    }


    bool ifNodeIsRedBothChildrenAreBlack(node<comparable> *currentNode) {
        if(!currentNode)
            return true;
        if (!currentNode->right && !currentNode->left)
            return true;
        if (currentNode->isRed) {
            if (!isBlack(currentNode->left) || !isBlack(currentNode->right)) {
                cout << "ifNodeIsRedBothChildrenAreBlack:: false" << endl;
                cout << "node value= " << currentNode->value << endl;
                return false;
            }
        }

        return ifNodeIsRedBothChildrenAreBlack(currentNode->left) &&
               ifNodeIsRedBothChildrenAreBlack(currentNode->right);
    }

    /**
     * helper boolean,
     * turns false if in any instance of countNumberOfBlackNodes()
     * this property failed
     */
    bool numberBlackNodesPropertyDidNotFail = true;

    /**
     * returns true if the property of the same number of black nodes holds
     * it automatically restores the helper variable above
     * @return
     */
    bool sameNumberOfBlackNodes() {
        countNumberOfBlackNodes(this->root);

        bool result = numberBlackNodesPropertyDidNotFail;
if(!result)
    cout << "sameNumberOfBlackNodes:: false" << endl;
        numberBlackNodesPropertyDidNotFail = true;

        return result;
    }

    /**
     * counts the number of black nodes from the current node
     * until the leafs
     * @param currentNode
     * @return
     */
    int countNumberOfBlackNodes(node<comparable> *currentNode) {
        if (!currentNode)
            return 1;

        int blacksOnLeft = countNumberOfBlackNodes(currentNode->left);
        int blacksOnRight = countNumberOfBlackNodes(currentNode->right);

        if (blacksOnLeft != blacksOnRight)
            numberBlackNodesPropertyDidNotFail = false;

        if (currentNode->isRed) {
            return blacksOnLeft;
        } else {
            return blacksOnLeft + 1;
        }

    }

};
