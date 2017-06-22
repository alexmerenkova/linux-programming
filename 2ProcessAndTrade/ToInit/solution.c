/*
Разработать программу solution, которая по заданному pid
осуществляет поиск пути в дереве процессов до процесса
с идентификатором 1 (init). Для каждого найденного процесса
печатается в отдельной строке его идентификатор.

Пример вызова
./solution 1766
1766
1299
465
1

*/

#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	char cpid[10];
	char *pid;
	char path[20];
	char last[10] = "1";

	pid = argv[1];
	printf("%s\n", pid);
	
	while (strcmp(pid, last)) {
		sprintf(path, "/proc/%s/stat", pid);
		FILE *fid = fopen(path, "r");
		fscanf(fid, "%s%*s%*s%s", cpid, pid);
		printf("%s\n", pid);
	}
	return 0;
}