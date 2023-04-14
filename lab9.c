#include <stdio.h>
#include <stdlib.h>

// table size is 11

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    // create a next pointer (for linkedlist structure)
	struct RecordType *next;
};

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
	struct RecordType *recordP;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
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
            pRecord->next = NULL;
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

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
	int x = record -> id;
    // call the hash function to get the index
	int index = hash(x, tableSize);

	// create current 
	struct RecordType *pCurrent = hashTable[index].recordP;
    // if the RecordType at that index is NULL
	if (pCurrent == NULL)
	{
        // set 'record' equal to the HashType pointer in the table at index
		hashTable[index].recordP = record;
	}
    // else
	else
        // traverse to the end of the linkedlist and add 'record' to the end of it
		{
			while(pCurrent -> next != NULL)
			{
				pCurrent = pCurrent -> next;
			}
			pCurrent->next = record;
		}
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    // for each entry in the table
	for(int i = 0; i < tableSize; i ++)
	{
        // print the contents in that index
		printf("Index %d -> ", i);
		struct RecordType *pCurrent = hashTable[i].recordP;
		if (pCurrent != NULL)
		{
			while(pCurrent != NULL)
			{
				// print ID name and order
				printf("%d, %c, %d", pCurrent->id, pCurrent->name, pCurrent->order);
				if(pCurrent->next == NULL)
				{
					printf(" -> NULL");
				}
				pCurrent = pCurrent -> next;
			}
			printf("\n");
		}
	}
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
	struct HashType *hashTable = NULL;
    // create a variable hashTableSize and assign it a value
	int hashTableSize = 11;
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
	hashTable = (struct HashType *) calloc (sizeof(struct HashType), hashTableSize);
    // for each record in pRecords, insert it into the hash table using the insertRecord function
	for (int i = 0; i < recordSz; i ++)
	{
		insertRecord(hashTable, &pRecords[i],hashTableSize);
	}
    // call the display records function
	displayRecordsInHash(hashTable, hashTableSize);
    // free all the allocated memory
    free(pRecords);
	free(hashTable);

    return 0;
}