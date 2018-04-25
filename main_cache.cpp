#include <iostream>
#include <emmintrin.h>
#include <unistd.h>
#include <math.h>

using namespace std;

int main() {
    clock_t start = clock();
    srand(time(0));

    int cache_size = sysconf(_SC_LEVEL3_CACHE_SIZE );
    int block_size = (cache_size / 3) * 0.8;
    int elem_amount = block_size / 4;
    int size_cell = (int)(sqrt(elem_amount) / 64) * 64;

//    int size_cell = 100;

    const int count_columns = 4;

    const int size_matr = size_cell * count_columns;

    float** matr1 = new float*[size_matr];
    float** matr2 = new float*[size_matr];
    float** matr_res = new float*[size_matr];
    float** matr_res1 = new float*[size_matr];

    for (int i = 0; i < size_matr; ++i) {

        matr1[i] = new float [size_matr];
        matr2[i] = new float [size_matr];
        matr_res[i] = new float [size_matr];
        matr_res1[i] = new float [size_matr];

        for (int j = 0; j < size_matr; ++j) {
            matr1[i][j] = random()%4;
            matr2[i][j] = random()%4;
            matr_res[i][j] = 0;
            matr_res1[i][j] = 0;
        }
    }

    for (int x = 0; x < count_columns; ++x) {
        for (int r = 0; r < count_columns; ++r) {
            for (int y = 0; y < count_columns; ++y) {

                for (int i = 0; i < size_cell; i++) {
                    for (int j = 0; j < size_cell; j++) {
                        for (int m = 0; m < size_cell; m++) {

                            int matr1_x = i + size_cell * x;
                            int matr_m = m + size_cell* r;
                            int matr2_y = j + size_cell * y;

                            matr_res[matr1_x][matr2_y] += matr1[matr1_x][matr_m] * matr2[matr_m][matr2_y];
                        }
                    }
                }
            }
        }
    }

//    for (int i = 0; i < size_matr; i++) {
//        for (int j = 0; j < size_matr; j++) {
//            for (int m = 0; m < size_matr; m++) {
//                matr_res1[i][j] += matr1[i][m] * matr2[m][j];
//            }
//        }
//    }


    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "runtime = " << seconds << endl;
    return 0;
}
