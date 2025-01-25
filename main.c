#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#define MAX_SIZE 10


static void Menu() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    printf("�������� ��� ���������:\n");
    printf("1.�������� �������\n");
    printf("2.�������������� �������\n");
    printf("3.�������� �� ������\n");
    printf("4.��������� �������\n");
    printf("5.³������� �������\n");
    printf("6.�������� �������\n");
    printf("7.���������\n");
    printf("0. ���������� ������\n");
    printf("������� �������� ��� ���������:\n");
}

static void inputMatrix(int rows, int cols, double matrix[MAX_SIZE][MAX_SIZE]) {
    printf("������ �������� ������� (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("������� [%d][%d]: ", i + 1, j + 1);
            while (scanf_s("%lf", &matrix[i][j]) != 1) {
                printf("������ ����� �����: ");
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
        printf("������� �� �� �������� (��������� = 0).\n");
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
        printf("�������� ��������� (������� �������� A �� ���������� ������� ����� B).");
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
            printf(" ������ ����� �� 0 �� 7.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("������ ����� ��������� ������� (n x n): ");
            while (scanf_s("%d", &rowsA) != 1 || rowsA <= 0 || rowsA > MAX_SIZE) {
                printf("������ ���� ����� �� 1 �� %d: ", MAX_SIZE);
                while (getchar() != '\n');
            }
            colsA = rowsA;
            inputMatrix(rowsA, colsA, A);
            if (inverseMatrix(rowsA, A, result)) {
                printf("�������� �������:\n");
                printMatrix(rowsA, colsA, result);
            }
            break;
        case 2:
            printf("������ ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            transposeMatrix(rowsA, colsA, A, result);
            printf("������������� �������:\n");
            printMatrix(colsA, rowsA, result);
            break;
        case 3:
            printf("������ ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            double scalar;
            printf("������ ������: ");
            while (scanf_s("%lf", &scalar) != 1) {
                printf("������ ����� �����: ");
                while (getchar() != '\n');
            }
            multiplyMatrixByScalar(rowsA, colsA, A, scalar, result);
            printf("��������� �������� �� ������:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 4:
            printf("������ ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            inputMatrix(rowsA, colsA, B);
            addMatrices(rowsA, colsA, A, B, result);
            printf("��������� ���������:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 5:
            printf("������ ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            inputMatrix(rowsA, colsA, B);
            subtractMatrices(rowsA, colsA, A, B, result);
            printf("��������� ��������:\n");
            printMatrix(rowsA, colsA, result);
            break;
        case 6:
            
            printf("������ ����� ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0 || rowsA > MAX_SIZE || colsA > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            inputMatrix(rowsA, colsA, A);
            printf("������ ����� ����� ������� (����� �������): ");
            while (scanf_s("%d %d", &rowsB, &colsB) != 2 || rowsB <= 0 || colsB <= 0 || rowsB > MAX_SIZE || colsB > MAX_SIZE) {
                printf("������ ��� �������� �����: ");
                while (getchar() != '\n');
            }
            if (colsA != rowsB) {
                printf("�������� ��������� (������� �������� ����� ������� �� ���������� ������� ����� �����).\n");
                break;
            }
            inputMatrix(rowsB, colsB, B);
            multiplyMatrices(rowsA, colsA, A, rowsB, colsB, B, result);
            printf("��������� ��������:\n");
            printMatrix(rowsA, colsB, result);
            break;
        case 7:
            printf("������ ����� ��������� ������� (n x n): ");
            while (scanf_s("%d", &rowsA) != 1 || rowsA <= 0 || rowsA > MAX_SIZE) {
                printf("������ ���� ����� �� 1 �� %d: ", MAX_SIZE);
                while (getchar() != '\n');
            }
            colsA = rowsA;
            inputMatrix(rowsA, colsA, A);
            double det = determinant(rowsA, A);
            printf("��������� �������: %.2lf\n", det);
            break;
        case 0:
            printf("���������� ������.\n");
            break;
        default:
            printf("������� ����.\n");
        }
    } while (choice != 0);

    return 0;
}