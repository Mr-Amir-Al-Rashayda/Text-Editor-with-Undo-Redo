
// Name : Amir Rasmi Al-Rashayda
// ID : 1222596
// Sec : 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* General Notes : * The program is able to insert/delete a string(one word or more) at any position from the initail string ..
 * I've inculded a wide range of case handling
 */

/***************************************** "Global" *****************************************/

// define pointer types for stack and queue nodes
typedef struct StackNode *PtrStackNode;
typedef struct QueueNode *PtrQueueNode;
int counterOperation = -1; // -1 -> defualt // 1 -> insert // 0 -> delete
int indexAt = -1;          //  -1 at last
int loadFileCounter = 1;   // 1 is set if didn't load the
typedef struct wordsLinkedList *ptrWords;

/***************************************** "Structs Implementaions" *****************************************/

// define structures for stack and queue nodes
struct StackNode
{
    char *string;      // To store the string involved in the operation
    int operation;     // To store the type of operation (insert or remove) // 1 -> insert // 0 -> delete
    int index;         // To store the position at which the operation was performed
    PtrStackNode Next; // Pointer to the next node in the stack
};

struct QueueNode
{
    char *string;  // To store the string to be added
    int operation; // To store the type of operation (insert or remove) // 1 -> insert // 0 -> delete
    int index;
    PtrQueueNode Next; // Pointer to the next node in the queue
    PtrQueueNode Prev; // Pointer to the previous node in the queue
};

// Define structures for stack and queue implementations
typedef struct
{
    PtrStackNode Top; // Pointer to the top node of the stack
} Stack;

typedef struct
{
    PtrQueueNode Front; // Pointer to the front node of the queue
    PtrQueueNode Rear;  // Pointer to the rear node of the queue
    int size;           // To keep track of the number of items in the queue
} Queue;

// making a linked list of words
struct wordsLinkedList
{
    int indexOfTheWord;
    int totalIndex;
    ptrWords Next;
    char *words;
};

/***************************************** "Queue Functions" *****************************************/

// Create a new, empty queue
Queue *createQueue()
{

    Queue *que = malloc(sizeof(Queue)); // Allocate memory

    if (que == NULL)
    {
        printf("The System is Out of memory !\n"); // couldn't allocate the mem then
        return NULL;
    }

    que->Front = NULL; // Front = Rear = NULL ... if it's array fornt = 1 , rear = size = 0 "cir".
    que->Rear = NULL;
    que->size = 0;

    return que;
}

int isEmptyQueue(Queue *que)
{
    return (que->Front == NULL); // Return 1 if empty, 0 otherwise
}

void dequeue(Queue *que)
{
    if (isEmptyQueue(que))
    {
        printf("Queue is empty.\n");
        return;
    }
    PtrQueueNode temp = que->Front;
    que->Front = que->Front->Next;
    if (que->Front == NULL)
    {
        que->Rear = NULL; // If the queue is now empty then update the Rear pointer
    }
    free(temp->string); // Free the string
    free(temp);         // Free the node
    que->size--;        // Decrement the size of the queue
}

void makeEmptyQueue(Queue *que)
{
    while (!isEmptyQueue(que))
    {
        dequeue(que); // Remove all elements
    }
}

void enqueue(Queue *que, char *str, int operation, int index)
{

    PtrQueueNode newNode = malloc(sizeof(struct QueueNode));

    if (newNode == NULL)
    { // it means that we couldn't allocate the memo
        printf("The System is Out of Memory\n");
        return;
    }

    newNode->string = strdup(str); // Duplicate the string
    newNode->operation = operation;
    newNode->index = index;
    newNode->Next = NULL;      // always to null since it's queue
    newNode->Prev = que->Rear; // Set the previous node

    if (isEmptyQueue(que))
    {
        que->Front = newNode; // If the queue was empty, set the new node as the Front
    }
    else
    {
        que->Rear->Next = newNode; // Link the old Rear node to the new node
    }

    que->Rear = newNode; // now the Rear pointer sets to the new node
    que->size++;         // Increment the size of the queue
}

