#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Employee {
    int Employee_ID;
    int salary;
    string name;
    string designation;

    void writedata(ofstream &out) {
        out << Employee_ID << endl;
        out << name << endl;
        out << designation << endl;
        out << salary << endl;
    }

    void readdata(ifstream &in) {
        in >> Employee_ID;
        in.ignore();
        getline(in, name);
        getline(in, designation);
        in >> salary;
    }
};

void add() {
    ofstream out("employee.dat", ios::app);
    if (!out) {
        cout << "Error! Can't open the file." << endl;
        return;
    }

    Employee e;
    cout << "Enter the Employee ID: ";
    cin >> e.Employee_ID;
    cin.ignore();  

    cout << "Enter the Employee Name: ";
    getline(cin, e.name);

    cout << "Enter the Employee Designation: ";
    getline(cin, e.designation);

    cout << "Enter the Employee Salary: ";
    cin >> e.salary;

    e.writedata(out);
    out.close();
    cout << "Employee data added successfully." << endl;
}

void deleteEmployee() {
    int del_ID;
    cout << "Enter the Employee ID whose data is to be deleted: ";
    cin >> del_ID;

    ifstream in("employee.dat");
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    ofstream out("temp.dat");
    if (!out) {
        cout << "Error! Can't create the temporary file." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);
        if (!in) break;

        if (e.Employee_ID == del_ID) {
            found = true;
            cout << "Employee with ID " << del_ID << " deleted." << endl;
            continue;  
        }

        e.writedata(out);
    }

    in.close();
    out.close();

    if (found) {
        remove("employee.dat");
        rename("temp.dat", "employee.dat");
        cout << "Employee data has been successfully deleted." << endl;
    } else {
        cout << "No employee found with ID " << del_ID << endl;
        remove("temp.dat");
    }
}

void display() {
    int display_ID;
    cout << "Enter the Employee ID to display: ";
    cin >> display_ID;

    ifstream in("employee.dat");
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);
        if (!in) break;

        if (e.Employee_ID == display_ID) {
            cout << "Employee Found:" << endl;
            cout << "Employee ID: " << e.Employee_ID << endl;
            cout << "Name: " << e.name << endl;
            cout << "Designation: " << e.designation << endl;
            cout << "Salary: " << e.salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << display_ID << " not found." << endl;
    }

    in.close();
}

void updateEmployee() {
    int update_ID;
    cout << "Enter the Employee ID whose data is to be updated: ";
    cin >> update_ID;

    ifstream in("employee.dat");
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    ofstream out("temp.dat");
    if (!out) {
        cout << "Error! Can't create the temporary file." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);
        if (!in) break;

        if (e.Employee_ID == update_ID) {
            found = true;           

            cin.ignore();
            cout << "Enter new Name: ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                e.name = newName;
            } 
            cout << "Enter new Designation : ";
            string newDesignation;
            getline(cin, newDesignation);
            if (!newDesignation.empty()) {
                e.designation = newDesignation;
            }

            cout << "Enter new Salary : ";
            int newSalary;
            cin >> newSalary;
            e.salary = newSalary;

            cout << "Employee data updated." << endl;
        }

        e.writedata(out);
    }

    in.close();
    out.close();

    if (found) {
        remove("employee.dat");
        rename("temp.dat", "employee.dat");
        cout << "Employee data has been successfully updated." << endl;
    } else {
        cout << "No employee found with ID " << update_ID << endl;
        remove("temp.dat");
    }
}

int main() {
    int choice = 0;

    do {
        cout << "Menu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee Information\n";
        cout << "4. Update Employee Information\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                add();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                display();
                break;
            case 4:
                updateEmployee();  
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }

    } while (choice != 5);

    return 0;
}
