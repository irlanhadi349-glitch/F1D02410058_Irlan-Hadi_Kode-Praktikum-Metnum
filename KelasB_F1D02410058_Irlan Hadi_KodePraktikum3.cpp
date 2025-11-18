#include <iostream>
#include <cmath>

void linearRegression(double x[], double y[], int n, double& a0, double& a1) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    a1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a0 = (sumY - a1 * sumX) / n;
}

void quadraticRegression(double x[], double y[], int n, double& a0, double& a1, double& a2) {
    double sumX = 0, sumY = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0, sumXY = 0, sumX2Y = 0;

    for (int i = 0; i < n; ++i) {
        double xi2 = x[i] * x[i];
        sumX += x[i];
        sumY += y[i];
        sumX2 += xi2;
        sumX3 += x[i] * xi2;
        sumX4 += xi2 * xi2;
        sumXY += x[i] * y[i];
        sumX2Y += xi2 * y[i];
    }

    double det = n * sumX2 * sumX4 + 2 * sumX * sumX2 * sumX3 - sumX * sumX * sumX4 - n * sumX3 * sumX3 - sumX2 * sumX2 * sumX2;
    a0 = (sumY * sumX2 * sumX4 + sumX * sumX3 * sumX2Y + sumX2 * sumXY * sumX3 - sumX2Y * sumX2 * sumX4 - sumX * sumX2Y * sumX3 - sumY * sumX3 * sumX2) / det;
    a1 = (n * sumX2Y * sumX4 + sumY * sumX * sumX4 + sumX2 * sumXY * sumX - sumX * sumX2Y * sumX4 - n * sumX * sumXY * sumX3 - sumY * sumX2 * sumX4) / det;
    a2 = (n * sumXY * sumX3 + sumX2Y * sumX * sumX3 + sumX * sumX2 * sumY - sumY * sumX2 * sumX3 - n * sumX * sumXY * sumX2 - sumX * sumX2Y * sumX) / det;
}

void exponentialRegression(double x[], double y[], int n, double& a, double& b) {
    double sumlnX = 0, sumlnY = 0, sumlnXY = 0, sumlnX2 = 0;

    for (int i = 0; i < n; ++i) {
        sumlnX += log(x[i]);
        sumlnY += log(y[i]);
        sumlnXY += log(x[i]) * log(y[i]);
        sumlnX2 += log(x[i]) * log(x[i]);
    }

    b = (n * sumlnXY - sumlnX * sumlnY) / (n * sumlnX2 - sumlnX * sumlnX);
    a = exp((sumlnY - b * sumlnX) / n);
}

double dividedDifference(double x[], double y[], int n, double xi) {
    double result = y[0];
    double F[8][8];
    
    for (int i = 0; i < n; i++) {
        F[i][0] = y[i];
    }
    
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            F[i][j] = (F[i+1][j-1] - F[i][j-1]) / (x[i+j] - x[i]);
        }
    }
    
    double product;
    for (int i = 1; i < n; i++) {
        product = 1;
        for (int j = 0; j < i; j++) {
            product *= (xi - x[j]);
        }
        result += product * F[0][i];
    }
    
    return result;
}

int main() {
    const int n = 8;
    double x[n] = {1, 2, 3, 4, 5, 6, 7, 8};
    double y[n] = {1.5577, 1.2131, 0.9447, 0.7358, 0.5730, 0.4462, 0.3476, 0.2706};

    double a0_linear, a1_linear;
    linearRegression(x, y, n, a0_linear, a1_linear);
    std::cout << "Regresi Linier: y = " << a0_linear << " + " << a1_linear << "x\n";

    double a0_quadratic, a1_quadratic, a2_quadratic;
    quadraticRegression(x, y, n, a0_quadratic, a1_quadratic, a2_quadratic);
    std::cout << "Regresi Kuadratik: y = " << a0_quadratic << "x^2 + " << a1_quadratic << "x + " << a2_quadratic << "\n";

    double a_exponential, b_exponential;
    exponentialRegression(x, y, n, a_exponential, b_exponential);
    std::cout << "Regresi Eksponensial: y = " << a_exponential << " * x^" << b_exponential << "\n";

    double xi = 4.5;
    double interpolatedValue = dividedDifference(x, y, n, xi);
    std::cout << "Interpolasi Newton pada x = 4.5: " << interpolatedValue << "\n";

    return 0;
}