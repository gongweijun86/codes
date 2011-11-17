#!/bin/bash
word="Large"
echo ${word}r
#var="var"
  echo "\${var-word} ${var-word}" # if var is defined return var else return word.var will not be changed.
  echo "\${var:-word} ${var:-word}" #if var is not defined or null return word,else return var.var will not be changde.
  echo "\${var=word} ${var=word}" #if var is not defined return word and var will be set by word.
  echo "\${var:=word} ${var:=word}" #if var is not defined or null return word and var will be set by word.
  echo "\${var+word} ${var+word}" #if var has been set return word else return null.var wont changed.
  echo "\${var:+word} ${var:+word}" #if var has been set by no-null return word,else return null.var wont changed.
  echo "\${var?message} ${var?message}" #if var hasnot been set then put message to stdout and stderr,at the same time the shell outputs the name of var else return var
  echo "\${var:?message} ${var:?message}" #if var hasnot been set or null then put message to stdout and stderr,at the same time the shell will outputs the name of var else return var
  echo "\${#var} ${#var}" #字符串长度($var 的字符数量).对于一个数组,${#array}是数组中第一个元素的长度.
  #一些例外:${#*}和#一些例外:${#*}和${#@}将给出位置参数的个数.
  #对于数组来说${#a#对于数组来说${#array[*]}和${$#array[@]}将给出数组元素的个数.
  echo "\${var#word} ${var#word}" #return the shortest match string after deleted from letf to right
  #返回删除掉 WORD #返回删除掉 WORD 的最短匹配之后的字符串,从左到右
  echo "\${var##word} ${var##word}" #返回删除掉 WORD 的最长匹配之后的字符串,从左到右
  echo "\${var%*c} ${var%*c}" #返回删除掉 WORD 的最短匹配之后的字符串,从右到左
  echo "\${var%%*c} ${var%%*c}" #返回删除掉 WORD 的最长匹配之后的字符串,从右到左
  echo "\${var:offset:length} ${var:offset:length}" #返回从第 offset 个字符开始的长度为length 的子字符串
  echo "\${var/s/t} ${var/s/t}" #将第一个 s 的最长匹配替换为 t 后返回
  echo "\${var//s/t} ${var//s/t}" #将所有 s 的最长匹配替换为 t 后返回
 
