#!/bin/bash
echo "\$*:$*"
echo "\$@:$@"
echo "numbers of parameter:$#"
echo "return value\$?:$?"
echo "pid:\$$:$$"
echo "\$!:$!"

#$0 这个程式的执行名字
#$n 这个程式的第n个参数值，n=1..9
#$* 这个程式的所有参数
#$# 这个程式的参数个数
#$$ 这个程式的PID
#$! 执行上一个背景指令的PID
#$? 执行上一个指令的返回值
