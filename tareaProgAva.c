#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func1(void *arg);
void *thread_func2(void *arg);
void *thread_func3(void *arg);
int input[][4] = {{1,2,3,4},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
int productoPuntoi[4][4];
int SumaAA[4][4];
int C[4][4];
     
int main()
{
  int res;
  pthread_t a_thread;
  pthread_t b_thread;
  pthread_t c_thread;
  void *thread_result;

  res = pthread_create(&a_thread, NULL, thread_func1, NULL);
  if (res != 0) 
  {
      perror("Thread creation failed");
      exit(EXIT_FAILURE);
  }

  res = pthread_create(&b_thread, NULL, thread_func3, NULL);
  if (res != 0) 
  {
      perror("Thread creation failed");
      exit(EXIT_FAILURE);
  }

  res = pthread_join(a_thread, &thread_result);
  if (res != 0) {
      perror("Thread join failed");
      exit(EXIT_FAILURE);
  } 
  res = pthread_join(b_thread, &thread_result);
  if (res != 0) {
      perror("Thread join failed");
      exit(EXIT_FAILURE);
  }
  printf("Thread joined\n");

  res = pthread_create(&c_thread, NULL, thread_func2, NULL);
  if (res != 0) 
  {
      perror("Thread creation failed");
      exit(EXIT_FAILURE);
  }

  res = pthread_join(c_thread, &thread_result);
  if (res != 0) {
      perror("Thread join failed");
      exit(EXIT_FAILURE);
  }
   
  for (int c = 0; c < 4; c++) {
      for (int d = 0 ; d < 4; d++) {
         printf("%d\t", C[c][d]);
      }
      printf("\n");
  }
  return 0;
}

void *thread_func1(void *arg)
{
  int sum =0;
  for (int i = 0; i < 4; i++) 
  {
    for (int j = 0; j < 4; j++) 
    {
      for (int k = 0; k < 4; k++) 
      {
        sum = sum + input[i][k]*input[k][j];
      }
      productoPuntoi[i][j] = sum;
      sum = 0;
    }
  }
  pthread_exit(NULL);
}

void *thread_func2(void *arg)
{
  for (int c = 0; c < 4; c++) 
  {
    for (int d = 0 ; d < 4; d++) 
    {
      C[c][d] = productoPuntoi[c][d] - SumaAA[c][d];
    }
  }
  pthread_exit(NULL);
}

void *thread_func3(void *arg)
{
  for (int c = 0; c < 4; c++) 
  {
    for (int d = 0 ; d < 4; d++) 
    {
      SumaAA[c][d] = input[c][d] + input[c][d];
    }
  }
  pthread_exit(NULL);
}
