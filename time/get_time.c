#include<stdio.h>
#include<time.h>
int main(int argc, const char * argv[]) {
    struct tm *ptr;
    time_t it;
    
    /*获取日历时间*/
    it = time(NULL);
    /*转化为本地时间*/
    ptr = localtime(&it);
    
    /*以本地时间的字符串方式打印*/
    printf("%s\n",asctime(ptr));
    
    /*以本地时间的字符串方式打印*/
    printf("%s\n",ctime(&it));
    return 0;
}

