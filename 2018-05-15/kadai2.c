#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

typedef char* String;

typedef struct slobj_ {
  struct slobj_* next; // 後の要素へのポインタ
  int h;
  String eng; // 英語文字列
  String jpn; // 日本語文字列
}* slobj;

typedef struct {
  slobj head; // 先頭要素
}* slist;

typedef struct {
  int n; // ハッシュに格納されている要素数
  int size; // ハッシュ表のサイズ
  slist T; // リストの配列
}* hash;


slobj slobj_new(int h, String eng, String jpn) {//x を持つリストの要素を作る
  slobj p;
  NEW(p,1);
  p->h = h;
  p->eng = eng;
  p->jpn = jpn;
  p->next = NULL; // 必ず初期化しておく
  return p;
}


slist slist_new(void) {
  slist L;
  NEW(L,1);
  L->head = NULL; // リストの要素が無いことを表す
  return L;
}

hash hash_new(int m) {
  hash H;
  NEW(H,1);
  H->size = m;
  H->n = 2;
  H->T = slist_new();
  return H;
}

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

void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
}

slobj slist_search(slist L, String key) {
  slobj p;
  p = L->head;
  while (p != NULL && string_compare(p->eng, key) != 0) {
    p = p->next;
  }
  return p;
}

slobj slist_delete(slist L, String str) {
  slobj p,q;
  p = L->head;
  q = NULL;
  while (p != NULL && string_compare(p->eng, str) != 0) {
    q = p;
    p = p->next;
  }
  if (p != NULL && p == L->head) {
    L->head = p->next;
  } else if (p != NULL && string_compare(p->eng, str) == 0) {
    q->next = p->next;
  }
  return p;
}


slobj hash_search(hash H, String key) {
  //キー(英単語)が key である要素を返す
  slobj p;
  p = slist_search(H->T,key);
  return p;
}

int hash_func(String key) {
  int h = 0, i = 0;
  while (key[i] != 0) {
    h = h * 101 + key[i]; // ハッシュ値を計算
    i++;
  }
  return abs(h);
}

void hash_insert(hash H, slobj obj) { //英語と日本語のペアをハッシュ表に入れる
  slist_insert_head(H->T,obj);
}

slobj hash_delete(hash H, String key) { //ハッシュ表からkeyを含む要素を削除
  slobj p = slist_delete(H->T,key);
  return p;
}

void slobj_print(slobj p) {
  if (p == NULL) {
    printf("Not found\n");
  } else {
    printf("%s %s\n",p->eng, p->jpn);
  }
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

void hash_free(hash H) {
  slist_free(H->T);
  free(H);
}

int main(void) {
  hash H;
  slobj p;
  String eng, jpn;
  char buf[100];
  int m = 20;
  H = hash_new(m);
  while (1) {
    if (fscanf(stdin,"%s", buf)!=1) break; // 文字列を読み込めなければループを抜ける
    if (buf[0] == 'i') { // 読み込んだ文字列の先頭が i のとき (注: “ ではない)
      eng = string_input(); // 挿入する文字列を str に読み込む
      jpn = string_input();
      int h = hash_func(eng);
      hash_insert(H, slobj_new(h,eng,jpn)); // リストの先頭に入れる
    } else if (buf[0] == 'd') { //読み込んだ文字列の先頭が d のとき
      eng = string_input(); // 挿入する文字列を str に読み込む
      p = hash_delete(H,eng); // str を含む要素をリストから削除する
      if (p != NULL) free(p); // 削除した要素のメモリを開放する
      free(eng); // str はもう不要なのでメモリを開放する
    } else if (buf[0] == 's') { //読み込んだ文字列の先頭が d のとき
      eng = string_input(); // 挿入する文字列を str に読み込む
      p = hash_search(H,eng); // str を含む要素をリストから削除する
      slobj_print(p);
    }
  }
  hash_free(H); // リストのメモリを開放する
  return 0;
}
