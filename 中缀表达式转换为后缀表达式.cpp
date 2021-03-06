#include<stdio.h>

#include<stdlib.h>

#include<ctype.h>



#define STACK_INIT_SIZE 20

#define STACKINCREMENT 10

#define MAXBUFFER 10



typedef char ElemType;

typedef struct

{

	ElemType *base;

	ElemType *top;

	int stacksize;

}sqStack;



void InitStack(sqStack *s)

{

	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));

	if (!s->base)

	{

		exit(0);

	}

	s->top = s->base;

	s->stacksize = STACK_INIT_SIZE;

}



void Push(sqStack *s, ElemType e)

{

	//栈满，追加空间

	if (s->top - s->base >= s->stacksize)

	{

		s->base = (ElemType*)realloc(s->base, (s->stacksize + STACKINCREMENT) *
			sizeof(ElemType));

		if (!s->base)

		{

			exit(0);

		}

		s->top = s->base + s->stacksize;

		s->stacksize = s->stacksize + STACKINCREMENT;

	}

	*(s->top) = e;//存放数据

	s->top++;

}



void Pop(sqStack *s, ElemType *e)

{

	if (s->top == s->base)

	{

		return;

	}

	*e = *--(s->top);//将栈顶元素出栈

}



int StackLen(sqStack s)

{

	return(s.top - s.base);

}



int main()

{

	sqStack s;

	char c, e;

	InitStack(&s);

	printf("请输入中缀表达式，以#作为结束标志：\n");

	scanf_s("%c", &c);

	while (c != '#')

	{

		while (c >= '0'&&c <= '9')

		{

			printf("%c ", c);

			scanf_s("%c", &c);

			if (c<'0' || c>'9')

			{

				printf(" ");

			}

		}

		if (')' == c)

		{

			Pop(&s, &e);

			while ('(' != e)

			{

				printf("%c ", e);

				Pop(&s, &e);

			}

		}

		else if ('+' == c || '-' == c)

		{

			if (!StackLen(s))

			{

				Push(&s, c);

			}

			else

			{

				do

				{

					Pop(&s, &e);

					if ('(' == e)

					{

						Push(&s, e);

					}

					else

					{

						printf("%c ", e);

					}

				} while (StackLen(s) && '(' != e);

				Push(&s, c);

			}

		}

		else if ('*' == c || '/' == c || '(' == c)

		{

			Push(&s, c);

		}

		else if ('#' == c)

		{

			break;

		}

		else

		{

			printf("\n出错：输入格式错误\n");

			return -1;

		}

		scanf_s("%c", &c);

	}

	while (StackLen(s))

	{

		Pop(&s, &e);

		printf("%c ", e);

	}

	/*double d, e;

	?char str[MAXBUFFER];

	????????int i = 0;

	????????InitStack(&s);

	????????printf("请按逆波兰表达式输出数据，数据与运算符之间用空格隔开，以'#'作为结束\n");

	????????scanf_s("%c", &c);



	????????while (c != '#')

	????????{

	???????????????while (isdigit(c) || c == '.')//用于过滤数字

	???????????????{

	???????????????????????str[i++] = c;

	???????????????????????str[i] = '\0';

	???????????????????????if (i >= 10)

	???????????????????????{

	??????????????????????????????printf("出错：输入的当个数据过大！\n");

	??????????????????????????????return -1;

	???????????????????????}

	???????????????????????scanf_s("%c", &c);

	???????????????????????{

	??????????????????????????????if (c == ' ')

	??????????????????????????????{

	??????????????????????????????????????d = atof(str);

	??????????????????????????????????????Push(&s, d);

	??????????????????????????????????????i = 0;

	??????????????????????????????????????break;

	??????????????????????????????}

	???????????????????????}

	???????????????}

	???????????????switch (c)

	???????????????{

	??????????? ????case '+':

	??????????????????????????????Pop(&s, &e);

	??????????????????????????????Pop(&s, &d);

	??????????????????????????????Push(&s, d + e);

	??????????????????????????????break;

	???????????????????????case'-':

	??????????????????????????????Pop(&s, &e);

	??????????????????????????????Pop(&s, &d);

	??????????????????????????????Push(&s, d - e);

	??????????????????????????????break;

	???????????????????????case '*':

	??????????????????????????????Pop(&s, &e);

	??????????????????????????????Pop(&s, &d);

	??????????????????????????????Push(&s, d * e);

	??????????????????????????????break;

	???????????????????????case'/':

	??????????????????????????????Pop(&s, &e);

	??????????????????????????????Pop(&s, &d);

	??????????????????????????????if (e != 0)

	??????????????????????????????{

	??????????????????????????????????????Push(&s, d / e);

	??????????????????????????????}

	??????????????????????????????else

	??????????????????????????????{

	??????????????????????????????????????printf("\n出错：除数为零！\n");

	??????????????????????????????????????return -1;

	??????????????????????????????}

	??????????????????????????????break;

	???????????????}

	???????????????scanf_s("%c", &c);

	????????}

	????????Pop(&s, &d);

	????????printf("\n最终的计算结果为：%f\n", d);

	????????*/

	system("pause");

	return 0;

}