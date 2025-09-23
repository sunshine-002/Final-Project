#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define keep 50
    char name[keep][15];
    char leave_type[keep][20];
    int start[keep];
    int end[keep];

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
    char line_temp[50], temp_name[20], temp_type[20];
    int date_start, date_end;
    int found = 0;
    char keyword[20];

    printf("Enter keyword to search : \n");
    scanf("%s",keyword);
    int keyword_num = atoi(keyword);

    

}

int load() {
    FILE *open = fopen("information.csv","r");
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
    FILE *naku = fopen("information.csv","a");
    printf("Enter name: ");
    scanf("%s",name[index]);

    printf("Enter leave type: ");
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