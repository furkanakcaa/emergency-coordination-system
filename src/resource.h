typedef enum
{
    ITFAIYE,
    AMBULANS,
    KURTARMA
} ResourceType;

typedef struct Resource
{
    int id;
    char name[50];
    ResourceType type;
    int isBusy;
    int regionId;
} Resource;

typedef struct ResourceNode
{
    Resource data;
    struct ResourceNode *next;
} ResourceNode;

typedef struct ResourceList
{
    ResourceNode *head;
    int count;
} ResourceList;

ResourceList *createList();
void addResource(ResourceList *list, Resource resource);
ResourceNode *findById(ResourceList *list, int id);
void removeResource(ResourceList *list, int id);
ResourceNode *findAvailable(ResourceList *list, ResourceType type);
void printList(ResourceList *list);
void freeList(ResourceList *list);