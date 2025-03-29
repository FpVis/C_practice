#if 0

#define _CRT_SECURE_NO_WARNINGS			
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
	int top;
	int items[MAX];
} Stack;


/*

Stack의 top 위치 초기화		-->		Stack Overflow, Underflow 방지

*/


void init(Stack* stack)
{
	stack->top = -1;
}



/*

push, pop 시 스택이 비었는지, 가득 찼는지 확인

*/


int isEmpty(Stack* stack)
{
	return stack->top == -1;
}


int isFull(Stack* stack)
{
	return stack->top == MAX - 1;		//		Stack 값의 조건 확인 및 Overflow, Underflow 오류를 쉽게 하기 위해 스택의 맨 끝부분은 비워둔다.
}



void push(Stack* stack, int value)
{

	if (isFull(stack))
	{
		printf("Stack overflow\n");
		exit(1);
	}

	stack->items[++(stack->top)] = value;
}



int pop(Stack* stack)
{
	if (isEmpty(stack))
	{
		printf("Stack underflow\n");
		exit(1);
	}

	return stack->items[(stack->top)--];
}


/*

infixToPostfix() 함수에서 Stack의 top과 입력의 우선순위를 비교할 때 사용

*/


int peek(Stack* stack)
{
	return stack->items[stack->top];
}



int precedence(char op)
{
	switch (op)
	{
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	default: return 0;
	}
}


/*

infix에 입력된 값이 숫자인지, 연산자인지 판별하기 위한 함수

*/


int isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}



/*

	실행 함수부

*/

/*


* 중위 연산 -> 후위 연산 규칙


1. 숫자는 그대로 출력한다.

2. 만약 스택이 비어있다면 연산자를 그냥 스택에 넣는다.

3. (스택의 top에 있는 연산자의 우선순위 < 현재 연산자의 우선순위) 이면 현재 연산자를 그냥 스택에 넣는다.

4. (스택의 top에 있는 연산자의 우선순위 >= 현재 연산자의 우선순위) 이면 2번 혹은 3번 상황이 될 때까지 pop 하여 출력하고 연산자를 스택에 넣는다.

5. 모든 수식을 다 사용했다면 스택이 빌 때까지 pop하여 출력한다.

6. 우선순위는 (더하기=빼기) < (곱하기=나누기)이다.

7. 여는 괄호는 스택에 그냥 추가한다.

8. 여는 괄호 다음에 오는 연산자는 그냥 스택에 추가한다.

9. 닫는 괄호는 여는 괄호가 나올 때까지 스택을 pop 하여 출력한다. 다 출력하고 난 뒤 괄호들은 버린다.


*/


void infixToPostfix(char* infix, char* postfix)
{
	Stack stack;
	init(&stack);
	int j = 0;


	for (int i = 0; infix[i] != '\0'; i++)
	{
		char ch = infix[i];

		if (isDigit(ch))
		{
			while (isDigit(infix[i]))		//	 숫자가 두자릿수 이상인 경우를 위해
				postfix[j++] = infix[i++];		//		1. 숫자는 그대로 출력한다.
			
			postfix[j++] = ' ';
			i--;  // 반복문에서 i++을 건너뛰지 않도록 조정
		}

		else if (ch == '(')			//		7. 여는 괄호는 스택에 그냥 추가한다.
		{
			push(&stack, ch);
		}

		else if (ch == ')')
		{
			while (!isEmpty(&stack) && peek(&stack) != '(')		//		9. 닫는 괄호는 여는 괄호가 나올 때까지 스택을 pop 하여 출력한다. 다 출력하고 난 뒤 괄호들은 버린다.
				postfix[j++] = pop(&stack);

			pop(&stack);  // 9. 다 출력하고 난 뒤 괄호들은 버린다.
		}

		else if (isOperator(ch))
		{
			while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch))		//		2. 만약 스택이 비어있다면 연산자를 그냥 스택에 넣는다.
				postfix[j++] = pop(&stack);			//			4. (스택의 top에 있는 연산자의 우선순위 >= 현재 연산자의 우선순위) 이면 2번 혹은 3번 상황이 될 때까지 pop 하여 출력하고 연산자를 스택에 넣는다.

			push(&stack, ch);		//		3. (스택의 top에 있는 연산자의 우선순위 < 현재 연산자의 우선순위) 이면 현재 연산자를 그냥 스택에 넣는다.

		}
	}


	while (!isEmpty(&stack))
	{
		postfix[j++] = pop(&stack);		//		5. 모든 수식을 다 사용했다면 스택이 빌 때까지 pop하여 출력한다.
	}
	postfix[j] = '\0';
}





/*

* 후위 연산 -> 중위 연산 규칙


1. 숫자는 스택에 그냥 추가한다.

2. 연산자가 나오면 숫자 2개를 pop 해서 계산한다.

3. 이때 먼저 pop 되는 숫자가 두 번째 값, 나중에 pop되는 숫자가 첫 번째 값으로 하여 계산해야 한다. 계산한 값은 다시 스택에 넣는다.


*/



int evaluatePostfix(char* postfix) {
	Stack stack;
	init(&stack);
	int i = 0;

	while (postfix[i] != '\0')		//		postfix 안의 값이 모두 출력될때까지 실행.
	{
		if (isDigit(postfix[i]))
		{
			int num_buffer = 0;


			while (isDigit(postfix[i]))		//	 숫자가 두자릿수 이상인 경우를 위해
			{
				num_buffer = num_buffer * 10 + (postfix[i] - '0');		//		문자 '0'을 빼서 문자 형태의 숫자('0' ~ '9')를 정수로 변환.
				i++;													//		현재 num의 값을 10배 늘려 자릿수를 앞으로 한 칸 밀고, postfix[i]의 값을 더해 새로운 자리 값을 추가. (Ex. num이 2일 때 postfix[i]가 '0'이라면 num * 10 + 0이 되어 num이 20이 됨)
			}
			push(&stack, num_buffer);		//		1. 숫자는 스택에 그냥 추가한다.

		}

		else if (isOperator(postfix[i]))		//		2. 연산자가 나오면 숫자 2개를 pop 해서 계산한다.
		{

			int val2 = pop(&stack);
			int val1 = pop(&stack);		//		3. 이때 먼저 pop 되는 숫자가 두 번째 값, 나중에 pop되는 숫자가 첫 번째 값으로 하여 계산해야 한다.

			switch (postfix[i])
			{
			case '+': push(&stack, val1 + val2); break;
			case '-': push(&stack, val1 - val2); break;
			case '*': push(&stack, val1 * val2); break;
			case '/': push(&stack, val1 / val2); break;		//	3. 계산한 값은 다시 스택에 넣는다.
			}
			i++;

		}

		else

		{
			i++;  // 공백 건너뛰기
		}


	}

	return pop(&stack);		//		최종적으로 계산된 값을 출력

}


/*

	Main 함수

*/


int main() {
	char infix[MAX];
	char postfix[MAX];
	Stack stack;

	printf("Enter an expression: ");
	fgets(infix, MAX, stdin);

	infixToPostfix(infix, postfix);
	printf("Postfix expression: %s\n", postfix);

	int result = evaluatePostfix(postfix);
	printf("Result: %d\n", result);

	printf("%d\n", &stack.items);


	return 0;
}


#endif
