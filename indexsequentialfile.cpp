#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Employee {
    int emp_id;
    char name[10];
    int salary;

public:
    void input();
    void display();
    int getID();
    void markDeleted();
    bool isDeleted();

    friend fstream& operator<<(fstream& out, Employee& e);
    friend fstream& operator>>(fstream& in, Employee& e);
};

void Employee::input() {
    cout << "Enter Emp_ID: "; cin >> emp_id;
    cout << "Enter Name: "; cin >> name;
    cout << "Enter Salary: "; cin >> salary;
}

void Employee::display() {
    if (emp_id != -1)
        cout << "\nEmp_ID: " << emp_id << "\tName: " << name << "\tSalary: " << salary;
}

int Employee::getID() { return emp_id; }

void Employee::markDeleted() { emp_id = -1; }

bool Employee::isDeleted() { return emp_id == -1; }

fstream& operator<<(fstream& out, Employee& e) {
    out.write((char*)&e, sizeof(e));
    return out;
}

fstream& operator>>(fstream& in, Employee& e) {
    in.read((char*)&e, sizeof(e));
    return in;
}

void create() {
    fstream file("EMP.dat", ios::out | ios::binary);
    Employee e;
    char ch;
    do {
        e.input();
        file << e;
        cout << "Add more? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    file.close();
}

void display() {
    fstream file("EMP.dat", ios::in | ios::binary);
    Employee e;
    cout << "\nEmployee Records:";
    while (file >> e) {
        e.display();
    }
    file.close();
}

void search() {
    int id; bool found = false;
    cout << "Enter Emp_ID to search: "; cin >> id;
    fstream file("EMP.dat", ios::in | ios::binary);
    Employee e;
    while (file >> e) {
        if (e.getID() == id && !e.isDeleted()) {
            cout << "\nRecord Found:"; e.display();
            found = true; break;
        }
    }
    if (!found) cout << "\nRecord Not Found";
    file.close();
}

void append() {
    fstream file("EMP.dat", ios::app | ios::binary);
    Employee e;
    e.input();
    file << e;
    file.close();
}

void update() {
    int id; bool found = false;
    cout << "Enter Emp_ID to update: "; cin >> id;
    fstream file("EMP.dat", ios::in | ios::out | ios::binary);
    Employee e;
    while (!file.eof()) {
        int pos = file.tellg();
        file >> e;
        if (e.getID() == id && !e.isDeleted()) {
            cout << "\nEnter new details:\n";
            e.input();
            file.seekp(pos);
            file << e;
            found = true; break;
        }
    }
    if (!found) cout << "\nRecord Not Found";
    file.close();
}

void remove() {
    int id; bool found = false;
    cout << "Enter Emp_ID to delete: "; cin >> id;
    fstream file("EMP.dat", ios::in | ios::out | ios::binary);
    Employee e;
    while (!file.eof()) {
        int pos = file.tellg();
        file >> e;
        if (e.getID() == id && !e.isDeleted()) {
            e.markDeleted();
            file.seekp(pos);
            file << e;
            found = true; break;
        }
    }
    if (!found) cout << "\nRecord Not Found";
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n\n1. Create\n2. Display\n3. Update\n4. Delete\n5. Append\n6. Search\n7. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: create(); break;
            case 2: display(); break;
            case 3: update(); break;
            case 4: remove(); break;
            case 5: append(); break;
            case 6: search(); break;
            case 7: cout << "Exiting..."; break;
            default: cout << "Invalid choice!";
        }
    } while (choice != 7);
    return 0;
}
