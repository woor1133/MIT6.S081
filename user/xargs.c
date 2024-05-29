#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* concatStrings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char)); // 分配足够的内存空间

    strcpy(result, str1); // 复制第一个字符串
    strcat(result, str2); // 追加第二个字符串

    return result;
}


void
xargs(int argc,char *argv[],char buf){
    concatStrings()
    int ret,status;
    ret = fork();
    if(ret<0){
            printf("the fork is error");
            exit(1);
    }
    else if(fork==0){
        exec(argv[1],)
    }
    else{
        wait(&status);
    }



}

int main(int argc,char *argv[]){
    char* buf_arg[MAXARG];
    int n;
    for(;;){
        n = read(0,buf_arg,sizeof(char));
        if(n==0) break;
        if(n<0){
            fprintf(2,"read error\n");
            exit(1);
        }
        if(buf_arg=='\n') break;
    }
    xargs(argc,argv,buf_arg);

    return 0;
}