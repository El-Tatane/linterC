// regle2 function-parameters-type


void fonction(int a, char b, int* c, char *d, char** e){

	puts("ok");
}

int main(int argc, char const *argv[])
{
	int a, char b, int* c, char *d, char** e

	fonction(a, b, c, d, e);
	fonction(a, a, a, a, a);
	fonction(10, 'f', *e, &b, e);
	
	return 0;
}

