#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

class node {
public:
    string word, meaning;
    int ht;
    node* left, * right;
};

class AVL {
public:
    node* root;
    AVL() { root = NULL; }

    int height(node* temp) {
        if (temp == NULL)
            return 0;
        return 1 + max(height(temp->left), height(temp->right));
    }

    int BF(node* temp) {
        if (temp == NULL)
            return 0;
        return height(temp->left) - height(temp->right);
    }

    node* RotateRight(node* parent) {
        node* temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        parent->ht = height(parent);
        temp->ht = height(temp);
        return temp;
    }

    node* RotateLeft(node* parent) {
        node* temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        parent->ht = height(parent);
        temp->ht = height(temp);
        return temp;
    }

    node* RR(node* T) {
        return RotateLeft(T);
    }

    node* LL(node* T) {
        return RotateRight(T);
    }

    node* LR(node* T) {
        T->left = RotateLeft(T->left);
        return RotateRight(T);
    }

    node* RL(node* T) {
        T->right = RotateRight(T->right);
        return RotateLeft(T);
    }

    node* insert(node* temp, string str_w, string str_m) {
        if (temp == NULL) {
            temp = new node;
            temp->word = str_w;
            temp->meaning = str_m;
            temp->left = temp->right = NULL;
        } else {
            if (str_w.compare(temp->word) > 0) {
                temp->right = insert(temp->right, str_w, str_m);
                if (BF(temp) == -2) {
                    if (temp->right && str_w.compare(temp->right->word) > 0)
                        temp = RR(temp);
                    else
                        temp = RL(temp);
                }
            } else {
                temp->left = insert(temp->left, str_w, str_m);
                if (BF(temp) == 2) {
                    if (temp->left && str_w.compare(temp->left->word) < 0)
                        temp = LL(temp);
                    else
                        temp = LR(temp);
                }
            }
        }
        temp->ht = height(temp);
        return temp;
    }

    node* findMin(node* root) {
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    node* deleteNode(node* root, string str_w) {
        if (root == NULL)
            return NULL;

        if (str_w < root->word)
            root->left = deleteNode(root->left, str_w);
        else if (str_w > root->word)
            root->right = deleteNode(root->right, str_w);
        else {
            if (root->left == NULL) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                node* temp = root->left;
                delete root;
                return temp;
            } else {
                node* temp = findMin(root->right);
                root->word = temp->word;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->word);
            }
        }
        root->ht = height(root);
        return root;
    }

    void preorder(node* root) {
        if (root != NULL) {
            cout << root->word << " : " << root->meaning << " (Bf=" << BF(root) << ")\n";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void inorder(node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->word << " : " << root->meaning << " (Bf=" << BF(root) << ")\n";
            inorder(root->right);
        }
    }

    void search(node* root, string str_w) {
        if (root == NULL) {
            cout << "Word not found" << endl;
            return;
        }

        if (str_w.compare(root->word) < 0)
            search(root->left, str_w);
        else if (str_w.compare(root->word) > 0)
            search(root->right, str_w);
        else {
            cout << "Word: " << root->word << "\nMeaning: " << root->meaning << endl;
        }
    }

    void modify(node* root, string str_w) {
        if (root == NULL) {
            cout << "Word not found" << endl;
            return;
        }
        if (str_w.compare(root->word) < 0)
            modify(root->left, str_w);
        else if (str_w.compare(root->word) > 0)
            modify(root->right, str_w);
        else {
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, root->meaning);
        }
    }
};

int main() {
    AVL Tree;
    int ch;
    string str1, str2;

    cout << "\tOPERATIONS ON AVL TREE\t" << endl;

    while (true) {
        cout << "\n1. Create tree\n2. Add word\n3. Display tree\n4. Delete word\n5. Search word\n6. Modify meaning\n7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1:
            case 2:
                cout << "Enter word: ";
                cin >> str1;
                cin.ignore();
                cout << "Enter meaning: ";
                getline(cin, str2);
                Tree.root = Tree.insert(Tree.root, str1, str2);
                break;

            case 3:
                cout << "\nPreorder:\n";
                Tree.preorder(Tree.root);
                cout << "\nInorder:\n";
                Tree.inorder(Tree.root);
                break;

            case 4:
                cout << "Enter word to delete: ";
                cin >> str1;
                Tree.root = Tree.deleteNode(Tree.root, str1);
                break;

            case 5:
                cout << "Enter word to search: ";
                cin >> str1;
                Tree.search(Tree.root, str1);
                break;

            case 6:
                cout << "Enter word to modify: ";
                cin >> str1;
                Tree.modify(Tree.root, str1);
                break;

            case 7:
                exit(0);

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
