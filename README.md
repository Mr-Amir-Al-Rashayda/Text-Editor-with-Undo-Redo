# Text Editor with Undo/Redo

This C program implements a text editor with differential Undo/Redo functionality. It allows users to load text from a file, insert and remove strings, and perform undo/redo operations. The program uses two stacks (Undo and Redo) and one queue (AddQueue) to manage the operations.

## Features

*   **Load Text**: Reads text from a specified file (`text.txt`).
*   **Print Text**: Displays the current text.
*   **Insert Strings**: Inserts strings into the text at a specified index.
*   **Remove Strings**: Removes strings from the text.
*   **Undo Operation**: Reverts the last operation performed.
*   **Redo Operation**: Reapplies the last undone operation.
*   **Print Stacks**: Displays the contents of the Undo and Redo stacks.
*   **Save to File**: Writes the modified text to a specified file (`Output.txt`).
*   **Exit**: Exits the program and frees all allocated memory.

## Data Structures

*   **`StackNode`**: Structure for nodes in the Undo and Redo stacks.
    *   `string`: Stores the string involved in the operation.
    *   `operation`: Stores the type of operation (1 for insert, 0 for remove).
    *   `index`: Stores the index at which the operation was performed.
    *   `Next`: Pointer to the next node in the stack.

*   **`QueueNode`**: Structure for nodes in the AddQueue.
    *   `string`: Stores the string to be added.
    *   `operation`: Stores the type of operation (1 for insert, 0 for remove).
    *   `index`: Stores the index at which the operation was performed.
    *   `Next`: Pointer to the next node in the queue.
    *   `Prev`: Pointer to the previous node in the queue.

*   **`Stack`**: Structure for the Undo and Redo stacks.
    *   `Top`: Pointer to the top node of the stack.

*   **`Queue`**: Structure for the AddQueue.
    *   `Front`: Pointer to the front node of the queue.
    *   `Rear`: Pointer to the rear node of the queue.
    *   `size`: Stores the number of items in the queue.

*   **`wordsLinkedList`**: Structure for nodes in the linked list of words.
    *   `indexOfTheWord`: Stores the index of the word.
    *   `totalIndex`: Stores the total index of the word.
    *   `Next`: Pointer to the next node in the list.
    *   `words`: Stores the word.

## Algorithms

*   **Load Text**: Reads words from a file and stores them in a linked list of words.
*   **Insert Strings**: Enqueues words to be inserted, then pushes the operation details to the Undo stack, and performs the action on the main text.
*   **Remove Strings**: Enqueues words to be removed, pushes the operation details to the Undo stack, and performs the action on the main text.
*   **Undo Operation**: Pops an operation from the Undo stack, performs the reverse action on the text, and pushes the operation details to the Redo stack.
*   **Redo Operation**: Pops an operation from the Redo stack, performs the action on the text, and pushes the operation details to the Undo stack.

## File Formats

*   **Input File (`text.txt`):** Contains the initial text loaded into the editor.
*   **Output File (`Output.txt`):** Contains the modified text saved by the user.

## Usage

1.  **Compile the Program**:

    ```bash
    gcc main.c -o text_editor
    ```

2.  **Run the Program**:

    ```bash
    ./text_editor
    ```

3.  **Interact with the Menu**: Follow the prompts to perform various text editing operations.

## Menu Options

1.  Load the input file which contains the initial text.
2.  Print the loaded text.
3.  Insert strings to the text.
4.  Remove strings from the text.
5.  Perform Undo operation.
6.  Perform Redo operation.
7.  Print the Undo Stack and the Redo stack.
8.  Save the updated text to the output file.
9.  Exit.

## Code Structure

*   **`struct StackNode`**: Represents a node in the stack.
*   **`struct QueueNode`**: Represents a node in the queue.
*   **`struct Stack`**: Represents the stack data structure.
*   **`struct Queue`**: Represents the queue data structure.
*   **`createQueue()`**: Creates a new queue.
*   **`isEmptyQueue()`**: Checks if the queue is empty.
*   **`dequeue()`**: Removes an element from the queue.
*   **`makeEmptyQueue()`**: Empties the queue.
*   **`enqueue()`**: Adds an element to the queue.
*   **`disposeQueue()`**: Frees the memory allocated for the queue.
*   **`FrontChar()`**: Returns the string at the front of the queue.
*   **`Front()`**: Returns the front queue node.
*   **`createStack()`**: Creates a new stack.
*   **`isEmptyStack()`**: Checks if the stack is empty.
*   **`pop()`**: Removes an element from the stack.
*   **`top()`**: Returns the top element of the stack.
*   **`makeEmptyStack()`**: Empties the stack.
*   **`push()`**: Adds an element to the stack.
*   **`disposeStack()`**: Frees the memory allocated for the stack.
*   **`loadTextFromFile()`**: Loads text from the input file.
*   **`insertWords()`**: Inserts words into the linked list of words.
*   **`indexSearch()`**: Searches for the index of a word in the linked list.
*   **`readUserEnteredAndEnqueue()`**: Reads user input and enqueues the words.
*   **`insertToUndoStack()`**: Inserts operations into the Undo stack.
*   **`Action()`**: Performs the action (insert or remove) on the text.
*   **`UndoOp()`**: Performs the Undo operation.
*   **`RedoOp()`**: Performs the Redo operation.
*   **`printText()`**: Prints the current text.
*   **`ActionStackUndo()`**: Performs the action based on the Undo stack.
*   **`ActionStackRedo()`**: Performs the action based on the Redo stack.
*   **`PrintUndoStack()`**: Prints the Undo stack.
*   **`saveToFile()`**: Saves the text to the output file.
*   **`Exit()`**: Exits the program and frees all memory.

## Notes

*   The program requires an input file (`text.txt`) to load the initial text.
*   Error handling is included for file operations and memory allocation.
*   The program uses dynamic memory allocation to efficiently manage the linked lists, stacks, and queues.

## Author

*   Amir Rasmi Al-Rashayda
