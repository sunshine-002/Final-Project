#include<stdio.h>
#define keep 100
    char employee_name[keep][15];
    char leavetype[keep][20];
    int start_date[keep];
    int end_date[keep];


void display_menu() {
    printf("\033[1mMenu\033[0m \n");
    printf("1.Save file to csv\n");
    printf("2.Read file csv\n");
    printf("3.Add information\n");
    printf("4.Search information\n");
    printf("5.Update information\n");
    printf("6.delete information\n");
    printf("Press 0 to exit\n");
}

int ohyea( FILE **in_fp , FILE **out_fp ){
    *in_fp = fopen("imscreaming.csv","r");
    *out_fp = fopen("information.csv","w");

    if( *in_fp == NULL || *out_fp == NULL ) {
        printf("ERROR\n");
        return 1;
    }
    return 0;
}

void save_file() {
    FILE *in_fp,*out_fp;
        if(ohyea(&in_fp ,&out_fp) != 0) return;
    char temp[300];
    while(fgets(temp,sizeof(temp),in_fp)) {
        fprintf(out_fp,"%s",temp);
    }
    fclose(in_fp);
    fclose(out_fp);
    printf("DONE\n");
}

int load() {
    FILE *open = fopen("information.csv","r");
    if(open == NULL) return 0;

    int loaded = 0;
    while(fscanf(open,"%[^,],%[^,],%d,%d",employee_name[loaded],leavetype[loaded],&start_date[loaded],&end_date[loaded]) == 4){
        loaded++;
        if(loaded >= keep ) break;
    }
    fclose(open);
    return loaded;
}

void add(int current_count) {
    int index = -1;

    for(int i=0; i < keep; i++) {
        if(employee_name[i][0] == '\0') {
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
    scanf("%s",employee_name[index]);

    printf("Enter leave type: ");
    scanf("%s",leavetype[index]);

    printf("Enter start date(ex.20251227): \n");
    scanf("%d",&start_date[index]);

    printf("Enter end date(ex'20251231): \n");
    scanf("%d",&end_date[index]);

    if(naku != NULL){
        fprintf(naku,"%s,%s,%d,%d\n",employee_name[index],leavetype[index],start_date[index],end_date[index]);
        fclose(naku);
    } else {
        printf("Can not add information\n");
    }

    printf("Added succesfully");
}

