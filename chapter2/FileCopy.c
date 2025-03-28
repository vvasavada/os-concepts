#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/*

This is exercise 2.24 from Operating Systems Concepts 10th Edition.
*/

#define BUFFER_SIZE 1024  // Define buffer size for reading/writing

int main( int argc, char *argv[] ) {


	if ( argc != 3 ) {
		perror( "Usage: FileCopy source destination\n" );
		exit( 1 );
	}

	char * src = argv[ 1 ];
	if ( access( src, F_OK ) != 0 ) {
		perror( "Soure file doesn't exist\n" );
		exit( 1 );
	} else {
		if ( access( src, R_OK ) != 0 ) {
			perror( "Source file doesn't have read permission\n" );
			exit( 1 );
		}
	}


	char * dst = argv[ 2 ];
	if ( access( dst, F_OK ) == 0 ) {
		perror( "Destination file already exists\n" );
		exit( 1 );
	}

	int src_fd = open( src, O_RDONLY );
	if ( src_fd == -1 ) {
		perror( "Error opening source file\n" );
		exit( 1 );
	}

	int dst_fd = open( dst, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR );
	if ( dst_fd == -1 ) {
		perror( "Error opening destination file\n" );
		exit( 1 );
	}

	char buffer[ BUFFER_SIZE ];
	ssize_t bytes_read, bytes_written;

	while( ( bytes_read = read( src_fd, buffer, BUFFER_SIZE ) ) > 0 ) {
		bytes_written = write( dst_fd, buffer, bytes_read );
		if ( bytes_read != bytes_written ) {
			perror( "Error writing to destination file\n" );
			close( src_fd );
			close( dst_fd );
			exit( 1 );
		}
	}

	close( src_fd );
	close( dst_fd );
}