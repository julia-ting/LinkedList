/*
* Julia Ting
* CS2110
*/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	const char* first_name;
	const char* last_name;
} Student;

/* Example functions given to you. Understand why these are written this way As you will be writing your own functions for part 2*/
Student* create_student(const char* first_name, const char* last_name)
{
	Student* s = malloc(sizeof(Student));
	s->first_name = first_name;
	s->last_name = last_name;
	return s;
}

void* copy_student(const void* data) {
	Student *newStudent = create_student(((Student*)data)->first_name, 
		((Student*)data)->last_name);
	return newStudent;
}

// remove if first name is Student
int remove_if_Student(const void* data) {
	return (strncmp(((Student*)data)->first_name, "Student", 15)==0);
}

void print_student(void* data)
{
	printf("%s %s\n", ((Student*)data)->first_name, ((Student*)data)->last_name);
}

void free_student(void* data)
{
	// free structure.
	free(data);
}


/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
  
  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Lets add a student and then print */
 	push_front(llist, create_student("Nick", "Emmel"));
 	printf("TEST CASE 2\nPUSH_FRONT ONCE: A List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Lets remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nREMOVE_FRONT: Another Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Test remove_front result return value */
 	int fronts = remove_front(llist, free_student);
 	printf("TEST CASE 3A\nREMOVE_FRONT: Another Empty list should print nothing here:\n");
 	traverse(llist, print_student);
	printf("remove_front should return -1 || remove_front result: %d", fronts);
 	printf("\n");
	printf("\n"); 	

 	/* Lets add two elements and then print */
 	push_front(llist, create_student("Scott", "Emmel"));
 	push_front(llist, create_student("David", "Johnson"));
 	printf("TEST CASE 4\nPUSH_FRONT twice: A List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

  	/* Lets kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 5\nEMPTY LIST: After freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);	
	printf("\n");
	
	// Test push_back
	push_back(llist, create_student("Pushed", "Back"));
	printf("TEST CASE 6\nPUSH_BACK: List should print one student:\n");
 	traverse(llist, print_student);	
	printf("\n");

	// Test remove back
	remove_back(llist, free_student);
	printf("TEST CASE 7\nREMOVE_BACK: List should be empty\n");
 	traverse(llist, print_student);	
	printf("\n"); 
	
	// Test remove_back from empty list
	int result = remove_back(llist, free_student);
	printf("TEST CASE 8\nREMOVE_BACK FROM EMPTY LIST: List should be empty\n");
 	traverse(llist, print_student);	
	printf("remove_back should return -1 || remove_back result: %d", result);
	printf("\n"); 	
	printf("\n");
	
	// Test copy list
	push_front(llist, create_student("Student", "One"));
	push_back(llist, create_student("Student", "Two"));
	push_front(llist, create_student("Student", "Zero"));
	printf("TEST CASE 9\nLIST WITH THREE AND COPY ARE THE SAME\n");
	printf("LIST: ");
	traverse(llist, print_student); 	
	printf("COPY: ");
	list *copy = copy_list(llist, copy_student);
	traverse(copy, print_student);
	
	// Test REMOVE MULTIPLE FROM BACK
	remove_back(copy, free_student);
	remove_back(copy, free_student);
	remove_back(copy, free_student);
	printf("\nTEST CASE 9\nLIST SHOULD STILL HAVE 3 AND COPY SHOULD BE EMPTY.");
	printf("\nTESTING REMOVING MULTIPLE FROM BACK");
	printf("LIST:\n");
	traverse(llist, print_student);
	printf("COPY:\n");
	traverse(copy, print_student);
	printf("\n");
	
	//Test isEmpty
	printf("TEST CASE 10\nISEMPTY(COPY) SHOULD RETURN 1.\n");
	int isEmpty = is_empty(copy);
	printf("COPY IS EMPTY: %d \n", isEmpty);
	
	// Test isEmpty
	printf("TEST CASE 10A\nISEMPTY(LLIST) SHOULD RETURN 0\n");
	printf("LLIST IS NOT EMPTY: %d\n", is_empty(llist));
	
	// Test Front
	printf("\nTEST CASE 11\nPEEK AT FRONT, SHOULD BE STUDENT ZERO:\n");
	printf("Front: ");
	void *f = front(llist);
	print_student(f);
	
	// Test back
	printf("\nTEST CASE 12: PEEK AT BACK, SHOULD BE STUDENT TWO:\n");
	printf("BACK: ");
	void *b = back(llist);
	print_student(b);
	
	// Test front NULL;
	printf("\nTEST CASE 13: PEEK AT NULL FRONT: SHOULD BE NULL\n");
	printf("Front: ");
	f = front(copy);
	if (f == NULL) {
		printf("Null\n");
	}
	
	// Test back NULL
	printf("\nTEST CASE 14: PEEK AT NULL BACK: SHOULD BE NULL\n");
	printf("Back: ");
	b = front(copy);
	if (b == NULL) {
		printf("Null\n");
	}
	
	// Test size
	printf("\nTEST CASE 15: SIZE OF LLIST SHOULD BE 3\n");
	printf("Size: %d\n", size(llist));

	// Test size
	printf("\nTEST CASE 16: SIZE OF COPY SHOULD BE 0\n");
	printf("Size: %d\n", size(copy));
	
	// Removing centers with remove_if
	printf("\nTEST CASE 17: REMOVE_IF FIRST NAME IS STUDENT\n");
	push_front(llist, create_student("John", "John"));
	push_back(llist, create_student("Richie", "Richie"));
	printf("\tBefore remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("\n");
	int center = remove_if(llist, remove_if_Student, free_student);
	printf("\tAfter remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("Num removed should be 3: %d\n", center);
	printf("\n");
	
	// Removing just head with REMOVE_IF
	printf("\nTEST CASE 18: REMOVE_IF JUST HEAD\n");
	remove_front(llist, free_student);
	remove_front(llist, free_student);
	push_front(llist, create_student("Student", "One"));
	push_front(llist, create_student("Student", "Two"));
	push_back(llist, create_student("Nick", "Ryan"));
	printf("\tBefore remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("\n");
	int justHead = remove_if(llist, remove_if_Student, free_student);
	printf("\tAfter remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("Num removed should be 2: %d\n", justHead);
	
	printf("\nTEST CASE 19: REMOVE_IF JUST TAIL\n");
	push_back(llist, create_student("Ashley", "Brown"));
	push_back(llist, create_student("Student", "Five"));
	printf("\tBefore remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("\n");
	int justTail = remove_if(llist, remove_if_Student, free_student);
	printf("\tAfter remove:\n");
	traverse(llist, print_student);
	printf("Head: ");
	print_student(front(llist));
	printf("Tail: ");
	print_student(back(llist));
	printf("Num removed should be 1: %d\n", justTail);
	
	printf("\nTEST CASE 20: EMPTY EMPTY LIST\n");
	empty_list(copy, free_student);
	traverse(copy, print_student);
	printf("Should be no line\n");
	free(copy);
	
	empty_list(llist, free_student);
	printf("\nTEST CASE 21: EMPTY LLIST\n");
	traverse(llist, print_student);
	printf("Should be no line\n");
	
	free(llist);
 	
  	return 0;
}
