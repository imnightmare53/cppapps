#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Student {
private:    
    string* names;
    string* studentNumbers;
    float* midterms;
    float* secondExams;
    float* assignments;
    float* finals;
    int* attendance;
    float* averages;
    int studentCount;

public:
    // Varsayılan constructor (bellek ayırma için)
    Student() : names(nullptr), studentNumbers(nullptr), midterms(nullptr),
                secondExams(nullptr), assignments(nullptr), finals(nullptr),
                attendance(nullptr), averages(nullptr), studentCount(0) {}

    // Parametreli constructor
    Student(int count) : studentCount(count) {
        // Dinamik bellek ayırma
        names = new string[studentCount];
        studentNumbers = new string[studentCount];
        midterms = new float[studentCount];
        secondExams = new float[studentCount];
        assignments = new float[studentCount];
        finals = new float[studentCount];
        averages = new float[studentCount];
        attendance = new int[studentCount];
    }
  
    ~Student() {
        delete[] names;
        delete[] studentNumbers;
        delete[] midterms;
        delete[] secondExams;
        delete[] assignments;
        delete[] finals;
        delete[] averages;
        delete[] attendance;
    }

    // CSV dosyasından veri okuma
    void readFromCSV(const string& fileName) {
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Dosya acilamadi: " << fileName << endl;
            return;
        }

        string line;
        int index = 0;

        // İlk satırı (başlıklar) atla
        getline(file, line);

        // Verileri satır satır oku
        while (getline(file, line)) {
            // Öğrenci sayısını hesapla
            studentCount++;

            // Dinamik bellek yeniden ayarlama
            resizeArrays(studentCount);

            stringstream ss(line);
            string token;

            // Ad
            getline(ss, token, ',');
            names[index] = (token.empty() ? "0" : token);  // Eğer boşsa 0 ile doldur

            // Öğrenci Numarası
            getline(ss, token, ',');
            studentNumbers[index] = (token.empty() ? "0" : token);  // Eğer boşsa 0 ile doldur

            // Ara Sınav
            getline(ss, token, ',');
            midterms[index] = (token.empty() ? 0.0f : stof(token));  // Eğer boşsa 0.0f ile doldur

            // 2. Sınav
            getline(ss, token, ',');
            secondExams[index] = (token.empty() ? 0.0f : stof(token));  // Eğer boşsa 0.0f ile doldur

            // Ödev
            getline(ss, token, ',');
            assignments[index] = (token.empty() ? 0.0f : stof(token));  // Eğer boşsa 0.0f ile doldur

            // Final
            getline(ss, token, ',');
            finals[index] = (token.empty() ? 0.0f : stof(token));  // Eğer boşsa 0.0f ile doldur

            // Devam Sayısı
            getline(ss, token, ',');
            attendance[index] = (token.empty() ? 0 : stoi(token));  // Eğer boşsa 0 ile doldur

            ++index;
        }

        file.close();
        cout << "Dosya basariyla okundu ve veriler yerlestirildi." << endl;
    }

    // Ortalama hesaplama
    void Average() {
        for (int i = 0; i < studentCount; i++) {
            averages[i] = (midterms[i] * 0.20) +
                         (secondExams[i] * 0.20) +
                         (assignments[i] * 0.20) +
                         (finals[i] * 0.40);
        }
    }

    // Öğrenci sayısını döndüren metod
    int getStudentCount() const {
        return studentCount;
    }

private:
    // Dinamik dizileri yeniden boyutlandırma
    void resizeArrays(int newCount) {
        names = resizeStringArray(names, newCount);
        studentNumbers = resizeStringArray(studentNumbers, newCount);
        midterms = resizeFloatArray(midterms, newCount);
        secondExams = resizeFloatArray(secondExams, newCount);
        assignments = resizeFloatArray(assignments, newCount);
        finals = resizeFloatArray(finals, newCount);
        attendance = resizeIntArray(attendance, newCount);
        averages = resizeFloatArray(averages, newCount);
    }

    // String dizilerini yeniden boyutlandırma
    string* resizeStringArray(string* arr, int newCount) {
        string* newArr = new string[newCount];
        for (int i = 0; i < newCount - 1; ++i) {  // Yeni boyut ile verileri kopyala
            newArr[i] = arr[i];
        }
        delete[] arr;
        return newArr;
    }

    // Float dizilerini yeniden boyutlandırma
    float* resizeFloatArray(float* arr, int newCount) {
        float* newArr = new float[newCount];
        for (int i = 0; i < newCount - 1; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        return newArr;
    }

    // Int dizilerini yeniden boyutlandırma
    int* resizeIntArray(int* arr, int newCount) {
        int* newArr = new int[newCount];
        for (int i = 0; i < newCount - 1; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        return newArr;
    }
};

int main(){
    string fileName = "https://raw.githubusercontent.com/zyavuz610/data/refs/heads/master/ogrenci-not/%C3%B6%C4%9Frenci%20notlar%C4%B1%20-%20isimli.csv"; // .csv dosyasının ismi
    Student ogr;

    // Verileri csv dosyasından oku
    ogr.readFromCSV(fileName);

    // Ortalamaları hesapla
    ogr.Average();

    // Öğrenci sayısını yazdır
    cout << "Öğrenci sayisi: " << ogr.getStudentCount() << endl;

    return 0;    
}
