#include<stdio.h>

void test_const_char_array() {
    char *carray[5];

    const char* bob1 = "a string1";
    const char* bob2 = "a string2";

    carray[0] = (char*)bob1;
    carray[1] = (char*)bob2;
    carray[2] = "";

    for(int x=0; x<sizeof(carray); x++) {
        if (!carray[x]) break;
        printf("%s", carray[x]);
    }
}

// void test_strncpy_offset() {
//     char buff[10] = "1234567890";
//     char *ptr = &buff[0];
//     strncpy(&buff[3], "whatsup", 3);
//     printf(buff);
// }

int main(int argc, char *argv[]) {
    test_const_char_array();
}
