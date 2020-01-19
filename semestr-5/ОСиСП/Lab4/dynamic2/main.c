#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dlfcn.h>

int main(void)
{
	long time = clock();
	void *handle = dlopen("libdynamic.so", RTLD_LAZY);
	int(*fun)(char* file1, char* file2) = dlsym(handle, "search_words");
	(*fun)("/home/user/t4/input.txt", "/home/user/t4/input2.txt");
	dlclose(handle);
	printf("Время выполнения: %ld мс\n", clock() - time);
	return 0;
}
