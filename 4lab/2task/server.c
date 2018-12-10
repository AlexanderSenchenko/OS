#include "main.h"

void createFIFO()
{
	if (mknod(FIFO, S_IFIFO | PERM, 0) < 0) {
		printf("Error, create FIFO\n");
		exit(1);
	}
}

int openFIFO()
{
	int in;
	if ((in = open(FIFO, O_RDONLY)) < 0) {
		printf("Error, open FIFO\n");
		exit(1);
	}

	return in;
}

char* searchTemplate(char *buff)
{
	char *str;
	if ((str = strstr(buff, TEMPLATE)) == NULL) {
		printf("Error, TEMPLATE not found\n");
		exit(1);
	}
	return str;
}

char* createFileName(char *str)
{
	int size_temp = strlen(TEMPLATE);
	int size_str = strlen(str);

	char *file_name = malloc(sizeof(char *) * (size_str - size_temp));
	strcpy(file_name, &str[size_temp]);

	int i = 0;
	while (file_name[i] != '\n') i++;
	file_name[i] = '\0';

	return file_name;
}

int openFile(char *file_name)
{
	int out;
	if ((out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
		printf("Error File not found\n");
		exit(1);
	}
	printf("File %s open\n", file_name);
	return out;
}

int main()
{
	char buff[MAXBUFF];

	createFIFO();
	int in = openFIFO();

	int size = read(in, buff, MAXBUFF);

	char *str = searchTemplate(buff);

	char *file_name = createFileName(str);

	int out = openFile(file_name);

	for (;;) {
		memset(buff, 0, MAXBUFF);
		size = read(in, buff, MAXBUFF);

		if (!strcmp(buff, &sig))
			break;

		write(1, buff, size);

		if (write(out, buff, size) != size) {
			printf("Error write in file\n");
			exit(1);
		}
	}

	free(file_name);
	close(out);
	close(in);

	if (unlink(FIFO) < 0) {
		printf("Error delete FIFO\n");
		exit(1);
	}

	return 0;
}