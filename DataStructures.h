#include <iostream>
#include <cmath>

template<class dataType> class SinglyLinkedList;
template<class dataType> class DoublyLinkedList;


// code of singly linked list
template<class dataType>
class Node{
    private:
        dataType value;
        Node * next;
    
    public:
        friend class SinglyLinkedList<dataType>;
        friend class DoublyLinkedList<dataType>;

        Node(){
            this->next = nullptr;
        }

        Node(const dataType & val){
            this->value = val;
            this->next = nullptr;
        }

        Node(Node<dataType> * other){
            this->value = other->getValue();
            this->next = other->getNext();
        }

        void setNextptr(Node<dataType> * nxt) {
            this->next = nxt;
        }

        void setValue(const dataType & newValue) {
            value = newValue;
            
        }

        dataType getValue(){
            return this->value; 
        }

        Node <dataType> * getNext(){
            return this->next;
        }
};

template<class dataType>
class SinglyLinkedList{
    private: 
        Node<dataType>* header;
    
    public:
        SinglyLinkedList(){
            header = nullptr;
        }

        SinglyLinkedList(Node <dataType> * head){
            this->header = head;
        }

        Node <dataType> * getHead(){
            return header;
        }

        int size(){
            if(this->header == nullptr) return 0;

            Node<dataType> * trav = this->header;
            int count(0);

            while(trav){
                count++;
                trav = trav->next;
            }

            return count;
        }

        bool isEmpty(){
            return header == nullptr;
        }

        void print(){
            if(header == nullptr) std::cout << "Linked list is empty" << std::endl;

            Node<dataType> * trav = header;

            while(trav){
                std::cout << trav->value << " ";
                trav = trav->next;
            }

            std::cout << std::endl;
        }

        bool doesExist(const dataType & target){
            if(this->header == nullptr) return false;

            Node<dataType> * trav = this->header ;
            while(trav != nullptr && trav->value != target){
                trav = trav->next;
            }

            return trav == nullptr ? false : true;
        }

        void pushFront(const dataType & newValue){
            if(doesExist(newValue)) return;

            Node<dataType> * newNode = new Node(newValue);

            if(header == nullptr){
                header = newNode;
            } else{
                newNode->next = header;
                header = newNode;
            }
        }

        void pushBack(const dataType & newValue){
            if(doesExist(newValue)) return;
            
            Node<dataType> * newNode = new Node(newValue);

            if(header == nullptr){
                header = newNode;
            } else{
                Node <dataType> * trav = header;
                
                while(trav->next != nullptr){
                    trav = trav->next ;
                }

                trav->next = newNode;
            }

        }

        bool pop(dataType & value){
            if(header == nullptr) return false;

            Node<dataType> * target = header;
            value = target->value;

            header = header->next;
            delete target;

            return true;
        }

        void deleteFirstOccurence(const dataType & target){
            if(! doesExist(target)) return ;

            Node<dataType> * trav = this->header ;

            while(trav->next->value != target){
                trav = trav->next;
            }

            Node<dataType> * targetNode = trav->getNext();

            trav->next = targetNode->next;

            delete targetNode;
        }

        void swapAdjacentElements(const dataType & val1, const dataType & val2){
            if(this->header == nullptr) std::cout << "There is nothing to swap" << std::endl;
            else{
                Node<dataType> * curr;
                Node<dataType> * trav = header;

                while(trav && trav->value != val1){
                    curr = trav;
                    trav = trav->next;
                }

                if(trav == nullptr || trav->value != val1 || trav->next == nullptr || trav->next->value != val2) std::cout << "Could not find any adjacent elements." << std::endl;
                else{
                    Node<dataType> * nodeFirst = trav;
                    Node<dataType> * nodeSecond = trav->next;
                    Node<dataType> * nodeBeforeFirst = curr;

                    nodeBeforeFirst->next = nodeSecond;
                    nodeFirst->next = nodeSecond->next;
                    nodeSecond->next = nodeFirst;
                }
            }
        }

        ~SinglyLinkedList(){
            delete header;
        }
        
};



// =============================================================================
// code of doubly linked list
template<class dataType>
class DoublyNode{
    private: 
        DoublyNode <dataType> * prev;  
        DoublyNode <dataType> * next; 
        dataType value; 

    public:
        friend class DoublyLinkedList<dataType>;

