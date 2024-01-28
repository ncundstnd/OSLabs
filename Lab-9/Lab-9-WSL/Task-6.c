#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	char c;
	int in = open("./students.txt", O_RDONLY), rowNumber = 0, out, num;
	bool yaBool = 0;

	if (argc != 2)
	{
		printf("Please, enter a parameter.\n");
		exit(1);
	}

	num = atoi(argv[1]);

	if (num % 2 != 0)
		out = open("./Task-6-X1.txt.txt", O_CREAT | O_WRONLY, 0777);
	else
	{
		out = open("./Task-6-X2.txt.txt", O_CREAT | O_WRONLY, 0777);
		yaBool = 1;
	}

	while (read(in, &c, 1) == 1)
	{
		if (!yaBool)
			write(out, &c, 1);
		if (c == '\n')
			yaBool = !yaBool;
	}
	 
	close(out);
	close(in);
	return 0;
}
