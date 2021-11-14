/*************************************************************************
>> File Name: cond_example5.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月15日 星期一 00时22分10秒

>> 此程序的功能是：
************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//链表的结点
struct msg
{
    int num;
    struct msg *next;
};

struct msg *head = NULL;    //头指针
struct msg *temp = NULL;    //节点指针

//静态方式初始化互斥锁和条件变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_producer = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    while (1)   //线程正常不会解锁，除非收到终止信号
	{
        pthread_mutex_lock(&mutex);         //加锁

        temp = malloc(sizeof(struct msg));
        temp->num = rand() % 100 + 1;
        temp->next = head;
        head = temp;                        //头插法
        printf("---producered---%d\n", temp->num);

        pthread_mutex_unlock(&mutex);       //解锁
        pthread_cond_signal(&has_producer); //唤醒消费者线程
        usleep(rand() % 3000);              //为了使该线程放弃cpu,让结果看起来更加明显。
    }

    return NULL;
}

void *consumer(void *arg)
{
    while (1)       //线程正常不会解锁，除非收到终止信号
	{
        pthread_mutex_lock(&mutex);     //加锁
        while (head == NULL)            //如果共享区域没有数据，则解锁并等待条件变量
	    {
            pthread_cond_wait(&has_producer, &mutex);   //我们通常在一个循环内使用该函数
        }
        temp = head;
        head = temp->next;
        printf("------------------consumer--%d\n", temp->num);
        free(temp);                     //删除节点，头删法
        temp = NULL;                    //防止野指针
        pthread_mutex_unlock(&mutex);   //解锁

        usleep(rand() % 3000);          //为了使该线程放弃cpu,让结果看起来更加明显。
    }

    return NULL;
}

int main(void)
{
    pthread_t ptid, ctid;
    srand(time(NULL));      //根据时间摇一个随机数种子

    //创建生产者和消费者线程
    pthread_create(&ptid, NULL, producer, NULL);
    pthread_create(&ctid, NULL, consumer, NULL);

    //主线程回收两个子线程
    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);

    return 0;
}
