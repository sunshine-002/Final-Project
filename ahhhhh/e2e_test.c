#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "e2e_test.h"
#define keep 50

extern char name[50][15];
extern char leave_type[50][20];
extern char start[50][20];
extern char end[50][20];


void e2e_test() {
    strcpy(name[0],"TestTest");
    strcpy(leave_type[0],"Vacation");
    strcpy(start[0],"2025-10-15");
    strcpy(end[0],"2025-10-17");

    FILE *imcrying = fopen("data.csv","w");
    if(imcrying == NULL) {
        printf("Can not open file for reading\n");
        return;
    }
    fprintf(imcrying,"%s,%s,%s,%s",name[0],leave_type[0],start[0],end[0]);
    fclose(imcrying);

    int count = load();
    assert(count > 0);
    assert(strcmp(name[0],"TestTest") == 0); 

    int found = 0;
    for(int i = 0; i < keep; i++) {
        if(strcmp(name[i],"TestTest") == 0 && strcmp(leave_type[i],"Vacation") == 0 &&
            strcmp(start[i],"2025-10-15") == 0 && strcmp(end[i],"2025-10-17") == 0) {
                found++;
            } 
    }
    assert(found == 1);

    name[0][0] = '\0';
    leave_type[0][0] = '\0';
    start[0][0] = '\0';
    end[0][0] = '\0';

    imcrying = fopen("data.csv","w");
    if(imcrying == NULL) {
        printf("Can not open file\n");
        return;
    }
     for (int i = 0; i < count; i++) {
        if (name[i][0] != '\0') {
            fprintf(imcrying, "%s,%s,%s,%s\n", name[i], leave_type[i], start[i], end[i]);
        }
    }
    fclose(imcrying);

    count = load();
    int check = 0;
    for(int i = 0; i < keep; i++) {
        if(strcmp(name[i],"TestTest") == 0) {
            check++;
        }
    }
    assert(check == 0);
    printf("E2E Test passed successfully!\n");

}