#include<stdio.h>
#include<stldib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node;

Node* newNode(int value, Node* next)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = value;
	temp->next = next;
	return temp;
}

void addFirst(Node** head, int value)
{
	*head = newNode(value, *head);
	return;
}

int removeLast(Node** head)
{
	int holder;
	Node* temp = NULL;
	if(*head == NULL)
	{
		return -1;
	}
	else if((*head)->next == NULL)
	{
		holder = (*head)->data;
		free(*head);
		*head = NULL;
		return holder;
	}
	else
	{
		temp = *head;
	       	while(temp->next->next)
	       	{
			temp = temp->next;
		}
		holder = temp->next->data;
		free(temp->next);
		temp->next = NULL;
		return holder;
	}		       
}

int isEmpty(Node* head)
{
	return (head == NULL) ? 1 : 0;
}

void enqueue(Node** head, int value)
{
	addFirst(head, value);
}

typedef struct node1
{
	Node* queue1;
	Node* queue2;
}Stack;

void newStack(Stack ** stack)
{
	*stack = (Stack*)malloc(sizeof(Stack));
	stack->queue1 = NULL;
	stack->queue2 = NULL;
	return;
}

int main()
{
	Stack* stack = NULL;
	newStack(&stack);
	int choice = 1, value;
	while(choice)
	{
		puts("1.Push to the stack\n2.Pop from the stack\n3.Check if the stack is empty\n4.Peek\n5.Press 0 to terminate");
		scanf(" %d", &choice);
		switch(choice)
		{
			case 1 : puts("Enter the value to be pushed : ");
				 scanf(" %d", &value);
				 push(&stack, value);
				 break;
			case 2 : value = pop(&stack);
				 if(value == -1)
				 {
					 fprintf(stderr, "The stack is empty!\n");
					 break;
				 }
				 printf("The value popped is : %d\n", value);
				 break;
			case 3 : if(isEmpty
	}
}
