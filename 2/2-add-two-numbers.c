#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* makeList(int* arr, int size) {
	if (size == 0) return NULL;
	struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
	head->val = arr[0];
	head->next = NULL;
	struct ListNode* curr = head;
	for (int i = 1; i < size; i++) {
		curr->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		curr = curr->next;
		curr->val = arr[i];
		curr->next = NULL;
	}
	return head;
}

void printList(struct ListNode* head) {
	printf("[");
	while (head != NULL) {
		printf("%d", head->val);
		if(head->next != NULL) {
			printf(", ");
		}
		head = head->next;
	}
	printf("]\n");
}

void freeList(struct ListNode* head) {
	while (head != NULL) {
		struct ListNode* tmp = head;
		head = head->next;
		free(tmp);
	}
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode dummy;
	dummy.next = NULL;
	struct ListNode* curr = &dummy;
	int carry = 0;

	while (l1 != NULL || l2 != NULL || carry) {
		int sum = carry;
		if (l1 != NULL) {
			sum += l1->val;
			l1 = l1->next;
		}
		if (l2 != NULL) {
			sum += l2->val;
			l2 = l2->next;
		}
		carry = sum / 10;
		curr->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		curr = curr->next;
		curr->val = sum % 10;
		curr->next = NULL;
	}
	return dummy.next;
}

int main() {
	int n1, n2;

	printf("Size of list 1: ");
	scanf("%d", &n1);
	int* arr1 = (int*)malloc(n1 * sizeof(int));
	printf("Enter %d digits: ", n1);
	for (int i = 0; i < n1; i++)
		scanf("%d", &arr1[i]);

	printf("Size of list 2: ");
	scanf("%d", &n2);
	int* arr2 = (int*)malloc(n2 * sizeof(int));
	printf("Enter %d digits: ", n2);
	for (int i = 0; i < n2; i++)
		scanf("%d", &arr2[i]);

	struct ListNode* l1 = makeList(arr1, n1);
	struct ListNode* l2 = makeList(arr2, n2);

	printf("l1: ");
	printList(l1);
	printf("l2: ");
	printList(l2);

	struct ListNode* result = addTwoNumbers(l1, l2);

	printf("result: ");
	printList(result);

	freeList(l1);
	freeList(l2);
	freeList(result);
	free(arr1);
	free(arr2);
	return 0;
}
