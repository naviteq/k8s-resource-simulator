#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

#define MILLION 1000000

volatile sig_atomic_t keep_running = 1;

// Signal handler for SIGINT and SIGTERM
void handle_signal(int sig) {
    keep_running = 0;
}

// Function to simulate CPU load
void simulate_cpu_load(int millicores) {
    long long start_time, current_time;
    struct timeval time_check;
    int active_time = millicores * 1000; // Microseconds active
    int sleep_time = MILLION - active_time; // Microseconds sleeping

    while (keep_running) {
        gettimeofday(&time_check, NULL);
        start_time = time_check.tv_sec * MILLION + time_check.tv_usec;

        // Busy-waiting for the duration of active_time
        do {
            gettimeofday(&time_check, NULL);
            current_time = time_check.tv_sec * MILLION + time_check.tv_usec;
        } while ((current_time - start_time) < active_time && keep_running);

        // Sleep for the remainder of the second
        if (keep_running) usleep(sleep_time);
    }
}

int main(int argc, char *argv[]) {
    int millicores = 0;  // Default to 0, meaning not set
    int memory_in_MiB = 0;  // Default to 0, meaning not set

    // Register signal handlers
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-millicores") == 0 && i + 1 < argc) {
            millicores = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-MiB") == 0 && i + 1 < argc) {
            memory_in_MiB = atoi(argv[++i]);
        } else {
            fprintf(stderr, "Unknown or incomplete argument: %s\n\n", argv[i]);
            fprintf(stderr, "Created by James Spurin @ DiveInto.\n\n");
            fprintf(stderr, "Usage: %s -millicores [value] -MiB [value]\n", argv[0]);
            fprintf(stderr, "Both arguments are optional but at least one must be provided.\n");
            return 1;
        }
    }

    if (millicores <= 0 && memory_in_MiB <= 0) {
        fprintf(stderr, "Created by James Spurin @ DiveInto.\n\n");
        fprintf(stderr, "No valid arguments provided. At least one parameter must be set.\n");
        fprintf(stderr, "Usage: %s -millicores [value] -MiB [value]\n", argv[0]);
        return 1;
    }

    if (millicores <= 0) {
        millicores = 100;  // Default millicore value if not specified
        printf("Defaulting millicores to 100 as none specified.\n");
    }

    if (memory_in_MiB <= 0) {
        memory_in_MiB = 10;  // Default memory value if not specified
        printf("Defaulting memory to 10 MiB as none specified.\n");
    }

    // Memory allocation
    size_t bytes = (size_t)memory_in_MiB * 1024ULL * 1024ULL;
    char *memory = malloc(bytes);
    if (memory == NULL) {
        fprintf(stderr, "Failed to allocate %zu bytes.\n", bytes);
        return 1;
    }
    memset(memory, 0, bytes);

    printf("Simulating %d millicores and allocating %d MiB of memory indefinitely...\n", millicores, memory_in_MiB);
    simulate_cpu_load(millicores);

    // Free memory and exit cleanly
    free(memory);
    printf("Cleanly exiting after signal interruption.\n");
    return 0;
}
