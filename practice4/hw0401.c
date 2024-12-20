#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    int32_t duration;
    int32_t earliest_start;
    int32_t latest_start;
}Job;

typedef struct
{
    int32_t precede;
    int32_t succeed;
}Dependency;

int32_t calculateEarliestCompletionTime(int32_t n, Job jobs[100], Dependency dependencies[100 * 100])
{
    int32_t *inDegree = (int32_t *)malloc(n * sizeof(int32_t));
    int32_t *completionTime = (int32_t *)malloc(n * sizeof(int32_t));

    for(int32_t i = 0; i < n; i++)
    {
        inDegree[i] = 0;
        completionTime[i] = 0;
    }

    for(int32_t i = 0; i < n; i++)
    {
        for(int32_t j = 0; j < n; ++j)
        {
            if(dependencies[j].succeed == i + 1)
            {
                inDegree[i]++;
            }
        }
    }

    int32_t *queue = (int32_t *)malloc(n * sizeof(int32_t));
    int32_t front = 0, rear = 0;

    for(int32_t i = 0; i < n; i++)
    {
        if(inDegree[i] == 0)
        {
            queue[rear++] = i;
            completionTime[i] = jobs[i].duration;
        }
    }

    while (front < rear)
    {
        int32_t currentJob = queue[front++];

        for(int32_t i = 0; i < n; i++)
        {
            if(dependencies[i].precede == currentJob + 1)
            {
                inDegree[dependencies[i].succeed - 1]--;
                if(inDegree[dependencies[i].succeed - 1] == 0)
                {
                    queue[rear++] = dependencies[i].succeed - 1;
                }

                if(completionTime[dependencies[i].succeed - 1] < completionTime[currentJob] + jobs[dependencies[i].succeed - 1].duration)
                {
                    completionTime[dependencies[i].succeed - 1] = completionTime[currentJob] + jobs[dependencies[i].succeed - 1].duration;
                }
            }
        }
    }

    int32_t earliestCompletionTime = 0;
    for(int32_t i = 0; i < n; i++)
    {
        if(completionTime[i] > earliestCompletionTime)
        {
            earliestCompletionTime = completionTime[i];
        }
    }

    for(int32_t i = 0; i < n; i++)
    {
        for(int32_t j = 0; j < n; j++)
        {
            if(dependencies[j].succeed == i + 1)
            {
                if(jobs[i].earliest_start < jobs[dependencies[j].precede - 1].earliest_start + jobs[dependencies[j].precede - 1].duration)
                {
                    jobs[i].earliest_start = jobs[dependencies[j].precede - 1].earliest_start + jobs[dependencies[j].precede - 1].duration;
                }
            }
        }
    }

    free(inDegree);
    free(completionTime);
    free(queue);

    return earliestCompletionTime;
}

void calculateLatestStartTimes(int32_t n, Job jobs[100], Dependency dependencies[100 * 100], int32_t earliestCompletionTime)
{
    int32_t *outDegree = (int32_t *)malloc(n * sizeof(int32_t));

    for(int32_t i = 0; i < n; i++)
    {
        outDegree[i] = 0;
    }

    for(int32_t i = 0; i < n; i++)
    {
        for(int32_t j = 0; j < n; ++j)
        {
            if(dependencies[j].precede == i + 1)
            {
                outDegree[i]++;
            }
        }
    }

    int32_t *queue = (int32_t *)malloc(n * sizeof(int32_t));
    int32_t front = 0, rear = 0;

    for(int32_t i = 0; i < n; i++)
    {
        if(outDegree[i] == 0)
        {
            queue[rear++] = i;
            jobs[i].latest_start = earliestCompletionTime - jobs[i].duration;
        }
    }

    while (front < rear)
    {
        int32_t currentJob = queue[front++];

        for(int32_t i = 0; i < n; i++)
        {
            if(dependencies[i].succeed == currentJob + 1)
            {
                outDegree[dependencies[i].precede - 1]--;
                if(outDegree[dependencies[i].precede - 1] == 0)
                {
                    queue[rear++] = dependencies[i].precede - 1;
                }

                if(jobs[dependencies[i].precede - 1].latest_start > jobs[currentJob].latest_start - jobs[dependencies[i].precede - 1].duration)
                {
                    jobs[dependencies[i].precede - 1].latest_start = jobs[currentJob].latest_start - jobs[dependencies[i].precede - 1].duration;
                }
            }
        }
    }

    free(outDegree);
    free(queue);
}

void outputCriticalJobs(int32_t n, Job jobs[100], int32_t earliestCompletionTime)
{
    int32_t *criticalJobs = (int32_t *)malloc(n * sizeof(int32_t));
    int32_t count = 0;

    for(int32_t i = 0; i < n; i++)
    {
        if(jobs[i].earliest_start == jobs[i].latest_start)
        {
            criticalJobs[count++] = i + 1;
        }
    }

    printf("%d\n", earliestCompletionTime);

    for(int32_t i = 0; i < n; i++)
    {
        printf("%d%c", jobs[i].latest_start, (i == n - 1) ? '\n' : ' ');
    }

    if(count >= 0)
    {
        for(int32_t i = 0; i < count; i++)
        {
            printf("%d", criticalJobs[i]);
            if(i != count-1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("0\n");
    }

    free(criticalJobs);
}



int main()
{
    int32_t n;
    scanf("%d", &n);

    Job jobs[100];
    Dependency dependencies[100 * 100];

    for(int32_t i = 0; i < n; i++)
    {
        scanf("%d", &jobs[i].duration);
        jobs[i].earliest_start = 0;
        jobs[i].latest_start = 999999;
    }

    int32_t k;
    scanf("%d", &k);

    for(int32_t i = 0; i < k; i++)
    {
        scanf("%d %d", &dependencies[i].precede, &dependencies[i].succeed);
    }

    int32_t earliestCompletionTime = calculateEarliestCompletionTime(n, jobs, dependencies);

    calculateLatestStartTimes(n, jobs, dependencies, earliestCompletionTime);

    outputCriticalJobs(n, jobs, earliestCompletionTime);

    return 0;
}
