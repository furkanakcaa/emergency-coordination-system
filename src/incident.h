#include <time.h>

typedef enum
{
    FIRE,
    MEDICAL,
    RESCUE
} IncidentType;

typedef enum
{
    WAITING,
    ASSIGNED,
    RESOLVED
} IncidentStatus;

typedef struct Incident
{
    int id;
    int priority; // 1 en kritik
    time_t timeStamp;
    IncidentType type;
    IncidentStatus status;
    int regionId;       // graph node'ları ile eşleşecek
    int assignedTeamId; // -1 ise henüz atanmamış
} Incident;

typedef struct PriorityQueue
{
    Incident *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue *createPQ(int capacity);
void insertPQ(PriorityQueue *pq, Incident incident);
Incident extractMin(PriorityQueue *pq);
Incident peekMin(PriorityQueue *pq);
int isEmptyPQ(PriorityQueue *pq);
void freePQ(PriorityQueue *pq);