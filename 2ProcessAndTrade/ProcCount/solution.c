/*
Разработать программу solution, которая осуществляет
поиск и подсчет числа процессов с именем genenv в
системе Linux на которой выполняется программа. 

Пример вызова
./solution
13

*/

#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>


int main(){
	char *pnum;
	char pname[20];
	char name[20] = "genenv"; 
	int cnt = 0;
	DIR *dir = opendir("/proc"); 
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL ){
		pnum = entry->d_name;

		if (entry->d_type == DT_DIR && isdigit(pnum[1])) {
			char fullname[20];
			sprintf(fullname, "/proc/%s/comm", pnum);
			FILE *fid = fopen(fullname, "r");

			if (fid){
				fscanf(fid, "%s", pname);
				if (strcmp (name, pname)==0) {
					cnt = cnt + 1;
				}
				fclose(fid);
			}
		}
	}
	printf("%d\n", cnt);
	closedir(dir);
	return 0;
}


