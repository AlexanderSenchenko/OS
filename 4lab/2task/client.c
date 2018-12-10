#include "main.h"

static int flag;
static int out;
static char buff[MAXBUFF];

void sighandler()
{
	write(out, &sig, 1);
	flag = 1;
	exit(0);
}

void *wait_signal(void *arg)
{
	signal(SIGTSTP, sighandler);
	return NULL;
}

int main()
{
	char buff2[1000];
	strcpy(buff, TEMPLATE);
	int start_write = strlen(buff);
	
	if ((out = open(FIFO, O_WRONLY)) < 0) {
		printf("Error open FIFO\n");
		exit(1);
	}

	write(STDOUT_FILENO, "Input name file: ", 17);
	read(STDIN_FILENO, &buff[start_write], MAXBUFF);

	int size = strlen(buff);

	if (write(out, buff, size) != size) {
		printf("Error write FIFO\n");
		exit(1);
	}

	// pthread_t tid;
	// pthread_create(&tid, NULL, wait_signal, NULL);

	signal(SIGTSTP, sighandler);
	flag = 0;
	while (!flag) {
		memset(buff2, 0, 1000);
		write(STDOUT_FILENO, "Input message: ", 15);

		size = read(STDIN_FILENO, buff2, 1000);

		if (size > MAXBUFF) {
			write(STDOUT_FILENO, "Error\n", 6);
			continue;
		} else {
			if (write(out, buff2, size) != size) {
				printf("Error write FIFO\n");
				exit(1);
			}
		}
		// scanf("%s", buff);
		// buff[strlen(buff)] = '\n';
		// printf("%ld %d\n", strlen(buff), MAXBUFF);

		// if (size >= MAXBUFF) {
		// 	// buff[MAXBUFF] = '\0';
		// 	write(STDOUT_FILENO, "test", 4);
		// 	size = MAXBUFF - 3;
		// }

		// write(out, buff, MAXBUFF);
	}

	// pthread_join(tid, NULL);

	close(out);

	return 0;
}