        DoublyNode(){
            prev = nullptr;
            next = nullptr;
        }

        DoublyNode(const dataType & val)
        {
            this->value = val;
            prev = nullptr;
            next = nullptr;
        }
};

template<class dataType>
class DoublyLinkedList{
    private: 
        DoublyNode<dataType>* header;
    
    public:
        DoublyLinkedList(){
            header = 0;
        }

        void insertAtFront(const dataType & val){
            DoublyNode<dataType> * newNode = new DoublyNode(val);

            if(header == 0){
                header = newNode;
            } else{
                newNode->next = header;
                header->prev = newNode;
                header = newNode;
            }
        }

        void inserAtEnd(int val){
            DoublyNode<dataType> * newNode = new DoublyNode(val);

            if(header == 0) header = newNode;
            else{
                DoublyNode <dataType> * trav = header;

                while(trav->next != nullptr){
                    trav = trav->next;
                }

                trav->next = newNode;
                newNode->prev = trav;
            }
        }

        bool removeFront(){
            if(header == 0) return false;

            DoublyNode<dataType> * temp = header;
            header = header->next;
            header->prev = nullptr;

            delete temp;
            
            return true;
        }

        bool removeEnd(){
            if(header == 0) return true;

            DoublyNode<dataType> * trav = header;

            while(trav->next != nullptr && trav->next->next != nullptr){
                trav = trav->next;
            }

            // case where the linked list has only one element
            if(trav->next == nullptr){
                header = 0;
                // simply delete the header
                return true;
            }

            DoublyNode<dataType> * target = trav->next;
            trav->next = nullptr;
            
            delete target;
            return true;
        }

        void print(){
            if(header == 0) std::cout << "No elements in the linked list" << std::endl;
            else{
                DoublyNode<dataType>* trav = header;

                while(trav != nullptr){
                    std::cout << trav->value << "  ";
                    trav = trav->next;
                }
                std::cout << std::endl;
            }
        }  

        void swapTwoAdjacentElements(const dataType & val1, const dataType & val2){
            if(header == 0) std::cout << "No elements to delete." << std::endl;
            else{
                DoublyNode<dataType> * trav = header;

                while(trav != nullptr && trav->value != val1){
                    trav = trav->next;
                }

                if(trav->next == nullptr || trav->next->value != val2) std::cout << "Elements specified are not adjacent." << std::endl;
                else{

                    DoublyNode<dataType>* firstNode = trav;
                    DoublyNode<dataType>* secondNode = trav->next;
                    DoublyNode<dataType>* nodeBeforeFirstVal = trav->prev;
                    DoublyNode<dataType>* nodeAfterSecondVal = trav->next->next;
                    
                    firstNode->next = nodeAfterSecondVal;
                    firstNode->prev = secondNode;

                    secondNode->next = firstNode;
                    secondNode->prev = nodeBeforeFirstVal;

                    // if the nodeBeforeFirstVal is null, then it is surely the header, and thus
                    // we will update the header by making it equal to the second Node
                    if(nodeBeforeFirstVal != nullptr) nodeBeforeFirstVal->next = secondNode;
                    else header = secondNode;

                    if(nodeAfterSecondVal != nullptr) nodeAfterSecondVal->prev = firstNode;
                }

            }
        }    
};



// =============================================================================
// code of stack
template<class dataType>
class Stack{
    SinglyLinkedList<dataType> linkedList;
    public:
        void push(const dataType & val){
            linkedList.pushFront(val);
        }

        bool pop(dataType & val){
            return linkedList.pop(val);
        }

        dataType peek(){
            return linkedList.getHead()->getValue();
        }

        void print(){
            linkedList.print();
        }

        bool isEmpty(){
            return linkedList.isEmpty();
        }
};



// =============================================================================
// code of queue
template<class dataType>
class Queue{
    SinglyLinkedList<dataType> linkedList;

    public:

    // O(n)
    void enqueue(const dataType & val){
        linkedList.pushBack(val);
    }

    // O(1)
    bool dequeue(dataType & val){
        return linkedList.pop(val);
    }

    // O(1)
    dataType peek(){
        return linkedList.getHead()->getValue();
    }

    int size(){
        return linkedList.size();
    }

    void print(){
        linkedList.print();
    }
};



