#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include<Windows.h>

using namespace std;

// ������� ��� ���������� �������� Y
double calculateY(double x, int n) {
    if (n <= 0) {
        throw invalid_argument("�������� n �� ���� ����� 0!");
    }
    double result = 0.0;

    if (x <= 0) {
        double P = 1.0;
        for (int i = 1; i < n; ++i) {
            P *= (i * i * i) + i;
        }
        result = P;
    }
    else {
        double S = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue; //
                S += x / (i + j);
            }
        }
        result = S;
    }

    return result;
}

// ������� ��� �������� �����
void inputParameters(int& n, double& a, double& b, double& h, char& saveToFile) {
    cout << "������ �������� n, �������, ����� �������� �� ����: ";
    cin >> n >> a >> b >> h;

    if (n <= 0 || h <= 0) {
        throw invalid_argument("�������: n �� h ����� ���� ������� �� 0.");
    }

    cout << "�� ������ �������� ���������� � ����? (y/n): ";
    cin >> saveToFile;
}

// ������� ��� ���������� ���������� � ����
void saveResultsToFile(ofstream& file, double x, double y) {
    file << "x: " << x << " Y: " << y << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double x, h, a, b;
    int n;
    char saveToFile;

    try {
        inputParameters(n, a, b, h, saveToFile);

        ofstream file;
        if (saveToFile == 'y') {
            file.open("results.txt");
            if (!file) {
                throw runtime_error("������� �������� �����!");
            }
        }

        cout << fixed << setprecision(4);
        if (saveToFile == 'y') {
            file << fixed << setprecision(4);
        }

        for (x = a; x <= b; x += h) {
            double y = calculateY(x, n);
            cout << "x: " << x << " Y: " << y << endl;

            if (saveToFile == 'y') {
                saveResultsToFile(file, x, y);
            }
        }

        if (saveToFile == 'y') {
            file.close();
            cout << "���� ���������� ��������� � ���� 'results.txt'.\n";
        }
    }
    catch (const exception& e) {
        cerr << "�������: " << e.what() << endl;
        return 1;
    }

    return 0;
}
