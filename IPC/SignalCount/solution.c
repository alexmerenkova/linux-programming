/*
Разработать приложение, умеющее обрабатывать сигналы SIGUSR1,
SIGUSR2, SIGTERM. После старта Ваше приложение должно по приходу
одного из сигналов SIGUSR1, SIGUSR2 выполнять их суммирование,
а после прихода сигнала SIGTERM, требуется вывести в стандартный
поток вывода 2 числа, разделенных пробелом, соответствующих количеству
обработанных сигналов SIGUSR1, SIGUSR2, и завершить программу.
Вывод оканчивается символом конца строки.

Пример вызова
./solution 
79 38

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//обработчик SIGUSR1 и SIGUSR2
void sigusr_handler(int signo) {
	//static инициализируется один раз и запоминает свое значение
	static int cnt1 = 0;
	static int cnt2 = 0;

	switch (signo) {
		case SIGUSR1:
			cnt1++;
			break;
		case SIGUSR2:
			cnt2++;
			break;
		case SIGTERM:
			printf("%d %d\n", cnt1, cnt2);
			break;

	}
}

void sigterm_handler(int signo) {
	//вызываем явно обработчик SIGUSR1/2 для печати значений
	sigusr_handler(signo);
	exit(0);
}

int main(int argc, char *argv[]) {

	signal(SIGUSR1, sigusr_handler);
	signal(SIGUSR2, sigusr_handler);
	signal(SIGTERM, sigterm_handler);
	while (1) {
		;
	}
	return 0;
}