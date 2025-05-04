#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Employee {
    int Employee_ID;
    int salary;
    string name;
    string designation;

    void writeData(ofstream &out) {
        out << Employee_ID << endl;
        out << name << endl;
        out << designation << endl;
        out << salary << endl;
    }

    void readData(ifstream &in) {
        in >> Employee_ID;
        in.ignore();
        getline(in, name);
        getline(in, designation);
        in >> salary;
    }
};

struct Index {
    int Employee_ID;
    long pos;
};

void addEmployee() {
    ofstream dataFile("employee.dat", ios::app);
    ofstream indexFile("index.dat", ios::app | ios::binary);
    if (!dataFile || !indexFile) {
        cout << "Error opening files.\n";
        return;
    }

    Employee e;
    cout << "Enter Employee ID: ";
    cin >> e.Employee_ID;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, e.name);
    cout << "Enter Designation: ";
    getline(cin, e.designation);
    cout << "Enter Salary: ";
    cin >> e.salary;

    long pos = dataFile.tellp();  // Get current position in file
    e.writeData(dataFile);

    Index idx{e.Employee_ID, pos};
    indexFile.write((char*)&idx, sizeof(Index));

    cout << "Employee added successfully.\n";

    dataFile.close();
    indexFile.close();
}

void displayEmployee() {
    int id;
    cout << "Enter Employee ID to display: ";
    cin >> id;

    ifstream indexFile("index.dat", ios::binary);
    ifstream dataFile("employee.dat");
    if (!indexFile || !dataFile) {
        cout << "Error opening files.\n";
        return;
    }

    Index idx;
    bool found = false;
    while (indexFile.read((char*)&idx, sizeof(Index))) {
        if (idx.Employee_ID == id) {
            dataFile.seekg(idx.pos);
            Employee e;
            e.readData(dataFile);
            cout << "Employee Found:\n";
            cout << "ID: " << e.Employee_ID << "\nName: " << e.name 
                 << "\nDesignation: " << e.designation 
                 << "\nSalary: " << e.salary << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Employee not found.\n";

    indexFile.close();
    dataFile.close();
}

void updateEmployee() {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;

    fstream dataFile("employee.dat", ios::in | ios::out);
    fstream indexFile("index.dat", ios::in | ios::out | ios::binary);
    if (!dataFile || !indexFile) {
        cout << "Error opening files.\n";
        return;
    }

    Index idx;
    bool found = false;

    while (indexFile.read((char*)&idx, sizeof(Index))) {
        if (idx.Employee_ID == id) {
            dataFile.seekp(idx.pos);

            Employee e;
            e.Employee_ID = id;
            cin.ignore();
            cout << "Enter new Name: ";
            getline(cin, e.name);
            cout << "Enter new Designation: ";
            getline(cin, e.designation);
            cout << "Enter new Salary: ";
            cin >> e.salary;

            dataFile.seekp(idx.pos);
            e.writeData(dataFile);
            cout << "Employee updated.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Employee not found.\n";

    dataFile.close();
    indexFile.close();
}

void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    ifstream indexIn("index.dat", ios::binary);
    ofstream indexOut("temp_index.dat", ios::binary);
    ifstream dataIn("employee.dat");
    ofstream dataOut("temp_employee.dat");
    if (!indexIn || !indexOut || !dataIn || !dataOut) {
        cout << "Error opening files.\n";
        return;
    }

    Index idx;
    Employee e;
    bool found = false;

    while (indexIn.read((char*)&idx, sizeof(Index))) {
        dataIn.seekg(idx.pos);
        e.readData(dataIn);

        if (e.Employee_ID == id) {
            found = true;
            continue;  // skip writing to temp files
        }

        long newPos = dataOut.tellp();
        e.writeData(dataOut);

        Index newIdx{e.Employee_ID, newPos};
        indexOut.write((char*)&newIdx, sizeof(Index));
    }

    indexIn.close();
    indexOut.close();
    dataIn.close();
    dataOut.close();

    if (found) {
        remove("employee.dat");
        rename("temp_employee.dat", "employee.dat");

        remove("index.dat");
        rename("temp_index.dat", "index.dat");

        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee not found.\n";
        remove("temp_employee.dat");
        remove("temp_index.dat");
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
