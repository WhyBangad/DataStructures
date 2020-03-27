#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int Data;
	struct node *next;
	} Node;

Node* addFirst (Node* node)
{
	puts("Enter the data you want to add : ");
	Node* temp = (Node*)malloc(1*sizeof(int));
	scanf(" %d", &temp->Data);
	if(node==NULL)
	{
		temp->next = NULL;
		node = temp;
		return node;
	}
	temp->next = node;
	node = temp;
	return node;
}
	
void display (Node* node)
{
	while(node)
	{
		printf("%d ", node->Data);
		node = node->next; 
	}
	printf("\n");
	return;
}

int count (Node* node)
{
	int count=0;
	while(node)
	{
		++count;
		node = node->next;
	}
	return count;
}

Node* removeFirst (Node* node)
{
	Node* temp;
	printf("Data being deleted : %d", node->Data);
	temp = node->next;
	free(node);
	return temp;
}

void addLast (Node* node)
{	
	Node* temp = (Node*)malloc(1*sizeof(Node));
	while(node->next)
	{
		node = node->next;
	}
	puts("Enter the element you want to add : ");
	scanf(" %d", &temp->Data);
	temp->next = NULL;
	node->next = temp;
	return;
}

void removeLast(Node* node)
{
	while(node->next->next)
	{
		node = node->next;
	}
	printf("The element being deleted is : %d", node->next->Data);
	node->next = NULL;
	free(node->next);
	return;
}

Node* addAtPosition (Node* node)
{
	int position;
	Node* begin = node;
	printf("Enter the postion at which you want to add an element : ");
	scanf(" %d", &position);
	if(position == 1)
	{
		return addFirst(node);
	}
	else if(position > count(node))
	{
		fprintf(stderr, "Entered value is greater than the list's size");
		return node;
	}
	for(int i=0; i<position-2 ; i++)
	{
		node = node->next;
	}
	Node* temp = (Node*)malloc(1*sizeof(int));
	puts("Enter the value you want to add : ");
	scanf(" %d", &temp->Data);
	temp->next = node->next;
	node->next = temp;
	return begin;
}

Node* removeAtPosition(Node* node)
{
	int position;
	Node* temp, *begin = node;
	puts("Enter the position whose element you want to remove : ");
	scanf(" %d", &position);
	if(position>count(begin))
	{
		fprintf(stderr, "Entered value more than number of nodes existing\nPlease try with a new number\n");
		return NULL;
	}
	else if(position == 1)
	{
		return removeFirst(node);
	}
	else if(position == count(begin))
	{
		removeLast(begin);
		return begin;
	}
	else
	{
		position -= 2;
		while(position)
		{
			node = node->next;
			--position;
			//printf("1234\n");
		}	
		printf("Data being deleted : %d", node->next->Data);
		temp = node->next->next;
		free(node->next);		//error here somewhere
		node->next = temp;
	}
	return begin;
}

void addOnOccurence(Node* node)
{
	int data;
	puts("Enter data whose occurence is to be looked for : ");
	scanf(" %d", &data);
	if(node == NULL)
	{
		fprintf(stderr, "List is empty!\n");
	}
	else
	{
		int flag = 0;
		while(node )
		{
			if(node->Data == data)
			{
				++flag;
				break;
			}
			node = node->next;
			//printf("%p\n", node);
		}
		if(flag!=0)
		{
			puts("Enter the data to be added : ");
			scanf(" %d", &data);
			Node* tempS, *tempN;
			tempS = (Node*)malloc(1*sizeof(Node));
			tempN = node->next;
			node->next = tempS;
			tempS->next = tempN;
			tempS->Data = data;
		}
		else
		{
			fprintf(stderr, "Entered value does not exist!\n");
		}
	}
	return;
}

