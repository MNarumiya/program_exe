#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

typedef char* String;


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

int main(void) {
  String p,q;
  int rslt;
  p = string_input();
  q = string_input();
  rslt = string_compare(p,q);
  printf("%d\n",rslt);
  return 0;
}
