#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student {
    int rollno;
    string name;
    char div;
    string address;

    void writedata(ofstream &out) {
        out<<rollno<<endl;
        out<<name<<endl;
        out<<div<<endl;
        out<<address<<endl;
    }
    void readdata(ifstream &in) {
        in>>rollno;
        in.ignore();
        getline(in,name);
        in>>div;
        in.ignore();
        getline(in, address);
    }
};

void add(){
    ofstream out("student.dat", ios::app);
    if(!out){
        cout<<"Error ! cannot open the file."<<endl;
        return;
    }
    Student s;
    cout << "Enter the roll number of the student: ";
    cin >> s.rollno;
    cin.ignore();
    cout << "Enter the name of the student: ";
    getline(cin, s.name);
    cout << "Enter the division of the student: ";
    cin >> s.div;
    cin.ignore();
    cout << "Enter the address of the student: ";
    getline(cin, s.address);
    
    s.writedata(out);
    out.close();
    cout<<"Student data added successfully"<<endl;
}
void display() {
    int displayRoll;
    cout<<"Enter the roll no of the student to display.";
    cin>>displayRoll;

    ifstream in("student.dat");
    Student s;
    bool found=false;

    while(in>>s.rollno) {
        in.ignore();
        getline(in, s.name);
        in>>s.div;
        in.ignore();
        getline(in, s.address);
        
        if(s.rollno == displayRoll) {
            cout<<"Student details:"<<endl;
            cout<<"Roll no:" << s.rollno <<endl;
            cout <<"Name: " << s.name << endl;
            cout <<"Division: " << s.div << endl;
            cout <<"Address: " << s.address << endl;
            found= true;
            break;
        }
    }
    if(!found) {
        cout<<"Student with roll no "<<displayRoll<<"not found!"<<endl;
    }
    in.close();
}

void deleteStudent() {
    int delRoll;
    cout<<"Enter the roll no of the student to delete."<<endl;
    cin>>delRoll;

    ifstream in("student.dat");
    ofstream out("temp.dat");
    Student s;
    bool found=false;

    while(in>>s.rollno) {
        in.ignore();
        getline(in,s.name);
        in>>s.div;
        in.ignore();
        getline(in, s.address);

        if(s.rollno== delRoll) {
            found=true;
            continue;
        }
        s.writedata(out);
    }
    in.close();
    out.close();

    if(found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout<<"Student record deleted successfully."<<endl;
    }else{
        cout<<"No student found with roll number "<<delRoll<<endl;
    }
}

int main() {
    int choice;

    do {
        cout << "Menu\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: deleteStudent(); break;
            case 3: display(); break;
            case 4: cout << "Exiting program.\n"; break;
            default: cout <<"Invalid choice. Try again.\n"; break;
        }

    } while (choice != 4);

    return 0;
}