// =============================================================================
// code of queue (using an array)
class QueueList{
    int *arr;
    int top;
    int end;
    int totalSize;
    int size;

    public:
        QueueList(int defaultSize = 10){
            this->arr = new int[defaultSize];
            top = 0;
            end = 0;
            totalSize = defaultSize;
            size = 0;
        }

        bool enqueue(int val){

            if(size == totalSize) return false;
            
            // case of empty queue
            if(top == end) {
                arr[top] = val;
                end++;
                size++;
                return true;
            }

            if(end != totalSize - 1){
                arr[end++] = val;
                size++;
            }
            else if(end == size - 1 && top != 0){
                end=0;
                arr[end] = val;
                size++;
            }

            return true;
            
        }

        bool dequeue(int & val){
            if(top == end) return false;

            if(top != totalSize - 1){
                val = arr[top];
                top++;
                size--;
                return true;
            } else{
                val = arr[top];
                top = 0;
                size--;
                return true;
            }

            return false;
        }

        int peek(){
            if(top == end) return INT16_MIN;

            return arr[top];
        }

        void print(){
            if(top == end) std::cout << "No elements in here." << std::endl;
            else if(top < end){
                for(int i=top ; i <= end ; i++){
                    std::cout << arr[i] << " ";
                }
            } else{
                int trav = top;

                while(trav != totalSize){
                    std::cout << arr[trav] << " ";
                }

                trav = 0;

                while(trav != end + 1){
                    std::cout << arr[trav] << " ";
                }
            }

            std::cout << std::endl;
        }

        int getSize() { return size ;}

        ~QueueList(){
            delete this->arr;
        }

};


// =============================================================================
// Code of Tree
template<class dataType> class Tree;

template<class dataType>
class TreeNode{

    dataType data;
    TreeNode<dataType> * firstChild;
    TreeNode<dataType> * sibling;

    public:
    friend class Tree<dataType>;

    TreeNode(){
        firstChild = 0;
        sibling = 0;
    }

    TreeNode(const dataType & element){
        firstChild = 0;
        sibling = 0;
        data = element;
    }
};

template<class dataType>
class Tree{
    private:
    TreeNode<dataType> * root;

    void preOrderTraversalHelper(TreeNode<dataType> * ptr){
        if(ptr == 0) return;

        std::cout << ptr->data << " ";

        preOrderTraversalHelper(ptr->firstChild);
            
        preOrderTraversalHelper(ptr->sibling);
    }

    void postOrderTraversalHelper(TreeNode<dataType> * ptr){
        if(ptr == 0) return; 

        postOrderTraversalHelper(ptr->firstChild);

        postOrderTraversalHelper(ptr->sibling);
        
        std::cout << ptr->data << " ";
    }

    void inOrderTraversalHelper(TreeNode<dataType> * ptr){
        if(ptr == 0) return ;

        postOrderTraversalHelper(ptr->firstChild);

        std::cout << ptr->data << " ";

        postOrderTraversalHelper(ptr->sibling);
    }

    // TODO
    // void insertNodeHelper(const dataType & newElement){

    // }

    public:
        Tree(){
            root = 0;
        }

        void postOrderTraversal(){
            postOrderTraversalHelper(this->root);
        }

        void preOrderTraversal(){
            postOrderTraversalHelper(this->root);
        }

        void inOrderTraversal(){
            postOrderTraversalHelper(this->root);
        }

        void insertNode(const dataType & newElement){
            insertNodeHelper(newElement);
        }

};


// ===========================================================================
// Code of Binary Tree

template<class dataType> class BinaryTree;

template<class dataType>
class BinaryTreeNode{
    private:
        

    public:
        BinaryTreeNode<dataType> * left;
        BinaryTreeNode<dataType> * right;
        dataType data;
        friend class BinaryTree <dataType>;

        BinaryTreeNode(){
            left = 0;
            right = 0;
        }

        BinaryTreeNode(const dataType & newElement){
            left = 0;
            right = 0;
            data = newElement;
        }
};

template<class dataType>
class BinaryTree{
    private:    
        BinaryTreeNode<dataType> * root;    

        void preOrderTraversalHelper(BinaryTreeNode<dataType> * ptr){
            if(ptr == 0) return;

            std::cout << ptr->data << " ";

            preOrderTraversalHelper(ptr->left);
            
            preOrderTraversalHelper(ptr->right);
        }

