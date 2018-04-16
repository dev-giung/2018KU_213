#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// student 구조체 정의 
typedef struct student {
	
	// Data Field
	char name[100];
	int student_number;
	int score;
	
	// Link Field
	struct student *llink;
	struct student *rlink;
	
} student;

/*
	function: 이중연결리스트를 초기화 
	Note	: llink, rlink 모두 자기자신을 가리키도록 함 
	input	: student형 포인터 (call by reference) 
	output	: (NULL)
*/
void init(student *phead) {
	
	(phead -> llink) = phead;
	(phead -> rlink) = phead;
}

/*
	function: 이중연결리스트에 요소를 삽입
	Note	: 요소들의 score 값이 내림차순이 되도록 삽입함. 
	input	: student형 포인터 (call by reference) 
	output	: (NULL)
*/
void dinsert_node(student *phead, student *new_node) {
	
	// cur_node 포인터는 head부터 가리킴 
	student *cur_node = phead;
	
	while(1) {
		
		// 마지막(가장 score 작은) 요소인 경우 while문 종료 
		if(cur_node -> rlink == phead) {
			break;
		}
		
		// 적정 위치(다음 요소보다 score가 큰 위치) 찾은 경우 while문 종료 
		if(cur_node -> rlink -> score < new_node -> score) {
			break;
		}
		
		// 다음 요소를 가리킴.
		cur_node = cur_node -> rlink;
	}
	
	// 요소 삽입 
	( new_node -> llink ) = cur_node;
	( new_node -> rlink ) = ( cur_node -> rlink );
	( ( cur_node -> rlink ) -> llink ) = new_node;
	( cur_node -> rlink ) = new_node;
}

/*
	function: 성적 상위 n명 데이터 출력
	Note	: n이 전체 데이터 수보다 클 시에는 있는만큼(전체 데이터)만 출력 후 별도로 메세지 출력 
	input	: student형 포인터 (call by reference) 
	output	: (NULL)
*/
void displayHigh(student *phead, int n) {
	
	student *p = phead;
	int cnt = n;
	
	while(cnt) {
		p = p -> rlink;
		if(p == phead) {
			printf("모든 데이터를 출력하였습니다. 남은 %d개의 데이터는 출력되지 않습니다.", cnt);
			break;
		} else {
			printf("< %d\t%s\t%3d >\n", p -> student_number, p -> name, p -> score);
		}
		cnt--;
	}
	printf("\n");
}

/*
	function: 성적 하위 n명 데이터 출력
	Note	: n이 전체 데이터 수보다 클 시에는 있는만큼(전체 데이터)만 출력 후 별도로 메세지 출력 
	input	: student형 포인터 (call by reference) 
	output	: (NULL)
*/
void displayLow(student *phead, int n) {
	
	student *p = phead;
	int cnt = n;
	
	while(cnt) {
		p = p -> llink;
		if(p == phead) {
			printf("모든 데이터를 출력하였습니다. 남은 %d개의 데이터는 출력되지 않습니다.", cnt);
			break;
		} else {
			printf("< %d\t%s\t%3d >\n", p -> student_number, p -> name, p -> score);
		}
		cnt--;
	}
}

/*
	function: main 함수
	Note	: 데이터 파일의 서식이 적절하지 못하면 오류가 발생하나 고려하지 않음.
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	FILE *f = NULL;
	
	// Student_info.txt 데이터 파일 불러오기 
	if( (f = fopen("Student_info.txt", "r")) == NULL ) {
		
		// 불러오지 못하면 Error 출력 및 프로그램 종료 
		printf("Error: Student_info.txt 파일을 찾을 수 없습니다.");
		return 1;
	}
	
	// 변수선언 
	student head_node;
	student *data[100];
	int input_sn;
	char input_name[100];
	int index = 0;
	
	// 랜덤시드설정 
	srand(time(NULL));

	// 리스트 초기화
	init(&head_node);
	
	// 데이터 파일 모든 행의 데이터를 이중연결리스트에 삽입 
	while(EOF != fscanf(f, "%d	%[^\n]s", &input_sn, &input_name)) {
		
		// 메모리 확보 
		data[index] = (student *)malloc(sizeof(student));
		
		// student_number에는 파일로부터의 학번값 넣어줌
		data[index] -> student_number = input_sn;
		
		// name에는 파일로부터의 이름값 넣어줌 
		strcpy(data[index] -> name, input_name);
		
		// score에는 0 ~ 100 랜덤값 넣어줌
		data[index] -> score = rand() % 101;
		
		// 내부변수가 모두 입력된 노드를 리스트에 삽입
		dinsert_node(&head_node, data[index]);
		
		index++;
	}
	
	// 성적 상위 10명의 정보 출력
	printf("성적 상위 10명의 <학번 이름 점수>: \n");
	displayHigh(&head_node, 10);
	
	// 성적 하위 10명의 정보 출력
	printf("성적 하위 10명의 <학번 이름 점수>: \n");
	displayLow(&head_node, 10);
	
	// 프로그램 종료
	return 0;
}
