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
  
    Course() : courseName(""), courseNumber(""), creditHours(0), grade('F') {}

    void setCourseInfo(const string& name, const string& number, int credits, char grd) {
        courseName = name;
        courseNumber = number;
        creditHours = credits;
        grade = grd;
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

    double gradeToGPA() const {
        switch (grade) {
            case 'A': return 4.0;
            case 'B': return 3.0;
            case 'C': return 2.0;
            case 'D': return 1.0;
            case 'E': return 0.5;
            case 'F': return 0.0;
            default: return 0.0;
        }
    }

    char getGrade() const {
        return grade;
    }

    // Kopya yapıcı
    Course(const Course& other) = default;

    // Kopya atama operatörü
    Course& operator=(const Course& other) = default;

    // Taşıma atama operatörü
    Course& operator=(Course&& other) noexcept = default;
};

class personType {
private:
    string firstName;
    string lastName;

public:
    void setName(const string& first, const string& last) {
        firstName = first;
        lastName = last;
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
class studentType : public personType {
private:
    string studentID;
    bool isTuitionPaid;
    int numberOfCourses;
    vector<Course> courses;

public:
    studentType() : studentID(""), isTuitionPaid(false), numberOfCourses(0) {}

    void setStudentInfo(const string& fName, const string& lName, const string& sID, bool tuitionPaid, int numCourses) {
        setName(fName, lName);
        studentID = sID;
        isTuitionPaid = tuitionPaid;
        numberOfCourses = numCourses;
    }

    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    double calculateGPA() const {
        double totalGPA = 0.0;
        int totalCredits = 0;

        for (const auto& course : courses) {
            totalGPA += course.gradeToGPA() * course.getCreditHours();
            totalCredits += course.getCreditHours();
        }

        if (totalCredits == 0) return 0.0;
        return totalGPA / totalCredits;
    }

    double billingAmount(int tuitionPerCredit) const {
        int totalCredits = 0;

        for (const auto& course : courses) {
            totalCredits += course.getCreditHours();
        }

        return totalCredits * tuitionPerCredit;
    }

    void courseEnrolled() const {
        auto tempCourses = courses; // Geçici olarak kopyala
        sort(tempCourses.begin(), tempCourses.end(), [](const Course& a, const Course& b) {
            return a.getCourseNumber().substr(a.getCourseNumber().size() - 3) < b.getCourseNumber().substr(b.getCourseNumber().size() - 3);
        });

        cout << "Student Name: ";
        printName();
        cout << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Number of courses enrolled: " << numberOfCourses << endl;
        cout << "Course No  Course Name      Credits Grade" << endl;

        for (const auto& course : tempCourses) {
            course.printCourse();
        }

        int totalCredits = 0;
        for (const auto& course : tempCourses) {
            totalCredits += course.getCreditHours();
        }
        cout << "Total number of credits: " << totalCredits << endl;
        cout << "Mid-Semester GPA: " << calculateGPA() << endl;
    }
};
void loadStudentData(const string& filename, vector<studentType>& students) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    int numberOfStudents, tuitionPerCredit;
    inputFile >> numberOfStudents >> tuitionPerCredit;

    string line;
    getline(inputFile, line); // Boş satırı atla

    for (int i = 0; i < numberOfStudents; ++i) {
        string firstName, lastName, studentID, tuitionPaid;
        int numberOfCourses;

        getline(inputFile, line);
        stringstream ss(line);
        ss >> firstName >> lastName >> studentID >> tuitionPaid >> numberOfCourses;

        studentType student;
        student.setStudentInfo(firstName, lastName, studentID, tuitionPaid == "Y", numberOfCourses);

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

int main() {
    vector<studentType> students;
    loadStudentData("input.txt", students);

    for (const auto& student : students) {
        student.courseEnrolled();
        cout << "--------------------------------------------" << endl;
    }

    return 0;
}