void disposeQueue(Queue *que)
{

    makeEmptyQueue(que); // Empty the queue
    free(que);           // Free the queue structure
}

char *FrontChar(Queue *que)
{
    if (isEmptyQueue(que))
    {
        printf("Queue is empty.\n");
        return NULL;
    }
    return que->Front->string; // Return the string at the front of the queue
}

PtrQueueNode Front(Queue *que)
{
    if (isEmptyQueue(que))
    {
        printf("Queue is empty.\n");
        return NULL;
    }
    return que->Front; // Return the string at the front of the queue
}

/***************************************** "Stack Functions" *****************************************/

Stack *createStack()
{
    Stack *stac = malloc(sizeof(Stack));
    stac->Top = NULL;
    return stac;
}

int isEmptyStack(Stack *stac)
{
    return stac->Top == NULL;
}

void pop(Stack *stac)
{
    if (isEmptyStack(stac))
    {
        printf("Stack is empty. Cannot pop more !\n");
        return;
    }

    PtrStackNode tempNode = stac->Top;
    stac->Top = stac->Top->Next;
    free(tempNode->string); // Free the string
    free(tempNode);         // Free the node
}

PtrStackNode top(Stack *stac)
{

    if (isEmptyStack(stac))
    {
        printf("Stack is empty. Cannot retrieve top element !\n");
        return NULL;
    }

    return stac->Top;
}

void makeEmptyStack(Stack *stac)
{
    while (!isEmptyStack(stac))
    {
        pop(stac);
    }
}

void push(Stack *s, char *string, int operation, int index)
{

    PtrStackNode tempNode = (PtrStackNode)malloc(sizeof(struct StackNode));

    if (tempNode == NULL)
    {
        printf("The System is Out of memory!\n");
        return;
    }
    tempNode->string = strdup(string);
    tempNode->operation = operation;
    tempNode->index = index;
    tempNode->Next = s->Top;
    s->Top = tempNode;
}

void disposeStack(Stack *s)
{
    makeEmptyStack(s);
    s->Top = NULL;
}

/***************************************** "Functoins Prototypes" *****************************************/

void loadTextFromFile(const char *filename, ptrWords text);
void insertWords(ptrWords text, ptrWords textNodes);
int indexSearch(ptrWords text);
void readUserEnteredAndEnqueue(Queue *que, int operation, int index);
void insertToUndoStack(ptrWords text, Queue *AddQueue, Stack *Undo, int index);
void Action(ptrWords text, Queue *AddQueue);
void ActionStackUndo(ptrWords text, Stack *stac);
void UndoOp(ptrWords text, Stack *Undo, Stack *Redo);
void RedoOp(ptrWords text, Stack *Undo, Stack *Redo);
void printText(ptrWords text);
void PrintUndoStack(Stack *Undo);
void ActionStackRedo(ptrWords text, Stack *stac);
void saveToFile(ptrWords text, const char *theFileName);
void Exit(ptrWords text, Queue *AddQueue, Stack *Undo, Stack *Redo);

/***************************************** "_________Main_________" *****************************************/

