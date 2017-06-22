/*
В текущем каталоге есть 2 канала in1 in2, в которые в случайном
порядке поступают числа, которые необходимо просуммировать и
вывести окончательную сумму на экран. Сумма выводится в отдельной
строке, завершающейся символом конца строки. Признаком окончания
подачи символов в каналы является закрытие этих каналов посылающей
стороной.

Подсказка: для неблокирующего чтения использовать select.
Замечание: ﻿протокол обмена по каналу текстовый, то есть числа
представлены строками

Пример вызова
./solution 
795

*/

#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


int read_pipe(int fd, int *sum) {
	char tmp[100];
	int numbytes = read(fd, tmp, 99);
	tmp[numbytes] = '\0';
	*sum = *sum + atoi(tmp);
	return numbytes;
}

int main(int argc, char *argv[]) {
	bool in1_open;
	bool in2_open;
	int sum = 0;
	int res_read = 0;
	int in1 = open("./in1", O_RDONLY);
	int in2 = open("./in2", O_RDONLY);
	fd_set w_list;
	in1_open = (in1 != -1);
	in2_open = (in2 != -1);

	while (in1_open || in2_open) {
		FD_ZERO(&w_list);
		if (in1_open)
			FD_SET(in1, &w_list);
		if (in2_open)
			FD_SET(in2, &w_list);

		int result = select(in2+1, &w_list, NULL, NULL, NULL);
		if (result) {
			if (FD_ISSET(in1, &w_list)) {
				res_read = read_pipe(in1, &sum);
				in1_open = (res_read != 0);
			}

			if (FD_ISSET(in2, &w_list)) {
				res_read = read_pipe(in2, &sum);
				in2_open = (res_read != 0);
			}
		}
	}
	printf("%d\n", sum);
	close(in1);
	close(in2);
	return 0;
}