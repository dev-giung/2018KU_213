#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define SIZE_QUEUE 100	//the maximum size of the news_queue
#define CAPACITY 6  //the capacity of ZNN.com (per sec)
#define NUM_USER 20  //the number of users
#define NUM_LOOP 100	//the number of loops


//ContentFidelity is one of the types: video, image, text
typedef enum { Video, Image, Text } ContentFidelity;

typedef struct {
	unsigned int requestedBy;
	ContentFidelity fidelity;
	unsigned int waitingtime;
} news;

typedef struct {
	news queue[SIZE_QUEUE];
	unsigned int front;
	unsigned int rear;
	unsigned int num;
} Queue;

Queue news_queue;
ContentFidelity currentFidelity = Video;
double array[20][3];// 사용자별 평균 대기시간, 점수를 구하기 위한 이차원 배열


/*메인 함수 선언*/
void request(Queue *q);
void setFidelity(Queue *q);
void provide(Queue *q);
void printQueue(Queue *q);
void printResult();

/*큐 관련 함수 선언*/
void initQ(Queue *q);
int is_empty(Queue *q);
int is_full(Queue *q);
void enQueue(Queue *q, news item);
news deQueue(Queue *q);
news peek(Queue *q);



void main() {
	initQ(&news_queue);
	unsigned int nthLoop;
	for (nthLoop = 0; nthLoop < NUM_LOOP; nthLoop++) {
		printf("\n=======%d seconds======\n", nthLoop);
		//users can request contents every two loops
		if (nthLoop % 2 == 0) {
			setFidelity(&news_queue);
			request(&news_queue);
		}
		printQueue(&news_queue);
		provide(&news_queue);
	}

	printResult();
}


void initQ(Queue *q) {
	q->front = 0;
	q->rear = 0;
	q->num = 0;
}


int is_empty(Queue *q) {
	return (q->front == q->rear);
}

int is_full(Queue *q) {
	return ((q->rear + 1) % SIZE_QUEUE == q->front);
}

void enQueue(Queue *q, news item) {
	if (is_full(q)) return;
	else {
		q->rear = (q->rear + 1) % SIZE_QUEUE;
		q->queue[q->rear] = item;
	}
}

news deQueue(Queue *q) {
	if (is_empty(q)) exit(1);
	else {
		q->front = (q->front + 1) % SIZE_QUEUE;
		return q->queue[q->front];
	}
}

//큐의 첫번째 원소를 리턴하는 함수
news peek(Queue *q) {
	if (is_empty(q)) exit(1);
	else return q->queue[(q->front + 1) % SIZE_QUEUE];
}

//콘텐츠를 요청하고 큐에 들어가는 알고리즘, 요청하는 사용자의 번호를 출력한다
void request(Queue *q) {

	news temp;
	int i = 0;
	int j;

	printf(" >>>>Requesting(ENQUEUE): ");
	for (i = 0; i < NUM_USER; i++) {
		int state = 1;		
		for (j = q->front + 1 ; j < (q->front + 1 + q->num); j++) {
		//한번 콘텐츠를 요청한 사용자는 그 콘텐츠가 제공되기 전까지 새로운 콘텐츠 요청을 할 수 없다. 조건을 만족하기 위한 검색 과정
			if (i == news_queue.queue[j%SIZE_QUEUE].requestedBy){
				state = 0;						
			}
		}
		if (state == 1) {			
			if (rand() % 2 == 0) {//50%확률
				temp.fidelity = currentFidelity;
				temp.requestedBy = i;
				temp.waitingtime = 0;
				printf("%d, ", i);
				enQueue(q, temp);
				q->num++;
			}
		}
	}
	printf("\n");
}
//콘텐츠 형태 조정 알고리즘, 계산한 평균 콘텐츠 대기시간과 조절된 콘텐츠 형태를 출력한다
void setFidelity(Queue *q) {
	int i = 0;
	double sum = 0;
	double aver_waiting_time = 0;
	char *contentType;

	//평균 대기 시간 구하기
	for (i;i < q->num;i++)
	{
		sum = sum + q->queue[(q->front + 1 + i) % SIZE_QUEUE].waitingtime;
	}
	aver_waiting_time = sum / q->num;
	if (_isnan(aver_waiting_time)) aver_waiting_time = 0;

	//평균 대기 시간에 따른 콘텐츠 종류 변경
	if (aver_waiting_time >= 3)
	{
		if (currentFidelity == Image)
		{
			currentFidelity = Text;
		}
		else if (currentFidelity == Video)
		{
			currentFidelity = Image;
		}		
	}
	else if (aver_waiting_time <= 2)
	{
		if (currentFidelity == Image)
		{
			currentFidelity = Video;
		}
		else if (currentFidelity == Text)
		{
			currentFidelity = Image;
		}
	}
	if (currentFidelity == 0) contentType = "Video";
	else if (currentFidelity == 1) contentType = "Image";
	else if (currentFidelity == 2) contentType = "Text";
	printf("Average waiting time: %lf, Current Quality: %s\n", aver_waiting_time, contentType);	
}

