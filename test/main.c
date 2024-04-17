#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS = 3
#define LEN sizeof(struct student)

struct student {
    int num;
    float score;
    struct student* next;
};

int main()
{
    
    // putchar(getchar());  // getchar函数只能接收一个字符

    /* printf() 
        
        %      d
        ^      ^
     格式声明 格式字符

        %m.nf 指定输出的实属占m列,公有n位小数,其中m必须>n

        %d,i: 以带符号的十进制形式输出整数
        %o: 以八进制无符号形式输出整数
        %x,X: 以十六进制无符号形式输出整数
        %u: 以无符号形式输出整数
        %c: 以字符串形式输出,只输出一个字符
        %s: 输出字符串
        %f: 以小数形式输出单，双精度数,隐含输出六位小数
        %e,E: 以指数形式输出
        %l: 用于长整型数据(%ld, %lo, %lx, %lu)以及double型数据

        scanf("%d, %d", &a, &b)  # 在输入数据时也应该保持形式  '1, 2'
                  ^       ^
               格式控制  变量列表

        getchar() + 32,变成大写

    */

    struct student* head, * p;

    head = p = (struct student*)malloc(LEN);

    scanf("%d,%f", &p->num, &p->score);

    p = (struct student*) malloc(LEN);

    scanf("%d,%f", &p->num, &p->score);

    head->next = p;

    p->next = NULL;

    p = head;

    printf("\n节点 1:%d,%6.2f\n", p->num, p->score);

    p = p->next;

    printf("结点 2:%d,%6.2f\n", p->num, p->score);
    
    return 0;
}
