#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Course {
private:
    string courseName;
    string courseNumber;
    int creditHours;
    char grade;

public:
    Course();
    void setCourseInfo(string courseName = "", string courseNumber = "", int creditHours = 0, char grade = '\0');
    void printCourse() const;
    int getCreditHours() const;
    string getCourseNumber() const;
    string getCourseName() const;
    double gradeToGPA() const;
    char getGrade() const;
};

class PersonType {
protected:
    string firstName;
    string lastName;

public:
    PersonType(string firstName = "", string lastName = "");
    void setName(string firstName, string lastName);
    string getFirstName() const;
    string getLastName() const;
    void printName() const;
};

class StudentType : public PersonType {
private:
    string studentID;
    int numberOfCourses;
    bool isTuitionPaid;

public:
    vector<Course> coursesEnrolled;

    StudentType();

    void addCourse(const Course& course);
    void setStudent(string firstName, string lastName, string studentID, bool isTuitionPaid, int numberOfCourses);
    int getHoursEndrolled() const;
    double getGpa() const;
    double billingAmount(int tuitionPerCredit) const;
    void sortCourses();
    void print(ostream& outFile) const;
    void print(const string& studentID) const;
};

void readStudentDataFromFile(const string& filename, vector<StudentType>& students, int& tuitionPerCredit);

void printStudentsToFile(const vector<StudentType>& students, const string& filename);


int main() {
    vector<StudentType> students;
    int tuitionPerCredit;

    readStudentDataFromFile("input.txt", students, tuitionPerCredit);

    printStudentsToFile(students, "output.txt");

    bool control = true;
    int secim;

    do {
        cout << "---------------------------------------------" << endl;
        cout << "1. Kurs bilgilerinin düzenlenmesi." << endl;
        cout << "2. Kurs bilgilerinin yazdirilmasi." << endl;
        cout << "3. Kredi saatlerinin gösterilmesi." << endl;
        cout << "4. Kurs numarasinin gösterilmesi." << endl;
        cout << "5. Notun gösterilmesi." << endl;
        cout << "6. Öğrenci bilgilerinin ayarlanmasi." << endl;
        cout << "7. Öğrenci bilgilerinin yazdirilmasi." << endl;
        cout << "8. Alinan saat sayisinin hesaplanmasi." << endl;
        cout << "9. GPA'nin (Not Ortalamasi) hesaplanmasi." << endl;
        cout << "10. Fatura tutarinin hesaplanmasi." << endl;
        cout << "11. Dersleri ders numarasina göre siralanmasi." << endl;
        cout << "0. CIKIS" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Yapmak istediğiniz işlemi girin: ";
        cin >> secim;

        switch (secim) {
        case 0:
            control = false;
            break;
        case 1: {
            string courseName, courseNumber;
            int creditHours;
            char grade;
            cout << "Kurs ismini girin: ";
            cin >> courseName;
            cout << "Kurs numarasını girin: ";
            cin >> courseNumber;
            cout << "Kredi saatlerini girin: ";
            cin >> creditHours;
            cout << "Notu girin (A-F): ";
            cin >> grade;
            Course course;
            course.setCourseInfo(courseName, courseNumber, creditHours, grade);
            cout << "Kurs bilgileri başarıyla düzenlendi." << endl;
            break;
        }
        case 2:
            for (const auto& student : students) {
                for (const auto& course : student.coursesEnrolled) {
                    course.printCourse();
                }
            }
            break;
        case 3:
            for (const auto& student : students) {
                cout << "Toplam kredi saatleri: " << student.getHoursEndrolled() << endl;
            }
            break;
        case 4:
            for (const auto& student : students) {
                for (const auto& course : student.coursesEnrolled) {
                    cout << "Kurs numarası: " << course.getCourseNumber() << endl;
                }
            }
            break;
        case 5:
            for (const auto& student : students) {
                for (const auto& course : student.coursesEnrolled) {
                    cout << "Not: " << course.getGrade() << endl;
                }
            }
            break;
        case 6: {
            string firstName, lastName, studentID;
            bool isTuitionPaid;
            int numberOfCourses;
            cout << "Öğrencinin adını girin: ";
            cin >> firstName;
            cout << "Öğrencinin soyadını girin: ";
            cin >> lastName;
            cout << "Öğrenci ID'sini girin: ";
            cin >> studentID;
            cout << "Ödenen öğrenim harcı (1: Evet, 0: Hayır): ";
            cin >> isTuitionPaid;
            cout << "Kurs sayısını girin: ";
            cin >> numberOfCourses;
            StudentType student;
            student.setStudent(firstName, lastName, studentID, isTuitionPaid, numberOfCourses);
            students.push_back(student);
            cout << "Öğrenci bilgileri başarıyla ayarlandı." << endl;
            break;
        }
        case 7:
            for (const auto& student : students) {
                student.print(cout);
            }
            break;
        case 8:
            for (const auto& student : students) {
                cout << "Alınan saat sayısı: " << student.getHoursEndrolled() << endl;
            }
            break;
        case 9:
            for (const auto& student : students) {
                cout << "GPA: " << student.getGpa() << endl;
            }
            break;
        case 10:
            for (const auto& student : students) {
                cout << "Fatura tutarı: " << student.billingAmount(tuitionPerCredit) << endl;
            }
            break;
        case 11:
            for (auto& student : students) {
                student.sortCourses();
            }
            cout << "Dersler başarıyla sıralandı." << endl;
            break;
        default:
            cout << "Geçersiz seçim! Lütfen tekrar deneyin." << endl;
            break;
        }

    } while (control);

    return 0;
}

