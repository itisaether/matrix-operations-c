#include <stdio.h>
#include <stdlib.h>

int countNonZeroRows(int**, int, int);
int maxRepeatedNumber(int**, int, int);
void swapRows(int**, int, int);
void replaceMaxMin(int**, int, int);

int main() {
    int rows, columns;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &columns);
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(columns * sizeof(int));
        for (int j = 0; j < columns; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nOriginal matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    int countNonZero = countNonZeroRows(matrix, rows, columns);
    printf("\nNumber of rows without zero elements: %d\n", countNonZero);

    int maxRepeated = maxRepeatedNumber(matrix, rows, columns);
    printf("\nMax repeated number: %d\n", maxRepeated);

    swapRows(matrix, rows, columns);
    printf("\nMatrix after swapping(3):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    replaceMaxMin(matrix, rows, columns);
    printf("\nMatrix after replacing(4):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

int countNonZeroRows(int** matrix, int rows, int columns) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        int hasZero = 0;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                hasZero = 1;
                break;
            }
        }
        if (!hasZero) {
            count++;
        }
    }
    return count;
}

int maxRepeatedNumber(int** matrix, int rows, int columns) {

    int* elements = (int*)malloc(rows * columns * sizeof(int));
    int elementIndex = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            elements[elementIndex] = matrix[r][c];
            elementIndex++;
        }
    }


    int* refactorElements = (int*)malloc(rows * columns * sizeof(int));
    int refactorElementsIndex = 0;

    for (int i = 0; i < rows * columns; i++) {
        int currentCount = 0;
        for (int g = 0; g < rows * columns; g++) {
            if (elements[i] == elements[g]) {
                currentCount++;
            }
        }

        if (currentCount > 1) {
            refactorElements[refactorElementsIndex] = elements[i];
            refactorElementsIndex++;
        }
    }

    if (refactorElementsIndex > 0) {
        int maxElement = refactorElements[0];
        for (int i = 1; i < refactorElementsIndex; i++) {
            if (maxElement < refactorElements[i]) {
                maxElement = refactorElements[i];
            }
        }

        return maxElement;
    }
    else {
        printf("There isn't any element repeated more than once, so the first item of the matrix is returned.\n");
        return elements[0];
    }
}

void swapRows(int** matrix, int rows, int columns) {
    int maxRowIndex = 0;
    int maxDiagonal = matrix[0][0];

    for (int r = 0; r < rows; r++) {
        if (maxDiagonal < matrix[r][r]) {
            maxDiagonal = matrix[r][r];
            maxRowIndex = r;
        }
    }

    int k = 0;
    printf("Enter the row index (0 to %d) to swap with the row having the maximum diagonal element: ", rows - 1);
    scanf("%d", &k);

    if (k >= 0 && k < rows) {
        int* temp = matrix[k];
        matrix[k] = matrix[maxRowIndex];
        matrix[maxRowIndex] = temp;
    }
    else {
        printf("Invalid row index. Please try again.\n");
        swapRows(matrix, rows, columns);
    }

}

void replaceMaxMin(int** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        int maxIndex = 0;
        int minIndex = 0;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] > matrix[i][maxIndex]) {
                maxIndex = j;
            }
            if (matrix[i][j] < matrix[i][minIndex]) {
                minIndex = j;
            }
        }
        int temp = matrix[i][minIndex];
        matrix[i][minIndex] = matrix[i][0];
        matrix[i][0] = temp;
        temp = matrix[i][maxIndex];
        matrix[i][maxIndex] = matrix[i][columns - 1];
        matrix[i][columns - 1] = temp;
    }
}
