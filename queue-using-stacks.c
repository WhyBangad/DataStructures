#include<stdio.h>
#include<stdlib.h>

//using flag so that in case of consecutive deuqeues, i don't have to push the whole stack and pop it again and again
// enqueue , dequeue, and then enqueue again and view the list, it doesn't work!
typedef struct node
{
    int data;
    struct node* next;
} stack;

stack* newNode(int value, stack* currentStack)
{
    stack* temp = (stack*)malloc(sizeof(stack));
    temp->data = value;
    temp->next = currentStack;
    return temp;
}

int isEmpty(stack* stack)
{
    if(stack == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pop(stack** mainStack)
{
    stack* temp = *mainStack;
    int data = temp->data;
    (*mainStack) = temp->next;
    free(temp);
    temp = NULL;
    return data;
}

void push(stack** mainStack, int value)
{
    stack* temp = newNode(value, *mainStack);
    *mainStack = temp;
    return;
}


int printQueue(stack** mainStack, stack** helperStack, int flag)
{                   //changes in travelling the list
                    //changed from single to doible pointer as i'm making changes to the list
    if(flag)
    {
        int dataHolder = 0;
        while(isEmpty(*helperStack) != 1)
        {
            dataHolder = pop(helperStack);
            push(mainStack, dataHolder);
        }
    }
    stack* stackIterator = *mainStack;
    while(stackIterator)
    {
        printf("%d->", stackIterator->data);
        stackIterator = stackIterator->next;
    }
    puts("BEGIN");
    //*flag = 0;
    return 0;
}

int enqueue(stack** mainStack, stack** helperStack, int flag)
{
    int value;
    puts("Enter the value to be enqueued : ");
    scanf(" %d", &value);
    if(flag)
    {
        int temp = 0;
        while(isEmpty(*helperStack) != 1)
        {
            temp = pop(helperStack);
            push(mainStack, temp);
        }
    }
    push(mainStack, value);
    //*flag = 0;
    return 0;
}

int dequeue(stack** mainStack, stack** helperStack, int flag)
{
    int temp = 0;
    if(flag)
    {
        if(isEmpty(*helperStack) == 1)
        {
            fprintf(stderr,"Queue is empty!\n");
            return 0;
        }
        temp = pop(helperStack);
        printf("The value dequeued is : %d", temp);
    }
    else
    {
        if(isEmpty(*mainStack) == 1)        //to check is man stack is empty
        {
            fprintf(stderr,"Queue is empty!\n");
            return 0;
        }
        while(isEmpty(*mainStack) != 1)
        {
            temp = pop(mainStack);
            push(helperStack, temp);
        }
        temp = pop(helperStack);
        printf("The element dequeued is : %d", temp);
    }
    puts("");
    //*flag = 1;
    return 1;   
}

int main(int argc, char* argv[])
{
    stack *mainStack = NULL, *helperStack = NULL;
    int flag = 0, choice = 1; //in case of dequeue being followed by a dequeue
    while(choice)
    {
        puts("Press 1 to Enqueue\nPress 2 to Dequeue\nPress 3 to View the Queue\nPress 4 to check if the queue is empty");
        puts("\nPress ZERO to terminate the program");
        scanf(" %d", &choice);
        switch(choice)
        {
            case 1 : flag = enqueue(&mainStack, &helperStack, flag);
                    break;
            case 2 : flag = dequeue(&mainStack, &helperStack, flag);
                    break;
            case 3 : flag = printQueue(&mainStack, &helperStack, flag);
                    break;
            case 4 : if(isEmpty(helperStack) && isEmpty(mainStack))
                    {
                        printf("The queue is empty!\n");
                    }
                    else
                    {
                        printf("The queue is not empty!\n");
                    }
                    break;
        }
    }
    puts("Thank you for using the program!");
    return 0;
}