        void postOrderTraversalHelper(BinaryTreeNode<dataType> * ptr){
            if(ptr == 0) return; 

            postOrderTraversalHelper(ptr->left);

            postOrderTraversalHelper(ptr->right);
        
            std::cout << ptr->data << " ";
        }

        void inOrderTraversalHelper(BinaryTreeNode<dataType> * ptr){
            if(ptr == 0) return ;

            postOrderTraversalHelper(ptr->left);

            std::cout << ptr->data << " ";

            postOrderTraversalHelper(ptr->right);
        }

        void insertNodeHelper(BinaryTreeNode<dataType> ** ptr, const dataType & newElement){
            if( *ptr == 0){
                *ptr = new BinaryTreeNode(newElement);
            } else{
                Queue<BinaryTreeNode<dataType> *> holder;
                holder.enqueue(root);

                while(holder.size() >= 1){
                    BinaryTreeNode<dataType> * curr;
                    holder.dequeue(curr);

                    if(curr->left != 0){
                        holder.enqueue(curr->left);
                    } else {
                        curr->left = new BinaryTreeNode<dataType>(newElement);
                        std::cout << "left\n";
                        return;
                    }

                    if(curr->right != 0){
                        holder.enqueue(curr->right);
                    } else {
                        curr->right= new BinaryTreeNode<dataType>(newElement);
                        std::cout << "right\n";
                        return;
                    }
                }
            }
        }

    public:

        BinaryTree(){
           root = 0; 
        }

        void preOrderTraversal(){
            preOrderTraversalHelper( root );
        }

        void postOrderTraversal(){
            postOrderTraversalHelper(root);
        }
        void inOrderTraversal(){
            inOrderTraversalHelper(root);
        }

        void insertNode(const dataType & newElement){
            insertNodeHelper( & (this->root) , newElement);
        }  


};

// ===============================================================================
// Code of Binary Search Tree

template<class dataType> class BinarySearchTree;
template<class dataType> class AvlTree;


template<class dataType>
class BinarySearchNode{
    private:
        dataType value;
        BinarySearchNode<dataType> * right;
        BinarySearchNode<dataType> * left;

    public:
        friend class BinarySearchTree <dataType> ;
        friend class AvlTree<dataType>;

         
        BinarySearchNode(){
            right = 0;
            left = 0;
        }

        BinarySearchNode(dataType val){
            this->value = val;
            right = 0;
            left = 0;
        }
};

template<class dataType>
class BinarySearchTree{

    protected:
        BinarySearchNode<dataType> * root;

        void insertNodeHelper(BinarySearchNode<dataType> ** root, dataType val){
            if(*root == 0){

                *root = new BinarySearchNode(val);
            
            } else{
                if(val < (*root)->value){
                    insertNodeHelper( & ( (*root)->left ) , val);
                } else if(val > (*root)->value){
                    insertNodeHelper(& ( (*root)->right ) , val);
                } else{
                    std::cout << "Duplicate values" << std::endl;
                }
            }
        } 

        void preOrderTraversalHelper(BinarySearchNode<dataType> * trav){
            if(trav == 0){
                return;
            } 

            std::cout << trav->value << " ";

            preOrderTraversalHelper(trav->left);
            preOrderTraversalHelper(trav->right);
        }

        void inOrderTraversalHelper(BinarySearchNode<dataType> * trav){
            if(trav == 0){
                return;
            } 

            inOrderTraversalHelper(trav->left);
            
            std::cout << trav->value << " ";
            
            inOrderTraversalHelper(trav->right);
        }

        void postOrderTraversalHelper(BinarySearchNode<dataType> * trav){
            if(trav == 0){
                return;
            } 

            postOrderTraversalHelper(trav->left);
            
            postOrderTraversalHelper(trav->right);

            std::cout << trav->value << " ";
        }

