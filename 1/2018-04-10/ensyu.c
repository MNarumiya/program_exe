#include <stdio.h>
#include <math.h>

int powSum(int n) {
  int i,x=0;
  for (i=1;i<=n;i++) {
    x += i*i;
  }
  return x;
}

int main() {
  int n,result;
  scanf("%d",&n);
  if (n<1) {
    printf("0\n");
    return 0;
  } else {
    result = powSum(n);
    printf("%d\n",result);
    return 0;
  }
}
