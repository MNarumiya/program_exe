#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}  //

// typedef struct slobj_ {
// int key; // 値
// struct slobj_* next; // 後の要素へのポインタ
// }* slobj;
//
// typedef struct {
// slobj head; // 先頭要素のポインタ
// }* slist;

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

slobj slist_search(slist L, int k)
{
  slobj p;
  p = L->head;
  while (p != NULL && p->key != k) {
    p = p->next;
  }
  return p;
}

/*** リストの表示 ***/
void show_list(slist L)
{
  slobj p;
  p = L->head;
	while (p != NULL) {	/* 次ポインタがNULLまで処理 */
		printf("%d ", p->key);
		p = p->next;
	}
}


void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
}


int main() {
  slist L; slobj p;
  int i;
  L = slist_new(); p = slobj_new(-1);
  slist_insert_head(L,p);
  for (i=1;i<=5;i++) {
    int x;
    //do {
      //printf("数字を入力:");
      scanf("%d", &x);
    //} while (x < 0);
    switch (x) {
      case -1:
        break;
      default:
        p = slobj_new(x);
        slist_insert_head(L,p);
    }
  }
  //表示
  show_list(L);
  return 0;
}
