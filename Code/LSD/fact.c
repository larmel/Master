
// Dummy function linked in to offset instruction addresses
int fact(int n)
{
	if (n <= 1) 
		return n;
	int a = 1;
	while (n)
		a *= n--;
	return a;
}
