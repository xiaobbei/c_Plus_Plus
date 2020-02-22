#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void *Join_func(void *arg)
{
	printf("Normal thrread will eixt\n");
	sleep(5);
	char *buf = "Normal thread eixt\n";
	return buf;
}

int main()
{
	pthread_t tid;
	int ret = pthread_create(&tid,NULL,Join_func,NULL);
	if(ret!=0)
	{
		printf("thread create failed\n");
		return -1;
	}
	printf("Main thread waiting Normal thread to eixt\n");
	char *retval = NULL;
	pthread_join(tid,(void**)&retval);
	printf("retval:%s\n",retval);
	return 0;
}

