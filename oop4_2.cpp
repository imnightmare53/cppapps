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
    Course(){
        this->courseName="";
        this->courseNumber = "";
        this->creditHours = 0;
        this->grade = 'F';
    }

    void setCourseInfo(string courseName="", string courseNumber="", int creditHours=0, char grade='\0') {
        this->courseName = courseName;
        this->courseNumber = courseNumber;
        this->creditHours = creditHours;
        this->grade = grade;
    }

    void printCourse() const {
        cout << left << setw(10) << courseNumber << setw(15) << courseName << setw(8) << creditHours << grade << endl;
    }

    int getCreditHours() const {
        return creditHours;
    }

    string getCourseNumber() const {
        return courseNumber;
    }

    string getCourseName() const {
        return courseName;
    }

    double gradeToGPA() const {
        switch (grade) {                    //break'e gerek yok return var
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

    char getGrade() const {
        return grade;
    }
};

class PersonType {
protected:
    string firstName;
    string lastName;

public:
    PersonType(string firstName = "", string lastName=""){
        this->firstName = firstName;
        this->lastName = lastName;
    }

    void setName(string firstName, string lastName) {
        this->firstName = firstName;
        this->lastName = lastName;
    }

    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    void printName() const {
        cout << firstName << " " << lastName << endl;
    }
};

class StudentType : public PersonType {
private:
    string studentID;
    int numberOfCourses;
    bool isTuitionPaid;
    vector<Course> coursesEnrolled;

public:
    StudentType(){
        this->studentID="";
        this->isTuitionPaid = false;
        this->numberOfCourses = 0;
    }

    void addCourse(const Course& course) {
        coursesEnrolled.push_back(course);
    }

    void setStudent(string firstName, string lastName, string studentID, bool isTuitionPaid, int numberOfCourses) {
        setName(firstName, lastName);
        this->studentID = studentID;
        this->isTuitionPaid = isTuitionPaid;
        this->numberOfCourses = numberOfCourses;
    }

    int getHoursEndrolled() const {
        int totalHours= 0;
        for(Course myCourse : coursesEnrolled)    
            totalHours += myCourse.getCreditHours();
        return totalHours;
    }

    double getGpa() const {
        double totalPointOfCourses = 0;
        int totalCredits = 0;
        for(Course myCourse : coursesEnrolled) {
            totalPointOfCourses += myCourse.gradeToGPA() * myCourse.getCreditHours();
            totalCredits += myCourse.getCreditHours();
        }
        
        return totalPointOfCourses / totalCredits;              // her öğrenci en az 1 ders aldığı için kredi sayısı 0 olamaz
    }

    double billingAmount(int tuitionPerCredit) {
        int totalCredits = 0;

        for(Course myCourse : coursesEnrolled) 
            totalCredits += myCourse.getCreditHours();

        return totalCredits * tuitionPerCredit;
    }

    void sortCourses() {                    //Kursları numaralarına göre sıralıyor bubble sort
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

    void print(ofstream& outFile) const {
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

    void print(const string& studentID) const {
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
};

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

int main() {
    vector<StudentType> students;
    int tuitionPerCredit;

    readStudentDataFromFile("input.txt", students, tuitionPerCredit);

    ofstream outFile("output.txt");

    for (const StudentType& student : students) {
        student.print(outFile);
        outFile << "---------------------------\n";
    }

    outFile.close();

    return 0;
}
