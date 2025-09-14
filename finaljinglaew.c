#include<stdio.h>
#include<stdlib.h>

//DISPLAY MENU

int display_menu() {
    printf("\033[1m --MENU-- \033[0m \n");
    printf("1.Save file\n");
    printf("2.Read file\n");
    printf("3.Search\n");
    printf("4.Add information\n");
    printf("5.Delete information\n");
    printf("6.Update information\n");
    return 0;
}

int choice() {
    int selected_choice;
    printf("Choose choice 1-6 (0 for exit) : \n");
    scanf("%d",&selected_choice);
    return selected_choice;
}

void ask_again() {
    char again;
    printf("\033[1mDo you want to return to menu? (y/n): \033[0m\n");
    scanf(" %c",&again);

    if(again == 'n' || again == 'N') {
        exit(0);
    }
}

//MENU

void save_file() {
    char temp[300];
    FILE *s = fopen("information.csv","r");
    FILE *save = fopen("data.csv","w");
    if(s==NULL&&save==NULL) {
        printf("Can not open file\n");
        return;
    }

    while(fgets(temp,sizeof(temp),s)) {
        fprintf(save,"%s",temp);
    }

    fclose(s);
    fclose(save);

    printf("DONE\n");
}

void read_file() {
    FILE *r = fopen("data.csv","r");
    if(r==NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    char temp[300];
    while(fgets(temp,sizeof(temp),r)) {
        printf("%s",temp);
    }
    fclose(r);
}


//MAIN

int main() {
    
    int choice_is_calling ;

    do {
        display_menu();
        choice_is_calling = choice();
            
        switch(choice_is_calling) {
            case 0:
            printf("Exit program\n");
            exit(0);
            break;

            case 1:
            printf("Save\n");
            save_file();
            break;

            case 2:
            printf("Read\n");
            read_file();
            break;

            case 3:
            printf("Search\n");
            break;

            case 4:
            printf("Add\n");
            break;

            case 5:
            printf("Delete\n");
            break;

            case 6:
            printf("Update\n");
            break;

            default:
            printf("Enter choice again");
            break;

        }
        ask_again();
    }while(1);

    return 0;
}