#include <stdio.h>
#include <time.h>
#include <math.h>
struct list {
	float value;
	struct list* next;
	struct list* prev;
	short flag;
};

typedef struct list list;

list* addToRight(list* tail, float value) {
	if (tail->flag == 0) {
		tail->flag = 1;
		tail->value = value;
		return tail;
	}
	tail->next = (list*)malloc(sizeof(list));
	tail->next->next = 0;
	tail->next->prev = tail;
	tail->next->value = value;
	return tail->next;
}

list* addToLeft(list* head, float value) {
	if (head->flag == 0) {
		head->flag = 1;
		head->value = value;
		return head;
	}
	head->prev = (list*)malloc(sizeof(list));
	head->prev->prev = 0;
	head->prev->prev = head;
	head->prev->value = value;
	return head->prev;
}

void outputToRight(list* head) {
	if (head == 0) {
		printf("List is empty\n");
		return;
	}
	while (head->next != 0) {
		printf("%.4f ->", head->value);
		head = head->next;
	}
	printf("%.4f", head->value);
}

void outputToLeft(list* tail) {
	if (tail == 0) {
		printf("List is empty\n");
		return;
	}
	while (tail->prev != 0) {
		printf("%.4f -> ", tail->value);
		tail = tail->prev;
	}
	printf("%.4f", tail->value);
}

void addBeforeCurrent(list* current, float value) {
	if (current == 0) {
		printf("Ptr == 0\n");
		return;
	}
	list* ptr = (list*)malloc(sizeof(list));
	ptr->value = value;
	ptr->flag = 1;
	ptr->next = current;
	ptr->prev = current->prev;
	if (current->prev != 0) {
		current->prev->next = ptr;
		current->prev = ptr;
	}
	else {		
		current->prev = ptr;
	}
}

void swapTwoElements(list* a, list* b) {
	if (a == 0 || b == 0) {
		printf("Error ptr == 0\n");
		return;
	}
	if (a->prev == b->prev || a->next == b->next) {
		return;
	}
	list* ptr;
	if (a->prev == 0) {		
		if (b->next == 0) {
			ptr = a->next->prev;
			a->next->prev = b->prev->next;
			b->prev->next = ptr;
			ptr = a->next;
			a->next = b->next;
			b->next = ptr;
			ptr = a->prev;
			a->prev = b->prev;
			b->prev = ptr;				
			return;
		}
		if (a->next == b) {
			b->next->prev = b->prev;
			a->prev = a->next;
			a->next = b->next;
			b->next = b->prev;
			b->prev = 0;
			return;
		}
		ptr = a->next->prev;
		a->next->prev = b->next->prev;
		b->next->prev = ptr;		
		b->prev->next = ptr;		
		ptr = a->next;
		a->next = b->next;
		b->next = ptr;
		ptr = a->prev;
		a->prev = b->prev;
		b->prev = ptr;
		return;
	}
	if (a->next == 0) {		
		if (b->prev == 0) {
			ptr = b->next->prev;
			b->next->prev = a->prev->next;
			a->prev->next = ptr;
			ptr = b->next;
			b->next = a->next;
			a->next = ptr;
			ptr = b->prev;
			b->prev = a->prev;
			a->prev = ptr;
			return;
		}
		
		if (b->next == a) {
			b->prev->next = b->next;
			a->next = a->prev;
			a->prev = b->prev;
			b->prev = b->next;
			b->next = 0;
			return;
		}		
		ptr = a->prev->next;
		a->prev->next = b->prev->next;
		b->prev->next = ptr;
		b->next->prev = ptr;
		ptr = a->prev;
		a->prev = b->prev;
		b->prev = ptr;
		ptr = a->next;
		a->next = b->next;
		b->next = ptr;
		return;
	}
	if (b->prev == 0) {
		if (b->next == a) {
			a->next->prev = a->prev;
			b->prev = b->next;
			b->next = a->next;
			a->next = a->prev;
			a->prev = 0;
			return;
		}
		ptr = b->next->prev;
		b->next->prev = a->next->prev;
		a->next->prev = ptr;
		a->prev->next = ptr;
		ptr = b->next;
		b->next = a->next;
		a->next = ptr;
		ptr = b->prev;
		b->prev = a->prev;
		a->prev = ptr;
		return;
	}
	if (b->next == 0) {
		if (a->next == b) {
			a->prev->next = a->next;
			b->next = b->prev;
			b->prev = a->prev;
			a->prev = a->next;
			a->next = 0;
			return;
		}
		ptr = b->prev->next;
		b->prev->next = a->prev->next;
		a->prev->next = ptr;
		a->next->prev = ptr;
		ptr = b->prev;
		b->prev = a->prev;
		a->prev = ptr;
		ptr = b->next;
		b->next = a->next;
		a->next = ptr;
		return;
	}
	ptr = a->prev->next;
	a->prev->next = b->prev->next;
	b->prev->next = ptr;
	ptr = a->next->prev;
	a->next->prev = b->next->prev;
	b->next->prev = ptr;
	ptr = a->next;
	a->next = b->next;
	b->next = ptr;
	ptr = a->prev;
	a->prev = b->prev;
	b->prev = ptr;
}

