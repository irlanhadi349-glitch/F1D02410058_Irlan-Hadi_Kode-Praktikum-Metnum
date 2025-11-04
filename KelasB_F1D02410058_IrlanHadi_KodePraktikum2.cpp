#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int N = 10;

class LUFactorization {
private:
    double A[N][N];
    double L[N][N];
    double U[N][N];
    double B[N];
    double Y[N];
    double X[N];

    void initializeMatrices() {
        // Inisialisasi L sebagai identitas dan U sebagai nol
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                L[i][j] = (i == j) ? 1.0 : 0.0;
                U[i][j] = 0.0;
            }
            Y[i] = 0.0;
            X[i] = 0.0;
        }
    }

    void performLUDecomposition() {
        // Copy A ke U
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                U[i][j] = A[i][j];
            }
        }

        // Proses dekomposisi LU
        for (int k = 0; k < N - 1; k++) {
            for (int i = k + 1; i < N; i++) {
                if (fabs(U[k][k]) < 1e-10) {
                    cout << "Error: Pivot mendekati nol!" << endl;
                    return;
                }
                double factor = U[i][k] / U[k][k];
                L[i][k] = factor;
                
                for (int j = k; j < N; j++) {
                    U[i][j] -= factor * U[k][j];
                }
            }
        }
    }

    void forwardSubstitution() {
        // Menyelesaikan L * Y = B
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * Y[j];
            }
            Y[i] = B[i] - sum;
        }
    }

    void backwardSubstitution() {
        // Menyelesaikan U * X = Y
        for (int i = N - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < N; j++) {
                sum += U[i][j] * X[j];
            }
            X[i] = (Y[i] - sum) / U[i][i];
        }
    }

public:
    LUFactorization() {
        // Inisialisasi vektor B dengan nilai yang ditentukan
        // b = [1, 0, 0, 0, 8, 0, 0, 0, 0, -1]
        B[0] = 1;
        B[1] = 0;
        B[2] = 0;
        B[3] = 0;
        B[4] = 8;  // V = 8 (digit terakhir NIM)
        B[5] = 0;
        B[6] = 0;
        B[7] = 0;
        B[8] = 0;
        B[9] = -1;
    }

    void generateRandomMatrix() {
        srand(time(0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = rand() % 11;  // Random 0-10
            }
        }
    }

    void printAugmentedMatrix() {
        cout << "Augmented Matrix [A|B]:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(7) << fixed << setprecision(2) << A[i][j] << " ";
            }
            cout << "| " << setw(6) << fixed << setprecision(2) << B[i] << endl;
        }
        cout << endl;
    }

    void printLMatrix() {
        cout << "Matriks L (Lower Triangular):" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(7) << fixed << setprecision(2) << L[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printUMatrix() {
        cout << "Matriks U (Upper Triangular):" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(7) << fixed << setprecision(2) << U[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printYVector() {
        cout << "Vektor Y (dari L*Y = B):" << endl;
        for (int i = 0; i < N; i++) {
            cout << "Y" << (i + 1) << " = " << fixed << setprecision(4) << Y[i] << endl;
        }
        cout << endl;
    }

    void printSolution() {
        cout << "Solusi Akhir (X):" << endl;
        for (int i = 0; i < N; i++) {
            cout << "X" << (i + 1) << " = " << fixed << setprecision(4) << X[i] << endl;
        }
    }

    void solve() {
        initializeMatrices();
        performLUDecomposition();
        printLMatrix();
        printUMatrix();
        forwardSubstitution();
        printYVector();
        backwardSubstitution();
        printSolution();
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  PROGRAM FAKTORISASI LU" << endl;
    cout << "  Sistem Persamaan Linear Simultan" << endl;
    cout << "========================================" << endl;
    cout << endl;

    LUFactorization lu;
    
    lu.generateRandomMatrix();
    lu.printAugmentedMatrix();
    
    cout << "Proses Faktorisasi LU dimulai..." << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    lu.solve();

    return 0;
}