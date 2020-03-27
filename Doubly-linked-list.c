# include<stdio.h>
# include<stdlib.h>
//# define Data int

typedef int Data;

//this time using double pointers only
//next time make sure to include a removeNode function
typedef struct node
{
	struct node* prev;
	Data data;
	struct node* next;
}Node;

Node* newNode(Node* prev, Data val, Node* next) 				//not 2-D to make it more generic and reusable
{

	Node* node = (Node*)malloc(1*sizeof(Node));
	node->prev = prev;
	node->next = next;
	node->data = val;
	if(node->next != NULL)
	{
		node->next->prev = node;
	}
	if(node->prev != NULL)
	{
		node->prev->next = node;
	}
	return node;
}

void addFirst(Node** head, Data val)
{
	*head = newNode(NULL, val, *head);
	return;
}

void display(Node* head)
{
	int choice;
	puts("Press 1 for forward (FIFO) display OR 2 for (LIFO) display : ");
	scanf(" %d", &choice);
	switch(choice)
	{
		case 1 : while(head)
			 {
				 printf("%d ", head->data);
				 head = head->next;
			 }
			 puts("\n");
			 break;
			 
		case 2 : while(head->next)
			 {
				 head = head->next;
			 }
			 while(head)
			 {
				 printf("%d ", head->data);
				 head = head->prev;
			 }
			 puts("\n");
			 break;

		default : break;
	}
	return;
}

int count (Node* head)
{
	int val = 0;
	while(head)
	{
		++val;
		head = head->next;
	}
	return val;
}

void deleteFirst(Node** head)
{
	printf("Data being deleted : %d", (*head)->data);
	(*head)->next->prev = NULL;
	Node* temp = *head;
	(*head) = (*head)->next;
	temp->next = NULL;
	free(temp);
	return;
}

void addLast(Node* head, Data val)
{
	while(head->next)
	{
		head = head->next;
	}
	head->next = newNode(head, val, NULL);
	return;
}

void removeLast(Node* node)
{
	if(node == NULL)
	{
		fprintf(stderr, "List is empty!");
		return;
	}
	while(node->next->next)
	{
		node = node->next;
	}
	printf("Data being deleted : %d\n", node->next->data);
	Node* temp = node->next;
	node->next->prev = NULL;
	node->next = NULL;
	free(temp);
	return;
}

void addAtPosition(Node** head, int position)
{
	if(position > count(*head))
	{
		fprintf(stderr, "Position greater than number of elements present!");
		return;
	}	
	int val;
	Node* temp = *head;
	puts("Enter the value you want to add : ");
	scanf(" %d", &val);
	if(position == 1)
	{
		return addFirst(head, val);
	}
	else
	{
		position -= 2;
		while(position)
		{
			temp = temp->next;
			--position;
		}
		temp->next = newNode(temp, val, temp->next);	
	}
	return;
}

void removeFromPosition(Node** head, int position)
{
	Node* temp = *head;
	if(position > count(*head))
        {
                fprintf(stderr, "Position greater than number of elements present!");
                return;
        }
	else if(position == 1)
	{
		return deleteFirst(head);
	}
	else
	{
		position -= 2;
		while(position)
		{
			temp = temp->next;
			--position;
		}
		Node* node = temp->next;
		temp->next->prev = NULL;
		temp->next->next->prev = temp;
		temp->next = temp->next->next;
		temp->next->next = NULL;
		free(node);
	}
	return;
}

void addAfterOccurence(Node* node, int val)
{
	int value;
	while(node->next != NULL && node->data != val)
	{
		node = node->next;
	}
	if(node->next == NULL)
	{
		fprintf(stderr, "The element was not found in the list!\n");
		return;
	}
	else
	{
		puts("Enter the data you want to add : ");
		scanf(" %d", &value);
		node->next = newNode(node, value, node->next);
	}
	return;
}

void removeAfterOccurence(Node* node, int val)
{
	int value;
	while(node->next != NULL && node->data != val)
	{
		node = node->next;
	}
	if(node->next == NULL)
	{
		fprintf(stderr, "The element was not found in the list!\n");
		return;
	}
	Node* temp = node->next;
	printf("Data being deleted : %d\n", node->next->data);
	node->next->prev = NULL;
	node->next = node->next->next;
	node->next->prev = node;
	temp->next = NULL;
	free(temp);
	temp = NULL;
	return;
}

