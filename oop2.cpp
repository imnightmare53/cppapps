#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
private:
    string* isim;
    string* ogr_no;
    float* ilk_vize;
    float* ikinci_vize;
    float* odev;
    float* final;
    int* devam_sayisi;
    float* ortalama;
    int ogr_sayisi = 0;
    int gecen_ogr_sayisi = 0;
    int kalan_ogr_sayisi = 0;

public:
    Student() {
        isim = nullptr;
        ogr_no = nullptr;
        ilk_vize = nullptr;
        ikinci_vize = nullptr;
        odev = nullptr;
        final = nullptr;
        devam_sayisi = nullptr;
        ortalama = nullptr;
        ogr_sayisi = 0;
        int gecen_ogr_sayisi = 0;
        int kalan_ogr_sayisi = 0;
    }

    Student(const string& fileName) {
        ogr_sayisi = counter(fileName);  // Öğrenci sayısını buluyo
        isim = new string[ogr_sayisi];
        ogr_no = new string[ogr_sayisi];
        ilk_vize = new float[ogr_sayisi];
        ikinci_vize = new float[ogr_sayisi];
        odev = new float[ogr_sayisi];
        final = new float[ogr_sayisi];
        ortalama = new float[ogr_sayisi];
        devam_sayisi = new int[ogr_sayisi];
        
        readFromCSV(fileName);  //Arr'leri dolduruyo
    }

    ~Student() {
        delete[] isim;
        delete[] ogr_no;
        delete[] ilk_vize;
        delete[] ikinci_vize;
        delete[] odev;
        delete[] final;
        delete[] ortalama;
        delete[] devam_sayisi;
    }


    void readFromCSV(const string& fileName) {
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Dosya acilamadi :( !) " << fileName << endl;
            return;
        }

        string line;
        int index = 0;

        getline(file, line);   //İlk satırı okumuyo (okuyo ama dikkate almıyo)

        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');                                      //İlki isim string
            isim[index] = (token.empty() ? "0" : token);

            getline(ss, token, ',');                                      //İkinci okul no string
            ogr_no[index] = (token.empty() ? "0" : token);

            getline(ss, token, ',');                                      //Üçüncü 1. ara sınav float
            ilk_vize[index] = (token.empty() ? 0.0f : stof(token));

            getline(ss, token, ',');                                      //Dördüncü 2. ara sınav float  
            ikinci_vize[index] = (token.empty() ? 0.0f : stof(token));

            getline(ss, token, ',');                                      //Beşinci ödev notu float
            odev[index] = (token.empty() ? 0.0f : stof(token));

            getline(ss, token, ',');                                      //Altıncı final float
            final[index] = (token.empty() ? 0.0f : stof(token));

            getline(ss, token, ',');                                      //Yedinci son devam sayısı int
            devam_sayisi[index] = (token.empty() ? 0 : stoi(token));

            index++;
        }

        file.close();
        cout << "Dosya basariyla okundu ve ögrenci bilgileri yerlestirildi." << endl;
    }

    void Average() {
        for (int i = 0; i < ogr_sayisi; i++){
            ortalama[i] = (ilk_vize[i] * 0.20) + (ikinci_vize[i] * 0.20) + (odev[i] * 0.20) + (final[i] * 0.40);
            int ortt = ortalama[i];
            if (ortt>=50) gecen_ogr_sayisi++;
            else kalan_ogr_sayisi++;
        }
    }

    void SpeAverage(int ort_) const{
        int sayi=0;
        for (int i=0; i<ogr_sayisi; i++){
            if(ortalama[i]>=ort_) sayi++;
        }
        cout<<ort_<<" ve üzeri ortalamaya sahip öğrenci sayisi: "<<sayi<<endl;
    }

    int getStudentCount() const {
        return ogr_sayisi;
    }

    int getFailedStudentCount() const{
        return kalan_ogr_sayisi;
    }
    int getPassedStudentCount() const {
        return gecen_ogr_sayisi;
    }

    void print() const {                                   //İlk print fonksiyonu
        for (int i = 0; i < ogr_sayisi; i++) {
            cout << "Öğrenci: " << left << setw(15) << isim[i];
            cout<< ", No: " << setw(6) << ogr_no[i];
            cout<< ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
            cout<< ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
            cout<< ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
            cout<< ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
            cout<< ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
            cout<< ", Devam: " << setw(3) << devam_sayisi[i]<<endl<<endl;
        }
    }


    void print(int durum) const {                            //İkinci print fonksiyonu
        if (durum == 0){
            for (int i = 0; i < ogr_sayisi; i++) {
                if (ortalama[i] >= 50) continue;

                cout << "Öğrenci: " << left << setw(15) << isim[i];
                cout << ", No: " << setw(6) << ogr_no[i];
                cout << ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
                cout << ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
                cout << ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
                cout << ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
                cout << ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
                cout << ", Devam: " << setw(3) << devam_sayisi[i] << endl << endl;
            }
        }
        else if (durum == 1) {
            for (int i = 0; i < ogr_sayisi; i++) {
                if (ortalama[i] < 50) continue;

                cout << "Öğrenci: " << left << setw(15) << isim[i];
                cout << ", No: " << setw(6) << ogr_no[i];
                cout << ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
                cout << ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
                cout << ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
                cout << ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
                cout << ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
                cout << ", Devam: " << setw(3) << devam_sayisi[i] << endl << endl;
            }
        }
    }

    void print(string dosyaAdi, int durum) const {
        ofstream outFile(dosyaAdi);
        if (outFile.is_open()) {
            if (durum == -1) {
                for (int i = 0; i < ogr_sayisi; i++) {
                    outFile << "Öğrenci: " << left << setw(15) << isim[i];
                    outFile << ", No: " << setw(6) << ogr_no[i];
                    outFile << ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
                    outFile << ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
                    outFile << ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
                    outFile << ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
                    outFile << ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
                    outFile << ", Devam: " << setw(3) << devam_sayisi[i] << endl;
                }
            } 
            else if (durum == 0) {
                for (int i = 0; i < ogr_sayisi; i++) {
                    if (ortalama[i] >= 50) continue;

                    outFile << "Öğrenci: " << left << setw(15) << isim[i];
                    outFile << ", No: " << setw(6) << ogr_no[i];
                    outFile << ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
                    outFile << ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
                    outFile << ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
                    outFile << ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
                    outFile << ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
                    outFile << ", Devam: " << setw(3) << devam_sayisi[i] << endl;
                }
            }
            else if (durum == 1) {
                for (int i = 0; i < ogr_sayisi; i++) {
                    if (ortalama[i] < 50) continue;

                    outFile << "Öğrenci: " << left << setw(15) << isim[i];
                    outFile << ", No: " << setw(6) << ogr_no[i];
                    outFile << ", 1. Vize: " << setw(6) << fixed << setprecision(1) << ilk_vize[i];
                    outFile << ", 2. Vize: " << setw(6) << fixed << setprecision(1) << ikinci_vize[i];
                    outFile << ", Ödev: " << setw(6) << fixed << setprecision(1) << odev[i];
                    outFile << ", Final: " << setw(6) << fixed << setprecision(1) << final[i];
                    outFile << ", Ortalama: " << setw(6) << fixed << setprecision(1) << ortalama[i];
                    outFile << ", Devam: " << setw(3) << devam_sayisi[i] << endl;
                }
            }

            outFile.close();
            cout << dosyaAdi << " dosyasına yazıldı." << endl;
        }
    }