int main()
{

    Stack *Undo = createStack();
    Stack *Redo = createStack();
    Queue *AddQueue = createQueue();

    int operation = 0;

    ptrWords text = malloc(sizeof(struct wordsLinkedList));
    if (text == NULL)
    {
        printf("The System is out of Memory !\n");
        return 0;
    }

    text->totalIndex = 0;     // the initial total index = 0
    text->indexOfTheWord = 0; // the index = 0
    text->Next = NULL;
    ptrWords temp = NULL;

    printf("Hello my friend");

    while (operation != 9) // while it's not 9
    {
        printf("\nWhich operation you want to do next sir :\n\n1-Load the input file which contains the initial text.\n2-Print the loaded text.\n3-Insert strings to the text.\n4-Remove strings from the text.\n");
        printf("5-Perform Undo operation\n6-Perform Redo operation\n7-Print the Undo Stack and the Redo stack\n8-Save the updated text to the output file.\n9-Exit\n");
        int result;
        while (1)
        {
            result = scanf("%d%*c", &operation);
            if (result != 1) // clear Entered buffer if non-numeric value is entered
            {
                while ((getchar()) != '\n')
                    ;
                printf("Invalid Entered. Please enter a number.\n");
            }
            else // break the loop if a valid number is entered
            {
                break;
            }
        }
        switch (operation)
        {
        case 1:
            if (loadFileCounter) // so it doesn't load more than once
            {
                loadTextFromFile("text.txt", text);
                loadFileCounter = 0;
            }
            else
                printf("Can't load more than once !\n\n");
            break;
        case 2:
            printText(text);
            break;
        case 3:
            counterOperation = 1;   // means that th op is insert
            if (text->Next != NULL) // mean if the there's a text ...
            {
                int wordIndex = indexSearch(text); // to find the index where to insert
                if (wordIndex != -2)               // when the user enter string that doesn't exist
                {
                    readUserEnteredAndEnqueue(AddQueue, counterOperation, wordIndex); //
                    if (loadFileCounter == 0)                                         // just in case the user didn't load so it doesn't make error in Front fun
                        insertToUndoStack(text, AddQueue, Undo, Front(AddQueue)->index);
                }
                else
                    continue;
            }
            else // if the text was all deleted and u want to insert ..
            {
                readUserEnteredAndEnqueue(AddQueue, counterOperation, -1); // insert but let it be last
                if (loadFileCounter == 0)                                  // just in case the user didn't load first so it doesn't make error in Front fun
                    insertToUndoStack(text, AddQueue, Undo, Front(AddQueue)->index);
            }
            break;
        case 4:
            counterOperation = 0; // means that th op is deleted
            readUserEnteredAndEnqueue(AddQueue, counterOperation, indexAt);
            insertToUndoStack(text, AddQueue, Undo, indexAt);
            break;
        case 5:
            UndoOp(text, Undo, Redo);
            break;
        case 6:
            RedoOp(text, Undo, Redo);
            break;
        case 7:
            printf("  Printting Undo Stack Info ...\n");
            PrintUndoStack(Undo);
            printf("\n  Printting Redo Stack Info ...\n");
            PrintUndoStack(Redo);
            break;
        case 8:
            saveToFile(text, "Output.txt");
            makeEmptyStack(Undo); // clear both undo and redo stack
            makeEmptyStack(Redo);
            break;
        case 9:
            Exit(text, AddQueue, Undo, Redo); // clear the data
            printf("Good Bye Friend....\n");
            break;
        default:
            printf("Enter a valid Number From The choices\n\n");
            continue;
        }
    }

    return 0;
}

/***************************************** "The Functions" *****************************************/

// to load text from a file
void loadTextFromFile(const char *filename, ptrWords text)
{

    FILE *file = fopen(filename, "r");

    if (file == NULL) // in case didn't load
    {
        printf("Error in Opening the Fill file ! \n");
        return;
    }
    char word[50]; // emporary buffer since there's not words exceed 50 character
    while (fscanf(file, "%49s", word) != EOF)
    {
        if (word[strlen(word) - 1] == '.') // this case for the words ends with dots only 0_0
        {

            word[strlen(word) - 1] = '\0'; // we delete the dot
            ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
            textNodes->words = strdup(word);
            insertWords(text, textNodes); // adding the word without the last dot

            ptrWords dotAsA_Word = malloc(sizeof(struct wordsLinkedList));
            dotAsA_Word->words = strdup(".");
            insertWords(text, dotAsA_Word); // adding the dot at the last as a seperated word
        }
        else // The Normal Case which is doesn't end with the dot
        {
            ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
            textNodes->words = strdup(word);
            insertWords(text, textNodes);
        }
    }
    fclose(file);
}

