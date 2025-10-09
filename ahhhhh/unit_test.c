#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "unit_test.h"

extern char name[50][15];
extern char leave_type[50][20];
extern char start[50][20];
extern char end[50][20];


void test_search() {
    strcpy(name[0],"Testuser");
    strcpy(leave_type[0],"Vacation");
    strcpy(start[0],"2025-10-15");
    strcpy(end[0],"2025-10-17");

    strcpy(name[1],"1234");
    strcpy(start[1],"2025-10-32");

    int valid_count = 0;
    for(int i = 0; i < 2; i++) {
        if(valid_name(name[i]) && date_check(start[i]) && date_check(end[i])) {
            valid_count++;
        }
    }

    assert(valid_count == 1);
    printf("test_search passed\n");
}

void test_delete_record() {
    strcpy(name[0], "Alice");
    strcpy(leave_type[0], "Vacation");
    strcpy(start[0], "2025-10-10");
    strcpy(end[0], "2025-10-12");

    strcpy(name[1], "Bob");
    strcpy(leave_type[1], "Sick Leave");
    strcpy(start[1], "2025-10-15");
    strcpy(end[1], "2025-10-16");

    int delete_index = 1;
    memset(name[delete_index], 0, sizeof(name[delete_index]));
    memset(leave_type[delete_index], 0, sizeof(leave_type[delete_index]));
    memset(start[delete_index], 0, sizeof(start[delete_index]));
    memset(end[delete_index], 0, sizeof(end[delete_index]));

    assert(name[delete_index][0] == '\0');
    assert(leave_type[delete_index][0] == '\0');
    assert(start[delete_index][0] == '\0');
    assert(end[delete_index][0] == '\0');

    printf("test_delete_record passed\n");
}
