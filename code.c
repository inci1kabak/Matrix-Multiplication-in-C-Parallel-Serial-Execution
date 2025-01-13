#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Matrisleri dosyadan okuma fonksiyonu
void read_matrix(const char *filename, int *rows, int *cols, double ***matrix)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Dosya açilamadı");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", rows, cols);
    *matrix = (double **)malloc(*rows * sizeof(double *));
    for (int i = 0; i < *rows; i++)
    {
        (*matrix)[i] = (double *)malloc(*cols * sizeof(double));
        for (int j = 0; j < *cols; j++)
        {
            fscanf(file, "%lf", &((*matrix)[i][j]));
        }
    }
    fclose(file);
}

// Matris çarpımı seri fonksiyon
void multiply_serial(double **a, int a_rows, int a_cols, double **b, int b_rows, int b_cols, double ***result)
{
    *result = (double **)malloc(a_rows * sizeof(double *));
    for (int i = 0; i < a_rows; i++)
    {
        (*result)[i] = (double *)calloc(b_cols, sizeof(double));
        for (int j = 0; j < b_cols; j++)
        {
            for (int k = 0; k < a_cols; k++)
            {
                (*result)[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Matris çarpımı paralel fonksiyon
void multiply_parallel(double **a, int a_rows, int a_cols, double **b, int b_rows, int b_cols, double ***result)
{
    *result = (double **)malloc(a_rows * sizeof(double *));
#pragma omp parallel for
    for (int i = 0; i < a_rows; i++)
    {
        (*result)[i] = (double *)calloc(b_cols, sizeof(double));
        for (int j = 0; j < b_cols; j++)
        {
            for (int k = 0; k < a_cols; k++)
            {
                (*result)[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Matris sonucu dosyaya yazma fonksiyonu
void write_matrix(const char *filename, double **matrix, int rows, int cols)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Dosya açilamadı");
        exit(EXIT_FAILURE);
    }

    // Satır ve sütun bilgisini yazma
    fprintf(file, "%d %d\n", rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(file, "%.2lf ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Bellek temizleme fonksiyonu
void free_matrix(double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Ana fonksiyon
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Kullanim: %s matrix_a.txt matrix_b.txt sonuclar.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int a_rows, a_cols, b_rows, b_cols;
    double **matrix_a, **matrix_b, **result_parallel, **result_serial;

    // Matrisleri okuma
    read_matrix(argv[1], &a_rows, &a_cols, &matrix_a);
    read_matrix(argv[2], &b_rows, &b_cols, &matrix_b);

    if (a_cols != b_rows)
    {
        fprintf(stderr, "Matris boyutlari çarpim için uyumsuz.\n");
        free_matrix(matrix_a, a_rows);
        free_matrix(matrix_b, b_rows);
        exit(EXIT_FAILURE);
    }

    // Seri matris çarpımı ve süre ölçümü
    clock_t start_serial = clock();
    multiply_serial(matrix_a, a_rows, a_cols, matrix_b, b_rows, b_cols, &result_serial);
    clock_t end_serial = clock();
    double serial_time = (double)(end_serial - start_serial) / CLOCKS_PER_SEC;

    // Paralel matris çarpımı ve süre ölçümü
    double start_parallel = omp_get_wtime();
    multiply_parallel(matrix_a, a_rows, a_cols, matrix_b, b_rows, b_cols, &result_parallel);
    double end_parallel = omp_get_wtime();
    double parallel_time = end_parallel - start_parallel;

    // Paralel sonucu dosyaya yazma
    write_matrix(argv[3], result_parallel, a_rows, b_cols);

    // Süreleri karşılaştırma
    printf("Seri Zaman: %.6f saniye\n", serial_time);
    printf("Paralel Zaman: %.6f saniye\n", parallel_time);

    // Belleği temizleme
    free_matrix(matrix_a, a_rows);
    free_matrix(matrix_b, b_rows);
    free_matrix(result_serial, a_rows);
    free_matrix(result_parallel, a_rows);

    return 0;
}
