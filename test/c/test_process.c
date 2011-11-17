#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char * pre = "update"; // 显示在前面的提示
#define NPRE 10
#define NSUF 8
#define NSTAR 4
const char star[NSTAR] = {'|','/','-','\\'}; // 旋转符号

int main()
{
    int output_width = 80; // 瞎填的
    struct winsize winsz;
    char *str;
    char *sq;
    char perc[10];
    int n;
    int size;
    int nq,k;

    n = 0;
    while (n<100)

         /*获得窗口大小*/
        if (isatty(1) && ioctl(1, TIOCGWINSZ, &winsz) >= 0) {
            if (winsz.ws_col > output_width) output_width = winsz.ws_col;

             /*申请一个buffer*/
            if ((str = malloc(output_width))) {

                 /*首先都填满空格符*/
                memset(str, 0x20, output_width); // 0x20 is space
                memcpy(str, pre, strlen(pre));
                n++; // 进度

                /*写入转动的横线，和百分制的进度*/
                size = snprintf(perc, 10, " %c%3d%%", star[n%NSTAR], n);
                if (size > 0) {
                    snprintf(&str[output_width-size-NSUF], size, "%s",perc);

                    /*下面填入滚动箭头*/
                    sq = &str[NPRE];
                    nq = output_width - NPRE - size - NSUF -3;
                    k = n%nq+1;
                    memset(sq, '=', k);
                    sq[0] = '[';
                    sq[k] = '>';
                    sq[nq-1] = ']';

                    /*输出回车符，光标回到行首*/
                    write(1, "\r", 1);

                    /*输出进度，输出也可以使用printf函数，需要fflush*/
                    write(1, str, output_width);
                }

                /*睡1秒*/
                sleep(1);
            }
        }
}
