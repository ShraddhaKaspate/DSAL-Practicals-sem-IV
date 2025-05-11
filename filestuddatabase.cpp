#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
    int roll;
    char name[10];
    char div;
    char add[10];

public:
    void create();
    void display();
    void search();
    void deleteRecord();
};

void Student::create() {
    char ans;
    Student s;
    ofstream fout("stud.dat", ios::binary | ios::app); // append mode
    do {
        cout << "Enter Roll No: ";
        cin >> s.roll;
        cout << "Enter Name: ";
        cin >> s.name;
        cout << "Enter Division: ";
        cin >> s.div;
        cout << "Enter Address: ";
        cin >> s.add;

        fout.write((char*)&s, sizeof(s));

        cout << "Add another record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    fout.close();
}

void Student::display() {
    Student s;
    ifstream fin("stud.dat", ios::binary);
    cout << "\nRoll\tName\tDiv\tAddress\n";
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.roll != -1) {
            cout << s.roll << "\t" << s.name << "\t" << s.div << "\t" << s.add << "\n";
        }
    }
    fin.close();
}

void Student::search() {
    int r;
    Student s;
    ifstream fin("stud.dat", ios::binary);
    cout << "Enter Roll No to search: ";
    cin >> r;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.roll == r) {
            cout << "\nRecord Found:\n";
            cout << s.roll << "\t" << s.name << "\t" << s.div << "\t" << s.add << "\n";
            fin.close();
            return;
        }
    }
    cout << "Record Not Found\n";
    fin.close();
}

void Student::deleteRecord() {
    int r;
    Student s;
    fstream file("stud.dat", ios::in | ios::out | ios::binary);
    cout << "Enter Roll No to delete: ";
    cin >> r;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll == r) {
            file.seekp(-sizeof(s), ios::cur);
            s.roll = -1;
            strcpy(s.name, "NULL");
            s.div = 'N';
            strcpy(s.add, "NULL");
            file.write((char*)&s, sizeof(s));
            cout << "Record Deleted\n";
            file.close();
            return;
        }
    }
    cout << "Record Not Found\n";
    file.close();
}

int main() {
    Student obj;
    int choice;

    do {
        cout << "\n1. Create\n2. Display\n3. Search\n4. Delete\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: obj.create(); break;
            case 2: obj.display(); break;
            case 3: obj.search(); break;

            case 4: obj.deleteRecord(); break;
        }
    } while (choice != 5);

    return 0;
}
