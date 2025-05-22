#include <stdio.h>
#include <string.h>

int const max = 100;


char names[max][50];
int marks[max];
int n;

void show_name_mark(){
    for (int i = 0; i < n; i++){
        printf("name : %s\nmark : %d\n",names[i], marks[i]);
    }
}

void statiktik(){
    int average, highest = marks[0], lowest = marks[0],
    high_index, low_index;
    for (int i = 0; i < n; i++){
        average += marks[i];
        if (marks[i] > highest){
            highest = marks[i];
            high_index = i;
        }
        if (marks[i] < lowest){
            lowest = marks[i];
            low_index = i;
        }
    }

    printf("Average : %d\n", average / n);
    printf("Highest mark %d by %s\n", highest, names[high_index]);
    printf("lowest mark %d by %s\n", lowest, names[low_index]);

}

void count_passed(){
    int pass = 0, fail =  0;
    for (int i = 0; i < n; i++){
        if (marks[i] >= 50){
            pass++;
        }

        if (marks[i] < 50){
            fail++;
        }

    }
    printf("Passed : %d\nFailed : %d\n", pass, fail);
}

void search_mark(int find_mark){
    int found = 0;
    printf("Students with %d mark : \n", find_mark);
    for (int i = 0; i < n; i++){
        if (marks[i] == find_mark){
            printf("name : %s\n", names[i]);
        }
    }

    if (!found){
        printf("No students with that mark.\n");
    }

}

void search_name(char name[]){
    for (int i = 0; i < n; i++){
        if (!strcmp(names[i], name)){
            printf("student name : %s\ngrade : %d", names[i], marks[i]);
        }
    }
}

int main() {

    printf("How many students are in class : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        char t_[40];
        printf("Student #%d name : ", i);
        scanf(" %s", t_);
        strcpy(names[i], t_);
    }

    printf("Please input student grades : \n");

    for (int i = 0; i < n; i++){
        printf("%s : ", names[i]);
        scanf("%d", &marks[i]);
    }

    printf("Done inputting!\n");

    int choice;
    int exit = 1;


    do {
        printf("Student Monitoring Menu\n");
        printf("1. Display all students and marks\n");
        printf("2. Statistics\n");
        printf("3. Display pass and fail\n");
        printf("4. Mark Search\n");
        printf("5. Student search\n");
        printf("6. To exit\n");
        printf("Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            show_name_mark();
            break;
        case 2:
            statiktik();
            break;
        case 3:
            count_passed();
            break;
        case 4:
            int t_mark;
            printf("Insert mark : ");
            scanf("%d", &t_mark);
            search_mark(t_mark);
            break;
        case 5:
            char t_name[40];
            printf("Find name : ");
            scanf(" %s", t_name);
            search_name(t_name);
            break;
        case 6:
        printf("Goodbye!\n");
            exit = 0;
            break;
        default:
            break;
        }
    } while (exit);








    return 0;
}