//콘텐츠 제공 알고리즘, 어느 콘텐츠가 제공되었는지 출력한다
void provide(Queue *q) {
	int i = 0;
	int curCap = 0, size = 0;
	char *contentType;

	printf("Providing(DEQUEUE): ");

	while (1) {

		if (is_empty(q)) {
			break;
		}

		if (peek(q).fidelity == Video) {//콘텐츠 종류에 따른 크기
			size = 3;
		}
		else if (peek(q).fidelity == Image) {
			size = 2;
		}
		else if (peek(q).fidelity == Text) {
			size = 1;
		}

		if (curCap + size > CAPACITY) {//초당 최대 6밖에 제공 못함
			break;
		}

		news temp = deQueue(q);
		q->num--;
		if (temp.fidelity == 0) contentType = "Video";
		else if (temp.fidelity == 1) contentType = "Image";
		else if (temp.fidelity == 2) contentType = "Text";
		printf("(%u, %s), ", temp.requestedBy, contentType);
		curCap = curCap + size;
		//나중에 사용자별 평균을 내기 위한 이차원 배열 활용
		array[temp.requestedBy][0] = array[temp.requestedBy][0] + temp.waitingtime;
		array[temp.requestedBy][1] = array[temp.requestedBy][1] + size;
		array[temp.requestedBy][2]++;

	}
	
	printf("\n");

	for (i;i < q->num;i++)//대기 시간 측정
	{
		q->queue[(q->front + 1 + i) % SIZE_QUEUE].waitingtime++;
	}
}

//현재 큐에 들어 있는 콘텐츠들을 출력하는 함수
void printQueue(Queue *q) {
	int i,first,last;

	first = (q->front + 1) % SIZE_QUEUE;
	last = (q->rear + 1) % SIZE_QUEUE;
	printf("In the Queue : [");
	i = first;

	while (i != last) {
		char *contentType;
		if (q->queue[i].fidelity == 0) {
			contentType = "Video";
		}
		else if (q->queue[i].fidelity == 1) {
			contentType = "Image";
		}
		else if (q->queue[i].fidelity == 2) {
			contentType = "Text";
			}

		printf("(%u, %s), ", q->queue[i].requestedBy, contentType);
		i = (i + 1) % SIZE_QUEUE;
	}	
	printf("]\n");	
}

//각 사용자별로 평균 콘텐츠 대기 시간과 평균 콘텐츠 점수를 출력하는 함수
void printResult() {
	int i = 0;
	printf("\n");
	printf("******Result*****\n");
	printf("User    Avg.wait        Avg.score\n");
	for (i ; i < 20 ; i++)
	{	
		printf("User%d:  %.6lfs       %.6lf\n", i, array[i][0] / array[i][2], array[i][1] / array[i][2]);			
	}
}

