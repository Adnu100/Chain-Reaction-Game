/* Implementation of a holder of changed cells for animation */

typedef struct buffer {
	int x, y;
} buffer;

typedef struct node {
	buffer B;
	struct node *next;
} node;

typedef node *bucket;

void binit(bucket *b);
void addCell(bucket *b, buffer B);
int storage(bucket *b);
buffer check(bucket *b, int i);
void destroyBucket(bucket *b);
