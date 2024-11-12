#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика ",
                            "Радіоелектроніка", "Комп'ютерні науки",
                            "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_info;
};

#pragma pack(pop)

void Create(Students* S, const int N);
void Print(Students* S, const int N);
void p_sort(Students* S, const int N);
int* i_sort(Students* S, const int N);
void i_print(Students* S, int* I, const int N);
bool b_search(Students* S, const int N, const string surname, const int course, const int grade_physics);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    string f_surname;
    int f_course;
    int f_grade_physics;

    int MenuItem;

    while (true) {
        cout << endl << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про студентів" << endl;
        cout << "2 - Вивести інформацію про студентів" << endl;
        cout << "3 - Фізично впорядкувати інформацію" << endl;
        cout << "4 - Індексно впорядкувати інформацію" << endl;
        cout << "5 - Бінарний пошук студента" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> MenuItem; cout << endl;

        switch (MenuItem) {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            p_sort(S, N);
            Print(S, N);
            break;
        case 4:
            i_print(S, i_sort(S, N), N);
            break;
        case 5:
            cout << "Введіть критерії пошуку: " << endl;
            cout << "Прізвище: "; cin.get(); cin.sync(); getline(cin, f_surname);
            cout << "Курс: "; cin >> f_course;
            cout << "Оцінка з фізики: "; cin >> f_grade_physics;

            if (b_search(S, N, f_surname, f_course, f_grade_physics)) {
                cout << "Студента знайдено" << endl;
            }
            else {
                cout << "Студента не знайдено" << endl;
            }
            break;
        }

        if (MenuItem == 0) break;
    }

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;

        do
        {
            cout << "Курс: "; cin >> S[i].course; cout << endl;
        } while (S[i].course < 1 || S[i].course > 6);

        do
        {
            cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,"
                "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (S[i].speciality < 0 || S[i].speciality > 4);

        do
        {
            cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        } while (S[i].grade_physics < 1 || S[i].grade_physics > 5);

        do
        {
            cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        } while (S[i].grade_math < 1 || S[i].grade_math > 5);

        do
        {
            cout << "Оцінка з інформатики: "; cin >> S[i].grade_info; cout << endl;
        } while (S[i].grade_info < 1 || S[i].grade_info > 5);

        cout << endl;
    }
}

void Print(Students* S, const int N)
{
    cout << "=================================================================================================" << endl;
    cout << "|  №  |   Прізвище   |  Курс  |     Спеціальність     |  Фізика  |  Математика  |  Інформатика  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;
        cout << "|" << setw(15) << left << S[i].grade_info << "|" << endl;
    }
    cout << "=================================================================================================" << endl << endl;
}

void p_sort(Students* S, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            bool shouldSwap = (S[j].grade_physics < S[j + 1].grade_physics) ||
                (S[j].grade_physics == S[j + 1].grade_physics && S[j].course > S[j + 1].course) ||
                (S[j].grade_physics == S[j + 1].grade_physics && S[j].course == S[j + 1].course && S[j].surname < S[j + 1].surname);

            if (shouldSwap) {
                Students temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;
            }
        }
    }
}

int* i_sort(Students* S, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) I[i] = i;

    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;
        while (j >= 0 && (
            (S[I[j]].grade_physics < S[value].grade_physics) ||
            (S[I[j]].grade_physics == S[value].grade_physics && S[I[j]].course > S[value].course) ||
            (S[I[j]].grade_physics == S[value].grade_physics && S[I[j]].course == S[value].course && S[I[j]].surname < S[value].surname)
            )) {
            I[j + 1] = I[j];
            j--;
        }
        I[j + 1] = value;
    }
    return I;
}

void i_print(Students* S, int* I, const int N)
{
    cout << "=================================================================================================" << endl;
    cout << "|  №  |   Прізвище   |  Курс  |     Спеціальність     |  Фізика  |  Математика  |  Інформатика  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[I[i]].surname;
        cout << "|" << setw(8) << left << S[I[i]].course;
        cout << "|" << setw(23) << left << speciality_str[S[I[i]].speciality];
        cout << "|" << setw(10) << left << S[I[i]].grade_physics;
        cout << "|" << setw(14) << left << S[I[i]].grade_math;
        cout << "|" << setw(15) << left << S[I[i]].grade_info << "|" << endl;
    }
    cout << "=================================================================================================" << endl << endl;
}

bool b_search(Students* S, const int N, const string surname, const int course, const int grade_physics) {
    int L = 0, R = N - 1, mid;
    while (L <= R) {
        mid = (L + R) / 2;
        if (S[mid].surname == surname && S[mid].course == course && S[mid].grade_physics == grade_physics) {
            return true;
        }
        if (S[mid].grade_physics > grade_physics ||
            (S[mid].grade_physics == grade_physics && S[mid].course < course) ||
            (S[mid].grade_physics == grade_physics && S[mid].course == course && S[mid].surname > surname)) {
            L = mid + 1;
        }
        else {
            R = mid - 1;
        }
    }
    return false;
}
