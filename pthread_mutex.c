#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int tickets = 100; //假设有100张火车票
pthread_mutex_t  mutex;//由于互斥锁为一个临界资源，需要被各个线程访问


void *func(void *arg)
{
	while(1)
	{
		//加锁放在临界资源访问之前，保护临界区资源
		pthread_mutex_lock(&mutex);
		if(tickets>0)
		{
			sleep(1);
			printf("抢到一张票%p,票号为：%d\n",pthread_self(),tickets);
			tickets--;
			pthread_mutex_unlock(&mutex);
		}
		else
		{
			//在任意有可能退出的地方都需要解锁
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);//没有票退出
		}
	}
}

int main()
{
	int i;
	pthread_t tid[4];//模拟四个黄牛
	//初始化互斥锁，一定要在创建线程前初始化
	pthread_mutex_init(&mutex,NULL);
	for(i = 0 ;i<4;++i)
	{
		int ret = pthread_create(&tid[i],NULL,func,NULL);
		if(ret !=0)
		{
			printf("线程创建失败\n");
			return -1;
		}
	}
	for(i = 0;i<4;++i)
	{
		pthread_join(tid[i],NULL); //等待线程退出
	}
	//不使用互斥锁，则释放锁资源
	pthread_mutex_destroy(&mutex);
	return 0;
}
