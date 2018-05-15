#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

typedef char* String;

typedef struct slobj_ {
  String key; // 値
  struct slobj_ *next; // 後の要素
}* slobj;

typedef struct {
  slobj head; // 先頭要素
}* slist;

int string_len(String str){
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

String string_input(void){
  int i, len;
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
  int rslt = 0;
  plen = string_len(p);
  qlen = string_len(q);
  if (plen > qlen) len = qlen;
  else len = plen;
  for (int i = 0; i < len; i++) {
    if (p[i] < q[i]) {
      rslt  = -1;
      break;
    } else if (p[i] > q[i]) {
      rslt  = 1;
      break;
    }
  }
  if (rslt==0 && plen > qlen) {
    rslt = 1;
  } else if (rslt==0 && plen<qlen) {
    rslt  = -1;
  }
  return rslt;
}


slobj slobj_new(String x) //x を持つリストの要素を作る
{
  slobj p;
  NEW(p,1);
  p->key = x;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

slist slist_new(void) {
  slist L;
  NEW(L,1);
  L->head = NULL; // リストの要素が無いことを表す
  return L;
}

slobj slist_search(slist L, String key) {
  slobj p;
  p = L->head;
  while (p != NULL && string_compare(p->key, key) != 0) {
    p = p->next;
  }
  return p;
}


slobj slist_delete(slist L, String str) {
  slobj p,q;
  p = L->head;
  q = NULL;
  while (p != NULL && string_compare(p->key, str) != 0) {
    q = p;
    p = p->next;
  }
  if (p != NULL && p == L->head) {
    L->head = p->next;
  } else if (p != NULL && string_compare(p->key, str) == 0) {
    q->next = p->next;
  }
  return p;
}

/*** リストの表示 ***/
void slist_print(slist L) {
  slobj p;
  p = L->head;
	while (p != NULL) {	/* 次ポインタがNULLまで処理 */
		printf("%s ", p->key);
		p = p->next;
	}
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

int main(void)
{
  int i, n;
  slist L;
  slobj p;
  String str;
  char buf[100];
  L = slist_new();
  while (1) {
    if (fscanf(stdin,"%s", buf)!=1) break; // 文字列を読み込めなければループを抜ける
    if (buf[0] == 'i') { // 読み込んだ文字列の先頭が i のとき (注: “ ではない)
      str = string_input(); // 挿入する文字列を str に読み込む
      slist_insert_head(L, slobj_new(str)); // リストの先頭に入れる
    } else if (buf[0] == 'd') { //読み込んだ文字列の先頭が d のとき
      str = string_input(); //挿入する文字列を str に読み込む
      p = slist_delete(L, str); // str を含む要素をリストから削除する
      if (p != NULL) free(p); // 削除した要素のメモリを開放する
      free(str); // str はもう不要なのでメモリを開放する
    }
  }
  slist_print(L); // 現在のリストを表示する
  slist_free(L); // リストのメモリを開放する
  return 0;
}