// link the word with the text linked list
void insertWords(ptrWords text, ptrWords textNodes)
{
    ptrWords temp = text;

    while (temp->Next != NULL)
    {
        temp = temp->Next;
    }

    temp->Next = textNodes; // link the textNode
    textNodes->Next = NULL;

    textNodes->indexOfTheWord = temp->totalIndex;                              // a way to find the index
    textNodes->totalIndex = (temp->totalIndex) + strlen(textNodes->words) + 1; // 1 for the space // len for the word length // total index
}

// find the index of the word needed
int indexSearch(ptrWords text)
{
    ptrWords temp = text->Next;
    printf("Before which word do you want to insert the text?(at the end type -1)\n");

    char word[100];      // define an array to store the word
    scanf("%99s", word); // use %99s to avoid buffer overflow ...

    while ((getchar()) != '\n') // clear the buffer "The new line"
        ;

    word[strlen(word)] = '\0';
    while (temp != NULL)
    {
        if (strcasecmp(temp->words, word) == 0)
            return temp->indexOfTheWord; // if find it then return it index
        temp = temp->Next;
    }
    if (strcasecmp("-1", word) == 0) // if the user enter -1 meaning at last // now we cheak
    {
        printf("Adding at last !\n");
        return -1;
    }

    printf("there's no such word\n"); // now if i didn't find the word needed then return -2 ..
    return -2;                        // which will mean doesn't exist !
}

// ask the user to enter the text then enqueue in the AddQueue
void readUserEnteredAndEnqueue(Queue *que, int operation, int index)
{

    char Entered[1000]; // the Entered 1000 for holding the words inserted

    // some cheaks for the remove
    if (operation) // op = 1 -> insert // 0 -> remove
    {
        if (loadFileCounter == 0) // means that the info has been loaded ...
            printf("Enter the text you want to insert : \n");
        else
        {
            printf("Load The Info first !\n");
            return;
        }
    }
    else // when it's remove case
    {
        if (loadFileCounter == 0) // means that the info has been loaded ...
            printf("Enter the string you want to remove from the text : \n");
        else // when the info hasn't loaded
        {
            printf("There's Nothing to delete!\n");
            return;
        }
    }

    fgets(Entered, sizeof(Entered), stdin); // read the user Entered
    char *word = strtok(Entered, " \n");    // the entered on spaces and newline

    while (word != NULL)
    {
        char *copyword = strdup(word);
        enqueue(que, strdup(word), operation, index);            // enqueue each word
        if ((word = strtok(NULL, " \n")) != NULL && index != -1) // get the next word
        {
            index = index + strlen(copyword);
        }
    }
}

// push to the stack then make call action fun then dequeue
void insertToUndoStack(ptrWords text, Queue *AddQueue, Stack *Undo, int index)
{
    if (counterOperation == 1) // insert operation
    {
        while (!isEmptyQueue(AddQueue)) // while it's not empty
        {
            Action(text, AddQueue);                                                            // the action it self "adding"
            push(Undo, strdup(FrontChar(AddQueue)), counterOperation, Front(AddQueue)->index); // push it to the stack
            dequeue(AddQueue);                                                                 // now dequeue from the queue
        }
    }
    else if (counterOperation == 0) // delete Op
    {
        while (!isEmptyQueue(AddQueue)) // while it's not empty
        {
            Action(text, AddQueue);                                                            // the action it self "deleted"
            push(Undo, strdup(FrontChar(AddQueue)), counterOperation, Front(AddQueue)->index); // push it to the stack
            dequeue(AddQueue);                                                                 // now dequeue from the queue
        }
    }
    else
        printf("Error With the kind of operation \n\n");
}