Node* removeOnOccurence(Node* node)
{
	int data, flag=0;
	Node *begin = node;
	puts("Enter the data to be removed : ");
	scanf(" %d", &data);
	if(node == NULL)
	{
		fprintf(stderr, "The list is empty!\n");
		return begin;
	}
	else if(node->Data == data)
	{
		return removeFirst(begin);
	}
	else
	{
		flag = 0;
		while(node)
		{
			if(node->next->Data == data)
			{
				++flag;
				break;
			}
			node = node->next;
		}
		if(flag != 0)
		{
			printf("Data being deleted : %d\n", node->next->Data);
			Node *temp;
			temp = node->next->next;
			free(node->next);
			node->next = temp;
			return begin;
		}
		else
		{
			fprintf(stderr,"Data eneterd is not in the list!\n");
			return begin;
		}
	}
}

Node* reverse(Node* node)			//can be further optimized
{
	int position = 0;
	Node *pnext = NULL, *plast = NULL;
	if(node == NULL)
	{
		fprintf(stderr, "The list is empty!\n");
		return NULL;
	}
	while(node->next)
	{
		if(position == 0)
		{
			pnext = node->next;
			node->next = NULL;
			plast = node;
			node = pnext;
		}
		else
		{
			pnext = node->next;
			node->next = plast;
			plast = node;
			node = pnext;
		}
		++position;
	}
	node->next = plast;
	return node;
}

void reverseUsingRecursion(Node* node, Node** head)	//will have to use static head or global head or pass another pointer
{
	if(node == NULL)
	{
		return;
	}
	if(node->next == NULL)
	{
		*head = node;
		return;
	}
	reverseUsingRecursion(node->next, head);
	node->next->next = node;
	node->next = NULL;			//important for last element condition
	return;
}

Node* findMin(Node* head, int i)
{
	Node* min;
	int minimum;
	while(i)
	{
		head = head->next;
		--i;
	}
	minimum = head->Data;
	min = head;
	while(head)
	{
		printf("%p->", head);
		if(head->Data < minimum)
		{
			minimum = head->Data;
			min = head;
		}
		head = head->next;
	}
	printf("\n");
	return min;
}

void swapForSort(int i, Node* min, Node* head)
{
	while(i)
	{
		head = head->next;
	}
	int temp = head->Data;
	head->Data = min->Data;
	min->Data = temp;
	return;
}

void sort(Node* head)		//selection sort
{
	int i, size = count(head);
	Node* min = NULL;
	for(i = 0; i < size - 1; ++i)
	{
		min = findMin(head, i);
		swapForSort(i, min, head);
		printf("%d\n", i);
	}
	return;
}

int main()   		//always only have bear essentials in functions so that they can be reused
{
	Node *head = NULL, *holder = NULL;
	int choice=1;
	while(choice)
	{
		puts("Enter the operation you want to do :\n1. Add an element at the beginning of the list\n2. Display the elements in the list\n3. Count the number of elements in the list"); 
		puts("4. Remove the first element from the list\n5. Add an element at the end of the list\n6. Remove the last element of the list\n7. Add an element at the a given postion");
		puts("8. Remove from position\n9. Add data after occurence of a given element\n10. Remove an element\n11. Reverse the elements of a given list");
		puts("12. Reverse using recursion\n");
		puts("Press 0 to exit the menu");
		scanf(" %d", &choice);
		switch(choice)
		{
			case 1 : head = addFirst(head);
				 //printf("%p", head);
			 	 break;
			case 2 : display(head);
				 //printf("%p", head);
				 break;
			case 3 : printf("Number of elements is : %d", count(head));		
				 break;
			case 4 : head = removeFirst(head);
				 break;
			case 5 : addLast(head);
				 break;
			case 6 : removeLast(head);
				 break;
			case 7 : head = addAtPosition(head);
				 break;
			case 8 : head = removeAtPosition(head);		
				 break;
			case 9 : addOnOccurence(head);
				 break;
			case 10 : head = removeOnOccurence(head);
				 break;
			case 11 : head = reverse(head);
				 break;
			case 12 :reverseUsingRecursion(head, &holder);
				 head = holder;
				 break;
			case 13 : sort(head);
				 break;
			
		}
		printf("\n");
	}
	puts("Thank you for using the program!");
	return 0;
}