#include "../include/a_ctype.h"
#include "../include/a_stdlib.h"
#include "../include/a_stdio.h"

int a_toupper(int c){
    if(a_isupper(c)){
        return c;
    }
    if(c<='z' && c>='a'){
        c-=32;
        return c;
    }
    return A_EOF;
}

int a_tolower(int c){
    if(a_islower(c)){
        return c;
    }
    if(c<='Z' && c>='A'){
        c+=32;
        return c;
    }
    return A_EOF;
}
