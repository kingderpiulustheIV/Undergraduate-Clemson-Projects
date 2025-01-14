/*
 * Name: Sean Farrell
 * Date Submitted: 10/30/2023
 * Lab Section: 006
 * Assignment Name: Lab 7 - Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Node {
    int key;
    int size;
    Node* left;
    Node* right;
    Node(int k) { 
		key = k; 
		size = 1; 
		left = right = nullptr; }
};

void fix_size(Node* T)
{
    T->size = 1;
    if (T->left) 
		T->size += T->left->size;
    if (T->right) 
		T->size += T->right->size;
}

// Insert key k into tree T, returning a pointer to the resulting tree

Node* insert(Node* T, int k)
{
    if (T == nullptr)
		return new Node(k);
    if (k < T->key) 
		T->left = insert(T->left, k);
    else 
		T->right = insert(T->right, k);
    fix_size(T);
    return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)

vector<int> inorder_traversal(Node* T)
{
    vector<int> inorder;
    vector<int> rhs;
    if (T == nullptr) return inorder;
    inorder = inorder_traversal(T->left);
    inorder.push_back(T->key);
    rhs = inorder_traversal(T->right);
    inorder.insert(inorder.end(), rhs.begin(), rhs.end());
    return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node* find(Node* T, int k)
{
//Implement Node *find(Node *T, int k)
	
	// returns the node with the key k.
	
    if (T == nullptr || T->key == k) 
        return T;
	//  find fuction is recusrive until the node is found.
	
    if (k > T->key)
        return find(T->right, k); 

    return find(T->left, k); 
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node* select(Node* T, int r)
{
    //Implement Node *select(Node *T, int r)
    assert(T != nullptr && r >= 0 && r < T->size);
	
	// Dertermince precedence to the node T.
	
    int precedence = T->left ? T->left->size : 0; 
	
	// Selects the correct node based on precedence.
	
    if (precedence < r) 
        return select(T->right, r - precedence - 1);
    else if (precedence > r)
        return select(T->left, r);
    else
        return T;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node* join(Node* L, Node* R)
{
    // choose either the root of L or the root of R to be the root of the joined tree
    // (where we choose with probabilities proportional to the sizes of L and R)

    //Implement Node *join(Node *L, Node *R)
    if (R == nullptr)
        return L;
    if (L == nullptr)
        return R;
	
	// makes a random number.
	double randomNum = rand() * 101.0 / 100.0; 
	
	// finds probability based on nodes L & R sizes.
	double probability = L->size / (L->size + R->size); 


	// Rrandomly determines where to join node R based on probability.
    if (probability < randomNum)  {
        R->left = join(L, R->left);
	
		// Maintains correct size of the node R.
		fix_size(R); 
        return R;
    }
		//randomly determines where to join node L based on probability.
	
    else{
        L->left = join(L, R->left);
		
		// Maintains correct size of the node R.
		fix_size(R);
        return L;
    }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node* remove(Node* T, int k)
{
    assert(T != nullptr);

    //Implement Node *remove(Node *T, int k)

	// removes the left node if the key for node T is less than K.
    if (T->key > k)  {
        T->left = remove(T->left, k);
		// maintains correct size of node T
        fix_size(T); 
        return T;
    }
		
	// removes the right node if the key for node T is less than K.
    else if (T->key < k) {
        T->right = remove(T->right, k);
		// maintains correct size of node T
        fix_size(T);
        return T;
    }

	// Merges the right and the left node if the key of node T is equal to K.	
    else {
        Node* tempNode = T;

        T = join(T->left, T->right);

        if (T != nullptr) 
            fix_size(T);

        delete tempNode;

        return T;
    }

    return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node* T, int k, Node** L, Node** R)
{
    //Implement void split(Node *T, int k, Node **L, Node **R)
	
	// If the tree is emty sets L and R as base nullptr nodes
    if (T == nullptr) {
        *L = nullptr; 
        *R = nullptr;
    }
	
	// If the node T key is lessthan or equal to key k splits the following right nodes of the tree.
    if (T->key <= k) { 
        if (T->right == nullptr)  {
            *L = T;
            *R = nullptr;
        }
		// Recursive splits the node T into 2 trees
        else {
            split(T->right, k, L, R); 
			// pointers to trees.
            T->right = *L; 
            *L = T;
        }
        if (*L != nullptr)
            fix_size(*L);
    }
	// If the node T key is lessthan or equal to key k splits the following left nodes of the tree.
    else  { 	
        if (T->left == nullptr) {
            *R = T;
            *L = nullptr;
        }
		// Recursive splits the node T into 2 trees
        else {
            split(T->left, k, L, R);
			// pointers to trees.
            T->left = *R;
            *R = T;
        }
        if (*R != nullptr)
            fix_size(*R);
    }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node* insert_random(Node* T, int k)
{
    // If k is the Nth node inserted into T, then:
    // with probability 1/N, insert k at the root of T
    // otherwise, insert_random k recursively left or right of the root of T

    //Implement Node *insert_random(Node *T, int k)
	
	// If tree is emty it creates a new node
    if (T == nullptr)  {
        Node* newNode = new Node(k);
        return newNode;
    }
	
	//determins probiblity based on the remander of T size divided by a random number.
    double probability = rand() % T->size; 
	
	// Generates a random number
    double randomNum = rand() % 101 / 100.0; 
	
	// Inserts a new node into the tree.
    if (randomNum >= probability) { 
        Node* myNode = new Node(k);
        split(T, k, &myNode->left, &myNode->right);
        fix_size(myNode);
        return myNode;
    }
		
	//	Inserts the node recursively.
    else if (k > T->key) {
        T->right = insert_random(T->right, k); 

        fix_size(T);

        return T;
    }
    else {
        T->left = insert_random(T->left, k);

        fix_size(T); // maintains correct size

        return T;
    }
}

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

// int main()
// {
//     Node *T = nullptr;
//     std::vector<int> test{5, 13, 2, 19, 3, 29, 11, 7, 17, 23};
//     for (int i=0; i<10; i++) T = insert_random(T, test[i]);
//     std::vector<int> inorder = inorder_traversal(T);

//     Node *val = select(T, 9);
//     //ASSERT_NE(val, nullptr);
//     if (val == nullptr)
//     {
//         std::cout << "val = select(T, 9): val expected to be a valid pointer, val is null (val == nullptr).\n";
//         return 1;
//     }
//     //ASSERT_EQ(val->key, 29);
//     if (val->key != 29)
//     {
//         std::cout << "expected/correct value for val->key is 29, actual value when testing " << val->key << ".\n";
//         return 1;
//     }
//     std::cout << "Passed" << std::endl;
//     return 0;
// }