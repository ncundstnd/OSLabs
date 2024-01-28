#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	char c;
	int in = open("./students.txt", O_RDONLY), rowNumber = 0;

	while (read(in, &c, 1) == 1)
		if (c == '\n')
			rowNumber++;

	printf("Number of lines: %d \n", rowNumber);
	return 0;
}
