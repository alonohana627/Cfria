#ifndef A_CTYPE_H
#define A_CTYPE_H

#include "a_stdlib.h"

/*Macros for alphanumeric*/
#define a_isdigit(c) (c>='0'&&c<='9')
#define a_islower(c) (c>='a'&&c<='z')
#define a_isupper(c) (c>='A'&&c<='Z')
#define a_isalpha(c) a_islower(c)||a_isupper(c)
#define a_isalnum(c) a_isalpha(c)||a_isdigit(c)
#define a_isxdigit(c) a_isdigit(c)||(c>='a' && c<='f')||(c>='A'&&c<='F')

/**/
#define a_isspace(c) c=='\n'||c==' '||c=='\t'||c=='\r'||c=='\v'

/*shit like ;-!@#%*^ 
Simanei Kria
*/
#define a_ispunct(c) (c>=33&&c<=47)||(c>=58&&c<=64)||(c>=91&&c<=96)||(c>=123&&c<=126)

/**/
#define a_isprint(c) a_isspace(c)||a_isalnum(c)||a_ispunct(c)
#define a_isgraph(c) !(a_isspace(c)) && (a_isalnum(c)||a_ispunct(c))
#define a_iscntrl(c) (c>=0&&c<=32)||c==127

int a_toupper(int c);
int a_tolower(int c);

#endif
