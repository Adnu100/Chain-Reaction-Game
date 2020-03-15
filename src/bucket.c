#include <stdio.h>
#include <stdlib.h>
#include <bucket.h>

void binit(bucket *b) {
	*b = NULL;
}

void addCell(bucket *b, buffer B) {
	if(*b == NULL) {
		*b = (node *)malloc(sizeof(node));
		(*b)->B = B;
		(*b)->next = NULL;
		return;
	}
	addCell(&((*b)->next), B);
}

int storage(bucket *b) {
	int count = 0;
	node *temp = *b;
	while(temp != NULL) {
		temp = temp->next;
		count++;
	}
	return count;
}

buffer check(bucket *b, int i) {
	node *temp = *b;
	int myi;
	for(myi = 0; myi < i; myi++)
		temp = temp->next;
	return temp->B;	
}

void destroyBucket(bucket *b) {
	if(*b == NULL)
		return;
	destroyBucket(&((*b)->next));
	free(*b);
	*b = NULL;	
}
