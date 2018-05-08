#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

typedef char* String;

typedef struct slobj_ {
String str; // 文字列
struct slobj_* next; // 後の要素へのポインタ
}* slobj;

typedef struct {
slobj head; // 先頭要素のポインタ
}* slist;

slobj slobj_new(String str) {
  slobj p;
  NEW(p,1);
  p->str = str;
  p->next = NULL;
  return p;
}

slist slist_new(void) {
  slist L;
  NEW(L,1);
  L->head = NULL;
  return L;
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
    printf("%s\n", p->str);
    p = p->next;
  }
}

int string_len(String str){
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

String string_input(void){
  int c, i, len;
  char buf[1000];
  String str;
  scanf("%s", buf);
  len = string_len(buf);
  NEW(str, len+1);
  for (i=0; i<len; i++) {
    str[i] = buf[i];
  }
  str[len] =0;
  return str;
}


int string_compare(String p, String q) {
  int plen, qlen,len;
  int rslt;
  plen = string_len(p);
  qlen = string_len(q);
  if (plen>qlen) len = qlen;
  else len = plen;
  rslt = 0;
  for (int i = 0; i < len; i++) {
    if (p[i] < q[i]) {
      rslt  = -1;
      break;
    } else if (p[i] > q[i]) {
      rslt  = 1;
      break;
    }
  }
  if (rslt==0 && plen>qlen) {
    rslt = 1;
  } else if (rslt==0 && plen<qlen) {
    rslt  = -1;
  }

  return rslt;
}

void slist_sort_insert(slist L, slobj r) {
  slobj p, q;
  p = L->head;
  q = p;
  while (p != NULL && string_compare(p->str,r->str)<0) {
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


int main(void) {
  int num;
  slobj p;
  slist dic;
  dic = slist_new();
  scanf("%d",&num);
  for (int i = 0; i < num; i++) {
    p = slobj_new(string_input());
    slist_sort_insert(dic,p);
  }
  slist_print(dic);
  slist_free(dic);
  return 0;
}
