#include <stdio.h>
#include <stdlib.h>

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

int main() {

    char buffer[1024]; // 缓冲区，用于存储从文件中读取的数据

    // 打开文件
    FILE *file = fopen("D:\\xst_project_202212\\codeSet\\C\\test\\test.txt", "r"); // 替换为你的文件名
    if (file == NULL) {
        perror("Error opening file"); // 打印错误消息
        return 1;
    }

    // 读取并打印文件内容
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    // 关闭文件
    fclose(file);

}