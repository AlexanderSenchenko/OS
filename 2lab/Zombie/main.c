#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t pid = fork();
	int status;

	if (pid == 0) {
		wait(&status);
	} else {
		sleep(60);
	}

	return 0;
}