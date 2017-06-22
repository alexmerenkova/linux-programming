#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	size_t size = 1000;
	key_t key1 = atoi(argv[1]);
	key_t key2 = atoi(argv[2]);
	key_t key = ftok(".", 123);

	printf("%d\n", key);
	
	int memid1 = shmget(key1, size, 0);
	int memid2 = shmget(key2, size, 0);
	int memid = shmget(key, size, 0666|IPC_CREAT);

	int *memadd1;
	memadd1 = (int *) shmat(memid1, NULL, SHM_RDONLY);
	int *memadd2;
	memadd2 = (int *) shmat(memid2, NULL, SHM_RDONLY);
	int *memadd;
	memadd = (int *) shmat(memid, NULL, 0);
	int i;
	if (memadd1 && memadd2 && memadd) {
		for (i = 0; i < 100; i++) {
			*memadd = *memadd1 + *memadd2;
			memadd++;
			memadd1++;
			memadd2++;
		}
	}

	shmdt(memadd);
	shmdt(memadd1);
	shmdt(memadd2);

	
	return 0;
}