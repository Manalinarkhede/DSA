#include <iostream>
using namespace std;

class hash_table {
    int HT1[10], HT2[10]; // HT1 -> Linear , HT2 -> Quadratic
    int size = 10;

public:
    hash_table() {
        for (int i = 0; i < size; i++) {
            HT1[i] = -1;
            HT2[i] = -1;
        }
    }

    void insert_linearProbing();
    void search_linearProbing();
    void delete_linearProbing();
    void insert_quadraticProbing();
    void search_quadraticProbing();
    void delete_quadraticProbing();
    void display();
};

void hash_table::insert_linearProbing() {
    int value, address, count = 0;
    cout << "Enter the data to add in hash table (Linear Probing): ";
    cin >> value;
    address = value % size;

    while (HT1[address] != -1 && count < size) {
        address = (address + 1) % size;
        count++;
    }

    if (count == size) {
        cout << "Hash table is full! Cannot insert " << value << endl;
    } else {
        HT1[address] = value;
        cout << "Inserted " << value << " at index " << address << endl;
    }
}

void hash_table::search_linearProbing() {
    int value, address, count = 0;
    cout << "Enter the number to search in Linear Probing: ";
    cin >> value;
    address = value % size;

    while (HT1[address] != value && HT1[address] != -1 && count < size) {
        address = (address + 1) % size;
        count++;
    }

    if (HT1[address] == value) {
        cout << "Found " << value << " at index " << address << " with " << count + 1 << " comparisons.\n";
    } else {
        cout << "Number not found!\n";
    }
}

void hash_table::delete_linearProbing() {
    int value, address, count = 0;
    cout << "Enter the number to delete from Linear Probing: ";
    cin >> value;
    address = value % size;

    while (HT1[address] != value && HT1[address] != -1 && count < size) {
        address = (address + 1) % size;
        count++;
    }

    if (HT1[address] == value) {
        HT1[address] = -1;
        cout << "Deleted " << value << " from index " << address << endl;
    } else {
        cout << "Number not found!\n";
    }
}

void hash_table::insert_quadraticProbing() {
    int value, address, i = 0;
    cout << "Enter the data to add in hash table (Quadratic Probing): ";
    cin >> value;
    address = value % size;

    while (HT2[(address + i * i) % size] != -1 && i < size) {
        i++;
    }

    if (i == size) {
        cout << "Hash table is full! Cannot insert " << value << endl;
    } else {
        HT2[(address + i * i) % size] = value;
        cout << "Inserted " << value << " at index " << (address + i * i) % size << endl;
    }
}

void hash_table::search_quadraticProbing() {
    int value, address, i = 0, comparisons = 0;
    cout << "Enter the number to search in Quadratic Probing: ";
    cin >> value;
    address = value % size;

    while (HT2[(address + i * i) % size] != value && HT2[(address + i * i) % size] != -1 && i < size) {
        i++;
        comparisons++;
    }

    if (HT2[(address + i * i) % size] == value) {
        cout << "Found " << value << " at index " << (address + i * i) % size << " with " << comparisons + 1 << " comparisons.\n";
    } else {
        cout << "Number not found!\n";
    }
}

void hash_table::delete_quadraticProbing() {
    int value, address, i = 0;
    cout << "Enter the number to delete from Quadratic Probing: ";
    cin >> value;
    address = value % size;

    while (HT2[(address + i * i) % size] != value && HT2[(address + i * i) % size] != -1 && i < size) {
        i++;
    }

    if (HT2[(address + i * i) % size] == value) {
        HT2[(address + i * i) % size] = -1;
        cout << "Deleted " << value << " from index " << (address + i * i) % size << endl;
    } else {
        cout << "Number not found!\n";
    }
}

void hash_table::display() {
    cout << "\nHash Table (Linear Probing):\n";
    for (int i = 0; i < size; i++) {
        cout << i << " -> " << (HT1[i] == -1 ? "empty" : to_string(HT1[i])) << endl;
    }

    cout << "\nHash Table (Quadratic Probing):\n";
    for (int i = 0; i < size; i++) {
        cout << i << " -> " << (HT2[i] == -1 ? "empty" : to_string(HT2[i])) << endl;
    }
}

int main() {
    hash_table obj;
    int ch;

    do {
        cout << "\n___MENU___" << endl;
        cout << "1. Insert data using Linear Probing" << endl;
        cout << "2. Search data using Linear Probing" << endl;
        cout << "3. Delete data using Linear Probing" << endl;
        cout << "4. Insert data using Quadratic Probing" << endl;
        cout << "5. Search data using Quadratic Probing" << endl;
        cout << "6. Delete data using Quadratic Probing" << endl;
        cout << "7. Display both hash tables" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: obj.insert_linearProbing(); break;
            case 2: obj.search_linearProbing(); break;
            case 3: obj.delete_linearProbing(); break;
            case 4: obj.insert_quadraticProbing(); break;
            case 5: obj.search_quadraticProbing(); break;
            case 6: obj.delete_quadraticProbing(); break;
            case 7: obj.display(); break;
            case 8: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (ch != 8);

    return 0;
}

//OUTPUT:
__MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 1
Enter the data to add in hash table (Linear Probing): 32
Inserted 32 at index 2

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing

5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 1
Enter the data to add in hash table (Linear Probing): 45
Inserted 45 at index 5

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 4
Enter the data to add in hash table (Quadratic Probing): 78
Inserted 78 at index 8

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 1

Enter the data to add in hash table (Linear Probing): 12
Inserted 12 at index 3

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 2
Enter the number to search in Linear Probing: 45
Found 45 at index 5 with 1 comparisons.

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 5
Enter the number to search in Quadratic Probing: 78
Found 78 at index 8 with 1 comparisons.

___MENU___
1. Insert data using Linear Probing

2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 3
Enter the number to delete from Linear Probing: 12
Deleted 12 from index 3

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 7

Hash Table (Linear Probing):
0 -> empty
1 -> empty
2 -> 32
3 -> empty
4 -> empty
5 -> 45
6 -> empty
7 -> empty

8 -> empty
9 -> empty

Hash Table (Quadratic Probing):
0 -> empty
1 -> empty
2 -> empty
3 -> empty
4 -> empty
5 -> empty
6 -> empty
7 -> empty
8 -> 78
9 -> empty

___MENU___
1. Insert data using Linear Probing
2. Search data using Linear Probing
3. Delete data using Linear Probing
4. Insert data using Quadratic Probing
5. Search data using Quadratic Probing
6. Delete data using Quadratic Probing
7. Display both hash tables
8. Exit
Enter your choice: 8
Exiting program.

...Program finished with exit code 0
Press ENTER to exit console.
