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
 int n, m; // 行数，列数
 slist* A; // 行ベクトルを表すリストの配列
}* smatrix;

slobj slobj_new(int x) //x を持つリストの要素を作る
{
  slobj p;
  NEW(p,1);
  p->j = x;
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
		printf("%d ", p->j);
		p = p->next;
	}
  printf("-1\n");
}

int main(void) {
  slist L;
  int x;
  L = slist_new();
  while (1) {
    scanf("%d", &x);
    if (x < 0) break;
    slist_insert_tail(L, slobj_new(x));
  }
  slist_print(L);
  slist_free(L);
  return 0;
}
