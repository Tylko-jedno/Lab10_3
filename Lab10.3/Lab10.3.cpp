#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

struct Enterprise {
    string mobilePhone;       // номер телефону
    int numBuilding;          // номер приміщення
    string employees[4];      // список службовців у приміщенні (до 4)
    int employeeCount = 0;    // кількість службовців у приміщенні
};

void Create(Enterprise* p, const int N);
void Print(Enterprise* p, const int N);
void AddRecord(Enterprise* p, int& N);
void EditRecord(Enterprise* p, const int N);
void DeleteRecord(Enterprise* p, int& N);
void FindByPhone(Enterprise* p, const int N);
void FindByBuilding(Enterprise* p, const int N);
void FindBySurname(Enterprise* p, const int N);
void SaveToFile(Enterprise* p, const int N, const char* filename);
void LoadFromFile(Enterprise*& p, int& N, const char* filename);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість записів N: "; cin >> N;

    Enterprise* p = new Enterprise[N];
    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - додати запис" << endl;
        cout << " [4] - редагувати запис" << endl;
        cout << " [5] - видалити запис" << endl;
        cout << " [6] - пошук за номером телефону" << endl;
        cout << " [7] - пошук за номером приміщення" << endl;
        cout << " [8] - пошук за прізвищем службовця" << endl;
        cout << " [9] - зберегти дані у файл" << endl;
        cout << " [10] - завантажити дані з файлу" << endl<< endl;
        cout << " [0] - вихід" << endl;
        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            AddRecord(p, N);
            break;
        case 4:
            EditRecord(p, N);
            break;
        case 5:
            DeleteRecord(p, N);
            break;
        case 6:
            FindByPhone(p, N);
            break;
        case 7:
            FindByBuilding(p, N);
            break;
        case 8:
            FindBySurname(p, N);
            break;
        case 9:
            SaveToFile(p, N, "enterprise_data.dat");
            cout << "Дані збережено у файл 'enterprise_data.dat'" << endl;
            break;
        case 10:
            LoadFromFile(p, N, "enterprise_data.dat");
            cout << "Дані завантажено з файлу 'enterprise_data.dat'" << endl;
            break;
        case 0:
            break;
        default: cout << "Невірний вибір!" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Enterprise* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Приміщення № " << i + 1 << ":" << endl;
        cout << " Номер телефону: "; cin >> p[i].mobilePhone;
        cout << " Номер приміщення: "; cin >> p[i].numBuilding;
        cout << " Введіть кількість службовців (до 4): "; cin >> p[i].employeeCount;

        for (int j = 0; j < p[i].employeeCount; j++) {
            cout << "  Службовець № " << j + 1 << ": ";
            cin >> ws; // очистити буфер
            getline(cin, p[i].employees[j]);
        }
    }
}

void Print(Enterprise* p, const int N) {
    cout << "=========================================================================" << endl;
    cout << "| №  | Телефон | Номер приміщення | Службовці                           |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1
            << " | " << setw(8) << p[i].mobilePhone
            << " | " << setw(16) << p[i].numBuilding
            << " | ";
        for (int j = 0; j < p[i].employeeCount; j++) {
            cout << p[i].employees[j];
            if (j < p[i].employeeCount - 1) cout << ", ";
        }
        cout << " | " << endl;
    }
    cout << "=========================================================================" << endl;
}

void AddRecord(Enterprise* p, int& N) {
    if (N >= 100) {  // обмеження на кількість записів
        cout << "База переповнена!" << endl;
        return;
    }
    cout << "Додавання нового запису:" << endl;
    cout << " Номер телефону: "; cin >> p[N].mobilePhone;
    cout << " Номер приміщення: "; cin >> p[N].numBuilding;
    cout << " Введіть кількість службовців (до 4): "; cin >> p[N].employeeCount;

    for (int j = 0; j < p[N].employeeCount; j++) {
        cout << "  Службовець № " << j + 1 << ": ";
        cin >> ws; // очистити буфер
        getline(cin, p[N].employees[j]);
    }
    N++;
}

void EditRecord(Enterprise* p, const int N) {
    int index;
    cout << "Введіть номер запису для редагування (1 - " << N << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= N) {
        cout << "Невірний індекс!" << endl;
        return;
    }

    cout << "Новий номер телефону: "; cin >> p[index].mobilePhone;
    cout << "Новий номер приміщення: "; cin >> p[index].numBuilding;
    cout << "Введіть кількість службовців (до 4): "; cin >> p[index].employeeCount;
    for (int j = 0; j < p[index].employeeCount; j++) {
        cout << "  Службовець № " << j + 1 << ": ";
        cin >> ws;
        getline(cin, p[index].employees[j]);
    }
}

void DeleteRecord(Enterprise* p, int& N) {
    int index;
    cout << "Введіть номер запису для видалення (1 - " << N << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= N) {
        cout << "Невірний індекс!" << endl;
        return;
    }

    for (int i = index; i < N - 1; i++) {
        p[i] = p[i + 1];
    }
    N--;
}

void FindByPhone(Enterprise* p, const int N) {
    string phone;
    cout << "Введіть номер телефону: ";
    cin >> phone;
    for (int i = 0; i < N; i++) {
        if (p[i].mobilePhone == phone) {
            cout << "Номер приміщення: " << p[i].numBuilding << endl;
            cout << "Список службовців: ";
            for (int j = 0; j < p[i].employeeCount; j++) {
                cout << p[i].employees[j] << (j < p[i].employeeCount - 1 ? ", " : "");
            }
            cout << endl;
            return;
        }
    }
    cout << "Номер телефону не знайдено!" << endl;
}

void FindByBuilding(Enterprise* p, const int N) {
    int building;
    cout << "Введіть номер приміщення: ";
    cin >> building;
    for (int i = 0; i < N; i++) {
        if (p[i].numBuilding == building) {
            cout << "Номер телефону: " << p[i].mobilePhone << endl;
            return;
        }
    }
    cout << "Номер приміщення не знайдено!" << endl;
}

void FindBySurname(Enterprise* p, const int N) {
    string surname;
    cout << "Введіть прізвище службовця: ";
    cin >> ws;
    getline(cin, surname);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < p[i].employeeCount; j++) {
            if (p[i].employees[j] == surname) {
                cout << "Номер телефону: " << p[i].mobilePhone << ", Номер приміщення: " << p[i].numBuilding << endl;
                return;
            }
        }
    }
    cout << "Службовця не знайдено!" << endl;
}
void SaveToFile(Enterprise* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
    fout.write((char*)&N, sizeof(N)); // записали кількість елементів
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Enterprise)); // записали елементи масиву
    fout.close(); // закрили файл
}
void LoadFromFile(Enterprise*& p, int& N, const char* filename)
{
    delete[] p; // знищили попередні дані
    ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
    fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
    p = new Enterprise[N]; // створили динамічний масив
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Enterprise)); // прочитали елементи масиву
    fin.close(); // закрили файл
}
