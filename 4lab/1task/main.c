#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXBUFF 3000
#define INPUT_FILE "/etc/passwd"
#define OUTPUT_FILE "passwds"

int main(int argc, char const *argv[])
{
	char sig = 26;
	int filedes[2]; // 0 - read, 1 - write
	if (pipe(filedes) < 0) {
		printf("Error, get filedes\n");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0) {
		int out;
		int i;
		char buff[MAXBUFF];

		int n = read(filedes[0], buff, MAXBUFF);

		for (i = 0; i < n; i++) {
			if (buff[i] == sig) {
				break;
			} else if (buff[i] == 'b') {
				buff[i] = 'n';
			} else if (buff[i] == 'i') {
				buff[i] = 'a';
			} else if (buff[i] == 'n') {
				buff[i] = 'b';
			}
		}

		if ((out = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
			printf("Error, open %s\n", OUTPUT_FILE);
			exit(1);
		}

		if (write(out, buff, i) != i) {
			printf("Error, write in %s\n", OUTPUT_FILE);
			exit(1);
		}

		close(out);
	} else {
		int in;
		int status;
		char buff[MAXBUFF];

		if ((in = open(INPUT_FILE, O_RDONLY)) < 0) {
			printf("Error, open %s\n", INPUT_FILE);
			exit(1);
		}

		// write(filedes[1], &sig, 1);

		int n = read(in, buff, MAXBUFF);

		if (write(filedes[1], buff, n) != n) {
			printf("Error, write in channel\n");
			exit(1);
		}

		write(filedes[1], &sig, 1);

		close(in);

		wait(&status);
	}

	return 0;
}