#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

double L[N][N];
double U[N][N];
double A[N][N+13];

void print_array()
{
  int i, j;

  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      fprintf(stderr, "%lf ", round(A[i][j]));
      if (j%80 == 79) fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
}

void init_arrays()
{
  int i, j, k;

  /* have to initialize this matrix properly to prevent                                              
   * division by zero                                                                                 
   */
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      L[i][j] = 0.0;
      U[i][j] = 0.0;
    }
  }

  for (i=0; i<N; i++) {
    for (j=0; j<=i; j++) {
      L[i][j] = i+j+1;
      U[j][i] = i+j+1;
    }
  }

  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      for (k=0; k<N; k++) {
	A[i][j] += L[i][k]*U[k][j];
      }
    }
  }
}

double rtclock()
{
  struct timezone tzp;
  struct timeval tp;
  int stat;
  gettimeofday (&tp, &tzp);
  return (tp.tv_sec + tp.tv_usec*1.0e-6);
}

int main()
{
  init_arrays();

  double annot_t_start=0, annot_t_end=0, annot_t_total=0;
  int annot_i;

  for (annot_i=0; annot_i<REPS; annot_i++)
    {
      annot_t_start = rtclock();


/*@ begin PerfTuning (         
  def build 
  { 
    arg build_command = 'icc -O3 -openmp -I/usr/local/icc/include -lm'; 
  } 
    
  def performance_counter          
  { 
    arg repetitions = 1; 
  }

  def performance_params 
  {
    param PERM[] = [
     ['i','j'],
     #['j','i'],
    ];

    param U1[] = [14];
    param U2[] = [6];
    param U3[] = [1];

    param IVEC1[] = [True];
    param IVEC2[] = [True];

    param SCREP[] = [True];
  }

  def search 
  { 
    arg algorithm = 'Exhaustive'; 
#    arg algorithm = 'Simplex'; 
#    arg time_limit = 5;
#    arg total_runs = 1;
  } 
   
  def input_params 
  {
    param N[] = [512];
  }

  def input_vars
  {
    arg decl_file = 'decl_code.h';
    arg init_file = 'init_code.c';
  }
) @*/

/**-- (Generated by Orio) 
Best performance cost: 
  0.032368 
Tuned for specific problem sizes: 
  N = 512 
Best performance parameters: 
  IVEC1 = True 
  IVEC2 = True 
  PERM = ['i', 'j'] 
  SCREP = True 
  U1 = 14 
  U2 = 6 
  U3 = 1 
--**/

 

register int i,j,k,it,jt,kt;

for (k=0; k<=N-1; k++)
  {

/*@ begin Loop (
  transform Composite (
  regtile = (['i'],[U1]),
  vector = (IVEC1, ['ivdep','vector always']))
    for (j=k+1; j<=N-1; j++)
      A[k][j] = A[k][j]/A[k][k];
) @*/{
  register int cbv_1, cbv_2;
  cbv_1=k+1;
  cbv_2=N-1;
#pragma ivdep
#pragma vector always
  for (j=cbv_1; j<=cbv_2; j++ ) 
    A[k][j]=A[k][j]/A[k][k];
}
/*@ end @*/

/*@ begin Loop (
  transform Composite (
  permut = [PERM],
  scalarreplace = (SCREP, 'double'),
  regtile = (['i','j'],[U2,U3]),
  vector = (IVEC2, ['ivdep','vector always']))
    for(i=k+1; i<=N-1; i++)
      for (j=k+1; j<=N-1; j++)
        A[i][j] = A[i][j] - A[i][k]*A[k][j];
) @*/{
  for (it=k+1; it<=N-6; it=it+6) {
    register int cbv_1, cbv_2;
    cbv_1=k+1;
    cbv_2=N-1;
#pragma ivdep
#pragma vector always
    for (j=cbv_1; j<=cbv_2; j++ ) {
      double scv_1, scv_2, scv_3, scv_4, scv_5, scv_6, scv_7;
      scv_1=A[(it+2)][j];
      scv_2=A[(it+3)][j];
      scv_3=A[k][j];
      scv_4=A[it][j];
      scv_5=A[(it+5)][j];
      scv_6=A[(it+4)][j];
      scv_7=A[(it+1)][j];
      scv_4=scv_4-A[it][k]*scv_3;
      scv_7=scv_7-A[(it+1)][k]*scv_3;
      scv_1=scv_1-A[(it+2)][k]*scv_3;
      scv_2=scv_2-A[(it+3)][k]*scv_3;
      scv_6=scv_6-A[(it+4)][k]*scv_3;
      scv_5=scv_5-A[(it+5)][k]*scv_3;
      A[(it+2)][j]=scv_1;
      A[(it+3)][j]=scv_2;
      A[it][j]=scv_4;
      A[(it+5)][j]=scv_5;
      A[(it+4)][j]=scv_6;
      A[(it+1)][j]=scv_7;
    }
  }
  for (i=it; i<=N-1; i=i+1) {
    register int cbv_3, cbv_4;
    cbv_3=k+1;
    cbv_4=N-1;
#pragma ivdep
#pragma vector always
    for (j=cbv_3; j<=cbv_4; j++ ) {
      double scv_8;
      scv_8=A[i][j];
      scv_8=scv_8-A[i][k]*A[k][j];
      A[i][j]=scv_8;
    }
  }
}
/*@ end @*/

  }

/*@ end @*/




      annot_t_end = rtclock();
      annot_t_total += annot_t_end - annot_t_start;
    }

  annot_t_total = annot_t_total / REPS;

#ifndef TEST
  printf("%f\n", annot_t_total);
#else
  {
    int i, j;
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        if (j%100==0)
          printf("\n");
        printf("%f ",A[i][j]);
      }
      printf("\n");
    }
  }
#endif

  return ((int) A[0][0]);

}
