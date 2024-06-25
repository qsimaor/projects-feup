#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <papi.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#define SYSTEMTIME clock_t

void OnMult(int m_ar, int m_br)
{

  SYSTEMTIME Time1, Time2;
  char st[100];
  double temp;
  int i, j, k;
  double *pha, *phb, *phc;

  pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

  for (i = 0; i < m_ar; i++)
    for (j = 0; j < m_ar; j++)
      pha[i * m_ar + j] = (double)1.0;

  for (i = 0; i < m_br; i++)
    for (j = 0; j < m_br; j++)
      phb[i * m_br + j] = (double)(i + 1);

  Time1 = clock();

  for (i = 0; i < m_ar; i++)
  {
    for (j = 0; j < m_br; j++)
    {
      temp = 0;
      for (k = 0; k < m_ar; k++)
      {
        temp += pha[i * m_ar + k] * phb[k * m_br + j];
      }
      phc[i * m_ar + j] = temp;
    }
  }

  Time2 = clock();
  sprintf(st, "Time: %3.3f seconds\n",
          (double)(Time2 - Time1) / CLOCKS_PER_SEC);
  cout << st;

  // display 10 elements of the result matrix tto verify correctness
  cout << "Result matrix: " << endl;
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < min(10, m_br); j++)
      cout << phc[j] << " ";
  }
  cout << endl;

  free(pha);
  free(phb);
  free(phc);
}

void OnMultLine(int m_ar, int m_br)
{

  SYSTEMTIME Time1, Time2;
  char st[100];
  int i, j, k;
  double *pha, *phb, *phc;

  // Alocação de memória
  pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

  // Matriz A
  for (i = 0; i < m_ar; i++)
    for (j = 0; j < m_ar; j++)
      pha[i * m_ar + j] = (double)1.0;

  // Matriz B
  for (i = 0; i < m_br; i++)
    for (j = 0; j < m_br; j++)
      phb[i * m_br + j] = (double)(i + 1);

  // Matriz C
  for (i = 0; i < m_br; i++)
    for (j = 0; j < m_br; j++)
      phc[i * m_br + j] = (double)0.0;

  // Início do tempo
  Time1 = clock();

  // Multiplicação das matrizes
  for (i = 0; i < m_ar; i++)
  {
    for (k = 0; k < m_ar; k++)
    {
      for (j = 0; j < m_br; j++)
      {
        phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
      }
    }
  }

  // Fim do tempo
  Time2 = clock();

  // Cálculo do tempo
  sprintf(st, "Time: %3.3f seconds\n",
          (double)(Time2 - Time1) / CLOCKS_PER_SEC);
  cout << st;

  // display 10 elements of the result matrix tto verify correctness
  cout << "Result matrix: ";
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < min(10, m_br); j++)
      cout << phc[j] << " ";
  }
  cout << endl;

  // Libertação de memória
  free(pha);
  free(phb);
  free(phc);
}

// add code here for block x block matriz multiplication
void OnMultBlock(int m_ar, int m_br, int bkSize)
{

  SYSTEMTIME Time1, Time2;
  char st[100];
  int i, j, k, bi, bj, bk, ii, jj, kk;
  double *pha, *phb, *phc;

  // Alocação de memória
  pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
  phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

  // Matriz A
  for (i = 0; i < m_ar; i++)
    for (j = 0; j < m_ar; j++)
      pha[i * m_ar + j] = (double)1.0;

  // Matriz B
  for (i = 0; i < m_br; i++)
    for (j = 0; j < m_br; j++)
      phb[i * m_br + j] = (double)(i + 1);

  // Matriz C
  for (i = 0; i < m_br; i++)
    for (j = 0; j < m_br; j++)
      phc[i * m_br + j] = (double)0.0;

  // Início do tempo
  Time1 = clock();
  for (bi = 0; bi < m_ar; bi += bkSize)
  {
    for (bk = 0; bk < m_ar; bk += bkSize)
    {
      for (bj = 0; bj < m_ar; bj += bkSize)
      {
        // Perform mutiplication on blocks
        for (ii = bi; ii < bi + bkSize; ii++)
        {
          for (kk = bk; kk < bk + bkSize; kk++)
          {
            for (jj = bj; jj < bj + bkSize; jj++)
            {
              phc[m_ar * ii + jj] += pha[m_ar * ii + kk] * phb[m_ar * kk + jj];
            }
          }
        }
      }
    }
  }

  // Fim do tempo
  Time2 = clock();

  // Cálculo do tempo
  sprintf(st, "Time: %3.3f seconds\n",
          (double)(Time2 - Time1) / CLOCKS_PER_SEC);
  cout << st;

  // display 10 elements of the result matrix tto verify correctness
  cout << "Result matrix: ";
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < min(10, m_br); j++)
      cout << phc[j] << " ";
  }
  cout << endl;

  // Libertação de memória
  free(pha);
  free(phb);
  free(phc);
}

