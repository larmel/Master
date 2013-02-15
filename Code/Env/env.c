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
	printf("Environment size: %d\n", length);
	printf("Stack address:    %p\n", &i);
	return 0;
}

