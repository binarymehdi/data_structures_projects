
#include <stdio.h>
#include <stdlib.h>

typedef struct tag {
    int ID;
    char name[30];
    struct tag *next;
} node;

void menu(void) {
    printf("\n\n\t\t--------------- Menu to Use------------------------\n");
    printf("\t\t|                                                   |\n");
    printf("\t\t|1.  New student joins                              |\n");
    printf("\t\t|2.  Student time is up. Next!                      |\n");
    printf("\t\t|3.  Print list of student interested in playing    |\n");
    printf("\t\t|4.  A student wants to leave the Queue             |\n");
    printf("\t\t|5.  Dr. Talei wants her Toy back                   |\n");
    printf("\t\t|6.  To Quit                                        |\n");
    printf("\t\t----------------------------------------------------\n");
    printf("\n\t\tYour Choice Please:");
}

node *create_fill() {
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    getchar();
    printf("\n\t\tPlease enter the name of the student :");
    gets(new_node->name);
    printf("\n\t\tPlease enter the ID :");
    scanf("%d", &new_node->ID);
    new_node->next = NULL;
    return (new_node);
}

// circular queues are used to manage users requests
void enqueue(node **front, node **rear, node *new_node) {
    if (*front == NULL && *rear == NULL) {  // queue empty
        *front = *rear = new_node;
        (*rear)->next = *front;
    } else {  // not empty
        (*rear)->next = new_node;
        (*rear) = new_node;
        (*rear)->next = *front;  // bc it is circular
    }
}

void dequeue(node **front, node **rear) {
    node *temp;
    temp = *front;
    if (*front == NULL && *rear == NULL) {
        printf("The queue is Empty");
    } else if (*front == *rear) {  // one element
        *front = *rear = NULL;
        free(temp);
    } else {  // multiple elements
        *front = (*front)->next;
        (*rear)->next = *front;
        free(temp);
    }
}

void display(node **front) {
    node *temp;
    temp = *front;
    if (*front == NULL) {
        printf("\n\t\tThe queue is Empty");
    } else {
        while (temp->next != *front) {
            printf("\n\t\tStudent : %s \t with ID : %d\n", temp->name,
                   temp->ID);
            temp = temp->next;
        }
        printf("\n\t\tStudent : %s \t with ID : %d\n", temp->name, temp->ID);
    }
}

void moove(node **front, node **rear) {
    node *temp;
    temp = *front;
    if (*front == NULL && *rear == NULL) {
        printf("\n\t\tThe queue is Empty");
    } else {
        *front = (*front)->next;
        (*rear)->next = temp;
        *rear = temp;
        temp->next = *front;
    }
}

// we are using a ciruclar queue

void remove_student(node **front, node **rear, int id) {
    // algorithm
    node *temp, *walker;
    // case1: The node we want to delete is the first node. It contains two
    // cases
    if ((*front)->ID == id) {
        // case 1.1: That node is the only node in the queue:
        if ((*front) == (*rear)) {
            temp = *front;
            free(temp);
            *front = *rear = NULL;
            // You will need to free the front and assign both the front and the
            // rear to NULL
        }
        // case 1.2: That node is not the only node:
        else {
            // temp points to front
            temp = *front;
            // front should point to the next node
            *front = (*front)->next;
            // rear next should be front
            (*rear)->next = *front;
            // free temp
            free(temp);
        }
    }

    // General case: We traverse the list to find the targetted node
    else {
        // use a walker to traverse. Once walker->next->id == id, set temp to
        // walker->next and walker next to temp next. then free the temp.
        // Here handle the case of the last node separatly, because in that case
        // you will change the rear to walker (the before-last node that is now
        // the last node) You check the id of walker->next not walker because
        // you will need access to the previous node (walker) to link it to the
        // next node (walker->next->next or temp->next)
        walker = *front;
        do {
            if (walker->next->ID == id) {
                if (walker->next == *rear) {
                    *rear = walker;
                }
                temp = walker->next;
                walker->next = temp->next;
                free(temp);
                break;
            }
            walker = walker->next;
        } while (walker != *front);
    }
}

void destroy_queue(node **pfront, node **prear) {
    node *walker;
    walker = *pfront;
    // algorithmc
    // Here impliment a while loop that traverses the list and frees it node
    // after node. At the end, assign the front and the rear to NULL
    node *temp;
    while (walker != NULL) {
        if (walker == *prear) {
            free(walker);
            *prear = NULL;
            *pfront = NULL;
            break;
        }
        temp = walker;
        walker = walker->next;
        free(temp);
    }
}

int main() {
    // declare variables here
    node *front = NULL, *rear = NULL, *new_node;
    char choice_2;
    int choice, leave_id;
    do {
        menu();
        // choice input
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                new_node = create_fill();
                enqueue(&front, &rear, new_node);
                break;
            case 2:
                printf(
                    "The first student wants to remain in the queue ?\n\t -Y "
                    "for yes and N for No :");
                getchar();
                scanf("%c", &choice_2);
                if (choice_2 == 'N') {
                    dequeue(&front, &rear);
                } else {
                    moove(&front, &rear);

                }  // front should point to the node to serve and rear must
                   // point
                // to the last element. Queues can be empty

                break;
            case 3:
                display(&front);
                break;
            case 4:
                // Student leaves the Queues
                printf("Please Enter the id of the student: ");
                scanf("%d", &leave_id);
                remove_student(&front, &rear, leave_id);
                break;
            case 5:
                // destroys the queue and ends program
                destroy_queue(&front, &rear);
                printf("\n\n\t\tQueue Destroyed successfully\n");
                break;
            default:
                printf("Wrong input");
                break;
        }
    } while (choice != 6);
}
