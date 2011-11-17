变量
不能以数字开头，不能包含“!”，“*”,“-”等字符
变量值里有空格，要加‘’或者“”。
$test='hello world'
$test="hello world"
数组
初始化方式
1、a[0]=apple a[1]=banana a[2]=orange
2、a=(apple, banana, orange)
3、a=([0]=apple,[3]=orange,[2]=banana)
4、a[apple]=apple a[banana]=banana a[orange]=orange
访问数组
${name[index]}
1、echo ${name[*]}
2、echo ${name[@]}
output:
apple banana orange
若数组中某一项的值有空格，则 ${name[*]} 不能正常工作
a[3]="passion fruit"
echo ${name[*]} output:apple banana orange passion fruit
它将访问5个值，因为它将a[3]拆开了
echo ${name[@]} output:apple banana orange passion fruit
返回相同，但是它之访问了4个值，它将a[3]看做了一个整体
只读变量
fruit=apple
readonly fruit
fruit=banana #报错
readonly可以标识数组和变量
删除变量
unset name
unset fruit
不能删除只读变量
局部变量：只在当前shell中存在的变量，其他shell不能使用该变量
环境变量：shell任何子进程都能使用的变量
导出环境变量
export name #将环境变量导出到环境中
替换
ls [a-z A-Z 0-9]* #替换可以组合
不包括 ls[!a]*
变量替换
${parameter:-word} : parameter为空或未设置，则用word替换，parameter不变
${parameter:=word} : parameter为空或未设置，则用word替换，parameter设置为word
${parameter:?message} : parameter为空或未设置，则message作为标准错误打印出来，用来检查变量是否正确设置。当变量被删除时会向标准错误输     			出一个信息。
${parameter:+word} : 若parameter设置，则用word替换parameter，parameter不变