        int sizeHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == nullptr){
                    return 0;
            } 

            return 1 + sizeHelper(ptr->left) + sizeHelper(ptr->right);
        }

        int numberOfLeavesHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == nullptr){
                return 0;
            }
            
            if((ptr->left == 0) && (ptr->right == 0)){
                return 1;
            }

            return numberOfLeavesHelper(ptr->left) + numberOfLeavesHelper(ptr->right);
        }

        int numberOfFullNodesHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == 0){
                return 0;
            } 

            int counter(0);

            if((ptr->right != 0) && (ptr->left != 0)){
                counter++;
            }

            counter += ( numberOfFullNodesHelper(ptr->right) + numberOfFullNodesHelper(ptr->left) );

            return counter;
        }   

        int depthHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == 0){
                return 0;
            }

            return std::max(depthHelper(ptr->right), depthHelper(ptr->left)) + 1;
        }

        BinarySearchNode<dataType> * removeAllLeavesHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == 0) return nullptr;
            
            if((ptr->right == 0) && (ptr->left == 0)){
                delete(ptr);
                return nullptr;
            }

            BinarySearchNode<dataType> * leftPart = removeAllLeavesHelper(ptr->left);
            BinarySearchNode<dataType> * rightPart = removeAllLeavesHelper(ptr->right);

            ptr->left = leftPart;
            ptr->right = rightPart;

            return ptr;
        }

        int heightHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == 0){
                return 0;
            }

            return std::max(heightHelper(ptr->left), heightHelper(ptr->right))  + 1; 
        }

        dataType findMinHelper(BinarySearchNode<dataType> * ptr){
            if(ptr == 0) return INT16_MIN;

            if(ptr->left == 0) return ptr->value;

            return findMinHelper(ptr->left);
        }

        BinarySearchNode<dataType> * deleteNodeHelper(BinarySearchNode<dataType> * ptr,const dataType & value){
            if(ptr == 0) return ptr;

            if(value < ptr->value){
                ptr->left = deleteNodeHelper(ptr->left, value);
            } else if(value > ptr->value){
                ptr->right = deleteNodeHelper(ptr->right, value);
            } else{
                if(ptr->left == 0  && ptr->right == 0){
                    delete ptr;
                    return 0;
                } else if(ptr->left == 0 && ptr->right != 0){
                    BinarySearchNode<dataType> * temp = ptr->right;
                    delete(ptr);
                    return temp;
                } else if(ptr->right == 0 && ptr->left != 0){
                    BinarySearchNode<dataType> * temp = ptr->left;
                    delete(ptr);
                    return temp;
                } 

                dataType minOfRightSubTree = findMinHelper(ptr->right);

                ptr->value = minOfRightSubTree;

                ptr->right = deleteNodeHelper(ptr->right , minOfRightSubTree);
            }

            return ptr;
        }

        // this code had been brang from "https://simplesnippets.tech/what-is-avl-tree-data-structure-all-avl-operations-with-full-code/"
        void print2DHelper(BinarySearchNode<dataType> * r, int space){
            if (r == NULL) // Base case  1
                return;

            space += 10; // Increase distance between levels   2
            print2DHelper(r -> right, space); // Process right child first 3 
            std::cout << std::endl;
            for (int i = 10; i < space; i++) // 5 
            std::cout << " "; // 5.1  
            std::cout << r -> value << "\n"; // 6
            print2DHelper(r -> left, space); // Process left child  7
        }

        BinarySearchNode<int> * generateBalancedBSTHelper(BinarySearchNode<int> ** ptr, int min , int max){
            if(min == max){
                (*ptr) = new BinarySearchNode<int>(min);
                return *ptr;
            }

            std::cout << min  << " " << max << std::endl;
            (*ptr) = new BinarySearchNode<int>( (min + max) / 2 );
            (*ptr)->left = generateBalancedBSTHelper(& ((*ptr)->left) , min , max - ( ( max - min ) / 2) - 1 );
            (*ptr)->right = generateBalancedBSTHelper(& ((*ptr)->right) , min + ( ( max - min ) / 2) + 1 , max );

            return *ptr;
        }

    public:
        BinarySearchTree(){
            root = 0;
        }

        void insertNode(dataType val){
            insertNodeHelper( & this->root , val);
        }

        void preOrderTraversal(){
            preOrderTraversalHelper(this->root);
        }

        void inOrderTraversal(){
            inOrderTraversalHelper(this->root);
        }

        void postOrderTraversal(){
            postOrderTraversalHelper(this->root);
        }

        bool operator!=(const BinarySearchTree<dataType> & other){
            return  ! (this->root == other.root);
        }

        int size(){
            return sizeHelper(this->root);
        }

        int numberOfLeaves(){
            return numberOfLeavesHelper(this->root);
        }

        int numberOfFullNodes(){
            return numberOfFullNodesHelper(this->root);
        }

        int depth(){
            return depthHelper(this->root);
        }

        int height(){
            return heightHelper(this->root);
        }

        int findMin(){
            return findMinHelper(this->root);
        }

        void deleteNode(int value){
            deleteNodeHelper(this->root , value);
        }

        BinarySearchNode<dataType> * removeAllLeaves(){
            return removeAllLeavesHelper(this->root);
        }

        void generateBalancedBST(int height){
            generateBalancedBSTHelper( & (this->root) , 1 , ( pow(2, height +1) - 1 ) );
        }

        BinarySearchTree<char> EvalET(const std::string & expression){
            Stack< BinarySearchTree<char> > exp ;

            for(int i=0 ; i< expression.size() ; i++){
                BinarySearchTree<char> temp;

                if(expression[i] != '+' && expression[i] != '*'){
                    temp.insertNode(expression[i]);
                } else{
                    BinarySearchTree<char> T1char, T2char;

                    // popping the first two characters
                    exp.pop(T1char) ; exp.pop(T2char);

                    // inserting the operator in its own tree
                    temp.insertNode(expression[i]);

                    temp.root->left = T1char.root;
                    temp.root->right = T2char.root;
                }

                exp.push(temp);
            }

            BinarySearchTree<char> result; exp.pop(result);
            return result;
        }

        void print2D() {
            this->print2DHelper( this->root , 5);
        }
 
};


