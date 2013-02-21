/** Program printing its environment */
#include <unistd.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

int main(void)
{
	int i = 0;
	unsigned length = 0;

	FILE* f = fopen("program-output", "w");

	while (environ[i]) {
		char *str = environ[i++];
		length += strlen(str);
		fprintf(f, "%s\n", str);
	}
	fprintf(f, "Environment size:    %d\n", length);
	fprintf(f, "Environment address: %p\n", &environ[i-1][strlen(environ[i-1]) - 1]);
	fprintf(f, "Stack address:       %p\n", &i);

	fclose(f);

	printf("/proc/%d/maps\n", getpid());
	sleep(20);
	return 0;
}