void reverse(Node** head)
{
	Node* node = *head, *plast = NULL, *temp = NULL;
	while(node)
	{
		plast = node;
		temp = node->next;
		node->next = node->prev;
		node->prev = temp;
		node = node->prev;
	}
	*head = plast;
	return;
}

Node* reverseUsingRecursion(Node* head)
{
	Node* temp;
	if(head->next == NULL)
	{
		head->next = head->prev;
		head->prev = NULL;
		return head;
	}
	else
	{
		temp = head->next;
		head->next = head->prev;
		head->prev = temp;
		return reverseUsingRecursion(head->prev);
	}
}

void swapDataForInsertionSort(Node* a, Node* b)
{
	Data holder = 0, current = 0;
	Node* tempNode = a;
	while(tempNode!= b->next)
	{
		current = tempNode->data;
		tempNode->data = holder;
		holder = current;
	}
	a->data = current;
	return;
}

void sort(Node* head)		//why isn't this working?
{
	Node* temp, *iteratingPtr = head;
	int counter = 0, size = count(head), i, j;
	for(i = 1; i < size; ++i)
	{
		temp = head;
		counter = i;
		while(counter)
		{
			temp = temp->next;
			--counter;
		}
		for(j = 0; j < i; ++j)
		{
			iteratingPtr = head;
			if(iteratingPtr->data > temp->data)
			{
				printf("%d : ", __LINE__);
				swapDataForInsertionSort(iteratingPtr, temp);
				printf("%d %d\n", iteratingPtr->data, temp->data);
			}
			iteratingPtr = iteratingPtr->next;
		}
	}
	return;
}

int main()
{
	int choice = 1, position;
	Data val;
	Node* head = NULL;
	while(choice)
	{
		puts("Enter your choice OR press 0 to exit the menu");
		puts("1. Add at the beginning of th list\n2. Display the list\n3. Count the number of elements in the list\n4. Remove the first element");
		puts("5. Add at the end of the list\n6. Remove the last element\n7. Add at a given position\n8. Remove from a given position");
		puts("9. Add after the occurence of a given element\n10. Remove after the occurence of a given element\n11. Reverse the list");
		puts("12. Sort the list\n13. Rotate the list\n");
		scanf(" %d", &choice);
		switch(choice)
		{
			case 1 : puts("Enter the value you want to add : ");
				 scanf(" %d", &val);
				 addFirst(&head, val); 
				 break;
			case 2 : display(head);
				 break;
			case 3 : printf("The number of elements is : %d\n", count(head));
				 break;
			case 4 : deleteFirst(&head);
				 break;
			case 5 : puts("Enter the value you want to add : ");
				 scanf(" %d", &val);
				 addLast(head, val);
				 break;
			case 6 : removeLast(head);
				 break;
			case 7 : puts("Enter the position at which you want to add : ");
				 scanf(" %d", &position);
				 addAtPosition(&head, position);
				 break;
			case 8 : puts("Enter the position whose element you want to remove : ");
				 scanf(" %d", &position);
				 removeFromPosition(&head, position);
				 break;
			case 9 : puts("Enter the data after whose occurence you want to add an element : ");
				 scanf(" %d", &val);
				 addAfterOccurence(head, val);
				 break;
			case 10 : puts("Enter the element whose next you want to delete : ");
				 scanf(" %d", &val);
				 removeAfterOccurence(head, val);
				 break;
			case 11 : //reverse(&head);
				 puts("Press 1 to reverse using iteration and 2 to reverse using recursion : ");
				 scanf(" %d", &val);
				 if(val == 1)
				 {
					reverse(&head);
				 }
				 else
				 {
					if(head == NULL)
					{
						fprintf(stderr, "List is empty!\n");
					}
					else
					{
						head = reverseUsingRecursion(head);
					}
				 }
				 
				 break;
			case 12 : sort(head);
				 break;
		}
	}
	puts("Thank you for using the program!");
	return 0;
}