void handle_error(int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi()
{
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0)
  {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0)
    handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

int main(int argc, char *argv[])
{

  char c;
  int lin, col, blockSize;
  int op;

  int EventSet = PAPI_NULL;
  long long values[3];
  int ret;

  ret = PAPI_library_init(PAPI_VER_CURRENT);
  if (ret != PAPI_VER_CURRENT)
    std::cout << "FAIL" << endl;

  ret = PAPI_create_eventset(&EventSet);
  if (ret != PAPI_OK)
    cout << "ERROR: create eventset" << endl;

  ret = PAPI_add_event(EventSet, PAPI_L1_DCM);
  if (ret != PAPI_OK)
    cout << "ERROR: PAPI_L1_DCM" << endl;

  ret = PAPI_add_event(EventSet, PAPI_L2_DCM);
  if (ret != PAPI_OK)
    cout << "ERROR: PAPI_L2_DCM" << endl;

  ret = PAPI_add_event(EventSet, PAPI_DP_OPS);
  if (ret != PAPI_OK)
    cout << "ERROR: PAPI_DP_OPS" << endl;

  op = 1;
  do
  {
    cout << endl
         << "1. Multiplication" << endl;
    cout << "2. Line Multiplication" << endl;
    cout << "3. Block Multiplication" << endl;
    cout << "Selection?: ";
    cin >> op;
    if (op == 0)
      break;
    printf("Dimensions: lins=cols ? ");
    cin >> lin;
    col = lin;

    // Start counting
    ret = PAPI_start(EventSet);
    if (ret != PAPI_OK)
      cout << "ERROR: Start PAPI" << endl;

    switch (op)
    {
    case 1:
      OnMult(lin, col);
      break;
    case 2:
      OnMultLine(lin, col);
      break;
    case 3:
      cout << "Block Size? ";
      cin >> blockSize;
      OnMultBlock(lin, col, blockSize);
      break;
    }

    ret = PAPI_stop(EventSet, values);
    if (ret != PAPI_OK)
      cout << "ERROR: Stop PAPI" << endl;
    printf("L1 DCM: %lld \n", values[0]);
    printf("L2 DCM: %lld \n", values[1]);
    printf("Number of FLOP: %lld \n", values[2]);

    // write to results file in format size, run1, run2, run3, run4, run5, average
    FILE *f = fopen("results.txt", "a");
    if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

    fprintf(f, "%d, %lld, %lld, %lld, %lld, %lld, %lld\n", lin, values[0],
            values[1], values[2], values[3], values[4],
            (values[0] + values[1] + values[2] + values[3] + values[4]) / 5);

    ret = PAPI_reset(EventSet);
    if (ret != PAPI_OK)
      std::cout << "FAIL reset" << endl;

  } while (op != 0);

  ret = PAPI_remove_event(EventSet, PAPI_L1_DCM);
  if (ret != PAPI_OK)
    std::cout << "FAIL remove event" << endl;

  ret = PAPI_remove_event(EventSet, PAPI_L2_DCM);
  if (ret != PAPI_OK)
    std::cout << "FAIL remove event" << endl;

  ret = PAPI_remove_event(EventSet, PAPI_DP_OPS);
  if (ret != PAPI_OK)
    std::cout << "FAIL remove event" << endl;

  ret = PAPI_destroy_eventset(&EventSet);
  if (ret != PAPI_OK)
    std::cout << "FAIL destroy" << endl;
}
