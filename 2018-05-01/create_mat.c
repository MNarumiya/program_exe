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

slobj slobj_new(int x,double v) //x を持つリストの要素を作る
{
  slobj p;
  NEW(p,1);
  p->j = x;
  p->v = v;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

slist slist_new(void)
{
  slist L;
  NEW(L,1);
  L->head = NULL; // リストの要素が無いことを表す
  L->tail = NULL;
  return L;
}

void slist_insert_tail(slist L, slobj p)
{
  if (L->head == NULL) {
    p->next = L->head; //これはinsert headと同じ
    L->head = p;
    L->tail = p;
  } else {
    slobj q;
    q = L->tail;
    q->next = p;
    L->tail = p;
  }
}

smatrix create_smatrix(int n, int m) {
  smatrix S;
  NEW(S,1);
  S->row = n;
  S->col = m;
  return S;
}

void smatrix_insert(smatrix S, int i, int j, double x) {
  slist L;
  L = S->rvec[i-1];
  slist_insert_tail(L, slobj_new(j,x));
}

int main(void) {
  int n,m; smatrix S;
  scanf("%d%d",&n,&m);
  S = create_smatrix(n,m);
}
