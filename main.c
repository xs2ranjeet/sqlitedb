// #define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct InputBuffer_t {
	char* buffer;
	size_t buffer_length;
	size_t input_length;
};
typedef struct InputBuffer_t InputBuffer;

InputBuffer *new_input_buffer(){
	InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}
void print_prompt(){
	printf("db > " );
}
int getline(char **lineptr, size_t *n, FILE *stream)
{
static char line[256];
char *ptr;
unsigned int len;

   if (lineptr == NULL || n == NULL)
   {
      // errno = EINVAL;
      return -1;
   }

   if (ferror (stream))
      return -1;

   if (feof(stream))
      return -1;
     
   fgets(line,256,stream);

   ptr = strchr(line,'\n');   
   if (ptr)
      *ptr = '\0';

   len = strlen(line);
   
   if ((len+1) < 256)
   {
      ptr = realloc(*lineptr, 256);
      if (ptr == NULL)
         return(-1);
      *lineptr = ptr;
      *n = 256;
   }

   strcpy(*lineptr,line); 
   return(len);
}
// char *local_getline(char *zPrompt, FILE *in)

// {
//   char *zLine;
//   int nLine;
//   int n;

//   nLine = 100;
//   zLine = malloc( nLine );
//   if( zLine==0 ) return 0;
//   n = 0;
//   while( 1 ){
//     if( n+100>nLine ){
//       nLine = nLine*2 + 100;
//       zLine = realloc(zLine, nLine);
//       if( zLine==0 ) return 0;
//     }
//     if( fgets(&zLine[n], nLine - n, in)==0 ){
//       if( n==0 ){
//         free(zLine);
//         return 0;
//       }
//       zLine[n] = 0;
//       break;
//     }
//     while( zLine[n] ){ n++; }
//     if( n>0 && zLine[n-1]=='\n' ){
//       n--;
//       zLine[n] = 0;
//       break;
//     }
//   }
//   zLine = realloc( zLine, n+1 );
//   return zLine;
// }

void read_input(InputBuffer* input_buffer){
	// size_t bytes_read;
	// #ifdef _WIN32

	// #endif
	// #ifdef linux
	size_t bytes_read = getline(&(input_buffer->buffer),
		&(input_buffer->buffer_length), stdin);
	// #endif
	if(bytes_read <= 0){
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}
	// // Ignore trailing newline
	// input_buffer->input_length = bytes_read-1;
	// input_buffer->buffer[bytes_read -1] = 0;
	input_buffer->input_length = bytes_read;
	input_buffer->buffer[bytes_read] = 0;

}

void close_input_buffer(InputBuffer* input_buffer){
	free(input_buffer->buffer);
	free(input_buffer);
}

int main(int argc, char const *argv[])
{
	InputBuffer *input_buffer = new_input_buffer();
	while(true){
		print_prompt();
		read_input(input_buffer);

		if(strcmp(input_buffer->buffer, ".exit") == 0){
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command '%s' \n", input_buffer->buffer );
		}
	}
	return 0;
}