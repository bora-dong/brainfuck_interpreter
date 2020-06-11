#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char mem[30000] = {0, };
	FILE *src_file;
	char src_filename[128];
	char source[8192];
	char *source_ptr = source;
	char *ptr = mem;
	int loop_depth = 0;
	char c;


	printf("please enter file name to open: ");
	scanf("%s", src_filename);
	
	// read source code from stdin or file.
	src_file = fopen(src_filename, "r");
	if (src_file == NULL) {
		printf("Error: Can't open %s\n", src_filename);
		exit(EXIT_FAILURE);
	}

	// read source code from file
	while ((c = fgetc(src_file)) != EOF) {
		*source_ptr = c;
		++source_ptr;
	}
	*source_ptr = '\0';

	printf("GOT: %s\n", source);

	source_ptr = source;
	// execute source code
	for (; *source_ptr != '\0'; ++source_ptr) {
		switch (*source_ptr) {
			case '>':
				++ptr;
				break;
			case '<':
				--ptr;
				break;
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr = getchar();
				break;
			case '[':
				if (*ptr == 0) {
					while (*source_ptr != ']')
						++source_ptr;
					++source_ptr;
				}
				else {
					++loop_depth;
				}
				break;
			case ']':
				if (loop_depth < 1) {
					printf("Error, there is no precedence ']'\n");
					exit(EXIT_FAILURE);
				}
				else {
					if (*ptr == 0) {
						--loop_depth;
					}
					else {
						while (*source_ptr != '[')
							--source_ptr;
					}
				}
				break;
			default:
				break;
		}
		// printf("DEBUG | executed: %c, ptr: %p *ptr: %d\n", *source_ptr, ptr, *ptr);
		// printf("%c", *source_ptr);
	}

	fclose(src_file);

	return 0;
}

