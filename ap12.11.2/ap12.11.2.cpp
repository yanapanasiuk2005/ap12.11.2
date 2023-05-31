// ap12.11.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
using namespace std;

struct Book {
    string udc;
    string author;
    string title;
    int year;
    int quantity;
};

struct Node {
    Node* left;
    Node* right;
    Book book;
};

void initializeLibrary(Node*& root);
void addBook(Node*& root);
void removeBook(Node*& root, const string& udc);
void printLibrary(Node* root);
void saveLibraryToFile(Node* root, const string& filename);
void loadLibraryFromFile(Node*& root, const string& filename);
void menu(Node*& root);


void initializeLibrary(Node*& root) {
    root = nullptr;
}

void addBook(Node*& root) {
    // Request user input for book details
    Book newBook;
    cout << "Enter the details of the book:" << endl;
    cout << "UDC: ";
    getline(cin, newBook.udc);
    cout << "Author: ";
    getline(cin, newBook.author);
    cout << "Title: ";
    getline(cin, newBook.title);
    cout << "Year: ";
    cin >> newBook.year;
    cout << "Quantity: ";
    cin >> newBook.quantity;
    cin.ignore(); // Ignore the newline character in the input buffer

    // Create a new node for the book
    Node* newNode = new Node;
    newNode->book = newBook;
    newNode->left = nullptr;
    newNode->right = nullptr;

    // Insert the node into the tree
    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* current = root;
        while (true) {
            if (newBook.udc < current->book.udc) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                else {
                    current = current->right;
                }
            }
        }
    }

    cout << "Book added to the library." << endl;
}

void removeBook(Node*& root, const string& udc) {
    if (root == nullptr) {
        cout << "The library is empty. Cannot remove book." << endl;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    // Search for the node with the matching UDC
    while (current != nullptr && current->book.udc != udc) {
        parent = current;
        if (udc < current->book.udc) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // If the node with the UDC is not found
    if (current == nullptr) {
        cout << "Book with UDC " << udc << " not found in the library." << endl;
        return;
    }

    // Case 1: Node to be deleted is a leaf node
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            root = nullptr;
        }
        else if (current == parent->left) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }

        delete current;
    }
    // Case 2: Node to be deleted has only one child
    else if (current->left == nullptr) {
        Node* child = current->right;

        if (current == root) {
            root = child;
        }
        else if (current == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }

        delete current;
    }
    else if (current->right == nullptr) {
        Node* child = current->left;

        if (current == root) {
            root = child;
        }
        else if (current == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }

        delete current;
    }
    // Case 3: Node to be deleted has two children
    else {
        Node* successor = current->right;
        Node* successorParent = current;
        // Find the successor (minimum value in the right subtree)
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Replace the book details of the node to be deleted with the successor's book details
        current->book = successor->book;

        // Remove the successor node (which has now taken the place of the deleted node)
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        }
        else {
            successorParent->right = successor->right;
        }

        delete successor;
    }

    cout << "Book with UDC " << udc << " removed from the library." << endl;
}

void printLibrary(Node* root) {
    if (root == nullptr) {
        return;
    }

    printLibrary(root->left);
    cout << "UDC: " << root->book.udc << endl;
    cout << "Author: " << root->book.author << endl;
    cout << "Title: " << root->book.title << endl;
    cout << "Year: " << root->book.year << endl;
    cout << "Quantity: " << root->book.quantity << endl;
    cout << "-------------------------------" << endl;
    printLibrary(root->right);
}

void saveLibraryToFile(Node* root, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        // Perform an in-order traversal to save the library data to the file
        function<void(Node*)> saveHelper = [&](Node* node) {
            if (node == nullptr) {
                return;
            }
            saveHelper(node->left);
            file << node->book.udc << endl;
            file << node->book.author << endl;
            file << node->book.title << endl;
            file << node->book.year << endl;
            file << node->book.quantity << endl;
            saveHelper(node->right);
        };

        saveHelper(root);

        file.close();
        cout << "Library data saved to file: " << filename << endl;
    }
    else {
        cout << "Unable to open the file: " << filename << endl;
    }
}

void loadLibraryFromFile(Node*& root, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        initializeLibrary(root);

        string udc;
        string author;
        string title;
        int year;
        int quantity;

        while (getline(file, udc) && getline(file, author) && getline(file, title) && file >> year >> quantity) {
            file.ignore(); // Ignore the newline character in the input buffer

            // Create a new node for the book
            Node* newNode = new Node;
            newNode->book.udc = udc;
            newNode->book.author = author;
            newNode->book.title = title;
            newNode->book.year = year;
            newNode->book.quantity = quantity;
            newNode->left = nullptr;
            newNode->right = nullptr;

            // Insert the node into the tree
            if (root == nullptr) {
                root = newNode;
            }
            else {
                Node* current = root;
                while (true) {
                    if (newNode->book.udc < current->book.udc) {
                        if (current->left == nullptr) {
                            current->left = newNode;
                            break;
                        }
                        else {
                            current = current->left;
                        }
                    }
                    else {
                        if (current->right == nullptr) {
                            current->right = newNode;
                            break;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }
            }
        }

        file.close();
        cout << "Library data loaded from file: " << filename << endl;
    }
    else {
        cout << "Unable to open the file: " << filename << endl;
    }
}

void menu(Node*& root) {
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "------- Library Menu -------" << endl;
        cout << "1. Initialize Library" << endl;
        cout << "2. Add Book" << endl;
        cout << "3. Remove Book" << endl;
        cout << "4. Print Library" << endl;
        cout << "5. Save Library to File" << endl;
        cout << "6. Load Library from File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Ignore the newline character in the input buffer

        string saveFilename;
        string loadFilename;
        string udc;
    }
}