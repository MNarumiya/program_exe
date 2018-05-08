#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}  //

typedef double* row_vector;
typedef row_vector* matrix;


row_vector create_row_vector(int n) //row_vectorを返り値とする関数
{
  int i;
  row_vector V;
  NEW(V, n);
  for (i=0; i<n; i++) {
    V[i] = 0.0;
  } //値の初期化
  return V;
}

matrix create_matrix(int n, int m) //メモリの確保
{
  int i,j;
  matrix M;
  NEW(M, n);
  for (i=0; i<n; i++) {
    M[i] = create_row_vector(m);
    for (j=0; j<m; j++) M[i][j] = 0.0;
  }
  return M;
}

matrix read_matrix(int n, int m, matrix A) //行列を標準入力から読み込み A に格納する
{
  int i, j;
  A = create_matrix(n,m); //領域確保
  //printf("\n行列を入力してください\n");
  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      //printf("行列の要素 A[%d][%d] = ", i+1, j+1);
      scanf("%lf",&A[i][j]);
    }
  }
  return A;
}

void print_matrix(int n, int m, matrix A) //n 行 m 列の行列 A を標準出力に書く
{
  int i, j;
  for(i=0;i<n;++i){
    for(j=0;j<m;++j){
      printf("%f  ", A[i][j]);
      if(j==m-1)
          printf("\n");
    }
  }
}

matrix trans_matrix(int n, int m, matrix A)
{
  matrix transA;
  transA = create_matrix(m,n);
  int i,j;
  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      transA[j][i] = A[i][j];
    }
  }
  return transA;
}

int main()
{
  matrix A;
  int n, m;
  int i,j;
  //printf("行数を入力：");
  scanf("%d", &n);
  //printf("列数を入力：");
  scanf("%d", &m);
  //printf("行列の形式\n");
  //printf("%d %d",n,m);
  A = read_matrix(n,m,A);
  //print_matrix(n,m,A);
  //printf("出力\n");
  printf("%d %d\n",m,n);
  A = trans_matrix(n,m,A);
  print_matrix(m,n,A);
  free(A); // 使わなくなった領域を開放する
  return 0;
}
