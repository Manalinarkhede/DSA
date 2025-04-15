#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    void insert(node*& root, node* temp) {
        if (root == nullptr) {
            root = temp;
        } else {
            node* parent = nullptr;
            node* current = root;

            while (current != nullptr) {
                parent = current;
                if (current->data < temp->data) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }

            if (parent->data < temp->data) {
                parent->right = temp;
            } else {
                parent->left = temp;
            }
        }
    }

    void preorder(node* temp) {
        if (temp != nullptr) {
            cout << temp->data << " ";
            preorder(temp->left);
            preorder(temp->right);
        }
    }

    void postorder(node* temp) {
        if (temp != nullptr) {
            postorder(temp->left);
            postorder(temp->right);
            cout << temp->data << " ";
        }
    }

    void inorder(node* temp) {
        if (temp != nullptr) {
            inorder(temp->left);
            cout << temp->data << " ";
            inorder(temp->right);
        }
    }

    node* search(node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        } else if (key < root->data) {
            return search(root->left, key);
        } else if (key > root->data) {
            return search(root->right, key);
        } else {
            return root;
        }
    }
};

int main() {
    node obj(0); // Dummy object to call member functions
    node* root = nullptr;
    int total, value;

    cout << "Enter how many nodes you want to insert? ";
    cin >> total;

    cout << "Enter the values one by one:" << endl;
    for (int i = 0; i < total; i++) {
        cin >> value;
        node* temp = new node(value);
        obj.insert(root, temp);
    }

    cout << "\nInorder: ";
    obj.inorder(root);

    cout << "\nPreorder: ";
    obj.preorder(root);

    cout << "\nPostorder: ";
    obj.postorder(root);

    int key;
    cout << "\n\nEnter the value you want to search: ";
    cin >> key;
    node* result = obj.search(root, key);

    if (result != nullptr) {
        cout << "Node with value " << key << " found!" << endl;
    } else {
        cout << "Node with value " << key << " not found." << endl;
    }

    return 0;
}
