#include <stdio.h>

int max_priority(int arr[], int n)
{
    int max = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            continue;
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    // printf("%d",max);
    return max;
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

    int index_of_burst = 0;
    int last_index = 0;
    int number_of_burst[n];
    int number_of_tburst[n];
    int priority[n];
    int quantom;
    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &number_of_burst[i]);
        number_of_tburst[i] = number_of_burst[i];

        printf("Enter priority for process P%d : ", i + 1);
        scanf("%d", &priority[i]);
    }
    printf("Enter time quantum : ");
    scanf("%d", &quantom);
    int p;
    int waiting_time[n];
    int can_run[n];
    int finish_time[n];
    int turnarround_time[n];
    int last_p = 0;
    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
        finish_time[i] = 0;
        can_run[i] = 0;
        turnarround_time[i] = 0;
    }
    int t = 0;
    int real_time=0;
    int number_inq = 0;
    int what_process = 0;
    printf("Order of execution :\n");
    while (1)
    {

        p = max_priority(priority, n);
        if (p == -1)
        {
            break;
        }
        // printf("p:%d\n", p);
        if (p != last_p)
        {
            // printf("salam\");
            number_inq = 0;
            what_process = 0;
            for (int i = 0; i < n; i++)
            {
                if (priority[i] == p)
                {
                    can_run[i] = number_of_burst[i];
                    number_inq++;
                }
                else
                {
                    can_run[i] = 0;
                }
            }
        }
        if (t % quantom == 0)
        {
            int num = 0;
            what_process %= number_inq;
            what_process++;
            for (int i = 0; i < n; i++)
            {
                if (can_run[i] != 0)
                {
                    // printf("can run[%d] : %d \n", i,can_run[i]);
                    num++;
                    if (num == what_process)
                    {
                        index_of_burst = i;
                    }
                }
            }
            printf("p%d ", index_of_burst + 1);
            // t=0;
        }
        if (index_of_burst != last_index)
        {
            finish_time[last_index] = real_time;
            waiting_time[index_of_burst] += real_time - finish_time[index_of_burst];
            turnarround_time[index_of_burst] = waiting_time[index_of_burst] + number_of_tburst[index_of_burst];
        }
        t++;
        real_time++;
        number_of_burst[index_of_burst]--;
        // printf("%d : %d\n", index_of_burst, number_of_burst[index_of_burst]);
        if (number_of_burst[index_of_burst] == 0)
        {
            priority[index_of_burst] = 0;
            can_run[index_of_burst] = 0;
            t = 0;
            what_process--;
            number_inq--;
        }
        last_p = p;
        last_index = index_of_burst;
    }

    printf("\nProcess    Burst Time    Waiting Time   Turnaround Time\n");
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