// make the action on the text for case 3-4
void Action(ptrWords text, Queue *AddQueue)
{

    if (text->Next == NULL && Front(AddQueue)->operation == 0) // delete from nothing case
    {
        printf("There's Nothing to delete !\n\n"); // print can't delete
        return;
    }
    else if (Front(AddQueue)->operation == 0) // now the delete case
    {
        ptrWords temp = text->Next;
        ptrWords tempPrev = text;
        while (temp != NULL)
        {
            if (strcasecmp(temp->words, FrontChar(AddQueue)) == 0) // if we found the word then ...
            {
                Front(AddQueue)->index = temp->indexOfTheWord;
                tempPrev->Next = temp->Next;
                temp->Next = NULL;
                free(temp->words);
                free(temp);
                // update the indices of the remaining nodes
                ptrWords temp2 = tempPrev->Next;
                while (temp2 != NULL)
                {
                    temp2->indexOfTheWord = tempPrev->totalIndex;
                    temp2->totalIndex = tempPrev->totalIndex + strlen(temp2->words) + 1;
                    temp2 = temp2->Next;
                    tempPrev = tempPrev->Next;
                }
                printf("Text Deleted successfully\n\n");
                return;
            }
            tempPrev = tempPrev->Next;
            temp = temp->Next;
        }
        printf("No such Word (%s)\n", FrontChar(AddQueue));
    }
    else if (Front(AddQueue)->operation == 1) // insert from nothing case
    {

        ptrWords temp = text->Next;
        ptrWords tempPrev = text;

        if (Front(AddQueue)->index == -1) // when index is -1 add at last
        {
            ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
            textNodes->words = strdup(FrontChar(AddQueue));
            insertWords(text, textNodes);
            return;
        }
        while (temp != NULL && Front(AddQueue)->index > temp->indexOfTheWord)
        {
            temp = temp->Next;
            tempPrev = tempPrev->Next;
        }
        ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
        textNodes->words = strdup(FrontChar(AddQueue));
        tempPrev->Next = textNodes;
        textNodes->Next = temp;
        temp = textNodes;
        // update the indices of the remaining nodes
        while (temp != NULL)
        {
            temp->indexOfTheWord = tempPrev->totalIndex;
            temp->totalIndex = (tempPrev->totalIndex) + strlen(temp->words) + 1;
            tempPrev = tempPrev->Next;
            temp = temp->Next;
        }
        printf("Text inserted successfully\n\n");
    }
}

// undo op
void UndoOp(ptrWords text, Stack *Undo, Stack *Redo)
{
    if (!isEmptyStack(Undo))
    {
        ActionStackUndo(text, Undo);                                           // the action which's remove or delete "updating" the initail text
        push(Redo, top(Undo)->string, top(Undo)->operation, top(Undo)->index); // push it to the stack
        pop(Undo);                                                             // then pop it from the undo
    }
    else
    {
        printf("There No Operation Yet to Undo it !\n\n");
        return;
    }
}

// redo op
void RedoOp(ptrWords text, Stack *Undo, Stack *Redo)
{
    if (!isEmptyStack(Redo))
    {
        ActionStackRedo(text, Redo);                                           // the action which's remove or delete "updating" the initail text
        push(Undo, top(Redo)->string, top(Redo)->operation, top(Redo)->index); // push it to the stack
        pop(Redo);                                                             // then pop it from the Redo
    }
    else
    {
        printf("There No Operation can be Redoing it !\n\n");
        return;
    }
}

// printing the text
void printText(ptrWords text)
{
    ptrWords temp = text->Next;
    if (temp == NULL)
    {
        printf("Nothing has been loaded to print it\n\n");
        return;
    }
    while (temp != NULL)
    {
        if (temp->Next != NULL && strcmp(temp->Next->words, ".") == 0) // the case only for dot "."
            printf("%s", temp->words);
        else
            printf("%s ", temp->words);

        temp = temp->Next;
    }
    printf("\n");
}

