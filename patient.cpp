#include<iostream>
#include<queue>
#include<string>
using namespace std;

struct Patient {
    string name;
    int priority;

    Patient(string name, int priority) : name(name), priority(priority) {}
};

auto compare=[] (Patient &P1, Patient &P2) {
    return P1.priority>P2.priority;
};

int main() {
    priority_queue<Patient, vector<Patient>, decltype(compare)>PQ(compare);
    int n;
    cout<<"Enter the number of patients: ";
    cin>>n;
    for(int i=0; i<n; i++) {
        string name;
        int p;
        cout<<"Enter the name of Patient:" ;
        cin>>name;
        cout<<"Enter the priority of the patient (1 for serious, 2 for non-serious, 3 for general checkup): ";
        cin>>p;
        PQ.emplace(name, p);
    }
    cout<<"List of Patients:"<<endl;
    while(!PQ.empty()) {
        Patient P=PQ.top();
        if (P.priority == 1) {
            cout << "Serious patient, Name: " << P.name << endl;
        } else if (P.priority == 2) {
            cout << "Non-Serious patient, Name: " << P.name << endl;
        } else if (P.priority == 3) {
            cout << "General patient, Name: " << P.name << endl;
        }
        PQ.pop();
    }
    return 0;
}