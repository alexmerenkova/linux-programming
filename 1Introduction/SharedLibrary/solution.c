/*
В этом задании Вам необходимо создать разделяемую динамическую библиотеку
libsolution.so в которой реализовать функцию со следующим прототипом:

int stringStat(const char *string, size_t multiplier, int *count);

Функция возвращает значение длины строки string, умноженное на multiplier,
и увеличивает на 1 значение, на которое указывает count.

*/

#include <stdio.h>
#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
	
	int slen = strlen(string);
	*count = *count + 1;
	return multiplier * slen;
}

int main(){
    int s = 0;
    int *p = 0;
    int pp = 10;
    p = &pp;
    s = stringStat("asdf", 5, &pp);
	printf("s = %d",s);
	printf("p = %d", pp);
	return 0;
}