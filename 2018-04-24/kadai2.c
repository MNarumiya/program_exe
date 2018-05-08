#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));} 

 typedef struct slobj_ {
 int key; // 値
 struct slobj_ *next; // 後の要素
 }* slobj;

typedef struct {
  slobj head; // 先頭要素
}* slist;

slobj slobj_new(int x) //x を持つリストの要素を作る
{
  slobj p;
  NEW(p,1);
  p->key = x;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

slist slist_new(void)
{
  slist L;
  NEW(L,1);
  L->head = NULL; // リストの要素が無いことを表す
  return L;
}

slobj slist_search(slist L, slobj q)
{
  slobj p;
  int k;
  k = q->key;
  p = L->head;
  while (p->key != -1  && k < p->key) {
      p = p->next;
    }
  return p;
}

/*** リストの表示 ***/
slobj show_list(slist L)
{
  slobj p;
  p = L->head;
	while (p != NULL) {	/* 次ポインタがNULLまで処理 */
		printf("%d ", p->key);
		p = p->next;
	}
  return p;
}


void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
}

void slist_insert_sort(slist L, slobj q)
{
  slobj p; slobj r=NULL;
  int k;
  k = q->key;
  p = L->head;
  while (p->key != -1  && k >= p->key) {
      r = p;
      p = p->next;
  }
  if (r == NULL) {
    q->next = L->head; //これがinsert headと同じ
    L->head = q;
  } else {
    r->next = q;
    q->next = p;
  }
}

int main() {
  slist L; slobj p; slobj q; //slobj r;
  L = slist_new(); p = slobj_new(-1);
  slist_insert_head(L,p);
  while (1) {
    int x;
    scanf("%d", &x);
    if (x == -1) {
      break;
    } else {
      q = slobj_new(x);
      slist_insert_sort(L,q);
    }
  }
  //表示
  show_list(L);
  return 0;
}
