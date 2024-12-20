#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

struct Node
{
    char data;
    struct Node* prev;
    struct Node* next;
};

struct TextEditor
{
    struct Node* head;
    struct Node* tail;
    struct Node* cursor;
};

struct TextEditor* createTextEditor(const char* initialText);
void insertChar(struct TextEditor* editor, char c);
void deleteChar(struct TextEditor* editor);
void moveLeft(struct TextEditor* editor);
void moveRight(struct TextEditor* editor);
void undo(struct TextEditor* editor);
void redo(struct TextEditor* editor);
void printText(struct TextEditor* editor);
void freeTextEditor(struct TextEditor* editor);

char aredo[100];
char aundo[100];
int32_t r = 0;
int32_t u = 0;
int32_t check = 0;

int main()
{
    printf("Please enter an initial string consisting of a/A-z/Z and space: ");
    char initialText[1000000];
    fgets(initialText, sizeof(initialText), stdin);
    strtok(initialText, "\n");

    struct TextEditor* editor = createTextEditor(initialText);

    char choice;
    while(1)
    {
        printf("\n");
        printText(editor);
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("|0) Delete                                    |\n");
        printf("|1) Move left                                 |\n");
        printf("|2) Move right                                |\n");
        printf("|3) Insert character (enter a/A-z/Z or space) |\n");
        printf("|4) Redo (redo)                               |\n");
        printf("|5) Undo (undo)                               |\n");
        printf("|ESC) Exit                                    |\n");
        printf("-----------------------------------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if(choice == '0')
        {
            deleteChar(editor);
        }
        else if(choice == '1')
        {
            aundo[u] = '2';
            u++;
            moveLeft(editor);
        }
        else if(choice == '2')
        {
            aundo[u] = '1';
            u++;
            moveRight(editor);
        }
        else if(choice == '3')
        {
            aundo[u] = '0';
            u++;
            char c;
            printf("Enter a character to insert: ");
            scanf(" %c", &c);
            insertChar(editor, c);
        }
        else if(choice == '4')
        {
            redo(editor);
        }
        else if(choice == '5')
        {
            undo(editor);
        }
        else if(choice == '6')
        {
            printText(editor);
        }
        else if(choice == 27)
        {
            break;
        }
        else
        {
            printf("Wrong Input!\n");
        }
        /*
        for(int32_t i=0; i<u; i++)
        {
            printf(" %c ", aundo[i]);
        }
        printf("\n");
        for(int32_t i=0; i<r; i++)
        {
            printf(" %c ", aredo[i]);
        }
        printf("\n");
        */
       if(u == 98)
       {
            for(int32_t i=0; i<u; i++)
            {
                aundo[i] = aundo[i+1];
            }
            u--;
       }
       if(r == 98)
       {
            for(int32_t i=0; i<r; i++)
            {
                aredo[i] = aredo[i+1];
            }
            r--;
       }
    }
    freeTextEditor(editor);

    return 0;
}

struct TextEditor* createTextEditor(const char* initialText)
{
    struct TextEditor* editor = (struct TextEditor*)malloc(sizeof(struct TextEditor));

    struct Node* reservedNode = (struct Node*)malloc(sizeof(struct Node));
    reservedNode->data = ' ';
    reservedNode->prev = NULL;
    reservedNode->next = NULL;

    editor->head = reservedNode;
    editor->tail = reservedNode;
    editor->cursor = reservedNode;

    for (int i = 0; i < strlen(initialText); i++)
    {
        insertChar(editor, initialText[i]);
    }
    return editor;
}

void insertChar(struct TextEditor* editor, char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = c;

        if (editor->cursor == NULL)
        {
            newNode->prev = editor->tail;
            newNode->next = NULL;
            if (editor->tail != NULL)
            {
                editor->tail->next = newNode;
            }
            editor->tail = newNode;
            if (editor->head == NULL)
            {
                editor->head = newNode;
            }
        }
        else
        {
            newNode->prev = editor->cursor;
            newNode->next = editor->cursor->next;
            if (editor->cursor->next != NULL)
            {
                editor->cursor->next->prev = newNode;
            }
            editor->cursor->next = newNode;
            if (editor->cursor == editor->tail)
            {
                editor->tail = newNode;
            }
        }
        editor->cursor = newNode;
    }
}

void deleteChar(struct TextEditor* editor)
{
    if (editor->cursor != NULL)
    {
        struct Node* toDelete = editor->cursor;
        editor->cursor = editor->cursor->prev;

        if(check == 0)
        {
            aundo[u] = toDelete -> data;
            u++;
        }
        else if(check == 1)
        {
            aredo[r] = toDelete -> data;
            r++;
        }
        check = 0;

        if (toDelete->prev != NULL)
        {
            toDelete->prev->next = toDelete->next;
        }
        else
        {
            editor->head = toDelete->next;
        }

        if (toDelete->next != NULL)
        {
            toDelete->next->prev = toDelete->prev;
        }
        else
        {
            editor->tail = toDelete->prev;
        }
        free(toDelete);
    }
}

void moveLeft(struct TextEditor* editor)
{
    if (editor->cursor != NULL && editor->cursor->prev != NULL)
    {
        editor->cursor = editor->cursor->prev;
    }
}

void moveRight(struct TextEditor* editor)
{
    if (editor->cursor != NULL && editor->cursor->next != NULL)
    {
        editor->cursor = editor->cursor->next;
    }
}

void printText(struct TextEditor* editor)
{
    struct Node* current = editor->head;

    while (current != NULL)
    {
        printf("%c", current->data);
        if (current == editor->cursor)
        {
            if (editor->cursor == editor->tail)
            {
                printf("|");
            }
            else
            {
                printf("|");
            }
        }
        current = current->next;
    }
    printf("\n");
}

void undo(struct TextEditor* editor)
{
    if(u>=0)
    {
        u --;
        if(aundo[u] == '0')
        {
            check = 1;
            deleteChar(editor);
        }
        else if(aundo[u] == '1')
        {
            aredo[r] = '2';
            r++;
            moveLeft(editor);
        }
        else if(aundo[u] == '2')
        {
            aredo[r] = '1';
            r++;
            moveRight(editor);
        }
        else
        {
            aredo[r] = '0';
            r++;
            insertChar(editor, aundo[u]);
        }
    }
}

void redo(struct TextEditor* editor)
{
    if(r>=0)
    {
        r --;
        if(aredo[r] == '0')
        {
            deleteChar(editor);
        }
        else if(aredo[r] == '1')
        {
            aundo[u] = '2';
            u++;
            moveLeft(editor);
        }
        else if(aredo[r] == '2')
        {
            aundo[u] = '1';
            u++;
            moveRight(editor);
        }
        else
        {
            aundo[u] = '0';
            u++;
            insertChar(editor, aredo[r]);
        }
    }
}

void freeTextEditor(struct TextEditor* editor)
{
    struct Node* current = editor->head;
    while (current != NULL)
    {
        struct Node* next = current->next;
        free(current);
        current = next;
    }

    free(editor);
}