#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <optional>

using namespace std;

class Student;

// Function declarations
void project();
void addData();
void displayData();
std::optional<Student> deleteData();
void getTrash();

// Student class
class Student {
private:
    int admissionNo;
    string sname;
    char sgender;
    int std;
    float smarks;
    double spercentage;

public:
//Default constructiors:
    Student() : admissionNo(0), sname(""), sgender(' '), std(0), smarks(0.0f), spercentage(0.0) {}
    void getData();
    void showData();
    int getAdmno() {
        return admissionNo;
    }


    string getSname() const { return sname; }
    char getSgender() const { return sgender; }
    int getStd() const { return std; }
    float getSmarks() const { return smarks; }
    double getSpercentage() const { return spercentage; }

    // Setter functions
    void setAdmno(int no) { admissionNo = no; }
    void setSname(const string& name) { sname = name; }
    void setSgender(char gender) { sgender = gender; }
    void setStd(int std) { this->std = std; }
    void setSmarks(float marks) { smarks = marks; }
    void setSpercentage(double percentage) { spercentage = percentage; }
};
// Main function
int main() {
    project(); // Function call
    return 0;
}

void clearConsole() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}
void pauseProgram() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Project function declaration
void project() {
    int ch;
    do {
        system("cls"); // Clear screen
        cout << "************** STUDENT MANAGEMENT SYSTEM ***************\n";
        cout << "1. Write Student Record\n";
        cout << "2. Read Student Record\n";
        cout << "3. Delete Student Record\n";
        cout << "4. Get Deleted Records\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        system("cls");
        switch (ch) {
        case 1:
            addData(); // Add student data to file (Student.txt)
            break;
        case 2:
            displayData(); // Read data from file (Student.txt)
            break;
        case 3: {
            auto deletedStudent = deleteData(); // Remove data from (Student.txt) and store in Trash.txt
            if (deletedStudent.has_value()) {
                cout << "This Record " << deletedStudent->getAdmno() << " has been sent to Trash:\n";
                deletedStudent->showData();
            }
            else {
                cout << "No Record found\n\n";
            }
            break;
        }
        case 4:
            getTrash(); // Add data from Trash.txt to Stu.txt
            break;
        }
        system("pause");
    } while (ch);
}

// Member function definitions for Student class
void Student::getData() {
    cout << "\n\n******* Enter Student Data *******\n";
    cout << "Admission No.: "; cin >> admissionNo;
    cout << "Full Name: "; cin.ignore(); getline(cin, sname);
    cout << "Gender (M/F): "; cin >> sgender;
    cout << "Class: "; cin >> std;
    cout << "Total Marks (/500): "; cin >> smarks;
    cout << endl;
    spercentage = (smarks / 500.0) * 100.0;
}

void Student::showData() {
    cout << "\n\n******* Student Details *******\n";
    cout << "Admission No.: " << admissionNo << endl;
    cout << "Full Name: " << sname << endl;
    cout << "Gender: " << sgender << endl;
    cout << "Class: " << std << endl;
    cout << "Total Marks (/500): " << smarks << endl;
    cout << "Percentage: " << spercentage << endl;
    cout << endl;
}

// Function definitions
void addData() {
    ofstream fout("Student.txt", ios::out | ios::app); // Output stream
    Student s; // Object of class Student
    s.getData(); // Get data from console
    fout << s.getAdmno() << '\n'
        << s.getSname() << '\n'
        << s.getSgender() << '\n'
        << s.getStd() << '\n'
        << s.getSmarks() << '\n'
        << s.getSpercentage() << '\n';
    fout.close(); // Close the file
    cout << "\n\n******* Data Successfully Saved to File *******\n";
}

std::optional<Student> readStudent(std::ifstream& fin) {
    Student s;
    string name;
    int admissionNo, std;
    char gender;
    float marks;
    double percentage;

    if (fin >> admissionNo
        && getline(fin, name)
        && getline(fin, name)
        && fin >> gender
        && fin >> std
        && fin >> marks
        && fin >> percentage) {
        s.setAdmno(admissionNo);
        s.setSname(name);
        s.setSgender(gender);
        s.setStd(std);
        s.setSmarks(marks);
        s.setSpercentage(percentage);
        return s;
    }

    return std::nullopt;
}

void displayData() {
    ifstream fin("Student.txt"); // Input stream
    if (!fin) {
        std::cerr << "Unable to open file.\n";
        return;
    }

    while (auto student = readStudent(fin)) {
        student->showData(); // Display data on console
    }

    fin.close(); // Close the file
    cout << "\n\n****** Data Reading from File Successfully Done *****\n";
    }

std::optional<Student> deleteData() {
    int n;
    ifstream fin("Student.txt"); // Input stream
    ofstream fout("Temp.txt", ios::out | ios::app); // Output stream
    ofstream tout("Trash.txt", ios::out | ios::app); // Output stream

    cout << "Enter Admission Number : ";
    cin >> n;

    Student s; // Object of class Student
    optional<Student> deletedStudent;
    string name;
    int admissionNo, std;
    char gender;
    float marks;
    double percentage;

    while (fin >> admissionNo) {
        getline(fin, name); // Consume newline character
        getline(fin, name); // Read the actual name
        fin >> gender
            >> std
            >> marks
            >> percentage; // Read the file (Student.txt)
        s.setAdmno(admissionNo);
        s.setSname(name);
        s.setSgender(gender);
        s.setStd(std);
        s.setSmarks(marks);
        s.setSpercentage(percentage);
        if (n == s.getAdmno()) {
            tout << s.getAdmno() << '\n'
                << s.getSname() << '\n'
                << s.getSgender() << '\n'
                << s.getStd() << '\n'
                << s.getSmarks() << '\n'
                << s.getSpercentage() << '\n'; // Write data to Trash.txt
            deletedStudent = s;
        }
        else {
            fout << s.getAdmno() << '\n'
                << s.getSname() << '\n'
                << s.getSgender() << '\n'
                << s.getStd() << '\n'
                << s.getSmarks() << '\n'
                << s.getSpercentage() << '\n'; // Write data to Temp.txt
        }
    }

    fout.close();
    tout.close();
    fin.close();

    filesystem::remove("Student.txt"); // Delete Student.txt
    filesystem::rename("Temp.txt", "Student.txt"); // Rename Temp.txt to Student.txt

    return deletedStudent;
}

void getTrash() {
    ifstream fin("Trash.txt"); // Input stream
    Student s; // Object of class Student
    string name;
    int admissionNo, std;
    char gender;
    float marks;
    double percentage;

    while (fin >> admissionNo) {
        getline(fin, name); // Consume newline character
        getline(fin, name); // Read the actual name
        fin >> gender
            >> std
            >> marks
            >> percentage; // Read data from file
        s.setAdmno(admissionNo);
        s.setSname(name);
        s.setSgender(gender);
        s.setStd(std);
        s.setSmarks(marks);
        s.setSpercentage(percentage);
        s.showData(); // Display data on console
    }
    fin.close(); // Close file
    cout << "\n\n******* Data Reading from Trash File Successfully Done *****\n";
}