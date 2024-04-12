#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 41

// RecordType
struct RecordType
{
    int		id;
    char	name;
    int		order;
};

typedef struct Node {
    struct RecordType *record;
    struct Node *next;
} Node;

// Fill out this structure
struct HashType {
    struct Node* head;
};


// Compute the hash function
int hash(int x) {
    return x % HASHTABLE_SIZE;  //mode by HASHTABLE_SIZE
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i=0;i<hashSz;++i)
    {
        // if index is occupied with any records, print all
        Node *node = pHashArray[i].head;
        if (node == NULL) continue;

        printf("index %d",i);
        while (node != NULL) {
            printf(" -> %d, %c, %d",node->record->id, node->record->name, node->record->order);
            node = node->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation

    //init
    struct HashType arr[HASHTABLE_SIZE] = {0};

    //fill array
    for (int i = 0; i < recordSz; ++i)
    {
        //getting hash
        int idx = hash(pRecords[i].id);
        //creating new node
        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->record = &pRecords[i];  // Copy data
        newNode->next = arr[idx].head;
        //adding to array
        arr[idx].head = newNode;
    }

    displayRecordsInHash(arr, HASHTABLE_SIZE);
}