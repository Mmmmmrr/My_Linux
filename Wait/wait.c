//非阻塞的等待方式
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        exit(1);
    }
    else if(id == 0)
    {
        //child
        printf("I am child\n");
        sleep(5);
        exit(20);
    }
    else
    {
        int status = 0;
        pid_t ret = 0;
        do
        {
            ret = waitpid(-1,&status,WNOHANG);
            if(ret == 0)
            {
                printf("child is running\n");
            }
            sleep(1);
        }while(ret == 0);
        if(WIFEXITED(status) && ret == id)
        {
        printf("wait success,child return code is %d\n",WEXITSTATUS(status));
        }
        else
        {
            printf("wait child fail,return\n");
            return 1;
        }
    }
    return 0;
}


//阻塞的等待方式
//int main()
//{
//    pid_t id = fork();
//    if(id < 0)
//    {
//        perror("fork");
//        exit(1);
//    }
//    else if(id == 0)
//    {
//        //child
//        printf("I am child\n");
//        sleep(5);
//        exit(20);
//    }
//    else
//    {
//        int status = 0;
//        pid_t ret = waitpid(-1,&status,0);//   阻塞式等待，等待5s
//        printf("procc wait...\n");
//        if(WIFEXITED(status) && ret == id)
//        {
//            printf("wait success,child return code is :%d.\n",WEXITSTATUS(status));
//
//        }else
//        {
//            printf("wait fail,return.\n");
//            return 1;
//        }
//    }
//    return 0;
//  }
//


//正常退出与信号杀死退出
//int main()
//{
//    pid_t id = fork();
//    if(id < 0)
//    {
//        perror("fork");
//        exit(1);
//    }
//    if(id == 0)
//    {
//        printf("I am child...\n");
//        sleep(20);
//        exit(10);
//    }
//    else
//    {
//        int st;
//        int ret = wait(&st);
//        if(ret > 0 && (st & 0x7F) == 0)
//        {
//            //正常终止
//            printf("child exit code:%d\n",(st >> 8)&0x7F);
//        }
//        else if(ret > 0)
//        {
//            //异常退出
//            printf("sig code:%d\n",st&0x7F);
//        }
//    }
//}
