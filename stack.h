#include "incident.h"

typedef enum
{
    EKIP_ATAMA,
    OLAY_KAPATMA
} TransactionType;

typedef struct Action
{
    TransactionType type;
    int incidentId;
    int resourceId;
    IncidentStatus eskiDurum;
} Action;

typedef struct Stack
{
    Action *data;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity);
void push(Stack *stack, Action action);
Action pop(Stack *stack);
Action peek(Stack *stack);
int isEmptyStack(Stack *stack);
void freeStack(Stack *stack);