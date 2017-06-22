/*
Для тестирования: запускаем программу с каким-нибудь числовым значением,
создается регион разделяемой памяти, заполняется числами, печатается ключ
созданного регина, после сегмент разделяемой памяти отстыковывается.
Для тестирования Solution необходимо запустить дважды в разных потоках с разными
числовыми значениями. 
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {   

    size_t size = 1000;
    key_t key = ftok(".", atoi(argv[1]));
    printf("key %d\n", key);

    int memid = shmget(key, size, 0666|IPC_CREAT);
    perror("SHMGet");
    int *memadd;
    memadd = (int *) shmat(memid, NULL, 0);
    perror("SHMAt");
    int i;
    for (i=0; i<100; i++) {
        *memadd = i;
        memadd++;
    }
    getchar();
    shmdt(memadd);  
    return 0;
}