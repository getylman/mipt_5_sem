#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"

double func(double arg) { return 4.0 / (1 + arg * arg); }

void CalcIntegral(int argc, char **argv, unsigned int num_of_segments) {
  int rank, size;
  double delta_x = 1.0 / num_of_segments;
  unsigned int num_dflt = 0;  // количество отрезков для p = 1...(p-1)
  unsigned int num_last = 0;  // количество отрезков для последнего процессора
  double integral_res = 0;    // значение интеграла
  double integral_res_solo = 0;  // значение интеграла через мастер процесс

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  num_dflt = (num_of_segments + size - 1) / size;
  num_last = num_dflt - (1ll * num_dflt * size - num_of_segments);

  if (rank == 0) {
    double *intrgl_res_of_procs;
    intrgl_res_of_procs =  // reinterpret_cast<decltype(intrgl_res_of_procs)>(::operator
                           // new(size * sizeof(double)));
        (double *)calloc(
            size,
            sizeof(
                double));  // массив для хранения значений на каждый процессор

    for (unsigned int i = 1; i < size; ++i) {
      MPI_Send(intrgl_res_of_procs + i, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
    for (unsigned int i = 0; i < num_dflt; ++i) {
      intrgl_res_of_procs[rank] += func(delta_x * i + rank * num_dflt) +
                                   func(delta_x * (i + 1) + rank * num_dflt);
    }
    // посчитали свою часть
    intrgl_res_of_procs[rank] /= 2;
    intrgl_res_of_procs[rank] *= delta_x;
    // просчет интеграла
    printf("i = %u\tIi = %f\n", rank, intrgl_res_of_procs[rank]);
    integral_res += intrgl_res_of_procs[0];
    for (unsigned i = 1; i < size; ++i) {
      MPI_Recv(intrgl_res_of_procs + i, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      integral_res += intrgl_res_of_procs[i];
    }
    // суммирование всех частей
    printf("I = %f\n", integral_res);
    // вывод итогого интеграла
    free(intrgl_res_of_procs);
    // освобождение памяти
    for (unsigned int i = 0; i < num_of_segments; ++i) {
      integral_res_solo += func(delta_x * i) + func(delta_x * (i + 1));
    }
    integral_res_solo /= 2;
    integral_res_solo *= delta_x;
    // посчитали интеграл чисто мастер процессом
    printf("I0 = %f\n", integral_res_solo);
  } else if (rank > 0 && rank < size - 1) {
    double cur_integral = 0;
    MPI_Recv(&cur_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    cur_integral = 0;
    for (unsigned int i = 0; i < num_dflt; ++i) {
      cur_integral += func(delta_x * i + rank * num_dflt * delta_x) +
                      func(delta_x * (i + 1) + rank * num_dflt * delta_x);
    }
    cur_integral /= 2;
    cur_integral *= delta_x;
    // просчет интеграла
    printf("i = %u\tIi = %f\n", rank, cur_integral);
    MPI_Send(&cur_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  } else {
    double cur_integral = 0;
    MPI_Recv(&cur_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    cur_integral = 0;
    for (unsigned int i = 0; i < num_last; ++i) {
      cur_integral += func(delta_x * i + rank * num_dflt * delta_x) +
                      func(delta_x * (i + 1) + rank * num_dflt * delta_x);
    }
    cur_integral /= 2;
    cur_integral *= delta_x;
    // просчет интеграла
    printf("i = %u\tIi = %f\n", rank, cur_integral);
    MPI_Send(&cur_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}

int main(int argc, char **argv) {
  unsigned int num_of_segments = 100500;
  CalcIntegral(argc, argv, num_of_segments);
  return 0;
}