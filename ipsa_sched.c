#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* First, we define the priorities of the tasks */
#define PRINT_WORKING_PRIORITY      (tskIDLE_PRIORITY)
#define CONVERT_TEMP_PRIORITY       (tskIDLE_PRIORITY + 3)
#define MULTIPLY_NUMBERS_PRIORITY   (tskIDLE_PRIORITY + 2)
#define BINARY_SEARCH_PRIORITY      (tskIDLE_PRIORITY + 1)
#define APERIODIC_TASK_PRIORITY     (tskIDLE_PRIORITY + 4)

/* Next, we define the frequencies of each task */
#define PRINT_WORKING_FREQUENCY_MS       pdMS_TO_TICKS( 400 ) 
#define CONVERT_TEMP_FREQUENCY_MS        pdMS_TO_TICKS( 330 )
#define MULTIPLY_NUMBERS_FREQUENCY_MS    pdMS_TO_TICKS( 330 )
#define BINARY_SEARCH_FREQUENCY_MS       pdMS_TO_TICKS( 350 )

/* Then, we declare the functions of the tasks */
static void task_1(void *pvParameters);
static void task_2(void *pvParameters);
static void task_3(void *pvParameters);
static void task_4(void *pvParameters);
static void aperiodic_task(void *pvParameters);

/* Function to initialize and start the scheduler with defined tasks */
void ipsa_sched(void)
{
    /* Create Task 1: Print "Working" */
    xTaskCreate(task_1, "PrintWorking", configMINIMAL_STACK_SIZE, NULL, PRINT_WORKING_PRIORITY, NULL);

    /* Task 2: Convert Fahrenheit temperature to Celsius */
    xTaskCreate(task_2, "ConvertTemp", configMINIMAL_STACK_SIZE, NULL, CONVERT_TEMP_PRIORITY, NULL);

    /* Task 3: Multiply two large numbers */
    xTaskCreate(task_3, "MultiplyNumbers", configMINIMAL_STACK_SIZE, NULL, MULTIPLY_NUMBERS_PRIORITY, NULL);

    /* Task 4: Binary search in a list of 50 elements */
    xTaskCreate(task_4, "BinarySearch", configMINIMAL_STACK_SIZE, NULL, BINARY_SEARCH_PRIORITY, NULL);

    /* Optional aperiodic task: Simulate a 100ms execution */
    xTaskCreate(aperiodic_task, "AperiodicExample", configMINIMAL_STACK_SIZE, NULL, APERIODIC_TASK_PRIORITY, NULL);
	
    /* Start the scheduler */
    vTaskStartScheduler();
}

/* Task 1: Print "Working" at a specified frequency */
static void task_1 (void *pvParameters){
	for( ;; )
	{
		printf("Working \n");
        vTaskDelay(PRINT_WORKING_FREQUENCY_MS);
	}
}

/* Task 2: Convert Fahrenheit temperature to Celsius at a specified frequency */
static void task_2 (void *pvParameters){

    float celsius, fahrenheit = 60.0;
	for( ;; )
	{
        celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
        printf("%.2f Fahrenheit = %.2f Celsius\n", fahrenheit, celsius);
		vTaskDelay(CONVERT_TEMP_FREQUENCY_MS);
	}
}

/* Task 3: Multiply two large numbers at a specified frequency */
static void task_3 (void *pvParameters){

    double a = 6.214748e+30, b = 3.429643e+53, c;
	for( ;; )
	{
        c = a * b;
        printf("%.2e * %.2e = %.2e\n", a, b, c);
		vTaskDelay(MULTIPLY_NUMBERS_FREQUENCY_MS);
	}
}

/* Binary search function */
void binary_search (int target) {
    int tab[50], i;
    for (i = 0; i < 50; i++) {
        tab[i] = i;
    }
    int start = 0, end = 49, middle;
    while (start <= end) {
        middle = (start + end) / 2;
        if (tab[middle] == target) {
            printf("The number %d is in the list at position: %d\n", target, middle);
            break;
        } else if (tab[middle] < target) {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }
    if (start > end) {
        printf("The number %d is not in the list.\n", target);
    }
}

/* Task 4: Execute binary search at a specified frequency */
static void task_4 (void *pvParameters){

    int b = 36;
	for( ;; )
	{
        binary_search(b);
		vTaskDelay(BINARY_SEARCH_FREQUENCY_MS);
	}
}

/* Aperiodic task: Simulate an execution with a 100ms delay */
void aperiodic_task(void *pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(100); // Convert 100 ms to ticks
    for(;;) {
        printf("Aperiodic task is running...\n");
        vTaskDelay(xDelay); // Wait for 100 ms
    }
}
