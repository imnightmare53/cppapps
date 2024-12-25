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
    void printName(ofstream& outFile) const;
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
    void print(ofstream& outFile, int tuitionPerCredit) const;
};

void loadStudentData(const string& filename, vector<StudentType>& students, int& tuitionPerCredit);

int main() {
    vector<StudentType> students;
    int tuitionPerCredit;
    loadStudentData("input.txt", students, tuitionPerCredit);

    ofstream outFile("output.txt");
    if (!outFile) {
        cout << "Error opening output file!" << endl;
        return 1;
    }
 
    for (const auto& student : students) {
        student.print(outFile, tuitionPerCredit);
    }
    cout<<"Output.txt basariyla olusturuldu";
    outFile.close();

    bool control = true;
    int secim;
    do {
        cout << "---------------------------------------------" << endl;
        cout << "1. Kurs bilgilerinin düzenlenmesi." << endl;
        cout << "2. Kurs bilgilerinin yazdırılması." << endl;
        cout << "3. Kredi saatlerinin gösterilmesi." << endl;
        cout << "4. Kurs numarasının gösterilmesi." << endl;
        cout << "5. Notun gösterilmesi." << endl;
        cout << "6. Öğrenci bilgilerinin ayarlanması." << endl;
        cout << "7. Öğrenci bilgilerinin yazdırılması." << endl;
        cout << "8. Alınan saat sayısının hesaplanması." << endl;
        cout << "9. GPA'nın (Not Ortalaması) hesaplanması." << endl;
        cout << "10. Fatura tutarının hesaplanması." << endl;
        cout << "11. Dersleri ders numarasına göre sıralanması." << endl;
        cout << "0. Çıkış" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Yapmak istediğiniz işlemi girin: ";
        cin >> secim;

        switch (secim) {
        case 0:
            control = false;
            break;
        case 1:

            break;
        case 2:
           
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6: 
            
            break;
        case 7:
            
            break;
        case 8:
            
            break;
        case 9:
            
            break;
        case 10:
            
            break;
        case 11:
            
            break;
        default:

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

void PersonType::printName(ofstream& outFile) const {
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

void StudentType::print(ofstream& outFile, int tuitionPerCredit) const {
    outFile << "Student Name: ";
    outFile << firstName << " " << lastName << endl;
    outFile << "Student ID: " << studentID << endl;
    outFile << "Number of courses enrolled: " << numberOfCourses << endl;

    if (isTuitionPaid) {
        outFile << "Course No  Course Name      Credits Grade" << endl;

        // Kursları sıralayın
        vector<Course> sortedCourses = coursesEnrolled; // Vektörü geçici olarak kopyala
        sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& c1, const Course& c2) {
            return c1.getCourseNumber() < c2.getCourseNumber();
        });

        int totalCredits = 0;
        for (const auto& course : sortedCourses) {
            course.printCourse(); // Kurs detaylarını yazdır
            totalCredits += course.getCreditHours();
        }

        outFile << "Total Credit Hours: " << totalCredits << endl;
        outFile << "GPA: " << getGpa() << endl;
    } else {
        outFile << "Grades cannot be displayed because tuition is unpaid." << endl;
        outFile << "Tuition due: " << billingAmount(tuitionPerCredit) << " TL" << endl;
    }
    outFile << "--------------------------------------------" << endl;
}


void loadStudentData(const string& filename, vector<StudentType>& students, int& tuitionPerCredit) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    int numberOfStudents;
    inputFile >> numberOfStudents >> tuitionPerCredit;

    string line;
    getline(inputFile, line); // Boş satırı atla

    for (int i = 0; i < numberOfStudents; ++i) {
        string firstName, lastName, studentID, tuitionPaid;
        int numberOfCourses;

        getline(inputFile, line);
        stringstream ss(line);
        ss >> firstName >> lastName >> studentID >> tuitionPaid >> numberOfCourses;

        StudentType student;
        student.setStudent(firstName, lastName, studentID, tuitionPaid == "Y", numberOfCourses);

        for (int j = 0; j < numberOfCourses; ++j) {
            string courseName, courseNumber, grade;
            int creditHours;

            getline(inputFile, line);
            stringstream courseStream(line);
            courseStream >> courseName >> courseNumber >> creditHours >> grade;

            Course course;
            course.setCourseInfo(courseName, courseNumber, creditHours, grade[0]);
            student.addCourse(course);
        }

        students.push_back(student);
        getline(inputFile, line); // Boş satırı atla
    }

    inputFile.close();
}