// make the action on the text for case 5
void ActionStackUndo(ptrWords text, Stack *stac)
{
    ptrWords temp = text->Next;
    ptrWords tempPrev = text;

    //  was inserted so we must delete it
    if (top(stac)->operation == 1) // insert op which we need to delete it
    {
        if (top(stac)->index == -1) // if it was at last
        {
            while (temp->Next != NULL)
            {
                temp = temp->Next;
                tempPrev = tempPrev->Next;
            }
            tempPrev->Next = NULL;
            free(temp->words);
            free(temp);
        }
        else if (top(stac)->index > temp->indexOfTheWord) // when it's after the first the index
        {

            while (temp != NULL && top(stac)->index > temp->indexOfTheWord)
            {
                temp = temp->Next;
                tempPrev = tempPrev->Next;
            }

            tempPrev->Next = temp->Next;
            temp->Next = NULL;
            free(temp->words);
            free(temp);
            // Update indices of the remaining nodes
            ptrWords temp2 = tempPrev->Next;
            while (temp2 != NULL)
            {
                temp2->indexOfTheWord = tempPrev->totalIndex;
                temp2->totalIndex = tempPrev->totalIndex + strlen(temp2->words) + 1;
                temp2 = temp2->Next;
                tempPrev = tempPrev->Next;
            }
        }
        else if (top(stac)->index == temp->indexOfTheWord) // when it's the first index
        {
            tempPrev->Next = temp->Next;
            free(temp->words);
            free(temp);
            // Update indices of the remaining nodes
            ptrWords temp2 = tempPrev->Next;
            while (temp2 != NULL)
            {
                temp2->indexOfTheWord = tempPrev->totalIndex;
                temp2->totalIndex = tempPrev->totalIndex + strlen(temp2->words) + 1;
                temp2 = temp2->Next;
                tempPrev = tempPrev->Next;
            }
        }
    }
    // was deleted so we need to insert it
    else if (top(stac)->operation == 0) // delete op which we need to insert
    {

        if (top(stac)->index == -1) // if it was at last
        {
            ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
            textNodes->words = strdup(top(stac)->string);
            insertWords(text, textNodes);
            return;
        }
        while (temp != NULL && top(stac)->index > temp->indexOfTheWord) // if it was at
        {
            temp = temp->Next;
            tempPrev = tempPrev->Next;
        }
        ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
        textNodes->words = strdup(top(stac)->string);
        tempPrev->Next = textNodes;
        textNodes->Next = temp;
        temp = textNodes;

        while (temp != NULL)
        {
            temp->indexOfTheWord = tempPrev->totalIndex;
            temp->totalIndex = (tempPrev->totalIndex) + strlen(temp->words) + 1;
            tempPrev = tempPrev->Next;
            temp = temp->Next;
        }
    }
}

