#include <iostream>
#include <emmintrin.h>
#include <x86intrin.h>

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

//    float** matr_res1 = new float*[size_matrix*size_matrix];
//    for (int i = 0; i < size_matrix*size_matrix; ++i) {
//        matr_res1[i] = new float [size_cell*size_cell];
//        for (int j = 0; j < size_cell*size_cell; ++j) {
//            matr_res1[i][j] = 0;
//        }
//    }

    float mul_buff [4];
    float column_buff [4];

    for (int x = 0; x < size_matrix; ++x) {
        for (int y = 0; y < size_matrix; ++y) {
            for (int r = 0; r < size_matrix; ++r) {

                for (int i = 0; i < size_cell; ++i) {
                    for (int j = 0; j < size_cell; ++j) {
                        __m128 buffer = _mm_setzero_ps();
                        for (int m = 0; m< size_cell; m+=4 ) {
                            for (int l = 0; l < 4; l++) {
                                column_buff[l] = matr2[r * size_matrix + y][(m+l) * size_cell + j];
                            }
//                            __m128 a = _mm_load_ps(&matr1[r * size_matrix + y][m * size_cell + j]);
                            __m128 a = _mm_load_ps(&column_buff[0]);
                            __m128 b = _mm_load_ps(&matr1[x * size_matrix + r][i * size_cell + m]);
                            __m128 mul = _mm_mul_ps(a, b);
                            buffer = _mm_add_ps(mul, buffer);
                        }
                        buffer = _mm_add_ps(buffer, buffer);
                        buffer = _mm_add_ps(buffer, buffer);
                        _mm_store_ss(&matr_res[x * size_matrix + y][i * size_cell + j], buffer);
//                         += mul_buff[0] + mul_buff[1] + mul_buff[2] + mul_buff[3];
                    }
                }

            }
        }
    }

//    for (int x = 0; x < size_matrix; ++x) {
//        for (int y = 0; y < size_matrix; ++y) {
//            for (int r = 0; r < size_matrix; ++r) {
//
//                for (int i = 0; i < size_cell; i++) {
//                    for (int j = 0; j < size_cell; j++) {
//                        for (int m = 0; m< size_cell; m++) {
//                            matr_res1[x * size_matrix + y][i * size_cell + j] += matr1[x * size_matrix + r][i * size_cell + m] * matr2[r * size_matrix + y][m * size_cell + j];
//                        }
//                    }
//                }
//            }
//        }
//    }


//    for (int j = 0; j < size_cell; ++j) {
//        __m128 buffer = _mm_setzero_ps();
//        for (int m = 0; m< size_cell; ++m) {
//            __m128 a = _mm_load_ss(&matr2[r * size_matrix + y][m * size_cell + j]);
//            __m128 b = _mm_load_ss(&matr1[x * size_matrix + r][i * size_cell + m]);
//            buffer = _mm_add_ps(_mm_mul_ss(a, b), buffer);
//        }
//        _mm_store_ss(&matr_res[x * size_matrix + y][i * size_cell + j], buffer);
//    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "runtime = " << seconds << endl;
    return 0;
}
