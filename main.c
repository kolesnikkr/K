#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#define MAX_SIZE 10


static void Menu() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    printf("Операції над матрицями:\n");
    printf("1.Обернена матриця\n");
    printf("2.Транспонування матриці\n");
    printf("3.Множення на скаляр\n");
    printf("4.Додавання матриць\n");
    printf("5.Віднімання матриць\n");
    printf("6.Множення матриць\n");
    printf("7.Визначник\n");
    printf("0. Завершення роботи\n");
    printf("Виберіть операцію для виконання:\n");
}

static void inputMatrix(int rows, int cols, double matrix[MAX_SIZE][MAX_SIZE]) {
    printf("Введіть елементи матриці (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Елемент [%d][%d]: ", i + 1, j + 1);
            while (scanf_s("%lf", &matrix[i][j]) != 1) {
                printf("Введіть дійсне число: ");
                while (getchar() != '\n');
            }
        }
    }
}

static void printMatrix(int rows, int cols, double matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%7.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

static double determinant(int n, double matrix[MAX_SIZE][MAX_SIZE]) {
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    double temp[MAX_SIZE][MAX_SIZE];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        int sub_i = 0;
        for (int i = 1; i < n; i++) {
            int sub_j = 0;
            for (int j = 0; j < n; j++) {
                if (j == f)
                    continue;
                temp[sub_i][sub_j++] = matrix[i][j];
            }
            sub_i++;
        }
        det += sign * matrix[0][f] * determinant(n - 1, temp);
        sign = -sign;
    }
    return det;
}

static int inverseMatrix(int n, double matrix[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE]) {
    double det = determinant(n, matrix);
    if (fabs(det) < 1e-9) {
        printf("Матриця не має оберненої (визначник = 0).\n");
        return 0;
    }

    double temp[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sub_i = 0;
            for (int k = 0; k < n; k++) {
                if (k == i)
                    continue;
                int sub_j = 0;
                for (int l = 0; l < n; l++) {
                    if (l == j)
                        continue;
                    temp[sub_i][sub_j++] = matrix[k][l];
                }
                sub_i++;
            }
            result[j][i] = (pow(-1, i + j) * determinant(n - 1, temp)) / det;
        }
    }
    return 1;
}

static void transposeMatrix(int rows, int cols, double matrix[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

static void multiplyMatrixByScalar(int rows, int cols, double matrix[MAX_SIZE][MAX_SIZE], double scalar, double result[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

static void addMatrices(int rows, int cols, double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

static void subtractMatrices(int rows, int cols, double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

static void multiplyMatrices(int rowsA, int colsA, double A[MAX_SIZE][MAX_SIZE], int rowsB, int colsB, double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE]) {
    if (colsA != rowsB) {
        printf("Множення неможливе (кількість стовпців A має дорівнювати кількості рядків B).");
        return;
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


int main() {
    int choice, rowsA, colsA, rowsB, colsB;
    double A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];

    do {
        Menu();

        if (scanf_s("%d", &choice) != 1 || choice < 0 || choice > 7) {
            printf(" Введіть число від 0 до 7.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("Введіть розмір квадратної матриці (n x n): ");
            while (scanf_s("%d", &rowsA) != 1 || rowsA <= 0 || rowsA > MAX_SIZE) {
                printf("Введіть ціле число від 1 до %d: ", MAX_SIZE);
                while (getchar() != '\n');
            }
            colsA = rowsA;
            inputMatrix(rowsA, colsA, A);
            if (inverseMatrix(rowsA, A, result)) {
                printf("Обернена матриця:\n");
                printMatrix(rowsA, colsA, result);
            }
            break;
        case 2:
            printf("Введіть розмір матриці (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            transposeMatrix(rowsA, colsA, A, result);
            printf("Транспонована матриця:\n");
            printMatrix(colsA, rowsA, result);
            break;
        case 3:
            printf("Введіть розмір матриці (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            double scalar;
            printf("Введіть скаляр: ");
            while (scanf_s("%lf", &scalar) != 1) {
                printf("Введіть дійсне число: ");
                while (getchar() != '\n');
            }
            multiplyMatrixByScalar(rowsA, colsA, A, scalar, result);
            printf("Результат множення на скаляр:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 4:
            printf("Введіть розмір матриць (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            inputMatrix(rowsA, colsA, B);
            addMatrices(rowsA, colsA, A, B, result);
            printf("Результат додавання:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 5:
            printf("Введіть розмір матриць (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            inputMatrix(rowsA, colsA, B);
            subtractMatrices(rowsA, colsA, A, B, result);
            printf("Результат віднімання:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 6:
            
            printf("Введіть розмір першої матриці (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            printf("Введіть розмір другої матриці (рядки стовпці): ");
            while (scanf_s("%d %d", &rowsB, &colsB) != 2 || rowsB <= 0 || colsB <= 0 || rowsB > MAX_SIZE || colsB > MAX_SIZE) {
                printf("Введіть два додатних числа: ");
                while (getchar() != '\n');
            }
            if (colsA != rowsB) {
                printf("Множення неможливе (кількість стовпців першої матриці має дорівнювати кількості рядків другої).\n");
                break;
            }
            inputMatrix(rowsB, colsB, B);
            multiplyMatrices(rowsA, colsA, A, rowsB, colsB, B, result);
            printf("Результат множення:\n");
            printMatrix(rowsA, colsB, result);
            break;
        case 7:
            printf("Введіть розмір квадратної матриці (n x n): ");
            while (scanf_s("%d", &rowsA) != 1 || rowsA <= 0 || rowsA > MAX_SIZE) {
                printf("Введіть ціле число від 1 до %d: ", MAX_SIZE);
                while (getchar() != '\n');
            }
            colsA = rowsA;
            inputMatrix(rowsA, colsA, A);
            double det = determinant(rowsA, A);
            printf("Визначник матриці: %.2lf\n", det);
            break;
        case 0:
            printf("Завершення роботи.\n");
            break;
        default:
            printf("Невірний вибір.\n");
        }
    } while (choice != 0);

    return 0;
}