list* findByValue(list* head, float value) {
	if (head == 0) {
		printf("Error: ptr == 0\n");
		return;
	}
	while (head->next != 0) {
		if (fabs(head->value - value) < 0.000001) {
			return head;
		}
		head = head->next;
	}
	if (fabs(head->value - value) < 0.000001) {
		return head;
	}
	return 0;
}

void deleteByPointer(list* ptr) {
	if (ptr == 0) {
		printf("Error: ptr == 0\n");
		return;
	}
	if (ptr->next == 0 && ptr->prev == 0) {
		ptr = 0;
		return;
	}
	if (ptr->next == 0 && ptr->prev != 0) {
		ptr->prev->next = 0;
		*ptr = *ptr->prev;
		return;
	}
	if (ptr->prev == 0 && ptr->next != 0) {
		ptr->next->prev = 0;
		*ptr = *ptr->next;
		return;
	}
	ptr->next->prev = ptr->prev;
	ptr->prev->next = ptr->next;
	free(ptr);
}

void deleteByValue(list* head, float value) {
	deleteByPointer(findByValue(head, value));
}

void addBeforeValue(list* head, float valueFind, float valueAdd) {
	addBeforeCurrent(findByValue(head, valueFind), valueAdd);
}

void splice(list** oneHead, list** oneTail, list* left, list* right, list* two, list* position) {
	if (position == 0) {
		printf("Error: position == 0\n");
		return;
	} 
	
	if (left->prev == 0 && right->next == 0) {
		*oneHead = 0;
		*oneTail = 0;
	}
	else if (left->prev == 0 && right->next != 0) {
		*oneHead = right->next;
		(*oneHead)->prev = 0;
	}
	else if (left->prev != 0 && right->next == 0) {
		*oneTail = left->prev;
		(*oneTail)->next = 0;
	}
	else {
		left->prev->next = right->next;
		right->next->prev = left->prev;
	}
	position->next->prev = right;
	right->next = position->next;
	position->next = left;
	left->prev = position;
}

list* GetHead(list* head) {
	if (head != 0 && head->prev != 0) {
		while (head->prev != 0) {
			head = head->prev;
		}
		
	}
	return head;
}

list* GetTail(list* tail) {
	if (tail != 0 && tail->next != 0) {
		while (tail->next != 0) {
			tail = tail->next;
		}

	}
	return tail;
}

int main() {
	srand((unsigned int)time(0));
	list* head = (list*)malloc(sizeof(list));
	list* tail = (list*)malloc(sizeof(list));
	list* head2 = (list*)malloc(sizeof(list));
	list* tail2 = (list*)malloc(sizeof(list));
	head->next = 0;
	head->prev = 0;
	head->flag = 0;
	tail = head;
	head2->next = 0;
	head2->prev = 0;
	head2->flag = 0;
	tail2 = head2;
	for (int i = 0; i < 5; i++) {
		float hhh = (float)rand()*789/234;
		tail = addToRight(tail, hhh);
		hhh = (float)rand() * 789 / 234;
		tail2 = addToRight(tail2, hhh);
	}
	outputToRight(head);
	printf("\n");
	outputToLeft(tail);
	printf("\n");
	outputToRight(head2);
	printf("\n");
	outputToLeft(tail2);
	printf("\n");
	//float value1, value2;
	//scanf_s("%f %f", &value1, &value2);
	//addBeforeValue(head, value1, value2);
	//addBeforeCurrent(head, value1);
	//addBeforeValue(head, value1, value2);	
	//swapTwoElements(head->next, tail);
	splice(&head, &tail, head->next, tail->prev, head2, head2->next->next);

	head = GetHead(head);
	tail = GetTail(tail);
	printf("\n");
	outputToRight(head);
	printf("\n");
	outputToLeft(tail);
	printf("\n");
	outputToRight(head2);
	printf("\n");
	outputToLeft(tail2);
	printf("\n");
	return 0;
}