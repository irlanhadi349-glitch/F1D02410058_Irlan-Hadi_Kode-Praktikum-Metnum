#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// Deklarasi fungsi-fungsi matematika
double fungsiPertama(double x) {
    return (x * x) - (2 * x) + 1;
}

double fungsiKedua(double x) {
    double eksponen = exp(-2 * x);
    return (x * x * x) - ((x + 2) * eksponen) + 1;
}

double fungsiTransformasi(double x) {
    double hasil1 = fungsiPertama(x);
    double hasil2 = fungsiKedua(x);
    return (hasil1 + hasil2) / 2.0;
}

void eksekusiMetodeIterasi() {
    // Variabel input
    double tebakanAwal, batasToleransi;
    int batasIterasi = 1000;
    
    // Interface input
    cout << "PROGRAM PENYELESAIAN PERSAMAAN NON-LINIER\n";
    cout << "=========================================\n\n";
    
    cout << "Masukkan parameter berikut:\n";
    cout << "Nilai awal (x0): ";
    cin >> tebakanAwal;
    cout << "Batas toleransi error: ";
    cin >> batasToleransi;
    cout << "\n";
    
    // Variabel proses
    double nilaiSaatIni = tebakanAwal;
    double nilaiBerikutnya;
    double error;
    int iterasi = 0;
    bool konvergen = false;
    
    // Header output
    cout << "PERKEMBANGAN ITERASI:\n";
    cout << left << setw(8) << "Step" 
         << left << setw(12) << "x0" 
         << left << setw(12) << "f1(x)" 
         << left << setw(12) << "f2(x)" 
         << left << setw(12) << "x1" 
         << left << setw(12) << "Error" << endl;
    cout << string(68, '-') << endl;
    
    // Proses iterasi dengan for loop dan break condition
    for (iterasi = 0; iterasi < batasIterasi; iterasi++) {
        nilaiBerikutnya = fungsiTransformasi(nilaiSaatIni);
        error = fabs(nilaiBerikutnya - nilaiSaatIni);
        
        // Output iterasi
        cout << fixed << setprecision(6);
        cout << left << setw(8) << iterasi + 1
             << left << setw(12) << nilaiSaatIni
             << left << setw(12) << fungsiPertama(nilaiSaatIni)
             << left << setw(12) << fungsiKedua(nilaiSaatIni)
             << left << setw(12) << nilaiBerikutnya
             << left << setw(12) << error << endl;
        
        // Cek konvergensi
        if (error <= batasToleransi) {
            konvergen = true;
            break;
        }
        
        nilaiSaatIni = nilaiBerikutnya;
    }
    
    // Output hasil akhir
    cout << "\n" << string(50, '=') << endl;
    cout << "RINGKASAN HASIL:\n";
    cout << string(50, '=') << endl;
    
    if (konvergen) {
        cout << "STATUS: Konvergen\n";
        cout << "Nilai akar: " << nilaiBerikutnya << endl;
        cout << "f1(x) = " << fungsiPertama(nilaiBerikutnya) << endl;
        cout << "f2(x) = " << fungsiKedua(nilaiBerikutnya) << endl;
        cout << "Error akhir: " << error << endl;
        cout << "Iterasi diperlukan: " << iterasi + 1 << endl;
    } else {
        cout << "STATUS: Tidak konvergen\n";
        cout << "Iterasi maksimum (" << batasIterasi << ") tercapai\n";
        cout << "Nilai terakhir: " << nilaiBerikutnya << endl;
        cout << "Error terakhir: " << error << endl;
    }
}

int main() {
    // Menjalankan program
    eksekusiMetodeIterasi();
    
    cout << "\nProgram telah selesai dijalankan." << endl;
    return 0;
}