/*
Разработать программу solution, которая при запуске
себя "демонизирует" и остается в  памяти. Перед закрытием
стандартного потока вывода stdout унаследованного от родителя,
программа должна вывести в него Pid процесса-демона.

Пример вызова
./solution
13221

*/
#include <stdio.h>
#include <string.h>

int main(){
	FILE *fid = fopen("/proc/self/stat", "r");
	char pid[10];
	fscanf(fid, "%s", pid);
	printf("%s\n", pid);
	fclose(fid);
	int result;
	result = daemon(0,0);
	if (!result) {
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
		sleep(10);
	}
	return 0;
}