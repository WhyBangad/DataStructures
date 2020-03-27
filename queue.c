#include<stdio.h>
#include<stdlib.h>
#define Data int
#define DataDefaultValue -1

//queue* add(queue* mainQueue, Data value);

typedef struct node
{
    Data data;
    struct node* next;
}queue;

int isEmpty(queue* mainQueue)
{
    return ((mainQueue == NULL) ? 1 : 0);
}

void enqueue(queue** mainQueue)
{
    Data value;
    queue* add(queue* mainQueue, Data value)            //why problem with semi colon here?
    {
        queue* temp = (queue*)malloc(sizeof(queue));
        temp->data = value;
        temp->next = mainQueue;
        mainQueue = temp;
        return mainQueue;
    }
    puts("Enter the value you want to enqueue : ");
    scanf(" %d", &value);
    *mainQueue = add(*mainQueue, value);
    return;
}

int dequeue(queue** mainQueue)
{
    queue* temp = *mainQueue;
    Data holder = 0;
    if(isEmpty(*mainQueue))
    {
        //fprintf(stderr, "Queue is empty!\n");
        return DataDefaultValue;
    }
    else if(temp->next == NULL)
    {
        holder = (*mainQueue)->data;
        free(*mainQueue);
        *mainQueue = NULL;
        return holder;
    }
    while(temp->next->next)
    {
        temp = temp->next;
    }
    //queue* ptrHolder = temp->next;
    holder = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    //ptrHolder = NULL;
    return holder;
}

int peek(queue* mainQueue)
{
    if(isEmpty(mainQueue))
    {
        return DataDefaultValue;
    }
    while(mainQueue->next)
    {
        mainQueue = mainQueue->next;
    }
    return mainQueue->data;
}

int main()
{
    
}

