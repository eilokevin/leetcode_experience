#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *phoneMap[10] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};
// int参数无需在传递中保存值，递归返回仍是原来的值，而returnsize需要在传递中保存值，故使用指针
void backtrack(char *digits,int index,char *current,char **result,int *returnsize){
    if (digits[index] == '\0') {
        // 这里不能这样写，因为current是一个临时缓冲区，如果这样写，所有的结果都会被最终一次的结果覆盖掉
        // result[*returnsize] = current;
        result[*returnsize] = strdup(current);  // 深拷贝字符串副本，分配新内存并拷贝内容
        (*returnsize)++;
        return;
    };

    int digit = digits[index]-'0';
    char *letters = phoneMap[digit];
    int len = strlen(letters);

    for (int i =0;i<len;i++){
        current[index] = letters[i];
        backtrack(digits,index+1,current,result,returnsize);
    }
};
// 返回结果字母组合,为什么需要returnsize这个参数，因为生成结果后，需要知道生成了几个，这样在函数外传入就不用全局变量或者结构体来记录，放置遍历越界
char **letterCombinations(char *digits, int *returnSize){
    *returnSize=0;
    int len = strlen(digits);
    if (len==0){
        return NULL;
    }
    // 计算最大数组大小
    int maxSize=1;
    for (int i=0;i<len;i++){
        int digit=digits[i]-'0';
        if (digit==7||digit==9){
            maxSize*=4;
        }
        else if (digit>=2){
            maxSize*=3;
        }
    }

    //分配内存
    char **result = (char **) malloc(maxSize * sizeof(char *));
    char *current = (char *)malloc((len + 1) * sizeof(char));
    current[len] = '\0';  // 字符串结束符

    backtrack(digits,0,current,result,returnSize);
    free(current);
    return result;
}
int main(){
    char digits[100];  // 限制输入长度为99字符（留1位给'\0'）
    int size;
    char **combinations;
    // 1. 使用 scanf 读取输入（限制长度防止缓冲区溢出）
    printf("请输入电话号码（仅包含2-9的数字，长度≤99）：");
    if (scanf("%99s", digits) != 1) {  // %99s 最多读取99个字符
        printf("输入失败！\n");
        return 1;
    }

    // 2. 验证输入：仅允许2-9的数字
    for (int i = 0; digits[i] != '\0'; i++) {
        if (!isdigit(digits[i]) || (digits[i] < '2' || digits[i] > '9')) {
            printf("错误：输入包含无效字符或0/1！\n");
            return 1;
        }
    }
    combinations = letterCombinations(digits,&size);
    printf("\n输入的电话号码：%s\n", digits);
    if (size == 0) {
        printf("没有对应的字母组合。\n");
    } else {
        printf("生成的字母组合数量：%d\n", size);
        printf("组合列表：\n");
        for (int i = 0; i < size; i++) {
            printf("%d. %s\n", i + 1, combinations[i]);
            free(combinations[i]);  // 释放strdup申请的每个字符串
        }
    }
    
    // 6. 释放内存
    free(combinations);  //释放result
    
    return 0;
}
