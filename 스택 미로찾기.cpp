#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maze_size 7
#define max_stack_size 100

typedef struct
{
	short r;	// 행 
	short c;	// 열   
} element;

typedef struct
{
	element data[max_stack_size];
	int top;
} stacktype;

void init_stack(stacktype *s)	// 스택 초기화 함수  
{
	s->top = -1;
}

int is_empty(stacktype *s)	// 공백상태 검출 함수  
{
	return (s->top == -1);
}

int is_full(stacktype *s)	// 포화상태 검출 함수  
{
	return (s->top == (max_stack_size - 1));
}

void push(stacktype *s, element item)	// item을 삽입해주는 함수  
{
	
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		exit(1);
	}
	else
		s->data[++(s->top)] = item;
}

element pop(stacktype *s)	// 삭제 함수  
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(stacktype *s)	
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

element entry = {1,0};	// 입구 위치  
element here;			// 현재 위치  

char maze[maze_size][maze_size] = 
{
	{'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'e', ' ', ' ', ' ', 'O', 'O', 'O'},
	{'O', 'O', 'O', ' ', ' ', 'O', 'O'},
	{'O', ' ', ' ', ' ', 'O', 'O', 'O'},
	{'O', ' ', 'O', ' ', 'O', 'O', 'O'},
	{'O', ' ', 'O', ' ', ' ', ' ', 'G'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O'},
};

void push_loc (stacktype *s, int r, int c)
{
	if (r<0 || c<0) 
		return;
	if (maze[r][c] != 'O' && maze[r][c] != 'x')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void maze_print(char maze[maze_size][maze_size])
{
	printf("\n");
	for (int r=0; r < maze_size; r++)
	{
		for (int c=0; c < maze_size; c++)
		{
			printf ("%c", maze[r][c]);
		}
		printf ("\n");
	}
}

int main (void)
{
	int r, c;
	stacktype s;
	
	init_stack (&s);
	here = entry;
	while (maze[here.r][here.c] != 'G')
	{
		maze[here.r][here.c] = 'x';
		maze_print(maze);
		push_loc (&s, here.r - 1, here.c);	// 상 
		push_loc (&s, here.r + 1, here.c);	// 하 
		push_loc (&s, here.r, here.c - 1);	// 좌 
		push_loc (&s, here.r, here.c + 1);	// 우  
		
		if (is_empty(&s))
		{
			printf("실패\n");	// 출구가 없는 경우 실패  
			return 0;
		}
		else
			here = pop(&s);
	}
	printf ("성공\n");
	return 0;
}
		
		
	
