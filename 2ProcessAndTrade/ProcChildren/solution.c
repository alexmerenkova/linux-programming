/*
Разработать программу solution, которая по заданному pid
осуществляет поиск всех потомков процесса с этим идентификатором
и выводит их количество (включая процесс с заданным pid).

Пример вызова
./solution 1233
76

*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int find_elem(int elem, int *par, int *ch, int len) {
	int i;
	int count = 0;
	for (i = 0; i <= len; i ++) {
		if (par[i] == elem) {
			count = count + 1;
			count = count + find_elem(ch[i], par, ch, len);
		}
	} 
	return count;
}

int main(int argc, char *argv[]){
	int child[200];
	int parent[200];
	int ipid;
	ipid = atoi(argv[1]);
	int cnt = 0;
	char *pnum;
	char cpid[20], pid[20];

	DIR *dir = opendir("/proc"); 
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL ) {
		pnum = entry->d_name;
		if (entry->d_type == DT_DIR && isdigit(pnum[1])) {
			char fullname[20];
			sprintf(fullname, "/proc/%s/stat", pnum);
			FILE *fid = fopen(fullname, "r");
			fscanf(fid, "%s%*s%*s%s", cpid, pid);
			child[cnt] = atoi(cpid);
			parent[cnt] = atoi(pid);
			cnt = cnt + 1;
			fclose(fid);
		}
	}
	closedir(dir);
	printf("%d\n", 1 + find_elem(ipid, parent, child, cnt));

	return 0;
}
