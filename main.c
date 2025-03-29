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

Stack�� top ��ġ �ʱ�ȭ		-->		Stack Overflow, Underflow ����

*/


void init(Stack* stack)
{
	stack->top = -1;
}



/*

push, pop �� ������ �������, ���� á���� Ȯ��

*/


int isEmpty(Stack* stack)
{
	return stack->top == -1;
}


int isFull(Stack* stack)
{
	return stack->top == MAX - 1;		//		Stack ���� ���� Ȯ�� �� Overflow, Underflow ������ ���� �ϱ� ���� ������ �� ���κ��� ����д�.
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

infixToPostfix() �Լ����� Stack�� top�� �Է��� �켱������ ���� �� ���

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

infix�� �Էµ� ���� ��������, ���������� �Ǻ��ϱ� ���� �Լ�

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

	���� �Լ���

*/

/*


* ���� ���� -> ���� ���� ��Ģ


1. ���ڴ� �״�� ����Ѵ�.

2. ���� ������ ����ִٸ� �����ڸ� �׳� ���ÿ� �ִ´�.

3. (������ top�� �ִ� �������� �켱���� < ���� �������� �켱����) �̸� ���� �����ڸ� �׳� ���ÿ� �ִ´�.

4. (������ top�� �ִ� �������� �켱���� >= ���� �������� �켱����) �̸� 2�� Ȥ�� 3�� ��Ȳ�� �� ������ pop �Ͽ� ����ϰ� �����ڸ� ���ÿ� �ִ´�.

5. ��� ������ �� ����ߴٸ� ������ �� ������ pop�Ͽ� ����Ѵ�.

6. �켱������ (���ϱ�=����) < (���ϱ�=������)�̴�.

7. ���� ��ȣ�� ���ÿ� �׳� �߰��Ѵ�.

8. ���� ��ȣ ������ ���� �����ڴ� �׳� ���ÿ� �߰��Ѵ�.

9. �ݴ� ��ȣ�� ���� ��ȣ�� ���� ������ ������ pop �Ͽ� ����Ѵ�. �� ����ϰ� �� �� ��ȣ���� ������.


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
			while (isDigit(infix[i]))		//	 ���ڰ� ���ڸ��� �̻��� ��츦 ����
				postfix[j++] = infix[i++];		//		1. ���ڴ� �״�� ����Ѵ�.
			
			postfix[j++] = ' ';
			i--;  // �ݺ������� i++�� �ǳʶ��� �ʵ��� ����
		}

		else if (ch == '(')			//		7. ���� ��ȣ�� ���ÿ� �׳� �߰��Ѵ�.
		{
			push(&stack, ch);
		}

		else if (ch == ')')
		{
			while (!isEmpty(&stack) && peek(&stack) != '(')		//		9. �ݴ� ��ȣ�� ���� ��ȣ�� ���� ������ ������ pop �Ͽ� ����Ѵ�. �� ����ϰ� �� �� ��ȣ���� ������.
				postfix[j++] = pop(&stack);

			pop(&stack);  // 9. �� ����ϰ� �� �� ��ȣ���� ������.
		}

		else if (isOperator(ch))
		{
			while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch))		//		2. ���� ������ ����ִٸ� �����ڸ� �׳� ���ÿ� �ִ´�.
				postfix[j++] = pop(&stack);			//			4. (������ top�� �ִ� �������� �켱���� >= ���� �������� �켱����) �̸� 2�� Ȥ�� 3�� ��Ȳ�� �� ������ pop �Ͽ� ����ϰ� �����ڸ� ���ÿ� �ִ´�.

			push(&stack, ch);		//		3. (������ top�� �ִ� �������� �켱���� < ���� �������� �켱����) �̸� ���� �����ڸ� �׳� ���ÿ� �ִ´�.

		}
	}


	while (!isEmpty(&stack))
	{
		postfix[j++] = pop(&stack);		//		5. ��� ������ �� ����ߴٸ� ������ �� ������ pop�Ͽ� ����Ѵ�.
	}
	postfix[j] = '\0';
}





/*

* ���� ���� -> ���� ���� ��Ģ


1. ���ڴ� ���ÿ� �׳� �߰��Ѵ�.

2. �����ڰ� ������ ���� 2���� pop �ؼ� ����Ѵ�.

3. �̶� ���� pop �Ǵ� ���ڰ� �� ��° ��, ���߿� pop�Ǵ� ���ڰ� ù ��° ������ �Ͽ� ����ؾ� �Ѵ�. ����� ���� �ٽ� ���ÿ� �ִ´�.


*/



int evaluatePostfix(char* postfix) {
	Stack stack;
	init(&stack);
	int i = 0;

	while (postfix[i] != '\0')		//		postfix ���� ���� ��� ��µɶ����� ����.
	{
		if (isDigit(postfix[i]))
		{
			int num_buffer = 0;


			while (isDigit(postfix[i]))		//	 ���ڰ� ���ڸ��� �̻��� ��츦 ����
			{
				num_buffer = num_buffer * 10 + (postfix[i] - '0');		//		���� '0'�� ���� ���� ������ ����('0' ~ '9')�� ������ ��ȯ.
				i++;													//		���� num�� ���� 10�� �÷� �ڸ����� ������ �� ĭ �а�, postfix[i]�� ���� ���� ���ο� �ڸ� ���� �߰�. (Ex. num�� 2�� �� postfix[i]�� '0'�̶�� num * 10 + 0�� �Ǿ� num�� 20�� ��)
			}
			push(&stack, num_buffer);		//		1. ���ڴ� ���ÿ� �׳� �߰��Ѵ�.

		}

		else if (isOperator(postfix[i]))		//		2. �����ڰ� ������ ���� 2���� pop �ؼ� ����Ѵ�.
		{

			int val2 = pop(&stack);
			int val1 = pop(&stack);		//		3. �̶� ���� pop �Ǵ� ���ڰ� �� ��° ��, ���߿� pop�Ǵ� ���ڰ� ù ��° ������ �Ͽ� ����ؾ� �Ѵ�.

			switch (postfix[i])
			{
			case '+': push(&stack, val1 + val2); break;
			case '-': push(&stack, val1 - val2); break;
			case '*': push(&stack, val1 * val2); break;
			case '/': push(&stack, val1 / val2); break;		//	3. ����� ���� �ٽ� ���ÿ� �ִ´�.
			}
			i++;

		}

		else

		{
			i++;  // ���� �ǳʶٱ�
		}


	}

	return pop(&stack);		//		���������� ���� ���� ���

}


/*

	Main �Լ�

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
