#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[30];
    double percentage;
    char plateform[30];
    double number_of_users;
} social_media_info;

void menu() {
    printf("\n\t------------------- Menu to Use-----------------------\n");
    printf("\n\t\t1. View The file content\n");
    printf("\n\t\t2. Load the file content to an array\n");
    printf(
        "\n\t\t3. Get the country with the highest number of social media "
        "users\n");
    printf("\n\t\t4. Sort data by number of social media users\n");
    printf("\n\t\t5. Get a countrys social media data\n");
    printf("\n\t\t6. To Quit ");
    printf("\n\t\t-------------------------------------------------------\n");
    printf("\n\tYour choice please:");
}

double array_to_double(char arr[], FILE *infp, int n) {
    int i, ch;
    char *endptr;
    for (i = 0; ((i < n - 1) && ((ch = fgetc(infp)) != '\n')); i++) {
        if (ch != ',') {
            arr[i] = ch;
        } else {
            i--;  // to cancel the index incrementation to not let that spot
                  // filled with random value
        }
    }
    arr[i] = '\0';
    return strtod(arr, &endptr);
}
void remove_endline(char arr[]) {
    // trying to find the length of the array
    // using strlen
    int len;
    len = strlen(arr);
    arr[len - 1] = '\0';
}

int Load_The_File(FILE *infp, social_media_info *arr) {
    int i = 0;
    char *endptr;
    char temp, Line[50];
    char user_num[20];
    char number_of_users[30];
    fseek(infp, 0, 0);
    while (!feof(infp)) {
        fgets(arr[i].name, 30, infp);  // remove "\n" need to be done
        remove_endline(arr[i].name);
        fscanf(infp, "%lf%c%c", &arr[i].percentage, &temp, &temp);
        fgets(arr[i].plateform, 30, infp);
        arr[i].number_of_users = (array_to_double(number_of_users, infp, 9));
        fgets(Line, 50, infp);
        i++;
    }
    return (i);
}

void View_The_file_content(FILE *infp) {  // viewing file
    fseek(infp, 0, 0);
    char content[50];
    while (!feof(infp)) {
        fgets(content, 50, infp);
        printf("\n\t\t%s", content);
    }
}

void highest_users(social_media_info *arr, int x, int *i) {
    double max = 0;  // working properly
    for (int j = 0; j < x; j++) {
        if (arr[j].number_of_users > max) {
            max = arr[j].number_of_users;
            *i = j;
        }
    }
}

void sorting_array(social_media_info *arr, int n /* the length of the array*/) {
    /*
    using selection sort
    working with arr.number_of_users
    */
    // to contain the element in the swaping process.
    social_media_info container;  // to help us swap elements
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].number_of_users > arr[min_idx].number_of_users) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        if (min_idx != i) {  // meaning that
            // swap
            container = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = container;
        }
    }
}

void search_data_country(social_media_info *arr, char *country_search, int len,
                         int *index) {
    int value,
        flag = 0;  // flag to control the return (using a pointer)
    int i;
    for (i = 0; i < len; i++) {
        value = strcmp(country_search, arr[i].name);
        if (value == 0) {
            flag = 1;  // found
            break;
        }
    }
    if (flag == 1) {
        *index = i;
    } else {
        *index = -1;
    }
}

int main() {  // main function

    FILE *infp;
    infp = fopen("social_media.txt", "r");
    social_media_info arr[50];
    int choice, arr_len, i, b, z, flag2 = 0;
    char country_search[30], ch;
    do {
        menu();
        scanf("%d", &choice);
        printf(
            "\n\t\t--------------------------------------------------------"
            "\n");
        if (choice == 1)
            View_The_file_content(
                infp);  // working properly. returns number of countries
        else if (choice == 2) {
            arr_len = Load_The_File(infp, arr);  // to be fixed
            printf("Loading Successfull with the data of %d countries ",
                   arr_len);
            flag2 = 1;
        } else if (choice == 3 && flag2 != 0)
        // Get the country with the highest number of social
        {
            highest_users(arr, arr_len, &i);
            printf(
                "\n\tThe country that has the highest number of active "
                "social "
                "media users is :%s \n\t\t\t\twith %.2lf millions of "
                "users\n",
                arr[i].name, arr[i].number_of_users);
        } else if (choice == 4 &&
                   flag2 != 0)  // Sort data by number of social media users
        {
            sorting_array(arr, arr_len);
            printf("Sorted Successful");
        } else if (choice == 5 &&
                   flag2 != 0)  // get a country social media data
        {
            // choice 5 begin
            printf(
                "Please enter the name of the country that you want the data "
                "from:");
            ch = getchar();  // what is this used for
            gets(country_search);
            search_data_country(arr, country_search, z, &b);
            if (b >= 0) {
                printf(
                    "Country Data\n------------------------------------ "
                    "\n%s\n%.2lf\n%s%.2lf",
                    arr[b].name, arr[b].percentage, arr[b].plateform,
                    arr[b].number_of_users);

            } else {
                printf("\n\n\tCountry not found\n");
            }
            // choice 5 end
        } else if (choice == 6) {
            printf("\n\t\t You decided to QUIT,...Bye!\n\n\t\t");
        } else {
            printf(
                "\n\t\t You cannot execute this menus unless you select first "
                "the second menu ,or this number is not available \n");
        }
    } while (choice != 6);
    return 0;
}
