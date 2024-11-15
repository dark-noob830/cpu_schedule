#include <stdio.h>

int index_min(int arr[], int n)
{

    int min = -1;
    int index = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            continue;
        }
        if (min == -1)
        {
            index = i;
            min = arr[i];
        }
        else if (arr[i] < min)
        {
            index = i;
            min = arr[i];
        }
    }

    return index;
}

int sum(int arr[], int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return arr[0] + sum(arr + 1, n - 1);
    }
}

int main(int argc, char *argv[])
{

    int n;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    int index_min_burst = 0;
    int index_min_last = 0;
    int number_of_burst[n];
    int number_of_tburst[n];
    int arrivals[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process P%d : ", i + 1);
        scanf("%d", &arrivals[i]);
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &number_of_burst[i]);
        number_of_tburst[i] = number_of_burst[i];
    }
    int waiting_time[n];
    int finish_time[n];
    int can_run[n];
    int turnarround_time[n];
    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
        finish_time[i] = 0;
        can_run[i] = 0;
        turnarround_time[i] = 0;
    }
    int t = 0;
    while (1)
    {

        for (int i = 0; i < n; i++)
        {
            if (arrivals[i] <= t)
            {
                can_run[i] = number_of_burst[i];
            }
        }
        index_min_burst = index_min(can_run, n);
        if (index_min_burst == -1)
        {
            break;
        }

        if (index_min_burst != index_min_last)
        {
            finish_time[index_min_last] = t;
            waiting_time[index_min_burst] += t - finish_time[index_min_burst];
            if (!finish_time[index_min_burst])
            {
                waiting_time[index_min_burst] -= arrivals[index_min_burst];
            }
            turnarround_time[index_min_burst] = waiting_time[index_min_burst] + number_of_tburst[index_min_burst];
        }
        t++;
        number_of_burst[index_min_burst]--;
        index_min_last = index_min_burst;
    }
    printf("Process    Burst Time    Waiting Time   Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("p%d\t\t", i + 1);
        printf("%d\t\t", number_of_tburst[i]);
        printf("%d\t\t", waiting_time[i]);
        printf("%d\t\t", turnarround_time[i]);
        printf("\n");
    }
    printf("Average Waiting Time : %.2f\n", (float)sum(waiting_time, n) / n);
    printf("Average Turnaround Time : %.2f\n", (float)sum(turnarround_time, n) / n);
    return 0;
}