Course::Course() {
    this->courseName = "";
    this->courseNumber = "";
    this->creditHours = 0;
    this->grade = 'F';
}

void Course::setCourseInfo(string courseName, string courseNumber, int creditHours, char grade) {
    this->courseName = courseName;
    this->courseNumber = courseNumber;
    this->creditHours = creditHours;
    this->grade = grade;
}

void Course::printCourse() const {
        cout << left << setw(10) << courseNumber << setw(15) << courseName << setw(8) << creditHours << grade << endl;
    }

int Course::getCreditHours() const {
    return creditHours;
}

string Course::getCourseNumber() const {
    return courseNumber;
}

string Course::getCourseName() const {
    return courseName;
}

double Course::gradeToGPA() const {
    switch (grade) {
    case 'A':
        return 4.0;
    case 'B':
        return 3.0;
    case 'C':
        return 2.0;
    case 'D':
        return 1.0;
    case 'E':
        return 0.5;
    case 'F':
        return 0.0;
    default:
        return 0.0;
    }
}

char Course::getGrade() const {
    return grade;
}

PersonType::PersonType(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

void PersonType::setName(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

string PersonType::getFirstName() const {
    return firstName;
}

string PersonType::getLastName() const {
    return lastName;
}

void PersonType::printName() const {
    cout << firstName << " " << lastName << endl;
}

StudentType::StudentType() {
    this->studentID = "";
    this->isTuitionPaid = false;
    this->numberOfCourses = 0;
}

void StudentType::addCourse(const Course& course) {
    coursesEnrolled.push_back(course);
}

void StudentType::setStudent(string firstName, string lastName, string studentID, bool isTuitionPaid, int numberOfCourses) {
    setName(firstName, lastName);
    this->studentID = studentID;
    this->isTuitionPaid = isTuitionPaid;
    this->numberOfCourses = numberOfCourses;
}

int StudentType::getHoursEndrolled() const {
    int totalHours = 0;
    for (Course myCourse : coursesEnrolled)
        totalHours += myCourse.getCreditHours();
    return totalHours;
}

double StudentType::getGpa() const {
    double totalPointOfCourses = 0;
    int totalCredits = 0;
    for (Course myCourse : coursesEnrolled) {
        totalPointOfCourses += myCourse.gradeToGPA() * myCourse.getCreditHours();
        totalCredits += myCourse.getCreditHours();
    }

    return totalPointOfCourses / totalCredits; // her öğrenci en az 1 ders aldığı için kredi sayısı 0 olamaz
}

double StudentType::billingAmount(int tuitionPerCredit) const {
    int totalCredits = 0;

    for (Course myCourse : coursesEnrolled)
        totalCredits += myCourse.getCreditHours();

    return totalCredits * tuitionPerCredit;
}

void StudentType::sortCourses() { // Kursları numaralarına göre sıralıyor bubble sort
    for (size_t i = 0; i < coursesEnrolled.size() - 1; i++) {
        for (size_t j = 0; j < coursesEnrolled.size() - i - 1; j++) {
            if (coursesEnrolled[j].getCourseNumber() > coursesEnrolled[j + 1].getCourseNumber()) {
                Course temp = coursesEnrolled[j];
                coursesEnrolled[j] = coursesEnrolled[j + 1];
                coursesEnrolled[j + 1] = temp;
            }
        }
    }
}

void StudentType::print(ostream& outFile) const {
    outFile << "Student Name: " << firstName << " " << lastName << endl;
    outFile << "Student ID: " << studentID << endl;
    outFile << "Number of courses enrolled: " << numberOfCourses << endl;
    outFile << "Course No   Course Name     Credits   Grade" << endl;
    for (const Course& course : coursesEnrolled) {
        outFile << left << setw(12) << course.getCourseNumber()
            << setw(15) << course.getCourseName()
            << setw(8) << course.getCreditHours()
            << setw(10) << course.getGrade() << endl;
    }
    outFile << "Total number of credits: " << getHoursEndrolled() << endl;
    outFile << "Mid-Semester GPA: " << fixed << setprecision(2) << getGpa() << endl;
}

void StudentType::print(const string& studentID) const {
    if (this->studentID == studentID) {
        cout << "Student Name: " << firstName << " " << lastName << endl;
        cout << "Student ID: " << this->studentID << endl;
        cout << "Number of courses enrolled: " << numberOfCourses << endl;
        cout << "Course No   Course Name     Credits   Grade" << endl;
        for (const Course& course : coursesEnrolled) {
            cout << left << setw(12) << course.getCourseNumber()
                 << setw(15) << course.getCourseName()
                 << setw(8) << course.getCreditHours()
                 << setw(10) << course.getGrade() << endl;
        }
        cout << "Total number of credits: " << getHoursEndrolled() << endl;
        cout << "Mid-Semester GPA: " << fixed << setprecision(2) << getGpa() << endl;
    }
    else {
        cout << "Student with ID: " << studentID << " not found." << endl;
    }
}

void readStudentDataFromFile(const string& filename, vector<StudentType>& students, int& tuitionPerCredit) {
    ifstream inFile(filename);

    int numStudents;
    inFile >> numStudents >> tuitionPerCredit;
    inFile.ignore();

    for (int i = 0; i < numStudents; ++i) {
        string firstName, lastName, studentID;
        char tuitionPaidChar;
        int numberOfCourses;

        inFile >> firstName >> lastName >> studentID >> tuitionPaidChar >> numberOfCourses;
        bool isTuitionPaid = (tuitionPaidChar == 'Y');

        StudentType student;
        student.setStudent(firstName, lastName, studentID, isTuitionPaid, numberOfCourses);

        for (int j = 0; j < numberOfCourses; ++j) {
            string courseName, courseNumber;
            int creditHours;
            char grade;

            inFile >> courseName >> courseNumber >> creditHours >> grade;

            Course course;
            course.setCourseInfo(courseName, courseNumber, creditHours, grade);

            student.addCourse(course);
        }

        students.push_back(student);
    }
}

void printStudentsToFile(const vector<StudentType>& students, const string& filename) {
    ofstream outFile(filename);

    // Dosyanın başarıyla açıldığını kontrol et
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    // Öğrencileri yazdır
    for (const StudentType& student : students) {
        student.print(outFile); // Her öğrenciyi dosyaya yazdır
        outFile << "---------------------------\n"; // Öğrenciler arasına ayrıcı çizgi ekleyin
    }

    outFile.close(); // Dosyayı kapat
}