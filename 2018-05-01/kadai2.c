#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}



typedef struct slobj_ {
struct slobj_ *next; // 後の要素へのポインタ
int j; // j 列目
double v; // (i, j) 要素
}* slobj;

typedef struct {
slobj head; // 先頭要素のポインタ
slobj tail; // 末尾要素のポインタ
}* slist;

typedef struct {
 int row, col; // 行数，列数
 slist* rvec; // 行ベクトルを表すリストの配列
}* smatrix;

slobj slobj_new(int j,double v) //x を持つリストの要素を作る
{
  slobj p;
  NEW(p,1);
  p->j = j;
  p->v = v;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

slist slist_new(void){
  slist L;
  NEW(L,1);
  L->head = NULL; // リストの要素が無いことを表す
  L->tail = NULL;
  return L;
}

slobj slist_search(slist L, int j){
  slobj p;
  p = L->head;
  while (p != NULL && p->j != j) {
    p = p->next;
  }
  return p;
}

void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
}

void slist_insert_tail(slist L, slobj r)
{
  slobj p,q;
  p = L->head;
  q = NULL;
  while (p != NULL) {
    q = p;
    p = p->next;
  }
  if (q == NULL) {
    slist_insert_head(L,r);
  }else {
    r->next = p;
    q->next = r;
  }
}

void slist_free(slist L) {
  slobj
  p, q;
  p = L->head;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
  free(L);
}

/*** リストの表示 ***/
void slist_print(slist L)
{
  slobj p;
  p = L->head;
	while (p != NULL) {	/* 次ポインタがNULLまで処理 */
		printf("%d %lf",p->j,p->v);
		p = p->next;
	}
  printf("-1\n");
}

smatrix create_smatrix(int n, int m) {
  smatrix S; int i;
  NEW(S,1);
  S->row = n;
  S->col = m;
  NEW(S->rvec,n);
  for (i = 1; i <n; i++) {
    S->rvec[i-1] = slist_new();
  }
  return S;
}

void smatrix_insert(smatrix S, int i, int j, double x) {
  slist_insert_tail(S->rvec[i-1], slobj_new(j,x));
}

smatrix read_smatrix() {
  double v;
  int n,m,i,j; smatrix S;
  scanf("%d%d",&n,&m);
  S = create_smatrix(n,m);
  for (i = 1; i <= n; i++) {
    while (1) {
      scanf("%d",&j);
      if (j<0) break;
      scanf("%lf",&v);
      smatrix_insert(S,i,j,v);
    }
  }
  return S;
}



void print_smatrix(smatrix S) {
  int i; slist L; slobj p;
  printf("%d %d\n",S->row,S->col);
  for (i = 1; i <= S->row; i++) {
    slist_print(S->rvec[i-1]);
  }
}

double smatrix_access(smatrix S, int i, int j) {
  slobj p;
  p = slist_search(S->rvec[i-1],j);
  if (p != NULL) {
    return p->v;
  } else {
    return 0;
  }
}

smatrix multiply_smatrix(smatrix A, smatrix B) {
  smatrix C;
  C = create_smatrix(A->row,B->col);
  int i,j,k;
  for (i = 1; i <= C->row; i++) {
    for (j=1; j <= C->col; j++) {
      double x=0;
      for (k = 1; k <= A->col; k++) {
        x += smatrix_access(A,i,k)*smatrix_access(B,k,j);
        if (x!=0){
          smatrix_insert(C,i,j,x);
        }
      }
    }
  }
  return C;
}

void free_smatrix(smatrix S) {

}


int main(void) {
  smatrix A,B,C;
  A = read_smatrix();
  B = read_smatrix();
  if (A->col != B->row) {
    printf("0 0");
  } else {
    C = multiply_smatrix(A,B);
    print_smatrix(C);
  }
  return 0;
}
