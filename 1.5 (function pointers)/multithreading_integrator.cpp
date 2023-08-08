// This program calculates definite integral of some function
// using multiple threads

#include <iostream>
#include <cmath>

// Linux library that allows to create threads in POSIX-systems
#include <pthread.h>

// ====================================================================================================

// Thread creation function has this signature:
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                   void *(*start_routine) (void *), void *arg);

// structure to keep task data
struct Task
{
    // integrable function
    double (*int_function)(double);

    // start point
    double start;

    // end point
    double end;

    // integrating step
    double eps;

    // return value keeper
    double *result;
};

// ====================================================================================================

// thread function
void *thread_fun(void * data)
{
    // get task
    Task& t = *static_cast<Task *>(data);

    // variable for result
    double res = 0;

    // integrating process
    for (double x = t.start; x < t.end; x += t.eps)
        res += t.int_function(x + t.eps / 2) * t.eps;

    *t.result = res;

    return 0;
}

// integrable function
double function(double x) { return exp(x * sin(x)); }

// ====================================================================================================

int main( )
{
    // number of threads
    int const THREAD_COUNT = 8;

    // array which keeps the results
    double results[THREAD_COUNT] = {};

    // tasks for threads
    Task tasks[THREAD_COUNT] = {};

    // integrating limits
    double start, end;
    std::cout << ">> start point: ";
    std::cin >> start;
    std::cout << ">> end point: ";
    std::cin >> end;

    // fill tasks
    double const taskLen = (end - start) / THREAD_COUNT;
    for (int i = 0; i != THREAD_COUNT; ++i)
    {
        tasks[i].int_function = &function;
        tasks[i].start = start + taskLen * i;
        tasks[i].end = tasks[i].start + taskLen;
        tasks[i].eps = 1e-7;
        tasks[i].result = &results[i];
    }

    // create thread descriptors
    pthread_t threads[THREAD_COUNT];

    // create and release threads
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        pthread_create(&threads[i], 0, &thread_fun, &tasks[i]);

    // wait for threads to terminate
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        pthread_join(threads[i], 0);

    // sum results
    double res = 0;
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        res += results[i];

    std::cout << std::endl << ">> result: " << res << std::endl;

    return 0;
}

// compilation: "g++ multithreading_integrator.cpp -O2 -o integrate -pthread"