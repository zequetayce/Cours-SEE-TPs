#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 10

typedef struct {
    const char *name;
    uint32_t period_ms;
    uint32_t max_runs;
    uint64_t last_run_ms;
    uint32_t run_count;
    void (*func)(void);
} task_t;

static task_t tasks[MAX_TASKS];
static int task_count = 0;

uint64_t get_time_ms(void) {
    
    struct timespec ts;

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }else{
        //printf("Valeur clock nano sec: %lld\n",ts.tv_nsec);
        return ((ts.tv_nsec/1000000));
    }


    return 0;
}

void task_register(const char *name, uint32_t period_ms, uint32_t max_runs, void (*func)(void)) {
    // TODO
    // register a task
    // !!! Check max tasks
    printf("Init terminé: %s\n",name);
    tasks[task_count].name = name;
    tasks[task_count].period_ms = period_ms;
    tasks[task_count].max_runs = max_runs;
    tasks[task_count].last_run_ms = get_time_ms(); //get_time_ms();
    tasks[task_count].run_count = 0;
    tasks[task_count].func = func;
    printf("Init terminé: %s\n",name);

    task_count++;

}

void task_1_handler(void) {
    printf("-> Task 1 logic executed\n");
}

void task_2_handler(void) {
    printf("-> Task 2 logic executed\n");
}

int main(void) {
    task_register("SensorTask", 100, 12, task_1_handler); // Runs 12 times
    task_register("LoggerTask", 500, 2, task_2_handler); // Runs 2 time

    while (true) {

        for (int i = 0; i < MAX_TASKS; i++)
        {
            uint64_t current_time = get_time_ms();

            if ((current_time!=1) && ((current_time - tasks[i].last_run_ms) >= tasks[i].period_ms) && (tasks[i].run_count < tasks[i].max_runs))
            {
                printf("La task %s va etre executée, elle en est à %d/%d execution \n",tasks[i].name,(tasks[i].run_count)+1,tasks[i].max_runs);
                tasks[i].last_run_ms = current_time;
                tasks[i].run_count +=1; 
            }
        }
        

        
        
        
    }

    return 0;
}
