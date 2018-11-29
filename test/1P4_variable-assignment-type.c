// regle1 variable-assignment-type


int main(int argc, char const *argv[])
{

	int a = 0;
	int b = "test";
	int* c = 0;
	c = &a;

	char d = argc;
	char e[10] = {'\0'};
	e[1] = 'd';
	e = 'g';
	char f = 'j';
	e = &g;

	double ab = 1.2;
	float ba;

	ab = ba;
	
	ba = 12.2;
	
	return 0;
}

