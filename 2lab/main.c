#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	char command[128];
	char **argv = malloc(sizeof(char*));
	int count = 0;

	pid_t pid = getpid();
	gid_t gid = getgid();
	pid_t sid = getsid (pid);


	printf("pid = %d\ngid = %d\nsid = %d\n", pid, gid, sid);

	printf("Qq, input command: ");
	fgets(command, 128, stdin);
	// printf("%s\n", command);

	// printf("%ld\n", strlen(command));

	if (!strcmp(command, "\n")) {
		printf("Error\n");
		return 1;
	}

	for (int i = 0; command[i] != '\n' && command[i] != '\0'; count++, i++) {
		argv = realloc(argv, sizeof(char*) * (count + 1));
		for (int j = 0; !isspace(command[i]) && command[i] != '\0' && command[i] != '\n'; j++, i++) {
			argv[count] = realloc(argv[count], sizeof(char) * (j + 1));
			argv[count][j] = command[i];
		}
	}

	if (!strcmp(argv[0], "exit")) {
		printf("Exit\n");
		return 1;
	}

	#if 1
	for (int i = 0; i < count; i++) {
		printf("%s\n", argv[i]);
	}
	#endif

	pid_t fpid = fork();

	if (fpid == -1) {
		perror("fork");
		exit(1);
	}

	if (fpid == 0) {
		// printf("Lichinkus\n");
		int check = execvp(argv[0], argv);
		if (check == -1) {
			perror("execvp");
			return 1;
		}
		// sleep(1);
	} else {
		int status;
		// sleep(1);
		wait(&status);
		// printf("%d\n", status);
		if (WIFEXITED(status)) {
			printf("Дочерний процесс успешно завершился\n");
			if (WEXITSTATUS(status)) {
				printf("Восемь младших битов значения, которое вернул завершившийся дочерний процесс\n");	
			}
		} else if (WIFSIGNALED(status)) {
			printf("Дочерний процесс завершился из-за необработанного сигнала\n");
			if (WTERMSIG(status)) {
				printf("Hомер сигнала, который привел к завершению дочернего процесса\n");
			}
		} else if (WIFSTOPPED(status)) {
			printf("WIFSTOPPED\n");
			if (WSTOPSIG(status)) {
				printf("WSTOPSIG\n");
			}
		}
	}

	system("whoami");
	printf("621\n");
	system("whoami");
	// printf("iv621s16\n");

	return 0;
}