/*
Разработать программу solution, обеспечивающую загрузку динамической
библиотеки в режиме исполнения. При запуске, программе передается имя
динамической библиотеки, имя функции которая должна быть вызвана, и ее
аргумент. Функция в библиотеке принимает на вход int и возвращает int.
Результат, возвращаемый функцией должен быть выведен отдельной строкой
(оканчиваться символом новой строки \n)  в stdout.

Пример вызова
./solution libShared.so someSecretFunctionPrototype 8
16

*/

#include <stdio.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


int (*func)(int);

bool init_lib(const char *libname, const char *funname){
	char name[40] = "./";
	strcat (name, libname);

	void *hdl = dlopen(name, RTLD_LAZY);
	if (hdl == NULL)
		return false;
	func = (void (*))dlsym(hdl, funname);

	if (func == NULL)
		return false;

	return true;
}

int main(int argc, char *argv[]){
	int num = 0;
	num = atoi(argv[3]);
	int result = 0;
	if (init_lib(argv[1], argv[2]))
		result = func(num);
	printf("%d\n", result);
	return 0;

}