//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jenna Case
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;
    Node* parent;
    Node* tLeft;
    Node* tRight;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;

        //second binary search tree
        parent = nullptr;
        tLeft = nullptr;
        tRight = nullptr;
    }

    Node(Bid myBid) : Node() {
        this->bid = myBid;
    }

    ~Node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
        if (tLeft) {
            delete tLeft;
        }
        if (tRight) {
            delete tRight;
        }
        if (parent) {
            delete parent;
        }
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    Node* titleRoot;

    //bid id as a key
    void addNode(Node* node, Bid bid);
    void addTitleNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void insertID(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

    //bid title as a key
    void titleOrder(Node* node);
    void insertTitle(Bid bid, Node* newNode);
    void titleSearch(Node* node, string bidTitle);
    void postOrderTitle(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);

    //bid title as a key 
    void TitleOrder();
    void TitleSearch(string bidTitle);
    void PostOrderTitle();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
    titleRoot = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    if (this->root) {
        delete root;
    }
    if (this->titleRoot) {
        delete titleRoot;
    }
}

//display bid information
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(this->root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(this->root);
}

/**
 * Traverse the tree in title order
 */
void BinarySearchTree::TitleOrder() {
    //sorts in alphabetical
    this->titleOrder(this->titleRoot);
}

/**
 * Traverse the tree in post order by title
 *
 */
void BinarySearchTree::PostOrderTitle() {
    this->postOrderTitle(this->titleRoot);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid newBid) {
    Node* newNode = new Node(newBid);
    insertID(newBid, newNode);
    insertTitle(newBid, newNode);
}

// Inserts a bid based on bid ID
void BinarySearchTree::insertID(Bid bid, Node* newNode) {
    // Implement inserting a bid into the tree
    if (root == nullptr) {
        root = new Node();
    }
    else {
        this->addNode(root, bid);

    }
}
// Inserts a bid based on bid title
void BinarySearchTree::insertTitle(Bid bid, Node* newNode) {
    //inserts bid into tree 
    if (titleRoot == nullptr) {
        titleRoot = new Node();
    }
    else {
        this->addTitleNode(titleRoot, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string removeBidID) {
    // Implement removing a bid from the tree

    removeNode(this->root, removeBidID);
}

/**
 * Search for a bid based on bid ID
 */
Bid BinarySearchTree::Search(string bidId) {
    // Implement searching the tree for a bid based on ID
    Node* current = root;
    while (current != nullptr) {
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;

        }
        //left of tree
        if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;

        }
        //right of tree
        else {
            current = current->right;
        }
    }

    Bid bid;
    return bid;
}
/**
* Searches for bid based on bid title
*/
void BinarySearchTree::TitleSearch(string title) {
    // Implement searching the tree for a bid based on title
    Node* current = titleRoot;

    while (current != nullptr) {
        if (current->bid.title.compare(title) == 0) {
            displayBid(current->bid);
        }
        // left of tree
        if (title.compare(current->bid.title) < 0) {
            current = current->left;
        }
        else {
            //right of tree
            current = current->right;
        }
    }

    Bid bid;
    return;

}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // Implement inserting a bid into the tree
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            //add to left subtree
            this->addNode(node->left, bid);
        }

        //add to right subtree
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            this->addNode(node->right, bid);
        }
    }
}
void BinarySearchTree::addTitleNode(Node* node, Bid bid) {
    //inserts bid into tree
    if (node->bid.title.compare(bid.title) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            //add to left subtree
            this->addTitleNode(node->left, bid);
        }
    }
    //add to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            this->addTitleNode(node->right, bid);
        }
    }
}
//sorts bids by bid ID in order
void BinarySearchTree::inOrder(Node* node) {
    if (node) {
        //left recursive call
        inOrder(node->left);

        displayBid(node->bid);

        //right recursive call
        inOrder(node->right);
    }
}
//sorts bids by bid ID in pre Order
void BinarySearchTree::preOrder(Node* node) {
    if (node) {
        //root
        displayBid(node->bid);
        //left
        preOrder(node->left);
        //right
        preOrder(node->right);
    }
}

void BinarySearchTree::titleOrder(Node* node) {
    if (node) {
        //left recursive call
        titleOrder(node->left);

        displayBid(node->bid);

        //right recursive call
        titleOrder(node->right);
    }
}
void BinarySearchTree::postOrderTitle(Node* node) {
    if (node) {
        //left
        postOrderTitle(node->left);
        //right
        postOrderTitle(node->right);
        //root
        displayBid(node->bid);
    }
}
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }
    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);

    }
    else if (node->right == removeNode(node->right, bidId)) {

    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;
}
//============================================================================
// Static methods used for testing
//============================================================================



/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // @suppress("Invalid arguments")
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey, titleKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst{};

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids by ID" << endl;
        cout << "  3. Display Pre Order of Bids by ID" << endl;
        cout << "  4. Find Bid by ID" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  6. Display All Bids by Title" << endl;
        cout << "  7. Find Bid by Title" << endl;
        cout << "  8. Display Post Order of Bids by Title" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:

            bst->InOrder();
            break;

        case 3:
            bst->PreOrder();
            break;

        case 4:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bst->Remove(bidKey);
            cout << "Bid Removed" << endl;
            break;

        case 6:
            bst->TitleOrder();
            break;

        case 7:
            ticks = clock();
            bst->TitleSearch(titleKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.title.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Title " << titleKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        case 8:
            bst->PostOrderTitle();
            break;
        default:
            //prevents invalid input from being used
            //prevents infinite loop
            if (cin.fail()) {
                cout << "Invalid User Input. Please Select a Valid Option.." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
