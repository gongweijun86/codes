#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int n;
	int int1, int2;
	char line[128];

	while ((n = read(STDIN_FILENO, line, 128)) > 0)
	{
		line[n] = 0;
		if (sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != 0)
				printf("write error\n");
		}
		else
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				printf("write error\n");
		}
	}
	exit(0);
}

