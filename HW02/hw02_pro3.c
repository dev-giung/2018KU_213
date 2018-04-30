#include <stdio.h>
#include <stdlib.h>
#define SIZE_QUEUE 100	//the maximum size of the news_queue
#define CAPACITY 6		//the capacity of ZNN.com (per sec)
#define NUM_USER 20		//the number of users
#define NUM_LOOP 100	//the number of loops


//ContentFidelity is one of the types: video, image, text
typedef enum { Video, Image, Text } ContentFidelity;

typedef struct {
	unsigned int requestedBy;
	ContentFidelity fidelity;
} news;

typedef struct {
	news queue[SIZE_QUEUE];
	unsigned int front;
	unsigned int rear;
} Queue;

Queue news_queue;
ContentFidelity currentFidelity = Video;

/**/

void init(Queue *q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty(Queue *q) {
	return ( q->front == q->rear );
}

int is_full(Queue *q) {
	return ( (q->rear+1)%SIZE_QUEUE == q->front );
}

void enqueue(Queue *q, news item) {
	if( is_full(q) ) {
		printf("Queue is full");
		exit(1);
	} else {
		q->rear = (q->rear+1) % SIZE_QUEUE;
		q->queue[q->rear] = item;
	}
}

news dequeue(Queue *q) {
	if( is_empty(q) ) {
		printf("Queue is empty");
		exit(1);
	} else {
		q->front = (q->front+1) % SIZE_QUEUE;
		return q->queue[q->front];
	}
}

void request(Queue *q) {
	
	news temp;
	int i = 0;
	printf(" >>>>Requesting(ENQUEUE): ");
	for(i = 0; i < NUM_USER; i++) {
		if( rand() % 2 == 0 ) {
			temp.fidelity = currentFidelity;
			temp.requestedBy = i;
			printf("%d, ", i);
			enqueue(q, temp);
		}
	}
	printf("\n");
}

void setFidelity() {
	printf("Average waiting time: %.6f, Current Quality: %d\n", 3, 123412);
}

void provide(Queue *q) {
	
	int curCap = 0, size = 0;
	
	if(currentFidelity == Video) {
		size = 3;
	} else if(currentFidelity == Image) {
		size = 2;
	} else if(currentFidelity == Text) {
		size = 1;
	}
	
	printf("Providing(DEQUEUE): ");
	
	while(1) {
		
		if(curCap + size > CAPACITY) {
			break;
		}
		news temp = dequeue(q);
		printf("(%u, %d), ", temp.requestedBy, temp.fidelity);
		curCap = curCap + size;
	}
}

void printQueue(Queue *q) {
	
	unsigned int i = q->front;
	printf("In the queue: [");
	while( !(is_empty(q)) && (i % SIZE_QUEUE) < (q->rear % SIZE_QUEUE) ) {
		i = (i + 1) % SIZE_QUEUE;
		printf("(%u, %d), ", q->queue[i].requestedBy, q->queue[i].fidelity);
	}
	printf("]\n");
}

void printResult() {
}

void main() {
	unsigned int nthLoop;
	for (nthLoop = 0; nthLoop < NUM_LOOP; nthLoop++) {
		printf("\n=======%d seconds======\n", nthLoop);
		//users can request contents every two loops
		if (nthLoop % 2 == 0) {
			setFidelity();
			request(&news_queue);
		}
		printQueue(&news_queue);
		provide(&news_queue);
	}

	printResult();
}
