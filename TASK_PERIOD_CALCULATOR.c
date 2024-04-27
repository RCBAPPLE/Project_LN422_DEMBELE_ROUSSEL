#include <stdio.h>
#include <time.h> // For clock_gettime()
#include <stdint.h> // For types like int64_t, etc.
#include <unistd.h> // For usleep(), necessary for simulating waiting

// Macros for FreeRTOS-specific conversion
#define pdMS_TO_TICKS(x) ((x) / portTICK_PERIOD_MS) // Simulates FreeRTOS conversion (adjust portTICK_PERIOD_MS according to your configuration)

#define portTICK_PERIOD_MS 1 // Define based on your timer configuration

// Helper function to calculate elapsed time in nanoseconds
long long timespec_diff_ns(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1000000000LL + (end->tv_nsec - start->tv_nsec);
}

// Function to simulate waiting
void wait(int milliseconds) {
    usleep(milliseconds * 1000); // Convert to microseconds
}

/*-----------------------------------------------------------*/
// Task 1: Simple print task
/*-----------------------------------------------------------*/
void task1() {
    // Task execution
    printf("Working!\n");
}

/*-----------------------------------------------------------*/
// Task 2: Conversion Fahrenheit to Celsius
/*-----------------------------------------------------------*/
void task2() {
    float celsius, fahrenheit = 60.0;
    celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
    printf("%.2f Fahrenheit = %.2f Celsius\n", fahrenheit, celsius);
}

/*-----------------------------------------------------------*/
// Task 3: Large number multiplication
/*-----------------------------------------------------------*/
void task3() {
    double a = 6.214748e+30, b = 3.429643e+53, c;
    c = a * b;
    printf("%.2e * %.2e = %.2e\n", a, b, c);
}

/*-----------------------------------------------------------*/
// Task 4: Binary search in a static array
/*-----------------------------------------------------------*/
void task4() {
    int tab[50], i, b = 36;
    for (i = 0; i < 50; i++) {
        tab[i] = i;
    }

    int start = 0, end = 49, middle;
    while (start <= end) {
        middle = (start + end) / 2;
        if (tab[middle] == b) {
            printf("The number %d is in the list at position: %d\n", b, middle);
            break;
        } else if (tab[middle] < b) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }
    if (start > end) {
        printf("The number %d is not in the list.\n", b);
    }
}

/*-----------------------------------------------------------*/
// Aperiodic Task: Executes an aperiodic action with 100 ms simulated delay
/*-----------------------------------------------------------*/
void task_aperiodic() {
    printf("Aperiodic task is running...\n");

    // Wait for 100 milliseconds
    wait(100);
}

/*-----------------------------------------------------------*/
// Main function to run tasks 10000 times
/*-----------------------------------------------------------*/
int main() {
    long long max_ns1 = 0, max_ns2 = 0, max_ns3 = 0, max_ns4 = 0, max_ns_aperiodic = 0;
    long long elapsed_ns;
    int count = 10000;

    for (int i = 0; i < count; i++) {
        struct timespec start, end;

        // Task 1
        clock_gettime(CLOCK_MONOTONIC, &start);
        task1();
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_ns = timespec_diff_ns(&start, &end);
        if (elapsed_ns > max_ns1) max_ns1 = elapsed_ns;

        // Task 2
        clock_gettime(CLOCK_MONOTONIC, &start);
        task2();
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_ns = timespec_diff_ns(&start, &end);
        if (elapsed_ns > max_ns2) max_ns2 = elapsed_ns;

        // Task 3
        clock_gettime(CLOCK_MONOTONIC, &start);
        task3();
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_ns = timespec_diff_ns(&start, &end);
        if (elapsed_ns > max_ns3) max_ns3 = elapsed_ns;

        // Task 4
        clock_gettime(CLOCK_MONOTONIC, &start);
        task4();
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_ns = timespec_diff_ns(&start, &end);
        if (elapsed_ns > max_ns4) max_ns4 = elapsed_ns;
        
        // Aperiodic Task
        clock_gettime(CLOCK_MONOTONIC, &start);
        task_aperiodic();
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_ns = timespec_diff_ns(&start, &end);
        if (elapsed_ns > max_ns_aperiodic) max_ns_aperiodic = elapsed_ns;
    }

    // Convert nanoseconds to milliseconds then to ticks for each task
    printf("Maximum execution time for Task 1: %lld ns, %llu ticks\n", max_ns1, pdMS_TO_TICKS(max_ns1 / 1000000));
    printf("Maximum execution time for Task 2: %lld ns, %llu ticks\n", max_ns2, pdMS_TO_TICKS(max_ns2 / 1000000));
    printf("Maximum execution time for Task 3: %lld ns, %llu ticks\n", max_ns3, pdMS_TO_TICKS(max_ns3 / 1000000));
    printf("Maximum execution time for Task 4: %lld ns, %llu ticks\n", max_ns4, pdMS_TO_TICKS(max_ns4 / 1000000));
    printf("Maximum execution time for Aperiodic Task: %lld ns, %llu ticks\n", max_ns_aperiodic, pdMS_TO_TICKS(max_ns_aperiodic / 1000000));

    return 0;
}