// same as the Undo action
void ActionStackRedo(ptrWords text, Stack *stac)
{
    ptrWords temp = text->Next;
    ptrWords tempPrev = text;

    if (top(stac)->operation == 0) // delete which we need to delete
    {
        if (top(stac)->index == -1)
        {
            while (temp->Next != NULL)
            {
                temp = temp->Next;
                tempPrev = tempPrev->Next;
            }
            tempPrev->Next = NULL;
            free(temp->words);
            free(temp);
        }
        else if (top(stac)->index > temp->indexOfTheWord)
        {

            while (temp != NULL && top(stac)->index > temp->indexOfTheWord)
            {
                temp = temp->Next;
                tempPrev = tempPrev->Next;
            }

            tempPrev->Next = temp->Next;
            temp->Next = NULL;
            free(temp->words);
            free(temp);
            // Update indices of the remaining nodes
            ptrWords temp2 = tempPrev->Next;
            while (temp2 != NULL)
            {
                temp2->indexOfTheWord = tempPrev->totalIndex;
                temp2->totalIndex = tempPrev->totalIndex + strlen(temp2->words) + 1;
                temp2 = temp2->Next;
                tempPrev = tempPrev->Next;
            }
        }
        else if (top(stac)->index == temp->indexOfTheWord)
        {
            tempPrev->Next = temp->Next;
            free(temp->words);
            free(temp);
            // Update indices of the remaining nodes
            ptrWords temp2 = tempPrev->Next;
            while (temp2 != NULL)
            {
                temp2->indexOfTheWord = tempPrev->totalIndex;
                temp2->totalIndex = tempPrev->totalIndex + strlen(temp2->words) + 1;
                temp2 = temp2->Next;
                tempPrev = tempPrev->Next;
            }
        }
    }
    else if (top(stac)->operation == 1) // insert which mean we insert
    {

        if (top(stac)->index == -1)
        {
            ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
            textNodes->words = strdup(top(stac)->string);
            insertWords(text, textNodes);
            return;
        }
        while (temp != NULL && top(stac)->index > temp->indexOfTheWord)
        {
            temp = temp->Next;
            tempPrev = tempPrev->Next;
        }
        ptrWords textNodes = malloc(sizeof(struct wordsLinkedList));
        textNodes->words = strdup(top(stac)->string);
        tempPrev->Next = textNodes;
        textNodes->Next = temp;
        temp = textNodes;

        while (temp != NULL)
        {
            temp->indexOfTheWord = tempPrev->totalIndex;
            temp->totalIndex = (tempPrev->totalIndex) + strlen(temp->words) + 1;
            tempPrev = tempPrev->Next;
            temp = temp->Next;
        }
    }
}

void PrintUndoStack(Stack *stac)
{
    Stack *stacInsert = createStack();
    if (isEmptyStack(stac))
    {
        printf("No data stored to print !\n");
        return;
    }
    printf("| %-11s%-11s%-6s |", "Token", "Operation", "index"); // it's a way to print it like what the prog file did
    while (!isEmptyStack(stac))
    {
        printf("\n| %-11s%-11d%-6d |", top(stac)->string, top(stac)->operation, top(stac)->index);
        push(stacInsert, top(stac)->string, top(stac)->operation, top(stac)->index);
        pop(stac);
    }
    printf("\n|______________________________|");
    while (!isEmptyStack(stacInsert))
    {
        push(stac, top(stacInsert)->string, top(stacInsert)->operation, top(stacInsert)->index);
        pop(stacInsert);
    }
}

void saveToFile(ptrWords text, const char *theFileName)
{
    ptrWords temp = text;
    // fisrt be sure that it contains data
    if (temp == NULL || temp->Next == NULL)
    {
        printf("can't save to output file since The district list is empty!\n\n");
        return;
    }

    FILE *saveFileOutPut = fopen(theFileName, "w"); // w since we are writing

    if (saveFileOutPut == NULL)
    {
        printf("Error happend while opening %s file\n", theFileName);
        return;
    }
    temp = temp->Next;
    // printing every word by word ...
    while (temp != NULL)
    {

        if (temp->Next != NULL && strcmp(temp->Next->words, ".") == 0) // the case only for dot
            fprintf(saveFileOutPut, "%s", temp->words);
        else
            fprintf(saveFileOutPut, "%s ", temp->words);

        temp = temp->Next;
    }
    printf("Your text has been saved in file name %s\n\n", theFileName);
    fclose(saveFileOutPut);
}

void Exit(ptrWords text, Queue *AddQueue, Stack *Undo, Stack *Redo)
{
    // make empty for all kind of data
    makeEmptyQueue(AddQueue);
    free(AddQueue);
    makeEmptyStack(Undo);
    free(Undo);
    makeEmptyStack(Redo);
    free(Redo);

    // now for the linked list of words
    ptrWords temp = text->Next;
    ptrWords tempPrev = temp;
    while (temp != NULL)
    {
        tempPrev->Next = temp->Next;
        free(temp->words); // with freeing every word
        free(temp);        // free the node itself
        temp = tempPrev->Next;
    }

    free(text->words);
    free(text);
}