template<class dataType>
class AvlTree : public BinarySearchTree<dataType> {

    BinarySearchNode<dataType> * insertNodeHelper(BinarySearchNode<dataType> ** root, BinarySearchNode<dataType> * newElement){
        if( (*root) == 0){
            (*root) = newElement;
            return (*root);
        } 

        if(newElement->value < (*root)->value ){
            (*root)->left = insertNodeHelper( & ( (*root)->left ) , newElement);
        } else if(newElement->value > (*root)->value ){
            (*root)->right = insertNodeHelper( & ( (*root)->right ) , newElement);
        } else{
            std::cout << "DUPLICATE VALUES NOT ALLOWED" << std::endl;
        }

        int balanceFactor = getBalanceFactor(*root);

        if( balanceFactor > 1 && newElement->value < (*root)->left->value){
            return rightRotate(*root);
        } 

        if(balanceFactor < -1 && newElement->value > (*root)->right->value){
            return leftRotate(*root);
        }

        if(balanceFactor > 1 && newElement->value > (*root)->left->value){
            std::cout << "HERE 1" << std::endl;
            return leftRightRotate(*root);
        }

        if(balanceFactor < -1 && newElement->value < (*root)->right->value){
            std::cout << "HERE 2" << std::endl;
            return rightLeftRotate(*root);
        }

        return *root ;
    }

    BinarySearchNode<dataType> * rightRotate(BinarySearchNode<dataType> * ptr){
        BinarySearchNode<dataType> * temp = ptr->left;
        BinarySearchNode<dataType> * restOfTree = temp->right;

        // rotating
        temp->right = ptr;
        ptr->left = restOfTree;

        return temp;
    }

    BinarySearchNode<dataType> * leftRotate(BinarySearchNode<dataType> * ptr){
        BinarySearchNode<dataType> * temp = ptr->right;
        BinarySearchNode<dataType> * restOfTree = temp->left ;

        // rotating
        temp->left = ptr;
        ptr->right = restOfTree;
    
        return temp;
    }

    BinarySearchNode<dataType> * leftRightRotate(BinarySearchNode<dataType> * ptr){
        ptr->left = leftRotate(ptr->left);

        return rightRotate(ptr);
    }

    BinarySearchNode<dataType> * rightLeftRotate(BinarySearchNode<dataType> * ptr){
        ptr->right = rightRotate(ptr->right);

        return leftRotate(ptr);
    }

    int getBalanceFactor(BinarySearchNode<dataType> * ptr){
        if(ptr == 0){
            return 0;
        } 

        return (this->heightHelper(ptr->left) - this->heightHelper(ptr->right)) ;
    }

    public:
        void insertNode(const dataType & newElement){
            this->root = insertNodeHelper( & (this->root) , new BinarySearchNode(newElement) );
        }

        
};
