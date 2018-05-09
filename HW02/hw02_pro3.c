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
double array[20][3];// ����ں� ��� ���ð�, ������ ���ϱ� ���� ������ �迭


/*���� �Լ� ����*/
void request(Queue *q);
void setFidelity(Queue *q);
void provide(Queue *q);
void printQueue(Queue *q);
void printResult();

/*ť ���� �Լ� ����*/
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

//ť�� ù��° ���Ҹ� �����ϴ� �Լ�
news peek(Queue *q) {
	if (is_empty(q)) exit(1);
	else return q->queue[(q->front + 1) % SIZE_QUEUE];
}

//�������� ��û�ϰ� ť�� ���� �˰���, ��û�ϴ� ������� ��ȣ�� ����Ѵ�
void request(Queue *q) {

	news temp;
	int i = 0;
	int j;

	printf(" >>>>Requesting(ENQUEUE): ");
	for (i = 0; i < NUM_USER; i++) {
		int state = 1;		
		for (j = q->front + 1 ; j < (q->front + 1 + q->num); j++) {
		//�ѹ� �������� ��û�� ����ڴ� �� �������� �����Ǳ� ������ ���ο� ������ ��û�� �� �� ����. ������ �����ϱ� ���� �˻� ����
			if (i == news_queue.queue[j%SIZE_QUEUE].requestedBy){
				state = 0;						
			}
		}
		if (state == 1) {			
			if (rand() % 2 == 0) {//50%Ȯ��
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
//������ ���� ���� �˰���, ����� ��� ������ ���ð��� ������ ������ ���¸� ����Ѵ�
void setFidelity(Queue *q) {
	int i = 0;
	double sum = 0;
	double aver_waiting_time = 0;
	char *contentType;

	//��� ��� �ð� ���ϱ�
	for (i;i < q->num;i++)
	{
		sum = sum + q->queue[(q->front + 1 + i) % SIZE_QUEUE].waitingtime;
	}
	aver_waiting_time = sum / q->num;
	if (_isnan(aver_waiting_time)) aver_waiting_time = 0;

	//��� ��� �ð��� ���� ������ ���� ����
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

//������ ���� �˰���, ��� �������� �����Ǿ����� ����Ѵ�
void provide(Queue *q) {
	int i = 0;
	int curCap = 0, size = 0;
	char *contentType;

	printf("Providing(DEQUEUE): ");

	while (1) {

		if (is_empty(q)) {
			break;
		}

		if (peek(q).fidelity == Video) {//������ ������ ���� ũ��
			size = 3;
		}
		else if (peek(q).fidelity == Image) {
			size = 2;
		}
		else if (peek(q).fidelity == Text) {
			size = 1;
		}

		if (curCap + size > CAPACITY) {//�ʴ� �ִ� 6�ۿ� ���� ����
			break;
		}

		news temp = deQueue(q);
		q->num--;
		if (temp.fidelity == 0) contentType = "Video";
		else if (temp.fidelity == 1) contentType = "Image";
		else if (temp.fidelity == 2) contentType = "Text";
		printf("(%u, %s), ", temp.requestedBy, contentType);
		curCap = curCap + size;
		//���߿� ����ں� ����� ���� ���� ������ �迭 Ȱ��
		array[temp.requestedBy][0] = array[temp.requestedBy][0] + temp.waitingtime;
		array[temp.requestedBy][1] = array[temp.requestedBy][1] + size;
		array[temp.requestedBy][2]++;

	}
	
	printf("\n");

	for (i;i < q->num;i++)//��� �ð� ����
	{
		q->queue[(q->front + 1 + i) % SIZE_QUEUE].waitingtime++;
	}
}

//���� ť�� ��� �ִ� ���������� ����ϴ� �Լ�
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

//�� ����ں��� ��� ������ ��� �ð��� ��� ������ ������ ����ϴ� �Լ�
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

