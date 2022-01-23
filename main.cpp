#include <cstdio>
#include "library.h"
int main(){
    char str1[32];
    printf("Print the file name to find:");
    scanf("%31s", str1);
    search(str1);
}

