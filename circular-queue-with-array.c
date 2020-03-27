#include<stdio.h>
#include<stdlib.h>
#define DATA int
#define DataDefaultValue -787       //Because Dreamliner
//#define DEBUG

typedef struct cq
{
    int front;
    DATA* array;
    int rear;
    int size;
}queue;

void newQueue(queue** mainQueue)
{
    int size = 0;
    queue* tempQueue = *mainQueue;
    tempQueue->front = tempQueue->rear = -1;
    puts("Enter the size of the queue : ");
    scanf(" %d", &size);
    tempQueue->size = size;
    tempQueue->array = (DATA*)malloc(size*sizeof(DATA));
    return;
}

//static inline int isFull(queue* mainQueue)
int isFull(queue* mainQueue)
{
    return (((mainQueue->front) + 1)%(mainQueue->size) == mainQueue->rear) ? 1 : 0;
}

//static inline int isEmpty(queue* mainQueue)
int isEmpty(queue* mainQueue)
{
    return ((mainQueue->front == -1) && (mainQueue->rear) == -1) ? 1 : 0;
}

int enqueue(queue* mainQueue, int value)
{
    if(isFull(mainQueue))
    {
        //fprintf(stderr, "Queue is Full!\nCan't Enqueue!\n");
        return DataDefaultValue;
    }
    //int value;
    //puts("Enter the value to be enqueued : ");
    //scanf(" %d", &value);
    if(isEmpty(mainQueue))
    {
        mainQueue->array[++(mainQueue->rear)] = mainQueue->array[++(mainQueue->front)] = value;
    }
    else
    {
        mainQueue->array[(++(mainQueue->front))%(mainQueue->size)] = value;
    }
    return 0;
}

int dequeue(queue* mainQueue)
{
    int holder;
    if(isEmpty(mainQueue))
    {
        //fprintf(stderr, "Queue is Empty!\nCan't Dequeue\n");
        return DataDefaultValue;
    }
    else if(mainQueue->front == mainQueue->rear)        //implies only 1 element exists
    {
        holder = mainQueue->array[mainQueue->front];
        mainQueue->front = mainQueue->rear = -1;
        return holder;
    }
    else
    {
        holder = mainQueue->array[mainQueue->front];
        mainQueue->front = (mainQueue->size + (--(mainQueue->front))) % (mainQueue->size);
        return holder;
    }
}

void view(queue* mainQueue)
{
    if(isEmpty(mainQueue))
    {
        puts("EMPTY\n");
        return;
    }
    int i = mainQueue->rear;
    for(i = 0; i< mainQueue->front; )
    {
        printf("%d->", mainQueue->array[i]);
        i = (i + 1) % (mainQueue->size);
    }
    printf("%d->BACK TO FRONT\n", mainQueue->array[i]);
    //puts("BACK TO FRONT");
    return;
}

int main(int argc, char* argv[])
{
    int choice = 1, ret = 0, value;
    queue* mainQueue;
    newQueue(&mainQueue);
    while(choice)
    {
        puts("Press 1 to Enqueue\nPress 2 to Dequeue\nPress 3 to View the Queue\nPress 4 to check if the queue is Empty");
        puts("Press 5 to check is the queue is Full\n\nPress ZERO to terminate the program");
        scanf(" %d", &choice);
        switch(choice)
        {
            case 1 : puts("Enter the value to be enqueued : ");
            scanf(" %d", &value);
            ret = enqueue(mainQueue, value);
            if(ret == DataDefaultValue)
            {
                fprintf(stderr, "Element couldn't be added as queue is Full\n\n");
            }
            else
            {
                puts("Element added successfully!\n");
            }
            break;
            case 2 : value = dequeue(mainQueue);
            if(value == DataDefaultValue)
            {
                fprintf(stderr, "Queue is empty and can't be Dequeued!\n\n");
            }
            else
            {
                printf("Element Dequeued : %d\n\n", value);
            }
            break;
            case 3 : view(mainQueue);
            break;
            case 4 : ret = isEmpty(mainQueue);
            if(ret == 1)
            {
                puts("The queue is Empty!\n");
            }
            else
            {
                puts("The queue is not Empty!\n");
            }
            break;
            case 5 : ret = isFull(mainQueue);
            if(ret == 1)
            {
                puts("The queue is Full!\n");
            }
            else
            {
                puts("The queue is not Full!\n");
            }
            break;
        }
    }
    puts("Thank you for using the program!");
    return 0;
}