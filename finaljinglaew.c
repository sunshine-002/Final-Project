#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define keep 50
    char name[keep][15];
    char leave_type[keep][20];
    int start[keep];
    int end[keep];

//DISPLAY MENU
int display_menu() {
    printf("\033[1m --MENU-- \033[0m \n");
    printf("PLESE SAVE FILE BEFORE CHOOSE OTHER OPTIONS (press 1)\n");
    printf("1.Save file\n");
    printf("2.Read file\n");
    printf("3.Search\n");
    printf("4.Add information\n");
    printf("5.Delete information\n");
    printf("6.Update information\n");
    printf("7.Unit test\n");
    printf("8.End to end test\n");
    return 0;
}

int choice() {
    int selected_choice;
    printf("Choose choice 1-8 (0 for exit) : \n");
    scanf("%d",&selected_choice);
    return selected_choice;
}

void ask_again() {
    char again;
    while(1) {
        printf("\033[1m DO YOU WANT TO RETURN TO MENU (y/n)?\033[0m");
        scanf(" %c",&again);

        if(again == 'y' || again == 'Y') {
            system("cls");
            break;
        }
        else if(again == 'n' || again == 'N') {
            exit(0);
        }
        else{
            printf("Invalid input.Please enter y/n");
        }
    }
}

//MENU
void save_file() {
    char temp[300];
    FILE *s = fopen("information.csv","r");
    if( s == NULL ){
        printf("File not found\n");
    }
    FILE *save = fopen("data.csv","w");
    if(save==NULL) {
        printf("Can not open data.csv\n");
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
    int naku = 0;

    while(fgets(temp,sizeof(temp),r)) {
        printf("%s",temp);
        naku++;
    }

    if(naku == 0) {
        printf("No data found\n");
    }
    
    fclose(r);
}

void search() {
    FILE *fp = fopen("data.csv","r");
        if(fp==NULL) {
        printf("Error: Unable to open file for searching.\n");
        return;
    }
    char line_temp[100], temp_name[20], temp_type[20];
    int found = 0;
    char keyword[20];
    int choice;

    printf("Which keyword do you want to search\n");
    printf("1.Name\n");
    printf("2.Leavetype\n");
    printf("Enter choice 1,2 \n");
    scanf("%d",&choice);

    if(choice == 1) {
        printf("Enter name:\n");
        scanf("%s",keyword);

        while(fgets(line_temp,sizeof(line_temp),fp)) {
            if(sscanf(line_temp,"%[^,],%[^,]",temp_name,temp_type) == 2) {
                if(strcmp(temp_name,keyword) == 0 ) {
                    printf("%s",line_temp);
                    found++;
                }
            }
        }
    }

    else if(choice == 2) {
        int leave_choice;

        printf("\033[1m --LEAVE TYPE-- \033[0m \n");
        printf("1.Vacation\n");
        printf("2.Sick Leave\n");
        printf("3.Manitary Leave\n");
        printf("4.Personal Leave\n");
        printf("5.Annual Leave\n");
        printf("Enter choice 1-6 \n");
        scanf("%d",&leave_choice);

        switch(leave_choice) {
            case 1:
            strcpy(keyword,"Vacation");
            break;

            case 2:
            strcpy(keyword,"Sick Leave");
            break;

            case 3:
            strcpy(keyword,"Manitary Leave");
            break;

            case 4:
            strcpy(keyword,"Personal Leave");
            break;

            case 5:
            strcpy(keyword,"Annual Leave");
            break;

            default:
                printf("Invalid choice");
                fclose(fp);
                return;
        }
        while(fgets(line_temp,sizeof(line_temp),fp)) {
            if(sscanf(line_temp,"%[^,],%[^,]",temp_name,temp_type) == 2) {
                if(strcmp(temp_type,keyword) == 0) {
                    printf("%s",line_temp);
                    found++;
                }
            }
        }
    } else {
        printf("Invalid search choice \n");
    }
    if(found == 0) {
        printf("No matching data found\n");
    }
    
    fclose(fp);

}

int load() {
    FILE *open = fopen("data.csv","r");
    if(open == NULL) return 0;
    
    int loaded = 0;
    while(fscanf(open,"%[^,],%[^,],%d,%d",name[loaded],leave_type[loaded],&start[loaded],&end[loaded]) == 4){
        loaded++;
        if(loaded >= keep ) break;
    }
    fclose(open);
    return loaded;
}
void add(int current_count) {
    int index = -1;

    for(int i=0; i < keep; i++) {
        if(name[i][0] == '\0') {
            index = i;
            break;
        }
    }
    if( index == -1 ) {
        if(current_count >= keep ) {
            printf("DATA FULL\n");
        }
        else {
            printf("SOMETHING WRONG\n");
        }
        return;
    }
    FILE *naku = fopen("data.csv","a");
    printf("Enter name: \n");
    scanf("%s",name[index]);

    printf("Enter leave type: \n");
    scanf("%s",leave_type[index]);

    printf("Enter start date(ex.20251227): \n");
    scanf("%d",&start[index]);

    printf("Enter end date(ex'20251231): \n");
    scanf("%d",&end[index]);

    if(naku != NULL){
        fprintf(naku,"%s,%s,%d,%d\n",name[index],leave_type[index],start[index],end[index]);
        fclose(naku);
    } else {
        printf("Can not add information\n");
    }

    printf("Added succesfully");
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
            search();
            break;

            case 4:
            printf("Add\n");
            int count = load();
            add(count);
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