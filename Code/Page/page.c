

#define PAGE 0x1000

int main()
{
	char *a = malloc(PAGE * sizeof(char));

	for (int i = 2; i < PAGE-10) {
		*a += *(a-1);
	}

	return 0;
}

