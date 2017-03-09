#include <stdio.h>
#include <string.h>
#define clr(m) memset(m,0,sizeof m)
const char alpha[]={"abcdefghijklmnopqrstuvwxyz"};
//普通加密，buf为待加密字符串，k为偏移量
void encrypt(char *buf, int k) {
    for (int i=0; buf[i]; i++) {
        buf[i] = alpha[(buf[i]-'a'+k)%26];
    }
    printf("%s\n",buf);
}
//普通解密，buf为待解密字符串，k为偏移量
void decrypt(char *buf, int k) {
    for (int i=0; buf[i]; i++) {
        buf[i] = alpha[(buf[i]-'a'-k+26)%26];
    }
    printf("%s\n",buf);
}
//普通暴力解密，buf为待解密字符串
void decrypt(char *buf) {
    for (int j=1; j<=25; j++) {
        decrypt(buf, 1);
    }
}
//改进加密，buf为待加密字符串，key为偏移量
void encrypt(char *buf, int *key) {
    for (int i=0; buf[i]; i++) {
        buf[i] = alpha[(buf[i]-'a'+key[buf[i]-'a'])%26];
    }
    printf("%s\n",buf);
}
//改进解密，buf为待解密字符串，key为偏移量
void decrypt(char *buf, int *key) {
    for (int i=0; buf[i]; i++) {
        buf[i] = alpha[(buf[i]-'a'-key[buf[i]-'a']+26)%26];
    }
    printf("%s\n",buf);
}
int main() {
    int k,a[26];                                    //表示偏移量
    char s[2333],op[2333];                          //设成2333能防止大多数无效输入，op为操作符，s为输入字符串
    while (1) {
        puts("请选择功能：1加密，2解密，3暴力，4改进加密，5改进解密，6退出。");
        scanf("%s",op);

        //初始化变量
        bool flag = false;                          //退出标志
        clr(s);
        clr(a);

        switch (op[0]) {
            case '1':
                puts("请输入待加密的字符串s和移动常量位k:");
                scanf("%s%d",s,&k);
                printf("密文如下：");
                encrypt(s,(k+1300)%26);              //有效防止输入值为负或大于等于26的情况
                break;
            case '2':
                puts("请输入待解密的字符串s和移动常量位k:");
                scanf("%s%d",s,&k);
                printf("原串如下：");
                decrypt(s,(k+1300)%26);              //有效防止输入值为负或大于等于26的情况
                break;
            case '3':
                puts("请输入待暴力破解的字符串s:");
                scanf("%s",s);
                puts("所有可能解法如下：");
                decrypt(s);
                break;
            case '4':
                puts("请输入待加密的字符串s和各字母移动数:");
                scanf("%s",s);
                k = strlen(s);
                for (int i=0; i<26; i++) {
                    scanf("%d",&a[i]);
                    a[i] = (a[i] + 1300) % 26;       //有效防止输入值为负或大于等于26的情况
                }
                printf("密文如下：");
                encrypt(s,a);
                break;
            case '5':
                puts("请输入待解密的字符串s和各字母移动数:");
                scanf("%s",s);
                k = strlen(s);
                for (int i=0; i<26; i++) {
                    scanf("%d",&a[i]);
                    a[i] = (a[i] + 1300) % 26;       //有效防止输入值为负或大于等于26的情况
                }
                printf("原串如下：");
                decrypt(s,a);
                break;
            case '6':
                flag = true;
                break;
            default:
                puts("无效输入。");
                break;
        }
        if (flag) {
            puts("再见。");
            break;
        }
    }
    return 0;
}
