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

int main(int argc, char *argv[])
{
    int n;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    int index_min_burst = 0;
    int number_of_burst[n];
    long sum_w = 0;
    long sum_t = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &number_of_burst[i]);
    }
    int waiting_time = 0;
    int burst_time = 0;
    int turnaround_time = 0;
    printf("Process    Burst Time    Waiting Time   Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        index_min_burst = index_min(number_of_burst, n);
        burst_time = number_of_burst[index_min_burst];
        turnaround_time = waiting_time + burst_time;
        sum_w += waiting_time;
        sum_t += turnaround_time;
        printf("p%d\t\t", index_min_burst + 1);
        printf("%d\t\t", burst_time);
        printf("%d\t\t", waiting_time);
        printf("%d\t\t", turnaround_time);
        waiting_time += burst_time;
        number_of_burst[index_min_burst] = 0;
        // printf("number : %d index : %d", number_of_burst[index_min_burst], index_min_burst);
        printf("\n");
    }
    
    printf("Average Waiting Time : %.2f\n", (float)sum_w / n);
    printf("Average Turnaround Time : %.2f\n", (float)sum_t / n);
    return 0;
}