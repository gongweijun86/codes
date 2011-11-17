#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*len)(char *) = strlen;


typedef struct
{
	char *str;
	int len;
}CString;

CString *Init_CString(char *str)
{
	CString *p = malloc(sizeof(CString));
	p->str = malloc(sizeof(CString));
	p->len = strlen(str);
	strncpy(p->str, str, strlen(str) + 1);
	return p;
}

void Delete_CString(CString *p)
{
	free(p->str);
	free(p);
}

char Chomp(CString *cstring)
{
	char lastchar = *(cstring->str + cstring->len - 1);
	*(cstring->str + cstring->len - 1) = '\0';
	cstring->len = strlen(cstring->str);

	return lastchar;
}

CString *Append_Chars_To_CString(CString *p, char *str)
{
	char *newstr = malloc(p->len + 1);
	p->len = p->len + strlen(str);

	snprintf(newstr, p->len + 1, "%s%s", p->str, str);
	
	free(p->str);
	p->str = newstr;

	return p;
}

int main(void)
{
	CString *mystr;
	char c;

	mystr = Init_CString("Hello!");
	printf("Init:\n str:%s len:%d\n", mystr->str, mystr->len);
	c = Chomp(mystr);
	printf("Chomp %c:\n str:%s len:%d\n", c, mystr->str, mystr->len);
	mystr = Append_Chars_To_CString(mystr, " world!");
	printf("Append:\n str:%s len:%d\n", mystr->str, mystr->len);

	Delete_CString(mystr);

	return 0;
}

