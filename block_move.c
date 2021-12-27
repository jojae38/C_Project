#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
enum { blank, not_filled, filled };

typedef struct {
	int x_pos;
	int y_pos;
	long long start_time;
	long long end_time;
	int block_type;
	int color;
	int tag;
}block;
typedef struct {
	int x;
	int y;
	int default_x;
	int default_y;
}XY_pos;
void change_matrix(block*** matrix, block*** current_matrix, XY_pos* position);
void print_matrix(block*** current_matrix,XY_pos *position);
void gotoxy(int x, int y);


int main()
{
	
	
	int x, y;//만들 매트릭스 값
	int default_x, default_y;//매트릭스 시작위치
	default_x = 0; default_y = 3;
	//매트릭스 값 가져오기
	printf("x 값은: ");
	scanf("%d", &x);
	printf("x 값은: ");
	scanf("%d", &y);
	XY_pos Position = { x,y,default_x,default_y };

	//매트릭스 생성
	block** matrix=malloc(y*sizeof(block*));
	for (int i = 0; i < y; i++)
	{
		block* array = malloc(x * sizeof(block));
		matrix[i] = array;
	}
	
	//block** current_matrix = matrix;
	
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			matrix[i][j].x_pos = i;
			matrix[i][j].y_pos = j;
		}
	}
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf("%d %d\n", matrix[i][j].x_pos, matrix[i][j].y_pos);
		}

	}
	block** current_matrix = matrix;
	while (1)
	{
		print_block(&matrix,&current_matrix,&Position);
	}
	//매트릭스 할당 중지
	for (int i = 0; i<y; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void change_matrix(block*** matrix, block*** current_matrix, XY_pos* position)
{
	for (int i = 0; i < position->x; i++)
	{
		for (int j = 0; j < position->y; j++)
		{
			if (current_matrix[i][j]->block_type != matrix[i][j]->block_type)
			{
				current_matrix[i][j]->block_type = matrix[i][j]->block_type;
				current_matrix[i][j]->color = matrix[i][j]->color;
				current_matrix[i][j]->tag = matrix[i][j]->tag;
			}
			
		}
	}
	if(*current_matrix[i][j])
	gotoxy()
}
void print_matrix(block*** current_matrix, XY_pos* position)
{
	for (int i = 0; i < position->x; i++)
	{
		for (int j = 0; j < position->y; j++)
		{
		
		}
	}
	if (*current_matrix[i][j])
		gotoxy()
}