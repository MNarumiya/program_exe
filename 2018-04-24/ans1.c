#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory¥n"); exit(1);};}

typedef struct slobj_ {
int v; // 値
struct slobj_* next; // 後の要素へのポインタ
}* slobj;

typedef struct {
slobj head; // 先頭要素のポインタ
}* slist;

slobj slobj_new(int x)
{
  slobj p;
  NEW(p,1);
  p->v = x;
  p->next = NULL;
  return p;
}

slist slist_new(void)
{
  slist L;
  NEW(L,1);
  L->head = NULL;
  return L;
}

void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
}

void slist_free(slist L) {
  slobj p, q;
  p = L->head;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
  free(L);
}

void slist_print(slist L) {
  slobj p;
  p = L->head;
  while (p != NULL) {
    printf("%d ", p->v);
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
  slist_insert_head(L, slobj_new(x));
}
slist_print(L);
slist_free(L);
return 0;
}
