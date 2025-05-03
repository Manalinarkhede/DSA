#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Function to insert a node in the BST
void insert(Node*& root, Node* temp) {
    if (root == nullptr) {
        root = temp;
    } else {
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr) {
            parent = current;
            if (temp->data > current->data)
                current = current->right;
            else
                current = current->left;
        }
        if (temp->data > parent->data)
            parent->right = temp;
        else
            parent->left = temp;
    }
}

// Preorder traversal
void preorder(Node* temp) {
    if (temp != nullptr) {
        cout << temp->data << " ";
        preorder(temp->left);
        preorder(temp->right);
    }
}

// Inorder traversal
void inorder(Node* temp) {
    if (temp != nullptr) {
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
}

// Postorder traversal
void postorder(Node* temp) {
    if (temp != nullptr) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << " ";
    }
}

// Search for a value
Node* search(Node* root, int key) {
    if (root == nullptr || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Find the smallest node
Node* smallest(Node* root) {
    while (root != nullptr && root->left != nullptr)
        root = root->left;
    return root;
}

// Find the longest path (height)
int longest_path(Node* root) {
    if (root == nullptr)
        return 0;
    int L = longest_path(root->left);
    int R = longest_path(root->right);
    return max(L, R) + 1;
}

// Swap (mirror) nodes of the tree
void swapNodes(Node* root) {
    if (root == nullptr)
        return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    swapNodes(root->left);
    swapNodes(root->right);
}

int main() {
    Node* root = nullptr;
    int choice, num;

    while (true) {
        cout << "\nBinary Search Tree Menu\n";
        cout << "1. Insert Node\n";
        cout << "2. Preorder Traversal\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Postorder Traversal\n";
        cout << "5. Search Node\n";
        cout << "6. Smallest\n";
        cout << "7. Longest path\n";
        cout << "8. Swapping (Mirror Tree)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a number to insert: ";
                cin >> num;
                insert(root, new Node(num));
                cout << "Node inserted\n";
                break;

            case 2:
                if (root == nullptr)
                    cout << "Tree is empty!\n";
                else {
                    cout << "Preorder Traversal: ";
                    preorder(root);
                    cout << endl;
                }
                break;

            case 3:
                if (root == nullptr)
                    cout << "Tree is empty!\n";
                else {
                    cout << "Inorder Traversal: ";
                    inorder(root);
                    cout << endl;
                }
                break;

            case 4:
                if (root == nullptr)
                    cout << "Tree is empty!\n";
                else {
                    cout << "Postorder Traversal: ";
                    postorder(root);
                    cout << endl;
                }
                break;

            case 5: {
                cout << "Enter value to search: ";
                cin >> num;
                Node* foundNode = search(root, num);
                if (foundNode)
                    cout << "Node " << num << " found in the tree.\n";
                else
                    cout << "Node " << num << " not found in the tree.\n";
                break;
            }

            case 6: {
                Node* minNode = smallest(root);
                if (minNode)
                    cout << "Minimum value in tree is: " << minNode->data << endl;
                else
                    cout << "Tree is empty!\n";
                break;
            }

            case 7:
                cout << "Longest path is: " << longest_path(root) << endl;
                break;

            case 8:
                swapNodes(root);
                cout << "Postorder traversal after swapping: ";
                postorder(root);
                cout << endl;
                break;

            case 9:
                cout << "Exiting program\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
