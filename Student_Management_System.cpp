#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Student
{
public:
    int rollNo;
    char name[50];
    float marks;

    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nMarks       : " << marks;
        cout << "\n--------------------------";
    }
};

void addStudent()
{
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();

    file.write((char*)&s, sizeof(s));

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n===== Student Records =====\n";

    while (file.read((char*)&s, sizeof(s)))
    {
        s.display();
    }

    file.close();
}

void searchStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}

void updateStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            cout << "\nEnter New Details:\n";
            s.input();

            int pos = file.tellg();

            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            found = true;

            cout << "\nRecord Updated Successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}


void deleteStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            found = true;
        }
        else
        {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}