命令替换 `command`
DATE＝`date`
算术替换 $((expression))
foo=$((5+2*3))
echo $foo # 11
双撇号
× 用于 $ 参数替换
× 后引号用于命令替换
× \$ 打开美元字符（会将 $ 看成美元字符而不具备特殊含义）
× \` 打开后引号（同上）
× \" 使用嵌入的引号
× \\ 嵌入斜线

单撇号内的字符失去特殊含意
echo -e 'abcd\nabcd'
output:
abcd
abcd
流控制
if list1  	#命令返回值的真假
then
	list2
elif list3	#命令返回值的真假
then
	list4
else
	list5
fi

list1 －－> test expression
可以使用[]对test命令进行简写
test可以理解的expression分为三类
× 文件测试
× 字符串测试
× 数字比较

test使用
test expression
可以使用“[]”替换test，使用"[]"时，“[]”必须前后都有空格"[ expression ]"。
文件测试
test option file 或者 [option file]

	选项		描述
	-b file		若文件存在且是一个块文件，则为真
	-c file		若文件存在且是一个字符特殊文件，则为真
	-d file		若文件存在且是一个目录，则为真
	-e file		若文件存在，则为真
	-f file		若文件存在且是一个规则文件，则为真
	-g file		若文件存在且设置了SGIG位的值，则为真
	-h file		若文件存在且是一个符号链接，则为真
	-k file		若文件存在且设置了“sticky”位的值，则为真
	-p file		若文件存在且是一已命名管道，则为真
	-r file		若文件存在且可读，则为真
	-s file		若文件存在且其大小大于零，则为真
	-u file		若文件存在且设置了SUID位的值，则为真
	-w file		若文件存在且可写，则为真
	-x file		若文件存在且可执行，则为真
	-o file		若文件存在且被有效用户ID拥有，则为真
字符串比较
1）检查字符串存在
2）检查字符串相等

字符串不能使用test命令直接与一个表达式进行比较。若这样，则要用case语句代替。

选项			描述
-z string		若string长度为0，则为真
-n string		若string长度不为0，则为真
string1 = string2	若两个字符串相等，则为真
stirng1 != string2	若两个字符串不等，则为真

if [ -z "$FRUIT" ]; then
	echo "something"
else
	echo "somethingelse"
fi
这里引用了变量$FRUIT。当变量被删除发生时，要求这样做，否则$FRUIT未引用，则当其被删除时产生错误信息：
test：argument expected
类似于：[-z]
引用后类似于：[-z ""]

检查字符串是否相等
if[ "$FRUIT" = apple ];then
	echo "something"
else
	echo "somethingelse"
fi
数字比较
test int1 operator int2
或者
[int1 operator int2]
int1 int2是任何正整数或者负整数，operator如下。若int1 int2中有一个字符串而不是整数，则按0对待。
if [ $? -eq 0 ]; then
	echo "something"
else
	echo "somethingelse"
	exit
fi
操作符			描述
int1 -eq int2		相等，则为真
int1 -ne int2		不相等，则为真
int1 -lt int2		小于，则为真
int1 -le int2		小于等于，则为真
int1 -gt int2		大于，则为真
int1 -ge int2		大于等于，则为真
复合表达式
内置操作符

操作符			描述
！expr			expr为假，则复合表达式为真，expr可以是任何有效的测试表达式
expr1 -a expr2		expr1和expr2都为真为真
expr1 -o expr2		expr1和expr2有一个为真则整式为真

test expr1 operator expr2
or
[ expr1 operator expr2]

条件操作符

test expr1 operator test expr2
or
[ expr1 ] operator [ expr2 ]
operator是 && (and) 或 || (or)		

否定一个表达式

test !expr
or
[ !expr ]

case语句

1.
case word in
	pattern1)
		list1
		;;
	pattern2)
		list2
		;;
esac
2.
case word in
	pattern1) list1 ;;
	pattern2) list2 ;;
esac

case语句真正强大的地方是可以使用模式pattern执行匹配。
pattern（模式）是一个包含规则字符和特殊通配符的字符串，模式决定了匹配是否存在。
模式可以使用与路径名扩展模式相同的特殊字符，以及“或”字符“｜”。许多缺省行为可通过给出*号（匹配任何东西）来执行。

case "$TERM" in
	*term)
		TERM=xterm ;;
	network|dialup|unknown|vt[0-9][0-9][0-9]
		TERM=vt100 ;;
esac

循环

while command	#command 任何有效的UNIX命令，通常是一个test表达式
do
	list
done

while command； do list ；done

x=0
while [ $x -lt 10 ]
do
	echo $x
	x=`echo "$x + 1" | bc` # x=`echo $(($x+1))`
done

while循环嵌套
while command1 ; # loop1, outer loop
do
	list1
	while command2 ; # loop2, inner loop
	do
		list2
	done
	list3
done

x=0;
while [ "$x" -lt 10 ]
do
	y="$x"
	while [ "$y" -ge 0]
	do
		echo -e "$y\c"
		y=`echo "$y-1"|bc`
	done
	echo
	x=`echo "$x+1" | bc`
done
output:
0
10
210
3210
43210
543210
6543210
76543210
876543210
9876543210

RESPONSE=
while [ -z "$RESPONSE" ]
do
	echo "enter a directory:"
	read $RESPONSE
	if [ ! -d $RESPONSE ]; then
		echo "error:not a directory!"
		$RESPONSE=
	fi
done

until循环
当某些条件为真时，需要执行一个命令集 －－>while 循环
直到某个条件为真时，执行一个命令集 －－>until 循环

until command #command 通常是一个测试表达式
do
	list
done

until command; do list; done

x=1
while [ ! $x -ge 10 ]
do
	echo $x
	x=`echo "$x+1" | bc`
done
等价于：
x=1
until [ $x -ge 10 ]
do
	echo $x
	x=`echo "$x + 1"|bc`
done

for和select循环
for name in word1 word2 ...wordn #name 是一个变量名 word1~wordn是被空格分开的字符（单词）序列
do
	list
done

for name in word1 word2 ...wordn; do list; done

for i in 0 1 2 3 4 5 6 7 8 9
do
	echo $i
done

操纵文件集合
for FILE in $HOME/.bash*
do
	cp $FILE ${HOME}/public_html
	chmod a+r ${HOME}/public_html/${FILE}
done

select 循环
select循环提供一种从用户可选项中创建已编号菜单的简捷方式。当要求用户从一个选择清单中选择一项或多项时，该循环很有用。
由ksh引入，bash兼容，不能用于sh
select name in word1 word2 ...wordn #list1
do
	list	#list2
done
select循环的执行过程：
1）list1中的每一项都和一个数字一起显示
2）显示一个提示符，通常为#？
3）当用户输入一个值时，$REPLAY被赋予该值
4）若$REPLAY包含许多所显示的项，则name所选定的变量赋值为list1中被选的项，否则，list1中的项再次显示
若用户输入多个有效值，$REPLAY包含全部用户选项，在这种情况下，name指定的变量没有设置

select COMPONENT in comp1 comp2 comp3 all none
do
	case $COMPONENT in
		comp1|comp2|comp3) echo "choose $COMPONENT"
		;;
		all) echo "choose comp1,comp2,comp3" ;;
		none) break ;;
		*) echo "error:invalid selection.$REPLAY." ;;
	esac
done
改变提示符
通过修改变量PS3从而改变select循环的提示符。若PS3未设置，显示缺省提示符#？。
PS3="------->";export PS3
1) comp1
2) comp2
3) comp3
4) all
5) none
------->

循环控制
× break
× continue

使用while创建无限循环。由于while循环在command为真时执行list，指定command为“：”或者/bin/true就会使循环永远执行
while :
do
	list
done
------------------------------------------------------------------
while ：
do
	read CMD
	case $CMD in
		[qQ]|[qQ][uU][iI][tT]) break ;;
		*) process $CMD ;;
	esac
done
------------------------------------------------------------------
for i in 1 2 3 4 5
do
	mkdir -p /mnt/backup/docs/ch0${1}
	if [ $? -eq 0 ]; then # 通过 $? 判断mkdir是否成功 如果成功 则继续进行
		for j in doc c h m pl sh
		do
			cp $HOME/docs/ch0${i}/*.${j} /mnt/backup/docs/ch0${i}
			if [ $? -ne 0 ]; then break 2; fi # 通过 $? 判断cp是否成功 如果不成功 则停止
		done
	else
		echo "could not make backup directory"
	fi
done

continue 命令

for FILE in $FILE ;
do
	if [ ! -f "FILE" ]; then
		echo "error:$FILE is not a file"
		continue;
	fi
	#process the file
done

参数
处理传给Shell脚本的选项的最常用的方式有两种：
× 使用case语句手工处理选项
× 使用getopts命令处理选项


参数
特殊变量

变量		描述
$0		正在被执行命令的名字。对于shell脚本而言，这是被激活命令的路径
$n		该变量与脚本被激活时所带的参数相对应
$#		提供脚本的参数号
$*		所有这些参数都被双引号引住。若一个脚本接受两个参数，$*等于$1$2
$@		所有这些参数都分别被双引号引住。若一个脚本接受两个参数，$*等于$1$2
$?		前一个命令执行后的退出状态
$$		当前shell的进程号。对于shell脚本而言，这是其正在执行时的进程ID
$!		前一个后台命令的进程号

使用$0
对于可以使用多个名字激活的shell脚本而言，它的行为常用$0变量来决定。
#！/bin/bash
case $0 in
	*listtar) TARGS="-tvf $1" ;; # t －>tape a －>archive
	*maketar) TARGS="-cvf $1.tar $1"
esac
tar $TARGS

usage语句
echo "usage:$0[option][files]"

利用usage语句可以避免脚本被调用时带有的名字不是它知道的这两个名字。要做到这一点，将case语句改写成：
case $0 in
	*listtar) TARGS="-tvf $1" ;;
	*maketar) TARGS="-cvf $1.tar $1" ;;
	*) echo "Usage: $0 [file|directory]"
	   exit 0
	   ;;
esac

选项和参数
一个处理参数的实例
USAGE="Usage: $0 [-c|-t] [file|dirctory]"
case "$1" in
	-t) TARGS="-tvf $2" ;;
	-c) TARGS="-cvf $2.tar $2" ;;
	*)  echo "$USAGE"
	    exit 0
	    ;;
esac

使用basename
$ basename /usr/bin/sh
output: sh
修改USAGE：
USAGE＝“Usage: `basename $0` [-c|-t] [file|dirctory]”

公用参数处理问题
到目前，若第一个参数为提供case *)会解决，但是如果没有提供第二个参数呢？
检查参数个数：看给定的参数数目$#,是否与所要求参数的数目匹配。
添加检查：
#！/bin/bash
USAGE＝“Usage: `basename $0` [-t|-c] [file|dirctory]”
if [ $# -lt 2]; then
	echo "$USAGE"
	exit 1
fi

case "$1" in
	-t) TARGS="-tvf $2" ;;
	-c) TARGS="-cvf $2.tar $2" ;;
	*)  echo "$USAGE"
	    exit 0
	    ;;
esac
tar $TARGS

处理附加的文件
目前只处理作为参数给出的第一个文件而不检查给出的文件参数是否真的是一个文件，可以通过使用$@增加所有文件参数的处理过程。首先修改－t
的处理过程。
case "$1" in
	-t) TARGS="-tvf"
	    for i in "$@"; do
		if [ -f "$i" ] ; then tar $TARGS "$i" ; fi ;
	    done
	    ;;
	-c) TARGS="-cvf $2.tar $2" ;
	    tar $TARGS
	    ;;
	*) echo "$USAGE" ;
	   exit 0
	   ;;
esac
若将$@换为$*后，若 mytar －t "my tar file.tar"
$*意味着for循环三次调用tar分别被文件 my tar file.tar各调用一次
使用$@就避免了这个问题。

其他一些小问题
1、为脚本提供的参数包括第一个参数$1,都被认为是文件。使用shift命令将第一个参数从参数清单中移走，不仅能减少for循环次数，也能防止脚本在一些意外情况下试图使用tar操纵文件名中带-t的文件
2、操作失败时，脚本应该做什么。在 列出操作 时，若tar不能列出文件内容，就跳过该文件并打印错误信息。

#!/bin/bash
USAGE="Usage:`basename $0` [-t|-c] [files|dirctory]"

if [ $# -lt 2 ]; then
	echo "$USAGE"
	exit 1
fi

case "$1" in
	-t) shift ; TARGS="-tvf" ;
	for i in "$@" ; do
		if [ -f "$i" ] ; then
			FILES=`tar $TARGS "$i" 2>/dev/null`
			if [ $? -eq 0 ] ; then
				echo ; echo "$i" ; echo "$FILES"
			else
				echo "ERROR:$i not a tar file"
			fi
		else
			echo "ERROR: $i not a file"
		fi
	done
	;;
	-c) shift ; TARGS="-cvf " ;
	    tar $TARGS archive.tar "$@"
	    ;;
	*) echo "$USAGE"
	   exit 0
	   ;;
esac

输入输出
向终端输出的两个命令
× echo
× printf

ehco命令的转移序列
转义序列		描述
\n		换行
\t		tab
\c		打印字符串不带换行符

\c的用法
echo -e "copying file ,please wait\t\c"
for i in ${FILES} ; do cp $i $DEST && echo -e ".\c" ; done
echo -e "\tDone"

printf format arguments
format的格式：%[-]m.nx
%用于标识格式化序列的开始，x标识格式化序列的类型
x的可能值
字母	描述
s	字符串
c	字符
d	十进制整数
x	十六进制整数
o	八进制整数
e	指数型浮点数
f	固定浮点数
根据x值不同，整数m,n解释不同。通常m是该域的最小长度，n为该域的最大长度。若指定了一个实数格式，n被认为是应该使用的精度。

#！/bin/bash
printf "%32s %s\n" "File Name" "File Type"

for i in *;
do
	printf "%32s " "$i"
	if[ -d "$i" ]; then
		echo "directory"
	elif [ -h "$1" ]; then
		echo "symbolic link"
	elif [ -f "$i" ]; then
		echo "file"
	else
		echo "unknown"
	fi
done

重定向

输入重定向
command > file
command >> file
command | tee file
输出重定向
command < file
本地文档
command << delimiter
documents
delimiter
shell将 “<<” 操作符解释成一条指令，该指令用于读去输入直到它在输入中找到包含指定的定界符的行。包含定界符那一行以前的所有输入行都将反馈到
command的标准输入中
创建一个带有短URL清单文件
$:cat > urls << myurls
>http://www.baidu.com
>http://www.google.com
>http://www.github.com
>http://www.linux.com
>myurls
$cat urls
http://www.baidu.com
http://www.google.com
http://www.github.com
http://www.linux.com
----------------------------------------------------------------
读取用户输入
read name
它读取用户输入的一整行，直到用户输入回车键为止，它使得该行成为由name所指定变量的值。
示例：
YN＝yes
printf "do u want to play a game[$YN]?"
read YN
:${YN:=yes}
case $YN in
	[yY]|[yY][eE][sS] exec xblast ;;
	*) echo "maybe later" ;;
esac

read与输入重定向联合在一起使用
while read LINE
do
# manupulate file here
done < file

while read LINE
do 
	case $LINE in
		*root*) echo $LINE ;;
	esac
done < /etc/passwd

管道
command1｜command2｜...
警告:管道中每一个命令都按一个独立进程执行，管道的退出状态是最后一个命令的退出状态
一个非常重要的事实：当写脚本时必须做错误处理！
文件描述符
stdin 0
stdout 1
stderr 2
缺省时，shell为每一个命令提供三个标准文件描述符。在shell下，使用exec命令可将任何文件和文件描述符关联起来。
将一个文件和文件描述符相关联是非常重要的。当需要多次将输入输出重定向到一个文件但又不想多次重复文件名时，常常需要这样做。
当打开文件执行写操作时，可以使用以下格式中的一种：
exec n>file
exec n>>file
这里n是一个整数，文件file是打开的需要写入的文件。第一种格式覆盖了指定文件file；第二种格式在指定文件file后附加内容，
$exec 4>fd4.out
将文件fd4.out与文件描述符4相关联
当打开文件执行读操作时，使用如下格式：
exec n<file
n是一个整数，文件file表示打开的需要读取的文件
输入输出重定向格式
command n>file
command n>>file
command n<file
command 1>file1 2>file2 # command > file1 2>file2

for FILE in $FILES
do
	ln -s $FILE ./docs >> /tmp/ln.log 2> /dev/null
done
rm file > /dev/null #删除rm命令的输出
cat /dev/null > file # file仍存在，但是大小为0
stdout stderr重定向到同一个文件
command > file 2>&1
command >> file 2>&1
向stderr输出出错消息
echo string 1>&2 #echo string >&2
printf format args 1>&2 printf format args >&2 
重定向两个文件描述符
n>&m
这里n和m为文件描述符，设n＝2，m＝1，可以看到stderr被重定向到stdout，通过将stdout重定向到一个文件，也可以重定向stderr。
若m是一个连字符而不是一个数字，则对应的文件描述符的文件被关闭。当文件描述符被关闭时，对其读写都会报错。

函数（略过，讲的太简单）
文本过滤
head
tail -f file
grep word file
grep -i word file #忽略大小写
grep -v word file #不包含word的行
grep -n word file #输出行号
grep -l word file #只列出文件名
tr "set1" "set2" #tr -> transliterate
删除标点符号
tr '!?":;\[\]{},.' ' ' < /home/orion/testfile
注意：[ ] 这两个字符有特殊含意，所以转义
将大写变为小写
tr 'A-Z' 'a-z' < /home/orion/testfile
压缩连续相同的字符
tr -s "set1"
echo 'feed me' | tr -s 'e'
output:fed me
echo 'shell programming' | tr -s 'lm'
output:shel programing
uniq只为重复行保留一行，而抛弃其余重复部分
sort
sort -nr #r reverse n numeric 按数字值逆序排列
在不同列中按数字排序
sort -k start,end files #start 关键字的起始处 end 关键字的截止处 第一列为 1...
无法处理单引号。。。

tr可以理解的字符分类
分类		描述
alnum		字母和数字
alpha		字母
blank		空格
cntrl		控制字符
digit		数字
graph		可打印字符 不包括空格
lower		小写字母
print		可打印字符 包括空格
punct		标点符号
space		水平或垂直空格
upper		大些字母
xdigit		16进制数字
tr '[:classname:]' 'set2'

使用正则表达式过滤文本
awk sed激活语法
command ‘script’ filename
command->awd sed script->被awk和sed理解的命令清单 filenames->命令所作用的文件清单
script被单引号引起来，为了避免Shell执行替换。
没有给出文件名，awk和sed都从stdin读入，所以它们可以作为其他命令的输出过滤器
基本操作
1、从输入文件读取一行
2、为该行做一个拷贝
3、在该行上执行所给的脚本script
4、为下一行重复1
脚本的结构及脚本的运行
script包含一行或多行记录，格式：
/pattern/action
pattern为正则表达式，啊磁体哦你表示一些动作
执行脚本时，为每条记录执行：
1、顺序搜索每个模式pattern直到发现一个匹配
2、发现匹配后，为输入执行相应的动作action
3、当动作action执行完毕时，到达下一个模式pattern并重复1
4、所有模式都试过一遍后，读取下一行
在第四步执行前，sed显示被改动的记录，awk必须手动显示这条记录
正则表达式的元字符
字符		描述
.		匹配任何除换行符外的单个字符
*		匹配*字符前的零个或多个所给字符
[chars]		匹配在chars中给出的任一个字符，chars是一个字符序列。可用“-”字符指出字符范围。若"^"字符为chars中的第一个字符，则匹配
		在chanrs中未指定的字符
^		匹配一行的开始
$		匹配一行的结尾
\		将紧随在“\”字符后的字符作为文字字符处理，用于说明一种特殊模式，该模式含有本表前面给出的某个通配符，同时使用“\”消除该通配符的
		特殊含义
例如：
/peach/ 精确匹配字符串peach
/a.c/	匹配如a+c,a-c,abc
/a*c/	除了上述之外还匹配如ace,yacc和arctic等字符串，它也匹配下面这样的行
	close the window。注意在本句中没有字母a。"*"匹配恰在其之前的零个或多个所给字符
另一个重要事实，"*"总是试图进行尽可能长的匹配。如，考虑模式：
/a*a和如下一行字符串
able was I,ere I saw elba
例子中有如下几种情况：
able wa
able was I,ere I sa
able was I,ere I saw elba
由于使用了“*”，选最后一种可能情况。
可以将“.”"*"组合在一起使用，这样使用可以获得与在文件名扩展中所使用的*通配符相同的行为，
/ch.*doc/
匹配字符串ch01.doc,ch02.doc,ch02.doc和chdoc。Shell的“*”匹配与之同名的文件。
“.”操作的最大限制是不能指定想匹配的具体字符，它匹配所有字符。可以使用中括号"[","]",如/[chars]/
/[tT]he/匹配The和the
常用字符集
[a-z]		单个小写字母
[A-Z]		单个大写字母
[a-z A-Z]	单个字母
[0-9]		单个数字
[a-z A-Z 0-9]	单个字母或数字
/ch[^0-9]/	匹配chapter chocolate 不匹配ch01 ch02
使用*组合集合扩展它们的功能
/ch[0-9]*doc/	匹配ch01 ch02 不匹配chdoc changdoc
锚定（anchoring）模式
假定搜索以单词the开头的行，
the plains were rich with crops
如果使用模式
/the/
那么它匹配上面的这一行外，还匹配
there were many orchards of fruit tree
in the dark it was like summer lightning
两个问题：
* 只匹配单字the，以there这类单词开头的行不应匹配
* 字符串the应在行的开始
第一问题：在the后加一个空格 /the /
第二个问题：使用“^”，用于匹配一行的开始。/^the /
使用$将表达式锚定在一行的末尾
/friend$/
可以将“^”"$"与其他字符组合使用
/^Chapter[0-9]*[0-9]$/
匹配
Chapter 1
Chapter 20
不匹配
Chapter 00 Introduction
Chapter 101
因为^ $ 将表达式锚定在一行的开始和结尾，可以这样匹配空行
/^$/
转义元字符
Peach $0.89/lbs
不转义：/$[0-9].[0-9][0-9]/[a-z A-Z]*/
问题：
	1、$匹配行尾，则表达式试图在行尾寻找字符，这是不可匹配的模式
	2、三个"\".前两个用作模式的定界符，在模式[a-z A-Z]*/会使awk和sed不知道如何处理
	3、与"."有关。由于该字符可匹配处于该位置的任何一个字符，所以它除匹配想要的字符串外，还能匹配如下字符串。0x00 12345	
转义：/\$[0-9]*\.[0-9][0-9]\/[a-z A-Z]*/
\处于普通字符前任何影响 \a a 都被认为是小写字母a
有用的正则表达式
字符类型				表达式				
空行				/^$/				
整行				/^.*$/				
一个或多个空格			/ */				
html或xml标记	？？？		/<[^>][^>]*>/			
有效的URL	？？？		/[a-zA-Z][a-zA-Z]*:\/\/[a-zA-Z0-9][a-zA-Z0-9\.]*.*/			
美元数量格式			/\$[0-9]*\.[0-9][0-9]/

使用sed
它读取每行输入然后执行一组请求动作
sed ‘script’ files
files是一个或多个文件清单 script是一个或多个按如下格式写出的命令
/pattern/action
pattern是正则 action是下面的动作，若pattern被删去，则没行都执行动作action
sed中可以使用的某些动作
动作			描述
p			打出该行
d			删除该行
s/pattern1/pattern2	用第二种模式pattern2替换第一种模式pattern1
清单文件：fruit_prices.txt
Fruit		Price/lbs
Banana		0.89
Peach		0.79
Kiwi		1.50
Pineapple	1.29
Apple		0.99
Mango		2.20
假设想打印低于一美元的水果
$sed '/0.\[0-9][0-9]$/p' fruit_prices.txt
Fruit	Price/lbs
Banana	    0.89
Banana	    0.89
Peach	    0.79
Peach	    0.79
Kiwi	    1.50
Pineapple   1.29
Apple	    0.99
Apple	    0.99
Mango	    2.20
发现低于一美元的被打印了两次，价格高于一美元的打印了一次
验证了sed的缺省行为会将每一个输入的行都打印到输出上。为了避免这种行为，可以制定-n选项
$sed -n '/0.\[0-9][0-9]$/p' fruit_prices.txt
Banana	    0.89
Peach	    0.79
Apple	    0.99
删除行
/pattern/d
$sed '/^[Mm]ango/d' fruit_prices.txt
注意此时不必为sed指定-n选项就能得到正确输出。p命令告诉sed产生额外输出，而d命令告诉sed改变正规的输出。
-------------------------------
$mv fruit_prices.txt fruit_prices.txt.$$
$$的值是当前进程的ID。将进程ID附加到文件末尾是创建临时文件的常用方法。
-------------------------------
/pattern/s/pattern1/pattern2/
在任何匹配pattern的行中，都用pattern2代替pattern1
通常会略去pattern
s/pattern1/pattern2/
全局替换
s/pattern1/pattern2/g
不加g的话，一行只执行一次替换
重用表达式的值
现在输出中反映出价格是以美元为单位的，需要在每个价格之前加上一个$字符，现在用户已经知道，使用这样的表达式可以匹配所有以价格结尾的行：
/*[0-9][0-9]*\.[0-9][0-9]$/
虽然问题只是用一个前面带有$的价格代替已存在的价格，但是很显然，需要为文件中每种水果写一个独立的s命令。
幸运的是，s命令为我们提供了&操作符，它使得可以在pattern2中重用pattern1的字符串。在本例中，需要重用被匹配的价格：
$sed 's/\t*[0-9][0-9]*\.[0-9][0-9]$/\$&/'	fruit_prices.txt
使用多个sed命令
sed -e 'command1' -e 'command2' ...-e 'commandN' files
sed -e 's/Paech/Peach/' -e 's/\t*[0-9][0-9]*\.[0-9][0-9]$/\$&/'
在管道中使用sed
如果sed没有受到文件清单，那么它作用与stdin，这使的用户可在管道中使用sed。
$/usr/bin/id
uid=500(ranga) gid=100(users)
$/usr/bin/id | sed 's/(.*$//'
uid=500
$/usr/bin/id|sed -e 's/(.*$//' -e 's/^uid=//'
使用awk过滤文本
awk特别是如下特征：
* 域编辑
* 变量
* 流控语句
awk基本语法
awk ‘script’ files
files是一个或多个文件的清单 script是由一个或多个如下命令格式组成：
/pattern/{actions}
/pattern是一个正则表达式 actions是一个或多个命令。若去掉pattern，则awk为输入文件的每一行执行制定的动作（actions）。
awk的一个简单的任务：现实一个文件的所有行。
$awk '{print;}' fruit_prices.txt
使用awk的命令print向屏幕打印出输入的每一行，当不带参数给出print命令时，它按输入行被读入的方式原原本本的打印。
print后的分号“；”,让awk知道命令已结束。某些老版本并不要求，anyway，带上好点。
域编辑
awk中，有很多好优点，之一就是它可以自动将输入行分割成域（field）。域是被一个或多个域分隔符隔开的字符集，缺省域分隔符是tab和空格。
当读入一行时，awk将它已经分析过的域放入变量1中作为第一个域，变量2为第二个域and so on。访问一个域，使用域操作符$,这样，第一个为$1.
awk中，$的使用与shell中$的使用稍有不同。awk中，只有当访问域变量的值时才使用$,当访问其他变量值时，并不要求使用$.
$awk '{print$1 $3;}' fruit_prices.txt
FruitQuantity
Banana100
Peach65
Kiwi22
Pineapple35
Apple35
Mango78
没有分隔符，这是print的缺省行为。为在每个域之间打印空格，使用“，”
$awk '{print$1 ,$3;}' fruit_prices.txt
Fruit Quantity
Banana 100
Peach 65
Kiwi 22
Pineapple 35
Apple 35
Mango 78
使用printf代替print格式化
$awk '{printf "%-15s %s\n",$1,$3;}' fruit_prices.txt
Fruit           Quantity
Banana          100
Peach           65
Kiwi            22
Pineapple       35
Apple           35
Mango           78
执行“模式-特定”行为
awk '/ *\$[1-9][1-9]*\.[0-9][0-9] */ {print $1,$2,$3,"*";} / *\$0\.[0-9][0-9] */ {print;}' fruit_prices.txt 
这里两种模式：
Banana	    $0.89    100
Peach	    $0.79    65
Kiwi $1.50 22 *
Pineapple $1.29 35 *
Apple	    $0.99    35
Mango $2.20 78 *
用“*”标记的行不在与其他行按相同的方式进行格式化。可以使用printf解决这个问题，更好更简单的方法是使用$0域。awk使用变量0存储它所读入
的整个输入行，
awk '/ *\$[1-9][1-9]*\.[0-9][0-9] */ {print $0,"*";} / *\$0\.[0-9][0-9] */ {print;}' fruit_prices.txt
比较操作符
使用比较操作符比较数字和字符串
此时语法变为：
expression {action;}
操作符			描述
< > <= >= == !=		...
value~/pattern/		若value匹配pattern则为真
value!~/pattern/	若value不匹配pattern则为真
awk '$3 <= 75 {printf "%s\t%s\n", $0, "reorder";} $3 > 75 {print $0;}' fruit_prices.txt 
复合表达式
复合表达式通过使用“&&”“||”符合操作符组合起来的。
(expr1)&&(expr2)
(expr1)||(expr2)
需要用圆括号扩括
awk '($2~/^\$[1-9][0-9]*\.[0-9][0-9]$/)&&($3 < 75){printf "%s\t%s\t%s\n",$0,"*","reorder";}' fruit_prices.txt
Kiwi	    $1.50    22	*	reorder
Pineapple   $1.29    35	*	reorder
next命令
awk '$3<=75 {printf "%s\ts%s\n",$0,"recorder";} $3>75 {print $0;}' fruit_prices.txt
即使已经满足第一步，仍然要检查第二步；我们想要它检验完第一步再不用检验第二步。
awk '$3<=75 {printf "%s\ts%s\n",$0,"recorder"; next;} $3>75 {print $0;}' fruit_prices.txt
使用stdin作为输入
$/bin/ls -l | awk '$1 !~ /total/ {printf "%-32s %s",$8,$5;}'
利用awk的特点
* 变量
* 流控制
* 循环
定义一个变量： name = value
eg： fruit=peach
赋予变量的值可以是另一个变量或域的值，
fruit=peach
fruity=fruit
为了将一个变量的值设置成一个awk所分析出来的域的值，需要使用域访问操作符
fruit=$1
使用数字表达式
可以将一个变量的值设置为一个数字表达式。
num1 operator num2
num1 num2可以是常数，如1或2，或者变量名。
a=1
b=a+1
+-*/%^	加减乘除求余求幂
注意：
* 若num1或num2中有一个变量的值为字符串而不是数值，awk用0代替而不是字符串来计算
* 若使用了在数字表达式中未创建的变量，awk创建它并为它置0.
特殊模式BEGIN和END
通常语法：/pattern/ {actions}
pattern为正则表达式，但是pattern也可以为两个特殊模式BEGIN和END中的一个。当使用这些模式时，
awk '
	BEGIN {actions}
	/pattern/ {actions}
	/pattern/ {actions}
	END {actions}
' files
BEGIN模式必须是所指定的第一个模式，END模式必须是所指定的最后一个模式，在BEGIN和END之间，可以有任意数量的格式对，/pattern/{actions;}
BEGIN和END模式都是可选的，这样：
* 当指定BEGIN模式时，awk在读取任何输入前执行动作actions
* 当指定END模式时，awk在其退出前执行动作actions
若程序只包含一个BEGIN模式，awk在退出前不读入任何行。当awk的执行给出这些模式时，脚本执行顺序为：
1）若存在BEGIN模式，脚本执行其指定的动作actions
2）读取输入行并将其分析成域
3）针对输入行比较每个指定的模式pattern，直到发现匹配。当找到匹配时，脚本为该模式执行指定动作actions，并为所有不同模式pattern重复这一步
4）当输入行存在时，重复2）3）
5）在脚本读入所有输入行后，若END模式存在，它执行该模式指定的actions
解决之前的问题：
for i in $@;
do
	if [ -f $i ]; then
		echo -e "$i\c"
		awk '/^ *$/ {x=x+1;}
		END {printf " %s\n",x;}
		' "$i"
	else
		echo "ERROR:$i is not a file" >&2
	fi
done
内置变量输出域分隔符，默认空格
变量		描述
FILENAME	当前输入文件的文件名，不应该改变该变量的值
NR		输入文件中当前输入行或记录的编号，不应改变该变量的值
NF		当前行或记录中域的编号，不应改变该变量的值
OFS		输出域分隔符，默认空格
FS		输出域分隔符，默认空格或tab
ORS		输出记录分割符，默认换行符
RS		输入记录分割符，默认换行符
for i in $@;
do
	if [ -f $i ]; then
		awk 'BEGIN {printf "%s\t",FILENAME;}
		/^ *$/ {x=x+1;}
		END { ave=100 * (x/NR); printf " %s\t%3.1f\n",x,ave;}
		' "$i"
	else
		echo "ERROR:$i is not a file" >&2
	fi
done
改变输入域分隔符
输入域分隔符FS控制着awk如何将一个输入行分隔成域。可以手工将FS设置成其他任何字符，从而影响awk分隔输入行的方式。
两种方式：
* 在BEGIN模式中手工重置FS
* 为awk指定-F选项
例如将FS设为冒号“：” BEGIN{FS=":";} 或者 awk -F: '{...}'
两者的主要不同在于：-F选项可以使用Shell变量动态指定域分割符，如：
$MYFS=:;export MYFS;awk -F${MYFS} '{...}'
例如：$awk 'BEGIN {FS=":";} {print $1,$6;}' /etc/passwd
也可以写成 awk -F: '{print $1,$6;}' /etc/passwd
允许awk使用Shell变量
awk 'script' awkvar1=value awkvar2=value...files
假设变量作为$1提交给脚本
NUMFRUIT="$1"
if [ -f "NUMFRUIT" ] ; then NUMFRUIT=75 ; fi
awk '
	$3 <= numfruit {print ;}
' numfruit="$NUMFRUIT" fruit_prices.txt
流控制
* if语句
* while语句
* for语句
if(expr1){
	action1
}else if(expr2){
	action2
}else{
	action3
}
#!/bin/bash
awk'{
	printf "%s\t",$0;
	if($2 ~ /\$[1-9][0-9]*\.[0-9][1-9]/){
		printf "*";	
		if($3 <= 75){
			printf "REORDER\n"
		}else{
			printf "\n";	
		}
	}else{
		if($3 > 75){
			printf "REORDER\n";
		}else{
			printf "\n";
		}
	}
}' fruits_prices.txt
while语句
while(expr){
	actions
}
$awk 'BEGIN {x=0;while(x<5){x+=1;print x;}}'
do语句
do {
	actions
} while(expr)
$awk 'BEGIN{x=0;do{x+=1;print x;}while(x<5)}'
尽量使用nawk或gawk，老版本执行do有问题。
for循环
for(initialize_counter;test_counter;increment_counter){
	action
}
常用到for循环的地方：循环迭代处理记录中的域并输出它们，在该过程中，可能要改变每条记录。一下for循环打印记录中由两个空格分开的每个域.
#!/bin/bash
awk'{
	for (x=1;x<=NF;x+=1){
		printf "%s",$x
	}
	printf "\n"
}' fruit_prices.txt
各种工具
内部命令 eval...type
外部命令 sleep find xargs bc expr remsh
$output=">out.file"
$echo hello $output
output:hello >out.file
没有输出到文件
可以使用
eval echo hello $output
":"命令
":"字符是一个完整的Shell命令，它只用于返回一个完成代码“0”，该代码用于只是命令成功完成。它也可用作一个空操作no-op。空操作是一个什么
都不做的命令。这样命令就可以因为语法的需要安全的插入到命令的任何地方。
if [ -x $CMD ]
then :
else
	echo ERROR:$CMD is not executable >&2
fi
由于在一般情况下，":"返回的是成功结果，所以有时可以用它创建一个无限循环。
while :
do
	echo -e "Enter some fruit:\c"
	read INPUT
	[ "$INPUT" = stop ] && break;
done
有时会发现使用while true代替 while ：,但是后者效率更高，因为在Bourne Shell中，":"是一个内置命令而true必须从硬盘读入。
还有一种对":"命令的使用方法，这得益于Shell要为":"命令估计参数值这一事实。激活变量替换时，这是一种很有用的方法：
:${LINES:=24}${TREM:?"TERM not set"}
":"是一个空操作，但Shell仍计算它的参数，这样，若LINE为空或未定义，就为24.若TREM未定义，整个脚本失败并发出错误消息”TERM not set“
type命令
type命令可以告诉用户一个指定命令的全路径。
基本语法：
type command1 command2...
如果给出的命令不是作为一个独立的磁盘文件存在的实体，type会告诉用户它是否为如下类型的一种：
* Shell内置命令
* Shell关键字或保留字
* 别名
sleep命令
sleep n # n是睡眠或暂停的秒数 n一般不要超过65534
while ：
do
	date
	who
	sleep 300
done >> logfile
find命令
find start-dir options actions
eg: find / -name alpha -print
find /reports/1998 -name alpha -type f -print -exec lp{} \;
start-dir:注意为绝对路径还是相对路径
-name:可以使用通配符:* ? [charcters] [!charcters],必须用单撇号扩起来，否则find不起作用
find / -name '*alpha*' -print
-type:
类型	描述
f	规则或普通文件
d	目录
b	块设备文件
c	字符特殊设备
l	符号链接
p	命名管道
-mtime -atime -ctime
find -mtime 选项是的可以定位最后一次修改的文件，或者定位在很久一段时间内都未曾改变过的文件
find / -mtime -5 -print
-mtime接收一个整数参数，该参数以天为单位。上面这条find命令用于定位上次改变时间在最近5天之内的文件。当想要确定近来改变的文件但是又不记得
文件名或目录时，这是一个很有用的选项。
在-mtime后必须指定一个整数值
+n	只寻找改变日期在n天之前的	也就是最近n天内未改变的
n	只寻找改变日期恰在n天前当天的
-n	只寻找改变日期恰在n天之内的
find命令可以使用三种日期检查格式，每种都可以使用+n,n,-n作为参数
-mtime	找到上次改变时间大于、刚好在或小于n天前
-atime	找到上次访问时间大于、刚好在或小于n天前
-ctime	找到其inode上次改变时间大于、刚好在或小于n天前的文件。inode是磁盘表中的一项，它包含有关文件属性、大小、最后访问时间
	等信息。当文件最初被创建时，inode被改变；或者如果文件属主、组或访问许可权限被改变，inode也被改变
-size:可以基于文件大块大小定位文件
find / -size +2000 -print
打印所有大小超过2000块的文件的文件名。当想找到消耗磁盘空间最大的文件的时候，可以使用该选项。
+n	只寻找文件大小超过n块的文件
n	只寻找文件大小等于n块的文件
-n	只寻找文件大小小于n块的文件
组合选项
find / -name alpha -size +50 -mtime -3 -print
使用-o指定一个逻辑条件”或“
find / \(-size +50 -o -time -3\) -print
大小大于50块或者上次修改时间在三天内的文件
否定选项
使用”！“标记选择不匹配给定选项的文件
find /dev !\(-type b -o -type c -o type d\) -print
-print动作
告诉find显示匹配选项（在print前给出的选项）的文件的路径。若在命令行中把-print放在其他选项前，则在选择过程中不使用那些选项。
find / -size -20 -print -mtime +30
-mtime +30会被忽略
-exec动作
它使用户指定一个命令，该命令操纵每一个匹配给定选项的文件
find / -name alpha -exec chmod a+r {} \;
在-exec后应该指定一个完整的unix命令并将"{}"放在文件名应该插入的地方。在命令行末尾增加一个"\"，是为了完成所要求的语法。
find / -name core -exec rm -f {} \;
若有上千个文件要处理，xargs比-exec更高效，如
find / -name core -print | xargs rm -f
它也删除所有的core文件，而且，相比于-exec选项（它为每个文件的每次删除都调用一次rm）更迅速，开销更低
xargs
xargs它从标准输入接收一系列单词并将这些单词提供给一个给定命令作为参数
cat filelist | xargs rm
不能将cat的输出通过管道直接定向到rm，因为rm并不在标准输入上寻找文件名。xargs读取cat传来的文件并构造一个以rm开头以这些文件名
结尾的命令行。如果有大量文件，xargs会多次运行rm命令，每一次都删除这些文件的一部分。使用-n选项，可以指定每次从标准输入取来多少
参数用于构造命令行：
cat filelist | xargs -n 20 rm
-n 20是指在每个命令行上只放20个参数，这样每次只删除20个文件。
$ls
acme
report16
report3
report34
report527
$ls | xargs -n 2 echo ===
=== acme report16
=== report3 report34
=== report527
$
可以看出命令分三次执行了
xargs可以用于解决以下问题
$rm abc*
rm:arg list too long
当前目录包含太多以abc开头的文件名而且命令缓冲区溢出，所以打印错误信息，且文件没被删除。
ls | grep '^abc' | xargs -n 20 rm
expr命令
可以使用expr执行简单的整数算术运算
expr 2 / 3
通用语法 expr integer1 op integer2
op: + - \*(避免shell扩展) / %
注意参数之间都由一个空格分开，否则看不到结果
$expr 3+2
3+2
$
当一个变量增值时，expr常用在后引号中：
CNT=`expr $CNT + 1`
expr也可返回匹配一个正则表达式的字符数量
$ expr $ABC : '.*'
7
$ expr $ABC : '[0-9]*'
4 //知道$ABC第五个字符不是数字
$ expr abcdef : '..\(..\)..' 
cd // 每个点都是正则表达式通配符，代表给定字符串中的一个字符，中间两个点处于圆括号中，这样，那两个字符（cd）被输出
bc命令
bc是一个不局限于整数的算术工具
$bc
scale=4
8/3
2.6666
quit
$
+ - * / % ^
bc可以精确计算出任何大小的数字
ave=`echo "scale=4;$PRICE/$UNIT" | bc`
bc允许在不同进制之间转换
$bc
obase=16
ibase=8
$
obase : 输出设置成16进制
ibase :	输入设置成8进制
remsh/rsh/rcmd/remote

信号处理
1、shell编程中遇到的不同类型信号
2、使用kill
3、处理信号
4、怎样在脚本中
shell中重要信号
名称		值		描述
SIGHUP		1		检测控制终端的的挂起或控制进程的死亡	
SIGINT		2		键盘中断
SIGQUIT		3		从键盘退出
SIGKILL		9		杀死信号
SIGALRM		14		报警时钟信号
SIGTERM		15		终止信号
缺省动作
每个信号都有一个与之关联的缺省动作。一个信号的缺省动作是一个脚本或程序在接收到一个信号时执行的动作，缺省动作有
1、终止信号
2、忽略信号
3、内核转储 它创建一个名为core的文件，文件包含了接收到信号时进程的内存镜像
4、停止进程
5、继续一个停止的进程
传递信号
ctrl-c 传递SIGINT信号
传递信号的常用方法：
kill -signal pid
signal是要传递的信号数字或名字，pid是送往的进程ID
1）TERM
缺省情况下，kill向进程ID为pid的进程发送一个TERM或终止信号
kill pid 等价于 kill -s SIGTERM pid
2、HUP
kill -s SIGHUP 1001
向进程1001发送HUP或挂起信号。也可以使用信号的数字值
kill -1 1001
尽管该信号的缺省动作是让一个进程终止，但许多UNIX程序使用HUP信号来表明应该重新初始化本身。由于这个原因，用户如果要终止或杀死一个进程，应该使用不同的信号。
3、QUIT和INT
如果缺省不能终止一个进程，可以试着向进程发送QUIT或INT信号
kill -s SIGINT 1001 或 kill -s SIGQUIT 1001
这些信号应该终止一个进程，无论是要求它退出（QUIT）还是要求中断进程（INT）。
4、kill
一些程序和Shell脚本具有一类特殊的函数叫做信号处理函数，它能忽略或丢弃这些信号。要终止这样的程序，必须用kill信号：
kill -9 1001
处理信号
一个程序或者脚本可以使用三种不同的方式来处理信号：
* 不做任何处理而让缺省动作发生，这是脚本处理信号的最简单的方法
* 忽略信号并继续执行。这种方式与任何事情都不做是不同的，因为忽略一个信号要求在脚本中写一些代码来声明忽略信号
* 捕获信号并进行一些信号特定命令。使用这种方式的脚本在受到一个信号时有一个特殊的过程来执行。这是处理信号最复杂也是最强大的方式。
第一种方式：不需要用户在脚本中添加任何代码。
trap命令
trap命令设置或取消接收到一个信号时的动作，它的语法为：
trap name signals
当在signals中声明的信号被接收时，就执行name中列出的命令或shell函数的名字。如果没有给出name，则trap把给定信号的动作重设为缺省动作。
在shell脚本中有三种trap的常见用法。
* 清除临时文件
* 一直忽略信号
* 只在关键操作期间忽略信号
清除临时文件
使用shell清除临时文件：
trap "rm -f $TMPF;exit 2" 1 2 3 15
这里当接收到一个HUP，INT，QUIT或TERM信号时，就删除在$TEMF中存储的文件并返回代码2来指出退出非正常。脚本正常退出为0.非正常退出应为非零。
更复杂的退出使用函数：
CleanUp(){
	if [ -f "$OUTFILE" ];then
		printf"Cleaning up....";
		rm -f "$OUTFILE" 2> /dev/null;
		echo "Done";
	fi
}
trap CleanUp 1 2 3 15
一个“活着”的脚本在接收到不同信号时行为不同：
#!/bin/bash
if [ $# -lt 1 ]; then
	echo "USAGE:`basename $0` command."
	exit 0
fi
Init(){
	printf "INFO:Initializing..."
	# check if the last background pid is valid,if it is try an kill it.
	kill -0 $! 2>/dev/null
	if [ $? -eq 0 ]; then
		kill $! > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			echo "ERROR:Already running as pid $!.Exiting."
			exit 1
		fi
	fi
	#start a new program in the background
	$PROG &
	printf "Done.\n"
}

CleanUp(){
	kill -9 $!;exit 2;
}
#main()
trap CleanUp 2 3 15 
trap Init 1
while : ;
do
	wait $!
	$PROG &
done
忽略信号
两中方式：
trap '' signals
trap ： signals
在脚本关键操作期间忽略信号
trap '' 1 2 3 15
当在一个脚本中给出该命令时，脚本忽略所有信号，一直到它退出。
trap '' 1 2 3 15
DoImportantStuff
trap 1 2 3 15
建立一个计数器
在脚本中存在关键部分，这里的命令需要大量的时间来完成。在很少见的偶然情况下，这些命令也许还没完成。为了处理这种情况，用户需要在脚本中设置一个计数器，
当计数器到期时，应终止程序并通知用户非正常退出。
以下使用ALERM信号和一个信号处理函数设置一个计时器的主要内容。
脚本的主要动作：
1、为ALERM信号设置一个处理函数
2、设置计数器
3、执行程序
4、等待程序结束执行
5、取消计数器
如果计数器在程序结束前时间到，就需要ALARM信号的处理函数终止程序。
#main
trap AlarmHandler 14
SetTimer 15
$PROG &
CHPROCIDS="$CHPROCIDS $!"
wait $!
UnsetTimer
echo "All Done"
exit 0
变量$CHPROCIDS用来维护脚本所有的子进程列表，可能有的子进程为：
* 计数器
* 程序
AlarmHandler(){
	echo "Got SIGALERM,cmd too too long"
	KillSubProcs
	exit 14
}
KillSubProcs(){
	kill ${CHPROCIDS:-$!}
	if [ $? -eq 0 ]; then
		echo "Sub-processes killed";
	fi
}
SetTimer(){
	DEF_TOUT=${1:-10};
	if [ $DEF_TOUT -ne 0 ];then
		sleep $DEF_TOUT && kill -s 14 $$ &
		CHPROCIDS="$CHPROCIDS $!"
		TIMERPROC=$!
	fi	
}
计数器是一个后台进程，所以需要用进程ID来提交子进程列表。还要在变量TIMER PROC中保存计时器的进程ID，以便于在以后能取消计数器。
UnsetTimer(){
	kill $TIMERPORC
}

调试
1、语法检查
2、Shell跟踪
启动调试
启动调试的方法一：$/bin/bash option script arg1 arg2 ... argN
	方法二：改变脚本的第一行 $!/bin/bash option
shell调试选项
-n	读所有的命令，但是不执行它们
-v	在读时显示所有的行
-x	在执行时显示所有的行和它们的参数。该选项称为shell跟踪选项
以上的方法在调试一个脚本的时候有效，称为调用激活调试(invocaion activated)方式
使用set命令
调用激活调试模式时，调试模式的缺省行为对脚本中从第一行到最后一行都有效。有时候只需调试特定的函数或脚本的一部分，这是调试整个脚本就有些多余。
在本学时后可以看到调试输出十分广泛，通常很难从干扰中过滤出真正的错误。启动调试模式时可以使用set命令解决这个问题。
使用set命令，用户可以在shell脚本的任何地方启动或取消调试。
1、使用set启动模式
语法：set option
option是上图的选项之一。这些调试模式只当shell脚本程序员使用set命令时才被激活，所有称为 程序员激活 模式
#!/bin/bash
set -x
if [ -z "$1" ];then
	echo "error:insufficient args."
	exit 1
fi
set -x在if语句前出现，所以shell跟踪将在if语句执行时激活。除非在后面脚本中取消，否则直到脚本退出前总是有效。
2、使用set取消调试
set +option
所有为一个脚本启动的调试模式都可以使用下面的命令来取消。
set -
3、为一个函数启动调试模式
最常见的方法就是在一个函数执行前启动一个特定的调试模式，并在函数结束后取消模式
set -x;BuggyFunction;set +x;
这种调试方式只在函数调用前启动，并且在函数完成后取消。这种方法比在函数内部使用set命令启动调试要好，因为保证了函数实现不被改动。
语法检查
启动语法检查使用-n选项
/bin/bash -n script arg1 arg2 ...argN
#！/bin/bash
YN=y
if [ $YN = "y" ]
	echo "yes"
fi
$/bin/bash -n ./buggy.sh
output：./buggy.sh:syntax error at line 6:'fi' unexpected
因为if[ $YN = "y" ]后没有以then结尾
修改后就不会出现问题了
为什么应该使用语法检查
如果直接执行的话，它的输出与执行检查的输出是一样的啊？其实，并不总是这样的。
如果在出现错误的语法前已经执行了一些操作的话，那些操作已经产生影响了。如果是删除...
使用verbose模式
有时候光知道发生的错误是不够的，还希望看到发生错误的上下文，shell提供-v（verbose）调试模式检查语法错误发生的上下文。当声明这个选项的时候，shell在读脚本的每一行时都把它打印出来。
shell跟踪
在许多语法检查显示脚本没有问题时，并不是说明脚本真的没有问题。对一个脚本进行语法检查就相当于对一个文档进行拼写检查---它也许能发现大部分的拼写错误，但是它不修复类似于把read写成
red的错误。
用户需要通过阅读验证来发现和修改所有的拼写错误。要找到并修改这类错误，就需要使用shell跟踪。
在shell跟踪模式时，shell把每条命令按它执行的形式打印出来。
$set -x;ls *.sh;set +x
output:
+ls buggy.sh buggy1.sh buggy2.sh
buggy.sh buggy1.sh buggy2.sh
+set +x
带"+"符号的行是shell执行的命令，其他行是这些命令的输出。shell打印出ls命令的执行过程，在调试时及其有用，因为这使用户能判断所有的替换是否正确执行。
调试陷阱
#!/bin/bash

Debug(){
	if [ "$DEBUG" = "true" ]; then
		if [ "$1" = "on" -o "$1" = "ON" ]; then
			set -x
		else
			set +x
		fi
	fi
}
Failed(){
	Debug on
	if [ "$1" -ne 0 ];then
		echo "Failed.Exiting.";exit 1;
	fi
	echo "Done"
	Debug off
}
YesNo(){
	Debug on
	echo -e "$1 (y/n)" \c
	read RESPONGSE
	case "RESPONSE" in
		[yY]|[Yy][Ee][Ss]) RESPONSE=y ;;
		*) RESPONSE=n ;;
	esac
	Debug off
}
YesNo "Make backup"
if [ "RESPONSE" = "y" ]; then
	echo -e "Deleting old backups,please wait ...\c"
	rm -r backup > /dev/dull 2>&1
	Failed $?
fi
当脚本如下执行时，输出都是正常的
$/bin/bash ./buggy3.sh
$./buggy3.sh
当脚本如下执行时，输出将包括shell跟踪
$DEBUG=true /bin/bash ./buggy3.sh
$DEBUG=true ./buggy3.sh
使用函数解决问题
创建函数库
main code
#!/bin/bash	# main code
MSG="hello"	# main code
echo_error(){echo "ERROR:" $@ >&2 ;}
echo_error $MSG	# main code
shell 函数库不包含任何主代码，而只包含函数
#!/bin/bash
echo_error(){echo "ERROR:" $@ >2&;}
echo_warning(){echo "WARNING:" $@ >&2;}
并没有限制一个库中不能包含主代码。脚本和库只是概念上的区别。为了维护简单，用户应该在一个脚本中避免使用函数定义外的任何代码。
从一个库中包含函数
使用“.”命令，语法为：
.file
eg:
messages.sh
#!/bin/bash
MSG="hello"
echo_error() {echo "ERROR:" $@ >&2;}
echo_error $MSG
重写为：
#!/bin/bash
. $HOME/lib/sh/messages.sh
MSG="hello"
echo_error $MSG
如果mseeages.sh不存在将会显示错误。


























































