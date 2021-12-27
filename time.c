#include <stdio.h>
#include <Windows.h>

void calc_time(const long long t, int* year,int*year_dif, int* month, int* day, int* hour, int* minute, int* second);
void gotoxy(int x, int y);

int main()
{
	int x, y; x = 4; y = 0;
	long long prev=0;
	time_t t;//time_t 구조체 선언
	gotoxy(x, y); printf("%s", "[Using time_t function]");
	while (1)
	{	t = time(NULL);//time_t를 이용한 시간 측정
		if (prev != t)//1초에 한개만 출력
		{
			//time_t start
			prev = t;
			gotoxy(x+5, y+1); printf("[%ld]\n", prev); //1970년 1월 1일 부터 지금까지 초단위의 시간을 구한다.
			int year,year_dif, month, day, hour, minute, second;
			year = 1970; month = 1; day = 1; hour = 0; minute = 0; second = 0;
			calc_time(t, &year, &year_dif, &month, &day, &hour, &minute, &second);//단 UTC 기준
			gotoxy(x-4, y+2);printf("[%d년 %d월 %d일 %d시 %d분 %d초]\n",year,month,day,hour,minute,second);
			//time_t end
			
		}
	}
	return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void calc_time(const long long t, int* year,int*year_dif, int* month, int* day, int* hour, int* minute, int* second)
{
	long long time = t;
	*second = time % 60;
	time /= 60;
	*minute = time % 60;
	time /= 60;
	*hour = time % 24;
	time /= 24;
	time += 1;//1970년 1월 1일 기준이기에 +1을 더해줘야 한다.
	while (1)
	{
		if (*year % 400==0||(*year%4==0&&*year%100!=0))
		{
			if (time >= 366)
			{
				time -= 366;
				*year+=1;
			}
			else
			{
				year_dif = 0;//윤년
				break;
			}
				
		}
		else
		{
			if (time >= 365)
			{
				time -= 365;
				*year+=1;
			}
			else
			{
				year_dif = 1;//평년
				break;
			}
				
			
		}
	}//31 28 31 30 31 30 31 31 30 31 30 31
		if (year_dif == 1)
		{
			if (time - 31 < 0)
			{
				*month = 1;
			}
			else if (time - 59 < 0)
			{
				time -= 31;
				*month = 2;
			}
			else if (time - 90 < 0)
			{
				time -= 59;
				*month = 2;
			}
			else if (time - 120 < 0)
			{
				time -= 90;
				*month = 2;
			}
			else if (time - 151 < 0)
			{
				time -= 120;
				*month = 2;
			}
			else if (time - 181 < 0)
			{
				time -= 151;
				*month = 2;
			}
			else if (time - 212 < 0)
			{
				time -= 181;
				*month = 2;
			}
			else if (time - 243 < 0)
			{
				time -= 212;
				*month = 2;
			}
			else if (time - 273 < 0)
			{
				time -= 243;
				*month = 2;
			}
			else if (time - 304 < 0)
			{
				time -= 273;
				*month = 2;
			}
			else if (time - 334 < 0)
			{
				time -= 304;
				*month = 2;
			}
			else
			{
				time -= 334;
				*month = 12;
			}
		}
		else
		{
			if (time - 31 < 0)
			{
				*month = 1;
			}
			else if (time - 60 < 0)
			{
				time -= 31;
				*month = 2;
			}
			else if (time - 91 < 0)
			{
				time -= 60;
				*month = 2;
			}
			else if (time - 121 < 0)
			{
				time -= 91;
				*month = 2;
			}
			else if (time - 152 < 0)
			{
				time -= 121;
				*month = 2;
			}
			else if (time - 182 < 0)
			{
				time -= 152;
				*month = 2;
			}
			else if (time - 213 < 0)
			{
				time -= 182;
				*month = 2;
			}
			else if (time - 244 < 0)
			{
				time -= 213;
				*month = 2;
			}
			else if (time - 274 < 0)
			{
				time -= 244;
				*month = 2;
			}
			else if (time - 305 < 0)
			{
				time -= 274;
				*month = 2;
			}
			else if (time - 335 < 0)
			{
				time -= 305;
				*month = 2;
			}
			else
			{
				time -= 335;
				*month = 12;
			}
		}
		*day = time;
		time = 0;
}