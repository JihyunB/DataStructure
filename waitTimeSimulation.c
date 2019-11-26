#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queueADT.h"
#define CHANCE 35//매 분마다 손님이 나타날 확률 (%)
typedef struct
{
	int arriveTime;//도착 시간 
	int startTime;//서비스가 시작되는 시간 
	int svcTime;//서비스를 받아야하는 시간 
	int custNumber;//손님 수를 세기 위한 변수 
}customer;

customer* newCustomer(int,int*);//새로운 손님이 오는 경우 발생시키는 함수 

int main()
{
	srand(time(NULL));
	QUEUE* q;//대기열 
	customer* cust;//새로운 손님을 발생시키기 위해 생성 
	customer* now;//현재 서비스를 받고 있는 손님 
	q = createQueue();
	
	int count=1;//손님 수를 세는 변수 
	int clock=1;//시간 
	int workTime=0;//종업원이 서비스 시간을 채웠는지 확인을 위한 변수 
	int freeTime=0;//종업원이 쉰 시간 
	int totalWait=0;//전체 손님 대기 시간 
	int totalSvc=0;//전체 손님 서비스 요구 시간 
	int queueMax=0;//최대 대기열 
	
	while(clock<480||!(emptyQueue(q)))//480분 즉 8시간 동안 영업, 그 안에 손님이 와 있으면 480분이 지나도 계속 진행 
	{
		if(((rand()%100)+1)<=CHANCE&&(clock<480))//480분이 안됬으면 매 분마다 CHANCE % 로 손님 발생 
		{
			cust = newCustomer(clock,&count);
			enqueue(q,cust);
			totalSvc += cust->svcTime;
			if(queueMax<queueCount(q))
				queueMax = queueCount(q);
		}//손님이 오면 큐에 넣음 
		
		queueFront(q,(void**)&now);//큐에서 가장 먼저온 손님이 현재 서비스르 받는 now에 할당 됨 
		
		if(!(emptyQueue(q)))//큐에 손님이 있는지 확인 
		{	
			clock++;
			workTime++;
			if(workTime == now->svcTime)
			{
				workTime = 0;
				totalWait += clock-(now->arriveTime);
				dequeue(q,(void**)&now);
			}//clock 이 흐르면서 worktime이 올라가고 worktime이 now의 서비스타임과 같아지면 서비스가 완료되어 첫번째 손님을 dequeue, worktime은 0으로 초기화 
			
		}
		else
		{
			clock++;
			freeTime++;
		}//손님이 없으면 시간이 흐르고 freetime 증가 
	}
	
	destroyQueue(q);//시간이 다 흐르면 큐를 초기화, customer는 함수의 dataptr에서 초기화되므로 따로 초기화하지 않음 

	printf("Simulation Statistics %d%% chance:\n",CHANCE);
	printf("Total customers: %d\n",count);
	printf("Total service time: %d\n",totalSvc);
	printf("Average service time: %.2f\n",(float)totalSvc/count);
	printf("Average wait time: %.2f\n",(float)totalWait/count);	
	printf("Maximum queue size: %d\n",queueMax);
	//시뮬레이션 결과 출력
		
	return 0;
}

customer* newCustomer(int clock,int* count)//새로운 손님이 올 경우 난수로 서비스타임을 정하고 순번 부여해서 리턴 
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
