#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char response;
    FILE* file;
    const int bufferSize = 104857600; // 100 MB
    char* buffer = malloc(bufferSize);
    clock_t start, end;
    double cpu_time_used;
    errno_t err;

    printf("Do you want to proceed? (y/n): ");
    scanf_s(" %c", &response, 1);

    if (response == 'y' || response == 'Y') {
        // Write to file
        err = fopen_s(&file, "testfile", "wb");
        if (err != 0 || file == NULL) {
            perror("Error opening file");
            return 1;
        }

        start = clock();
        fwrite(buffer, 1, bufferSize, file);
        end = clock();

        fclose(file);

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Write time: %f seconds\n", cpu_time_used);
        printf("Write speed: %f MB/s\n", bufferSize / (cpu_time_used * 1048576));

        // Read from file
        err = fopen_s(&file, "testfile", "rb");
        if (err != 0 || file == NULL) {
            perror("Error opening file");
            return 1;
        }

        start = clock();
        fread(buffer, 1, bufferSize, file);
        end = clock();

        fclose(file);

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Read time: %f seconds\n", cpu_time_used);
        printf("Read speed: %f MB/s\n", bufferSize / (cpu_time_used * 1048576));

    }
    else {
        printf("Operation cancelled.\n");
    }

    free(buffer);
    return 0;
}
