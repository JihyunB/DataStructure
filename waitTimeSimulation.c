#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queueADT.h"
#define CHANCE 35//�� �и��� �մ��� ��Ÿ�� Ȯ�� (%)
typedef struct
{
	int arriveTime;//���� �ð� 
	int startTime;//���񽺰� ���۵Ǵ� �ð� 
	int svcTime;//���񽺸� �޾ƾ��ϴ� �ð� 
	int custNumber;//�մ� ���� ���� ���� ���� 
}customer;

customer* newCustomer(int,int*);//���ο� �մ��� ���� ��� �߻���Ű�� �Լ� 

int main()
{
	srand(time(NULL));
	QUEUE* q;//��⿭ 
	customer* cust;//���ο� �մ��� �߻���Ű�� ���� ���� 
	customer* now;//���� ���񽺸� �ް� �ִ� �մ� 
	q = createQueue();
	
	int count=1;//�մ� ���� ���� ���� 
	int clock=1;//�ð� 
	int workTime=0;//�������� ���� �ð��� ä������ Ȯ���� ���� ���� 
	int freeTime=0;//�������� �� �ð� 
	int totalWait=0;//��ü �մ� ��� �ð� 
	int totalSvc=0;//��ü �մ� ���� �䱸 �ð� 
	int queueMax=0;//�ִ� ��⿭ 
	
	while(clock<480||!(emptyQueue(q)))//480�� �� 8�ð� ���� ����, �� �ȿ� �մ��� �� ������ 480���� ������ ��� ���� 
	{
		if(((rand()%100)+1)<=CHANCE&&(clock<480))//480���� �ȉ����� �� �и��� CHANCE % �� �մ� �߻� 
		{
			cust = newCustomer(clock,&count);
			enqueue(q,cust);
			totalSvc += cust->svcTime;
			if(queueMax<queueCount(q))
				queueMax = queueCount(q);
		}//�մ��� ���� ť�� ���� 
		
		queueFront(q,(void**)&now);//ť���� ���� ������ �մ��� ���� ���񽺸� �޴� now�� �Ҵ� �� 
		
		if(!(emptyQueue(q)))//ť�� �մ��� �ִ��� Ȯ�� 
		{	
			clock++;
			workTime++;
			if(workTime == now->svcTime)
			{
				workTime = 0;
				totalWait += clock-(now->arriveTime);
				dequeue(q,(void**)&now);
			}//clock �� �帣�鼭 worktime�� �ö󰡰� worktime�� now�� ����Ÿ�Ӱ� �������� ���񽺰� �Ϸ�Ǿ� ù��° �մ��� dequeue, worktime�� 0���� �ʱ�ȭ 
			
		}
		else
		{
			clock++;
			freeTime++;
		}//�մ��� ������ �ð��� �帣�� freetime ���� 
	}
	
	destroyQueue(q);//�ð��� �� �帣�� ť�� �ʱ�ȭ, customer�� �Լ��� dataptr���� �ʱ�ȭ�ǹǷ� ���� �ʱ�ȭ���� ���� 

	printf("Simulation Statistics %d%% chance:\n",CHANCE);
	printf("Total customers: %d\n",count);
	printf("Total service time: %d\n",totalSvc);
	printf("Average service time: %.2f\n",(float)totalSvc/count);
	printf("Average wait time: %.2f\n",(float)totalWait/count);	
	printf("Maximum queue size: %d\n",queueMax);
	//�ùķ��̼� ��� ���
		
	return 0;
}

customer* newCustomer(int clock,int* count)//���ο� �մ��� �� ��� ������ ����Ÿ���� ���ϰ� ���� �ο��ؼ� ���� 
{
	customer* cust;
	
	cust = (customer*) malloc(sizeof(customer));
	if(cust)
	{
		cust->arriveTime=clock;
		cust->startTime=0;
		cust->svcTime=(rand()%5)+1;
		cust->custNumber = *count;
		(*count)++;
	}
	return cust;
}
