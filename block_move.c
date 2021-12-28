#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
enum { blank, not_filled, filled };
enum { none, Red, Orange, Yellow, Green, Blue, Purple };
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
void print_matrix(block*** current_matrix, XY_pos* position);
void gotoxy(int x, int y);
int Max(int x, int y);
int Min(int x, int y);


int main()
{

	long long time;
	int x, y;//���� ��Ʈ���� ��
	int default_x, default_y;//��Ʈ���� ������ġ
	default_x = 0; default_y = 3;
	//��Ʈ���� �� ��������
	printf("x ����: ");
	scanf("%d", &x);
	printf("x ����: ");
	scanf("%d", &y);
	XY_pos Position = { x,y,default_x,default_y };

	//���� ��Ʈ���� ����
	block** matrix = malloc(y * sizeof(block*));
	for (int i = 0; i < y; i++)
	{
		block* array = malloc(x * sizeof(block));
		matrix[i] = array;
	}
	//�����ִ� ��Ʈ���� ����
	block** current_matrix = malloc(y * sizeof(block*));
	for (int i = 0; i < y; i++)
	{
		block* array = malloc(x * sizeof(block));
		current_matrix[i] = array;
	}
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
	while (1)
	{
		change_matrix(&matrix, &current_matrix, &Position);
		print_matrix(&current_matrix, &Position);
	}
	/**��Ʈ���� �޸� �Ҵ� ����**/
	for (int i = 0; i < y; i++)
	{
		free(matrix[i]);
		free(current_matrix[i]);
	}
	free(matrix);
	free(current_matrix);
	/**��Ʈ���� �޸� �Ҵ� ����**/
	return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void change_matrix(block*** matrix, block*** current_matrix, XY_pos* position)
{
	int x1, x2, y1, y2;
	x1 = 0; x2 = 0; y1 = 0; y2 = 0;
	int block_type, color, tag;
	block_type = blank; color = none; tag = none;
	gotoxy(position->default_x, position->default_y + position->y + 1); printf("�ٲ� ����� X1��ǥ"); scanf("%d", &x1);
	gotoxy(position->default_x, position->default_y + position->y + 2); printf("�ٲ� ����� X2��ǥ"); scanf("%d", &x2);
	gotoxy(position->default_x, position->default_y + position->y + 3); printf("�ٲ� ����� Y1��ǥ"); scanf("%d", &y1);
	gotoxy(position->default_x, position->default_y + position->y + 4); printf("�ٲ� ����� Y2��ǥ"); scanf("%d", &y2);
	gotoxy(position->default_x, position->default_y + position->y + 5); printf("�ٲ� ����� Ÿ��"); scanf("%d", &block_type);
	gotoxy(position->default_x, position->default_y + position->y + 6); printf("�ٲ� ����� ��"); scanf("%d", &color);
	gotoxy(position->default_x, position->default_y + position->y + 7); printf("�ٲ� ����� �±�"); scanf("%d", &tag);

	for (int i = Min(x1, x2); i < Max(x1, x2); i++)
	{
		for (int j = Min(y1, y2); j < Max(y1, y2); j++)
		{
			current_matrix[i][j]->block_type = block_type;
			current_matrix[i][j]->color = color;
			current_matrix[i][j]->tag = tag;
		}
	}
	//�ð����� ������ ������ ����� �ڵ�
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
	for (int i = 0; i < position->x; i++)
	{
		for (int j = 0; j < position->y; j++)
		{
			gotoxy(position->default_x + i, position->default_y + j);
			if (current_matrix[i][j]->block_type)
			{
				//������� �� ��!
			}
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