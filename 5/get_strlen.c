#include<stdio.h>
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

typedef char* String;

int string_len(String str){
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

// String string_input(void){
//   int c, i, len;
//   char buf[1000];
//   String str;
//   scanf("%s", buf);
//   len = string_len(buf);
//   NEW(str, len+1);
//   for (i=0; i<len; i++) {
//     str[i] = buf[i];
//   }
//   str[len] =0;
//   return str;
// }

int get_stlen(void){
  int c, len;
  char buf[1000];
  String str;
  scanf("%s", buf);
  len = string_len(buf);
  return len;
}

int main(void) {
  int len;
  len = get_stlen();
  printf("%d",len);
  return 0;
}
