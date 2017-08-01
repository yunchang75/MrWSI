#ifndef WRWSI_PROBLEM_H
#define WRWSI_PROBLEM_H

#include <limits.h>
#include "resource.h"

#define DEMAND_DIM 2
#define CAPACITY_DIM DEMAND_DIM

typedef struct task_info_t {
    int num_prevs;
    int num_succs;
    int* prevs;
    int* succs;
    res_t demands[DEMAND_DIM];
    int* runtimes;
} task_info_t;

void task_info_init(task_info_t* task, res_t* demands, int* prevs,
                    int num_prevs, int* succs, int num_succs, int num_types);

typedef struct type_info_t {
    res_t capacities[CAPACITY_DIM];
    res_t* demands;
    double price;
} type_info_t;

void type_info_init(type_info_t* type, res_t* capacities, res_t* demands,
                    int platform_limit_dim);
void type_info_destory(type_info_t* type);

typedef struct problem_t {
    int num_tasks;
    int num_types;
    task_info_t* tasks;
    type_info_t* types;
    int charge_unit;
    res_t* platform_limits;
} problem_t;

void problem_init(problem_t* problem, int num_tasks, int num_types,
                  int charge_unit, res_t* platform_limits,
                  int platform_limit_dim);
void problem_destory(problem_t* problem);

void problem_reverse_dag(problem_t* problem);

#define problem_task_is_entry(problem, task_id) \
    ((problem)->tasks[task_id].num_prevs == 0)
#define problem_task_is_exit(problem, task_id) \
    ((problem)->tasks[task_id].num_succs == 0)
#define problem_task_demands(problem, task_id) \
    ((problem)->tasks[task_id].demands)
#define problem_task_runtime(problem, task_id, type_id) \
    ((problem)->tasks[task_id].runtimes[type_id])
#define problem_task_num_prevs(problem, task_id) \
    ((problem)->tasks[task_id].num_prevs)
#define problem_task_num_succs(problem, task_id) \
    ((problem)->tasks[task_id].num_succs)
#define problem_task_prevs(problem, task_id) ((problem)->tasks[task_id].prevs)
#define problem_task_succs(problem, task_id) ((problem)->tasks[task_id].succs)

#define problem_type(problem, type_id) ((problem)->types + type_id)
#define problem_type_demands(problem, type_id) \
    ((problem)->types[type_id].demands)
#define problem_type_capacities(problem, type_id) \
    ((problem)->types[type_id].capacities)
#define problem_type_price(problem, type_id) ((problem)->types[type_id].price)

int problem_task_average_runtime(problem_t* problem, int task_id);
int problem_cheapest_type(problem_t* problem);
int problem_cheapest_type_for_demands(problem_t* problem, res_t* demands);
double problem_charge(problem_t* problem, int type_id, int runtime);

#endif  // ifndef WRWSI_PROBLEM_H
