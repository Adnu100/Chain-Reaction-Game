/* Implementation of a holder data structure of changed cells for animation */

/* Define the structure and typedef it */
typedef struct buffer {
	int x, y;
} buffer;

typedef struct node {
	buffer B;
	struct node *next;
} node;

typedef node *bucket;

/* each node is connected to the next node like 
 * bucket -> |_| -> |_| -> |_| -> NULL
 */ 

/* Functions which will be needed */
void binit(bucket *b);
void addCell(bucket *b, buffer B);
int storage(bucket *b);
buffer check(bucket *b, int i);
void destroyBucket(bucket *b);
