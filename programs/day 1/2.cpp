#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main() {
    int sourceFile, destinationFile;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    sourceFile = open("source.txt", O_RDONLY);
    if (sourceFile == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open or create the destination file for writing
    destinationFile = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (destinationFile == -1) {
        perror("Error opening destination file");
        close(sourceFile);
        exit(EXIT_FAILURE);
    }

    // Read from the source file and write to the destination file
    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(destinationFile, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFile);
            close(destinationFile);
            exit(EXIT_FAILURE);
        }
    }

    // Close the files
    close(sourceFile);
    close(destinationFile);

    printf("File copy successful.\n");

    return 0;
}

