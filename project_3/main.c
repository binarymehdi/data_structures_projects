#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[70];
    int ID;
    int priority;
} student_info;

/*
1. Start the program
2. Add a request
3. Grant a student a room on campus
4. View requests in a sorted way
5. Cancel a request
6. Quit
*/
void swap(student_info *s1, student_info *s2) {
    student_info temp;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int find_largest_element_index(student_info *max_heap, int index1, int index2) {
    if (max_heap[index1].priority > max_heap[index2].priority)
        return (index1);
    else {
        return (index2);
    }
}

void heapify(student_info *heap, int parent_index, int last_index) {
    int right_child_index, left_child_index, largest_element_index;

    if (parent_index > ((last_index + 1) / 2) - 1)

        return;

    else {
        left_child_index = (2 * parent_index) + 1;

        right_child_index = (2 * parent_index) + 2;

        if (right_child_index > last_index)

            largest_element_index =

                find_largest_element_index(heap, left_child_index,
                                           parent_index);

        else {
            largest_element_index = find_largest_element_index(
                heap, left_child_index, parent_index);
            largest_element_index = find_largest_element_index(
                heap, right_child_index, largest_element_index);
        }

        if (largest_element_index != parent_index) {
            swap(&heap[largest_element_index], &heap[parent_index]);

            heapify(heap, largest_element_index, last_index);
        }
    }
}

int construct_heap(FILE *infp, student_info *max_heap) {
    int i = 0, last_index, n_students, result;
    char temp[80], line[80], c;
    fseek(infp, 0, 0);

    while (!feof(infp)) {
        fgets(max_heap[i].name, 70, infp);
        max_heap[i].name[strlen(max_heap[i].name) - 1] = '\0';

        fscanf(infp, "%d", &(max_heap[i].ID));
        fgets(line, 80, infp);
        fgets(temp, 80, infp);
        temp[strlen(temp) - 1] = '\0';
        fgets(line, 80, infp);

        if (strcmp(temp, "First year student") == 0) {
            max_heap[i].priority = 15;
        } else if (strcmp(temp, "I have health issues") == 0) {
            max_heap[i].priority = 10;
        } else {  // no valide reason to be prioritised
            max_heap[i].priority = 5;
        }
        i++;
    }
    n_students = i;
    last_index = n_students - 1;
    for (i = (last_index - 1) / 2; i >= 0; i--) {
        heapify(max_heap, i, last_index);
    }
    return (n_students);
}

int add_new_student_heap(student_info *max_heap, student_info new_student,
                         int *n_students, char *request) {
    int index;

    if (*n_students == 20) {  // heap is full
        return 0;
    } else {
        if (strcmp(request, "First year student") == 0) {
            new_student.priority = 15;
        } else if (strcmp(request, "I have health issues") == 0) {
            new_student.priority = 10;
        } else {  // no valide reason to be prioritised
            new_student.priority = 5;
        }
        index = (*n_students)++;  // assign the value, then increment
        max_heap[index] = new_student;

        while (index > 1 &&
               max_heap[index].priority > max_heap[(index - 1) / 2].priority) {
            swap(&max_heap[index], &max_heap[(index - 1) / 2]);
        }
        return 1;
    }
}

void delete_student_heap(student_info *max_heap, int *n_student,
                         student_info *ToServe) {
    int root_index = 0, last_index, child_index;

    if (*n_student == 0)
        strcpy((ToServe->name), "Empty");
    else {
        *ToServe = max_heap[root_index];
        max_heap[root_index] = max_heap[--(*n_student)];
        last_index = *n_student - 1;
        if (last_index < 0)
            return;
        else {
            child_index = (root_index * 2) + 1;
            while (child_index <= last_index) {
                if (child_index + 1 <= last_index &&
                    max_heap[child_index].priority <
                        max_heap[child_index + 1].priority)
                    child_index++;
                if (max_heap[child_index].priority >
                    max_heap[root_index].priority) {
                    swap(&max_heap[child_index], &max_heap[root_index]);
                    root_index = child_index;
                    child_index = (2 * root_index) + 1;
                } else
                    break;
            }
        }
    }
}

void menu(void) {
    printf("\n\n\t\t------------ Menu to Use-----------------\n");
    printf("\t\t|                                       |\n");
    printf("\t\t|1.  Start the program                  |\n");
    printf("\t\t|2.  Add a request                      |\n");
    printf("\t\t|3.  Grant a student a room on campus   |\n");
    printf("\t\t|4.  view requests in a sorted way      |\n");
    printf("\t\t|5.  Cancel a request                   |\n");
    printf("\t\t|6.  Quit                               |\n");
    printf("\t\t---- ------------------------------------\n");
    printf("\n\t\tYour Choice Please:");
}

void heap_sort(student_info *max_heap, int n_students) {
    student_info temp[70];
    student_info testing;
    int n_student_temp = n_students;
    // back up the content of the heap
    for (int i = 0; i < n_students; i++) temp[i] = max_heap[i];

    while (n_student_temp != 0) {
        delete_student_heap(temp, &n_student_temp, &testing);
        printf("\n\n\t%s with priority %d \n", testing.name, testing.priority);
    }
}

void print_heap_content(student_info *max_heap, int n_students) {
    for (int i = 0; i < n_students; i++) {
        printf("\n\n\t%s with ID of : %d and priority of %d", max_heap[i].name,
               max_heap[i].ID, max_heap[i].priority);
    }
}
void print_sorted_heap(student_info *max_heap, int n_students) {
    printf(
        "---------------------------------------------------------------------"
        "-\n");
    printf("Student ID\t\t\t Student Name:\t\t\t\t Reason:\t\t\t\n");
    printf(
        "---------------------------------------------------------------------"
        "-\n");
    for (int i = 0; i < n_students; i++) {
        printf("%s\t\t\t : %d\t\t\t %d\n", max_heap[i].name, max_heap[i].ID,
               max_heap[i].priority);
    }
    printf(
        "---------------------------------------------------------------------"
        "\n");
}

void load_to_file(FILE *infp, student_info *max_heap, int n_students) {
    for (int i = 0; i < n_students; i++) {
        fprintf(infp, "%d@aui.ma\n", max_heap[i].ID);
    }
}

int drop_student(student_info *max_heap, int size, int id_to_drop,
                 int *reason2) {
    int low = 0, mid;
    int high = size - 1;

    for (int i = 0; i < size; i++) {
        if (max_heap[i].ID == id_to_drop) {
            if (max_heap[i].priority == 15) {
                *reason2 = 15;
            } else if (max_heap[i].priority == 10) {
                *reason2 = 10;
            } else

            {
                *reason2 = 5;
            }
            strcpy(max_heap[i].name, "Student request cancel");
            max_heap[i].ID = 0;
            max_heap[i].priority = 0;
            heapify(max_heap,i,size-1);
            return i;
        }
        return -1;
    }
}

int main() {
    FILE *infp;
    student_info max_heap[80];
    student_info new_student, ToServe;
    int choice, n_students;
    int tag = 0;
    int index;
    int reason2, id_to_drop;

    int heap_status;
    char reason[60], c, request[70];

    infp = fopen("OnCampusRequests.txt", "r");
    if (infp == NULL) {
        printf("File not found");
    } else {
        do {
            menu();
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    n_students = construct_heap(infp, max_heap);
                    print_heap_content(max_heap, n_students);
                    tag = 1;
                    break;
                case 2:
                    if (tag == 1) {
                        printf("\n\t\tEnter the name:");
                        c = getchar();
                        gets(new_student.name);
                        printf("Enter the ID:");
                        scanf("%d", &(new_student.ID));
                        printf("\n\t\tPlease Enter Your Request:");
                        c = getchar();
                        gets(request);
                        heap_status = add_new_student_heap(
                            max_heap, new_student, &n_students, request);
                        if (heap_status == 1) {
                            printf("Added succesfully");
                        } else {
                        }
                        print_heap_content(max_heap, n_students);
                    } else {
                        printf("The heap is not constructed yet!");
                    }
                    break;

                case 3:
                    if (tag == 1) {
                        delete_student_heap(max_heap, &n_students, &ToServe);
                        if (ToServe.priority == 15) {
                            printf(
                                "\n\t\tStudent %s with ID: %d was assigned a "
                                "room on campus "
                                "because: He/She is a first year student\n",
                                ToServe.name, (ToServe.ID));
                        } else if (ToServe.priority == 10) {
                            printf(
                                "\n\t\tStudent %s with ID: %d was assigned a "
                                "room on campus "
                                "because: He/She has health issues\n",
                                ToServe.name, (ToServe.ID));
                        } else {
                            printf(
                                "\n\t\tStudent %s with ID: %d was assigned a "
                                "room on campus "
                                "because of Other reason\n",
                                ToServe.name, (ToServe.ID));
                        }

                    } else {
                        printf("The heap is not constructed yet!");
                    }
                    break;
                case 4:
                    if (tag == 0) {
                        printf("\n\n\t Heap is not constructed yet!\n");
                    } else {
                        heap_sort(max_heap, n_students);
                        print_sorted_heap(max_heap, n_students);
                    }
                    break;
                case 5:
                    if (tag == 1) {
                        printf("Please enter The ID of the student :");
                        scanf("%d", &id_to_drop);
                        index = drop_student(max_heap, (n_students - 1),
                                             id_to_drop, &reason2);
                        if (index == -1) {
                            printf("Student Not Founds");
                        } else {
                            if (reason2 == 15) {
                                printf(
                                    "Student %s with ID: %d who applied for "
                                    "living on campus for reason First year "
                                    "Student was deleted from the heap.",
                                    max_heap[index].name, max_heap[index].ID);
                            } else if (reason2 == 10) {
                                printf(
                                    "Student %s with ID: %d who applied for "
                                    "living on campus for reason Health Issues "
                                    "was deleted from the heap.",
                                    max_heap[index].name, max_heap[index].ID);
                            } else {
                                printf(
                                    "Student %s with ID: %d who applied for "
                                    "living on campus for others reason was "
                                    "deleted from the heap.",
                                    max_heap[index].name, max_heap[index].ID);
                            }
                        }
                    }
                    break;
                case 6:
                    if (tag == 0) {
                        printf("\n\t Heap is not constructed yet!\n");

                    } else if (n_students == 0) {
                        printf("\n\t Heap is empty!\n");

                    } else {
                        infp = fopen("ToContact.txt", "w");
                        load_to_file(infp, max_heap, n_students);
                        fclose(infp);
                    }
                    printf("\n\n\tDone!\n\n\t");
                    break;

                default:
                    printf("Wrong input!");
                    break;
            }
        } while (choice != 6);
    }
}