private:
    int counter(const string& fileName){
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Dosya acilamadi :( !) " << fileName << endl;
            return 0;
        }

        string line;
        int count = 0;

        getline(file, line);    //İlk satırı okumuyo (okuyo ama dikkate almıyo)

        while (getline(file, line)) {
            count++;
        }

        file.close();
        return count;
    }
};

void createFile(const Student& x);

int main() {
    string fileName = "csv.txt";
    Student ogr(fileName);

    ogr.Average();      //consturctor ile hesaplanamdığı için mainin hemen mainin içinde çağırıp ortalama hesapladık

    cout << "Öğrenci sayisi: " << ogr.getStudentCount() << endl;

    bool a = true;
    do{

        cout<<"---------------------------------"<<endl;
        cout<<"1.Öğrencileri listele"<<endl;
        cout<<"2.Kalan öğrencileri listeli"<<endl;
        cout<<"3.Geçen öğrencileri listele"<<endl;
        cout<<"4.Tüm/Kalan/Geçen öğrencileri dosyaya yazdır"<<endl;
        cout<<"5.Öğrenci sayısını gör"<<endl;
        cout<<"6.Kalan öğrenci sayısını gör"<<endl;
        cout<<"7.Geçen öğrenci sayısını gör"<<endl;
        cout<<"8.Belirli bir ortalama üstündeki öğrenci sayısını gör"<<endl;
        cout<<"0.Çıkış"<<endl;
        cout<<"---------------------------------"<<endl;

        int secim;
        cout<<"Yapmak istediğinz işlemi girin: ";
        cin>>secim;

        switch (secim)
        {
        case 0:
            a = false;
            break;
        case 1:
            ogr.print();
            break;
        case 2:
            ogr.print(0);
            break;
        case 3:
            ogr.print(1);
            break;
        case 4:
            createFile(ogr);
            break;
        case 5:
            cout << "Öğrenci sayısı: " << ogr.getStudentCount()<<endl;
            break;
        case 6:
            cout<<"Kalan öğrenci sayısı: "<<ogr.getFailedStudentCount()<<endl;
            break;
        case 7:
            cout<<"Geçen öğrenci sayısı: "<<ogr.getPassedStudentCount()<<endl;
            break;
        case 8:
            int belirli_ort;
            cout<<"Hangi ortalama ve üstündeki öğrenci sayısını görmek istiyorsunuz ?: ";
            cin>> belirli_ort;
            ogr.SpeAverage(belirli_ort);
            break;
        default:
            cout<<"Geçersiz seçim !!!"<<endl;
            break;
        }

    }while(a);

    return 0;    
}



void createFile(const Student& x){
    string yeni_dosya;
    cout<<"Lütfen oluşturulacak dosyanın ismini giriniz: ";
    cin>>yeni_dosya;
    cout<<"---------------------------------"<<endl;
    cout<<"1.Öğrencileri yazdır"<<endl;
    cout<<"2.Kalan öğrencileri yazdır"<<endl;
    cout<<"3.Geçen öğrencileri yazdır"<<endl;
    cout<<"0.İptal"<<endl;
    cout<<"---------------------------------"<<endl;

    int secim;
    cout<<"Yapmak istediğinz işlemi girin: ";
    cin>>secim;
    switch (secim)
    {
    case 0:
        cout<<"İşlem iptal edildi";
        break;
    case 1:
        x.print(yeni_dosya,-1);
        cout<<"Yazma işlemi başarılı"<<endl;
        break;
    case 2:
        x.print(yeni_dosya,0);
        cout<<"Yazma işlemi başarılı"<<endl;
        break;
    case 3:
        x.print(yeni_dosya,1);
        cout<<"Yazma işlemi başarılı"<<endl;
        break;
    
    default:
        cout<<"Geçersiz seçim !!!"<<endl;
        break;
    }
}
