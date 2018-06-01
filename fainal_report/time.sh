#!/bin/bash
# chmod +x time.sh で実行権限をつけて
# ./time.sh [繰り返し回数] [入力ディレクトリ] で実行
# 変数$1は[繰り返し回数]
for i in `seq -w 1 10`;do
  n=`head $2/bcspwr$i.txt -n1 | cut -d ' ' -f 1`
  avet=0
  for cnt in `seq -w 1 $1`;do
    t=`(time ./a.out < $2/bcspwr${i}.txt > $2/bcspwr${i}_out.txt) 2>&1 1>/dev/null | sed -n 2P`
    m=`echo $t | cut -d 'm' -f 1 | cut -d ' ' -f 2`
    s=`echo $t | cut -d 'm' -f 2 | cut -d 's' -f 1`
    # bcコマンドを使って足し算
    avet=`echo "60.0*$m+$s+${avet}" | bc -l`
  done
  # bcコマンドを使って割り算をして，整数部分が0だったら0を付け足す(bcのデフォルトだと0.1が.1と表示される)
  # scale=5の部分を変えると精度を変更できる
  avet=`echo "scale=5;${avet}/${1}.0" | bc -l | sed -e 's/^\./0./g'`
  echo "$n ${avet}"
done 
