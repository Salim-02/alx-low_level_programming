#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char *create_buffer(void);
void close_file(int fd);

/**
 * create_buffer - Allocates memory for a buffer.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *create_buffer(void)
{
    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

/**
 * close_file - Closes a file descriptor.
 * @fd: The file descriptor to close.
 */
void close_file(int fd)
{
    if (close(fd) == -1)
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

/**
 * main - Copies the contents of one file to another.
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 *
 * Return: 0 on success, otherwise 1!
 */
int main(int argc, char *argv[])
{
    int from, to;
    ssize_t bytes_read, bytes_written;
    char *buffer;

    // Check for correct number of arguments
    if (argc != 3)
    {
	    fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    // Allocate memory for buffer
    buffer = create_buffer();

	// Open source file for reading
from = open(argv[1], O_RDONLY);
    if (from == -1)
    {
	    perror("Error opening source file");
	free(buffer);
	exit(EXIT_FAILURE);
    }

    // Open destination file for writing, create if doesn't exist, truncate otherwise
    to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (to == -1)
    {
	    perror("Error opening destination file");
	free(buffer);
	close_file(from);
	exit(EXIT_FAILURE);
    }

    // Copy contents from source file to destination file
    do
    {
	    bytes_read = read(from, buffer, BUFFER_SIZE);
	    if (bytes_read == -1)
	{
		perror("Error reading from source file")
			free(buffer);
	    close_file(from);
	    close_file(to);
	    exit(EXIT_FAILURE);
	}

	bytes_written = write(to, buffer, bytes_read);
	if (bytes_written == -1 || bytes_written != bytes_read)
	{
		perror("Error writing to destination file");
	    free(buffer);
	    close_file(from);
	    close_file(to);
	    exit(EXIT_FAILURE);
	}
    } while (bytes_read > 0);

    // Clean up and close files
    // // free(buffer);
    if (close(from) == -1 || close(to) == -1)
    {
	    perror("Error closing files");
	    exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
