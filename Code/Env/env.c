/** Program printing its environment */
#include <unistd.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

int main(void)
{
	int i = 0;
	unsigned length = 0;

	while (environ[i]) {
		char *str = environ[i++];
		length += strlen(str);
		printf("%s\n", str);
	}
	printf("Environment size:    %d\n", length);
	printf("Environment address: %p\n", &environ[i-1][strlen(environ[i-1]) - 1]);
	printf("Stack address:       %p\n", &i);

	printf("/proc/%d/maps\n", getpid());
	printf("/proc/%d/environ\n", getpid());
	sleep(20);
	return 0;
}

