/*
В задании требуется доработать демон, разработанный ранее.
Задача - снабдить демон обработчиком сигнала SIGURG,
по приходу которого демон должен завершать свою работу.

Пример вызова
./solution
13336

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void sig_handler(int signo) {
	exit(0);
}

int main(int argc, char *argv[]) {
	signal(SIGURG, sig_handler);
	int result;
	result = daemon(0,0);

	if (!result) {
		FILE *fid = fopen("/proc/self/stat", "r");
		char pid[10];
		fscanf(fid, "%s", pid);
		printf("%s\n", pid);
		fclose(fid);
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
		while (1) {
			;
		}
	}
	return 0;
}