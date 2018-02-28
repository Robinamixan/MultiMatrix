#include <iostream>
using namespace std;

int main() {
    clock_t start = clock();
    srand(time(0));
    const int size_matrix = 500;
    const int size_cell = 8;


    float** matr1 = new float*[size_matrix*size_matrix];
    for (int i = 0; i < size_matrix*size_matrix; ++i) {
        matr1[i] = new float [size_cell*size_cell];
        for (int j = 0; j < size_cell*size_cell; ++j) {
            matr1[i][j] = random()%4;
        }
    }

    float** matr2 = new float*[size_matrix*size_matrix];
    for (int i = 0; i < size_matrix*size_matrix; ++i) {
        matr2[i] = new float [size_cell*size_cell];
        for (int j = 0; j < size_cell*size_cell; ++j) {
            matr2[i][j] = random()%4;
        }
    }

    float** matr_res = new float*[size_matrix*size_matrix];
    for (int i = 0; i < size_matrix*size_matrix; ++i) {
        matr_res[i] = new float [size_cell*size_cell];
        for (int j = 0; j < size_cell*size_cell; ++j) {
            matr_res[i][j] = 0;
        }
    }

    for (int x = 0; x < size_matrix; ++x) {
        for (int y = 0; y < size_matrix; ++y) {
            for (int r = 0; r < size_matrix; ++r) {

                for (int i = 0; i < size_cell; ++i) {
                    for (int j = 0; j < size_cell; ++j) {
                        for (int m = 0; m < size_cell; ++m) {
                            matr_res[x * size_matrix + y][i * size_cell + j] += matr1[x * size_matrix + r][i * size_cell + m] * matr2[r * size_matrix + y][m * size_cell + j];
                        }
                    }
                }
            }
        }
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "runtime = " << seconds << endl;
    return 0;
}