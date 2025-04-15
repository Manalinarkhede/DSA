#include<iostream>
#include<stack>
#include<string>
using namespace std;
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char c) {
        data=c;
        left=right=nullptr;
    }
};

bool isOperator(char c) {
    return (c =='+' || c =='-' || c =='*' || c == '/');
}

Node* ExpTree (const string& prefix) {
    stack<Node*>s;
    for(int i=prefix.length()-1; i>=0; i--) { //traverse R to L
        char ch=prefix[i];
        Node* newNode = new Node(ch);

        if(isaplha(ch)){
            s.push(newNode); //push operand till operator
        } else if (isOperator(ch)) {
            newNode->left = s.top(); //operand1 + operand2 + operator 
            s.pop();
            newNode-> right = s.top();
            s.pop();
            s.push(newNode); //push again into stack after applying formula
        }
    }
    return s.top(); //final root
}

void postorder(Node* root) {
    if(root == nullptr) return;
    stack<Node*>s;
    stack<char>result;
    s.push(root);

    while(!s.empty()) {
        Node* curr = s.top();
        s.pop();
        result.push(curr->data);

        if(curr->left) {
            s.push(curr->left);
        }
        if(curr->right) {
            s.push(curr->right);
        }
    }

    while (!result.empty()) {
        cout<<result.top()<<" ";
        result.pop();
    }
    cout<<endl;
}

void deleteNode(Node* root) {
    if(root == nullptr) return;

    stack<Node*>s;
    s.push(root);

    while(!s.empty()) {
        Node* t=s.top();
        s.pop();

        if(t->left){
            s.push(t->left);
        }
        if(t->right){
            s.push(t->right);
        }
        delete t;
    }
}
int main() {
    Node* root = nullptr;
    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Postorder Traversal\n";
        cout << "2. Delete Expression Tree\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string prefix;
            cout << "Enter prefix expression: ";
            cin >> prefix;
            root = ExpTree(prefix);
            cout << "Postorder Traversal: ";
            postorder(root);
            break;
        }
        case 2: {
            deleteNode(root);
            root = nullptr;
            cout << "Deleted nodes successfully." << endl;
            break;
        }
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 3);

    return 0;
}
