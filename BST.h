using namespace std;
/**
 * the basic struct of a node
 * for this type of tree,
 * possibly the height variable
 * could be removed without loss
 * of speed (research) @todo
 */
template<typename comparable>
struct node {
    comparable value;
    bool  isRed;
    node *right  = nullptr;
    node *left   = nullptr;
    node *parent = nullptr;
};


template<typename comparable>
class BST {

private:

    /**
     * actual test function
     * @param node
     * @param biggerThan
     * @param smallerThan
     * @return
     */
    bool testBST(node<comparable>* currentNode, node<comparable>* smallerThan, node<comparable>* biggerThan){
        if(!currentNode)
            return true;

        bool leftTest = true;
        if(!biggerThan && currentNode->value < biggerThan->value)
            leftTest = false;


        bool rightTest = true;
        if(!smallerThan && currentNode->value > smallerThan->value)
            rightTest = false;

        bool immediateTestOk = rightTest && leftTest;
        if(!immediateTestOk)
            return false;

        return testBST(currentNode->left, currentNode, biggerThan) && testBST(currentNode->right, smallerThan, currentNode);
    }

    int const COUNT = 10;
    void print2DUtil(node<comparable>* currentNode,int space)
    {
        // Base case
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        if(currentNode->right)
            print2DUtil(currentNode->right, space);

        // Print current node after space
        // count
        cout<<endl;
        for (int i = COUNT; i < space; i++)
            cout<<" ";
        cout<<currentNode->value<< (currentNode->isRed ? "R": "B") <<"\n";

        // Process left child
        if(currentNode->left)
            print2DUtil(currentNode->left, space);
    }

    /**
    * helper function for testing
    * or just for general checking of height
    *
    */
    int getHeight(node<comparable>* node){

        if(!node){
            return 0;
        }
        int leftHeight  = getHeights(node->left);
        int rightHeight = getHeights(node->right);

        int max = leftHeight > rightHeight ? leftHeight : rightHeight;

        return max + 1;
    }

protected:


    /**
     * IN THIS CONVENTION THE FUNCTION LIFTS THE CHILD NODE
     * the standard left rotation
     * but it also updates heights
     * @param currentNode
     */
    void rotateLeft(node<comparable> *currentNode) {

        node<comparable> *child = currentNode->right;
        node<comparable> *grandChild = currentNode->right->left;
        node<comparable> *parent = currentNode->parent;

        if (currentNode == this->root) {
            this->root = child;
        }

        if(parent){
            if(currentNode == parent->left){
                parent->left = child;
            } else {
                parent->right = child;
            }
        }

        child->parent = parent;
        currentNode->right = grandChild;
        child->left = currentNode;
        currentNode->parent = child;

        if(grandChild)
            grandChild->parent = currentNode;

    }

    /**
     * IN THIS CONVENTION THE FUNCTION LIFTS THE CHILD NODE
     * the standard right rotation
     * but it also updates heights
     * @param currentNode
     */
    void rotateRight(node<comparable> *currentNode) {

        node<comparable> *child = currentNode->left;
        node<comparable> *grandChild = currentNode->left->right;
        node<comparable> *parent = currentNode->parent;

        if (currentNode == this->root) {
            this->root = child;
        }

        if(parent){
            if(currentNode == parent->left){
                parent->left = child;
            } else {
                parent->right = child;
            }
        }

        child->parent = parent;
        currentNode->left = grandChild;
        child->right = currentNode;
        currentNode->parent = child;

        if(grandChild)
            grandChild->parent = currentNode;

    }


public:
    node<comparable>* root = nullptr;
    /**
     * will check if the value is already in the tree
     * @param value
     * @return
     */
    bool contains(comparable value){
        node<comparable> *currentNode = root;
        while(currentNode){
            if(value == currentNode->value){
                cout << "This tree contains the value " << value << endl;
                return true;

            } else if(value < currentNode->value){
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }
        cout << "This tree does not contain the value " << value << endl;
        return false;
    }

    /**
     * finds the absolute maximum
     * value of the tree
     * @return
     */
    comparable findMax() const{
        if(node<comparable>* max = findMax(root))

            return max->value;
        /**
         * throw error @todo
         */

    }

    /**
     * finds the maximum value
     * moving from the provided node
     * and returns that node
     *
     * @param currentNode
     * @return
     */
    node<comparable>* findMax(node<comparable>* currentNode) const{
        while(currentNode && currentNode->right){
            currentNode = currentNode->right;
        }
        return currentNode;
    }

    /**
     * finds the absolute minimum
     * value of the tree
     * @return
     */
    comparable findMin() const{
        if(node<comparable>* min = findMin(root))
            return min->value;

        /**
         * throw error @todo
         */
    }

    /**
     * finds the minimum value
     * moving from the provided node
     * and returns that node
     * @param currentNode
     * @return
     */
    node<comparable>* findMin(node<comparable>* currentNode) const{
        while(currentNode && currentNode->left){
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    /**
     * finds the node with that value if
     * that value is on the tree
     * returns the found node or nullptr
     * @param value
     * @return
     */
    node<comparable>* find(comparable value) const{
        node<comparable> *currentNode = root;
        while(currentNode){
            if(value == currentNode->value){
                cout << "This tree contains the value " << value << endl;
                return currentNode;

            } else if(value > currentNode->value){
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }
        cout << "This tree does not contain the value " << value << endl;
        return nullptr;
    }


    /**
     * inserts a node and verifies/fixes
     * AVL property
     * @param value
     * @return
     */
    node<comparable>* insert(comparable value){
        /**
         * if AVL is empty,
         * then currentNode nullptr as root is also
         */
        if(!root){
            root = new node<comparable>;
            root->value  = value;
            return root;
        }
        node<comparable>* currentNode = root;

        while(currentNode){
            int nodeValue = currentNode->value;
            if(nodeValue == value){
                return nullptr;
            }
            if(value < nodeValue){
                if(!currentNode->left){
                    node<comparable> *newNode = new node<comparable>;
                    newNode->value  = value;
                    newNode->parent = currentNode;
                    currentNode->left = newNode;
                    return newNode;
                } else {
                    currentNode = currentNode->left;
                }
            } else {
                if(!currentNode->right){
                    node<comparable> *newNode = new node<comparable>;
                    newNode->value  = value;
                    newNode->parent = currentNode;
                    currentNode->right = newNode;
                    return newNode;
                } else {
                    currentNode = currentNode->right;
                }
            }
        }
    }

    node<comparable>* remove(comparable value){
        node<comparable> *currentNode = find(value);

        if(!currentNode){
            return root;
        }

        if(currentNode->left){
            node<comparable>* replaceWith = findMin(currentNode->left);
            node<comparable> *parentOfReplacement = replaceWith->parent;
            /**
             * if the node has children
             */
            if(node<comparable> *right =replaceWith->right){
                right->parent = parentOfReplacement;
                parentOfReplacement->left = right;
            }
            replaceWith->parent = currentNode->parent;
            replaceWith->parent->left = currentNode;

            replaceWith->right = currentNode->right;
            replaceWith->left  = currentNode->left;

            delete currentNode;
            return replaceWith;
        } else {
            if(node<comparable> *parent = currentNode->parent){
                parent->left = nullptr;
                delete currentNode;
                return parent;
            }
            delete currentNode;
            return root;
        }
    }

    /**
     * callable test function
     * @return
     */
    bool testBST(){
        return testBST(root, nullptr, nullptr);
    }

    void print()
    {

        // Pass initial space count as 0
        print2DUtil(root, 0);
    }

};
