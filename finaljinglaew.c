#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define keep 50
    char name[keep][15];
    char leave_type[keep][20];
    char start[keep][20],end[keep][20];

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
        printf("Enter choice 1-5 \n");
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

    for(int i = 0; i<keep; i++) {
        name[i][0] = '\0';
        leave_type[i][0] = '\0';
        start[i][0] = '\0';
        end[i][0] = '\0';
    }

    FILE *open = fopen("data.csv","r");
    if(open == NULL) return 0;
    
    int loaded = 0;
    while(fscanf(open,"%[^,],%[^,],%[^,],%[^,\n]\n",name[loaded],leave_type[loaded],start[loaded],end[loaded]) == 4){
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
    
    char temp_name[50],temp_leave_type[100],temp_start[20],temp_end[20];
    int temp_type;

    printf("Enter name: \n");
    scanf("%s",temp_name);
    system("cls");

    printf("Leave type: \n");
    printf("1.Vacation\n");
    printf("2.Sick Leave\n");
    printf("3.Manitary Leave\n");
    printf("4.Personal Leave\n");
    printf("5.Annual Leave\n");
    printf("Enter choice 1-5 \n");
    scanf("%d",&temp_type);

    switch(temp_type) {
        case 1: strcpy(temp_leave_type,"Vacation"); break;
        case 2: strcpy(temp_leave_type,"Sick Leave"); break;
        case 3: strcpy(temp_leave_type,"Manitary Leave"); break;
        case 4: strcpy(temp_leave_type,"Personal Leave"); break;
        case 5: strcpy(temp_leave_type,"Annual Leave"); break;
        default:
            printf("Invalid type\n");
            return;
    }
    system("cls");

    printf("Enter start date(ex.2025-10-15): \n");
    scanf("%s",temp_start);

    printf("Enter end date(ex.2025-10-17): \n");
    scanf("%s",temp_end);

    for(int i =0; i < keep; i++) {
        if( name[i][0] != '\0' ){
            if(strcmp(name[i],temp_name) == 0 && strcmp(leave_type[i],temp_leave_type) == 0 
            && strcmp(start[i],temp_start) == 0 && strcmp(end[i],temp_end) == 0) {
                printf("There has the same information\n");
                return;
            }
        }
    }
    strcpy(name[index],temp_name);
    strcpy(leave_type[index],temp_leave_type);
    strcpy(start[index],temp_start);
    strcpy(end[index],temp_end);

    FILE*naku = fopen("data.csv","a");
    if(naku != NULL) {
        fprintf(naku,"%s,%s,%s,%s\n",temp_name,temp_leave_type,temp_start,temp_end);
        fclose(naku);
        printf("Add successfully\n");
    } else {
        printf("Can not add infoemation\n");
    }
}

void delete() {
    char target_name[50];
    int count = load();
    int match_indexs[keep];
    int match_count = 0 ;

    printf("Enter name to delete: \n");
    scanf("%s",target_name);

    for(int i = 0; i<count ; i++ ) {
        if(strcmp(name[i],target_name) == 0) {
            printf("%d. %s, %s, %s, %s\n", match_count+1, name[i], leave_type[i], start[i], end[i]);
            match_indexs[match_count] = i;
            match_count++;
        }
    }

    if(match_count == 0) {
        printf("No matching name found\n");
        return;
    }

    int choice;
    printf("Enter number of the record to delete (1-%d):\n",match_count);
    scanf("%d",&choice);

    if(choice < 1 || choice > match_count) {
        printf("Invalid selection\n");
        return;
    }

    int delete_index = match_indexs[choice - 1];

    name[delete_index][0] = '\0';
    leave_type[delete_index][0] = '\0';
    start[delete_index][0] = '\0';
    end[delete_index][0] = '\0';

    FILE *fp = fopen("data.csv","w");
    if( fp == NULL ) {
        printf("Can not open file for writing\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        if(name[i][0] != '\0') {
            fprintf(fp, "%s,%s,%s,%s\n", name[i], leave_type[i], start[i], end[i]);
        }
    }
    fclose(fp);
    printf("Record deleted successfully\n");

}

void update() {
    char target_name[50];
    int count = load();
    int match_indexs[keep];
    int match_count = 0 ;

    printf("Whose data do you want to update\n");
    scanf("%s",target_name);

    for(int i = 0; i<keep; i++) {
        if(strcmp(name[i],target_name) == 0) {
            printf("%d. %s,%s,%s,%s\n",match_count+1, name[i], leave_type[i], start[i], end[i]);
            match_indexs[match_count] = i;
            match_count++;
        }
    }
    
    if(match_count == 0) {
        printf("No matching name found\n");
        return;
    }

    int choice;
    printf("Enter number of the record to delete (1-%d):\n",match_count);
    scanf("%d",&choice);

    if(choice < 1 || choice > match_count) {
        printf("Invalid selection\n");
        return;
    }

    int update_index = match_indexs[choice - 1];

    int choice_update;
    printf("What do you want to update\n");
    printf("1.Name\n");
    printf("2.Leave type\n");
    printf("3.Start date\n");
    printf("4.End date\n");
    scanf("%d",&choice_update);

    switch(choice_update) {
        case 1: 
            printf("Change name:\n");
            scanf("%s",name[update_index]);
            break;
        case 2:
            int leave_choice;
            printf("Leave type: \n");
            printf("1.Vacation\n");
            printf("2.Sick Leave\n");
            printf("3.Manitary Leave\n");
            printf("4.Personal Leave\n");
            printf("5.Annual Leave\n");
            printf("Enter choice 1-5 \n");
            scanf("%d",&leave_choice);
        
             switch(leave_choice) {
                case 1: strcpy(leave_type[update_index],"Vacation"); break;
                case 2: strcpy(leave_type[update_index],"Sick Leave"); break;
                case 3: strcpy(leave_type[update_index],"Manitary Leave"); break;
                case 4: strcpy(leave_type[update_index],"Personal Leave"); break;
                case 5: strcpy(leave_type[update_index],"Annual Leave"); break;
                default:
                    printf("Invalid leave type\n");
                    return;
                }
            break;
        case 3:
            printf("Enter new date start(ex.2025-10-15):\n");
            scanf("%s",start[update_index]);
            break;
        case 4:
            printf("Enter new date end(ex.2025-10-17):\n");
            scanf("%s",end[update_index]);
            break;

    }

    for(int i = 0; i < count; i++) {
        if(i != update_index &&
           strcmp(name[i], name[update_index]) == 0 &&
           strcmp(leave_type[i], leave_type[update_index]) == 0 &&
           strcmp(start[i], start[update_index]) == 0 &&
           strcmp(end[i], end[update_index]) == 0) {
            printf("This updated information already exists in another record.\n");
            return;
        }
    }

    FILE *imdied = fopen("data.csv",'w');
    if(imdied == NULL) {
        printf("Can not open file for update\n");
        return;
    }

    for(int i = 0; i < keep; i++) {
        if(name[i][0] != '\0') {
            fprintf(imdied,"%s,%s,%s,%s",name[i], leave_type[i], start[i], end[i]);
        }
    }
    fclose(imdied);
    printf("Update successfully\n");


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
            delete();
            break;

            case 6:
            printf("Update\n");
            update();
            break;

            default:
            printf("Enter choice again");
            break;

        }
        ask_again();
    }while(1);

    return 0;
}