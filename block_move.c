#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

enum { blank, not_filled, half_filled, filled, star }; //테트리스 블록 모양 0->빈칸 1->안 채워진 사각형 2->체크무늬 사각형 3->다 채워진 사각형 4->별
enum { Black, Blue, Green, Jade_Green, Red, Purple, Yellow, White, Gray, Light_blue, Light_green, Light_Jade_Green, Light_Red, Light_Purple, Light_Yellow, Dark_White }; //블록 색
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
void matrix_init(block*** matrix, block*** current_matrix, XY_pos* position);
void change_matrix(block*** matrix, block*** current_matrix, XY_pos* position);
void print_matrix(block*** current_matrix, XY_pos* position);
void gotoxy(int x, int y);
int Max(int x, int y);
int Min(int x, int y);

int main()
{

	long long time;
	int x, y;//만들 매트릭스 값 x=열 y=행
	int default_x, default_y;//매트릭스 시작위치
	default_x = 0; default_y = 3;
	//매트릭스 값 가져오기
	printf("x 값은: ");
	scanf("%d", &x);
	printf("y 값은: ");
	scanf("%d", &y);
	XY_pos Position = { x,y,default_x,default_y };

	//변경 매트릭스 생성
	block** matrix = malloc(y * sizeof(block*));
	for (int i = 0; i < y; i++)
	{
		matrix[i] = malloc(x * sizeof(block));
	}
	//보여주는 매트릭스 생성
	block** current_matrix = malloc(y * sizeof(block*));
	for (int i = 0; i < y; i++)
	{
		current_matrix[i] = malloc(x * sizeof(block));
	}

	for (int i = 0; i < Position.y; i++)
	{
		for (int j = 0; j < Position.x; j++)
		{
			matrix[i][j].x_pos = i;
			matrix[i][j].y_pos = j;
			matrix[i][j].color = Black;
			matrix[i][j].tag = 1;
			matrix[i][j].block_type = 1;
		}
	}
	
	matrix_init(&matrix, &current_matrix, &Position);
	while (1)
	{
		change_matrix(&matrix, &current_matrix, &Position);
		print_matrix(&current_matrix, &Position);
	}
	/**매트릭스 메모리 할당 중지**/
	for (int i = 0; i < y; i++)
	{
		free(matrix[i]);
		free(current_matrix[i]);
	}
	free(matrix);
	free(current_matrix);
	/**매트릭스 메모리 할당 중지**/
	return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void matrix_init(block*** matrix, block*** current_matrix, XY_pos* position)
{
	for (int i = 0; i < position->y; i++)
	{
		for (int j = 0; j < position->x; j++)
		{
			(*matrix)[i][j].x_pos = j;
			(*matrix)[i][j].y_pos = i;
			(*current_matrix)[i][j].x_pos = j;
			(*current_matrix)[i][j].y_pos = i;

			(*matrix)[i][j].block_type = blank;
			(*matrix)[i][j].color = White;
			(*matrix)[i][j].tag = 1;
			(*current_matrix)[i][j].block_type = not_filled;
			(*current_matrix)[i][j].color = White;
			(*current_matrix)[i][j].tag = 1;
		}
	}
}
void change_matrix(block*** matrix, block*** current_matrix, XY_pos* position)
{
	int x1, x2, y1, y2;
	x1 = 0; x2 = 0; y1 = 0; y2 = 0;
	int block_type, color, tag;
	block_type = blank; color = Black; tag = 1;
	gotoxy(position->default_x, position->default_y + position->y + 1); printf("바꿀 블록의 X1좌표: "); scanf("%d", &x1);
	gotoxy(position->default_x, position->default_y + position->y + 2); printf("바꿀 블록의 X2좌표: "); scanf("%d", &x2);
	gotoxy(position->default_x, position->default_y + position->y + 3); printf("바꿀 블록의 Y1좌표: "); scanf("%d", &y1);
	gotoxy(position->default_x, position->default_y + position->y + 4); printf("바꿀 블록의 Y2좌표: "); scanf("%d", &y2);
	gotoxy(position->default_x, position->default_y + position->y + 5); printf("바꿀 블록의 타입: (blank, not_filled, half_filled, filled, star)"); scanf("%d", &block_type);
	gotoxy(position->default_x, position->default_y + position->y + 6); printf("바꿀 블록의 색: (Black, Blue, Green, Jade_Green, Red, Purple, Yellow, White, Gray, Light_blue, Light_green, Light_Jade_Green, Light_Red, Light_Purple, Light_Yellow, Dark_White)"); scanf("%d", &color);
	gotoxy(position->default_x, position->default_y + position->y + 8); printf("바꿀 블록의 태그: "); scanf("%d", &tag);

	for (int i = Min(x1, x2); i < Max(x1, x2); i++)
	{
		for (int j = Min(y1, y2); j < Max(y1, y2); j++)
		{
			(*matrix)[i][j].block_type = block_type;
			(*matrix)[i][j].color = color;
			(*matrix)[i][j].tag = tag;
			(*current_matrix)[i][j].block_type = block_type;
			(*current_matrix)[i][j].color = color;
			(*current_matrix)[i][j].tag = tag;
		}
	}
	//시간으로 제어할 다음에 사용할 코드
	/*for (int i = 0; i < position->x; i++)
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
	}*/
}
void print_matrix(block*** current_matrix, XY_pos* position)
{
	for (int i = 0; i < position->y; i++)
	{
		for (int j = 0; j < position->x; j++)
		{
			gotoxy(position->default_x + i*2, position->default_y + j);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (*current_matrix)[i][j].color);
			if ((*current_matrix)[i][j].block_type == blank)
			{
				printf("  ");//여기부터 할 것!
			}
			else if ((*current_matrix)[i][j].block_type == not_filled)
			{
				printf("□");
			}
			else if ((*current_matrix)[i][j].block_type == half_filled)
			{
				printf("▩");
			}
			else if ((*current_matrix)[i][j].block_type == filled)
			{
				printf("■");
			}
			else if ((*current_matrix)[i][j].block_type == star)
			{
				printf("★");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		}
	}
}
int Max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
int Min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}
