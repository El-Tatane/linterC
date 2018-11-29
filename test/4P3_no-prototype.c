// regle4 no-prototype

	
void fonction(int moi);

void fonction(int moi){

	puts("bonjour");
}

void jeSuisSansPrototype(int bonjour){
	puts("bonjour");
}

int main(int argc, char const *argv[])
{

	int bonjour = 0;

	fonction(bonjour);
	jeSuisSansPrototype(bonjour);
	
	return 0;
}

