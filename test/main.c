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
    
    // putchar(getchar());  // getchar����ֻ�ܽ���һ���ַ�

    /* printf() 
        
        %      d
        ^      ^
     ��ʽ���� ��ʽ�ַ�

        %m.nf ָ�������ʵ��ռm��,����nλС��,����m����>n

        %d,i: �Դ����ŵ�ʮ������ʽ�������
        %o: �԰˽����޷�����ʽ�������
        %x,X: ��ʮ�������޷�����ʽ�������
        %u: ���޷�����ʽ�������
        %c: ���ַ�����ʽ���,ֻ���һ���ַ�
        %s: ����ַ���
        %f: ��С����ʽ�������˫������,���������λС��
        %e,E: ��ָ����ʽ���
        %l: ���ڳ���������(%ld, %lo, %lx, %lu)�Լ�double������

        scanf("%d, %d", &a, &b)  # ����������ʱҲӦ�ñ�����ʽ  '1, 2'
                  ^       ^
               ��ʽ����  �����б�

        getchar() + 32,��ɴ�д

    */

    struct student* head, * p;

    head = p = (struct student*)malloc(LEN);

    scanf("%d,%f", &p->num, &p->score);

    p = (struct student*) malloc(LEN);

    scanf("%d,%f", &p->num, &p->score);

    head->next = p;

    p->next = NULL;

    p = head;

    printf("\n�ڵ� 1:%d,%6.2f\n", p->num, p->score);

    p = p->next;

    printf("��� 2:%d,%6.2f\n", p->num, p->score);
    
    return 0;
}
