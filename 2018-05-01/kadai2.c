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
 int n,m; // 行数，列数
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
  //L->tail = NULL;
  return L;
}

smatrix create_smatrix(int n, int m) {
  smatrix M;
  NEW(M,1);
  M->n = n;
  M->m = m;
  NEW(M->rvec,n);
  for (int i = 1; i <=n; i++) {
    M->rvec[i-1] = slist_new();
  }
  return M;
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

void slist_insert(slist L, slobj r) {
  slobj p, q;
  p = L->head;
  q = p;
  while (p != NULL && p->v <= r->v) {
    q = p;
    p = p->next;
  }
  if (p == L->head) {
    L->head = r;
    r->next = p;
  } else {
    q->next = r;
    r->next = p;
  }
}

/*** リストの表示 ***/
void slist_print(slist L)
{
  slobj p;
  p = L->head;
	while (p != NULL) {	/* 次ポインタがNULLまで処理 */
		printf("%d %lf ",p->j,p->v);
		p = p->next;
	}
  printf("-1\n");
}


void smatrix_insert(smatrix S, int i, int j, double x) {
  slist_insert_tail(S->rvec[i-1], slobj_new(j,x));
}

smatrix read_smatrix() {
  int n,m;
  scanf("%d%d",&n,&m);
  smatrix M = create_smatrix(n,m);
  for (int i = 1; i <= n; i++) {
    while (1) {
      int j;
      scanf("%d",&j);
      if (j<0) break;
      double v;
      scanf("%lf",&v);
      smatrix_insert(M,i,j,v);
    }
  }
  return M;
}



void print_smatrix(smatrix S) {
  printf("%d %d\n",S->n,S->m);
  for (int i = 1; i <= S->n; i++) {
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
  C = create_smatrix(A->n,B->m);
  for (int i = 1; i <= C->n; i++) {
    for (int j=1; j <= C->m; j++) {
      double x=0;
      for (int k = 1; k <= A->m; k++) {
        x += smatrix_access(A,i,k)*smatrix_access(B,k,j);
      }
      if (x!=0){
        smatrix_insert(C,i,j,x);
      }
    }
  }
  return C;
}

int main(void) {
  smatrix A,B,C;
  A = read_smatrix();
  B = read_smatrix();
  if (A->m != B->n) {
    printf("0 0");
  } else {
    C = multiply_smatrix(A,B);
    print_smatrix(C);
  }
  return 0;
}
