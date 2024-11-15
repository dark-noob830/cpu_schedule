#include <stdio.h>

int index_max(float arr[], int n)
{

    int max = -1;
    int index = -1;

    for (int i = 0; i < n; i++)
    {
        // if (arr[i] == 0)
        // {
        //     continue;
        // }
        // if (max == -1)
        // {
        //     printf("salam\n");
        //     index = i;
        //     max = arr[i];
        // }
        if (arr[i] > max)
        {
            index = i;
            max = arr[i];
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
    scanf("%d", &n);

    int index_max_burst = 0;
    int number_of_burst[n];
    int arrivals[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arrivals[i], &number_of_burst[i]);
    }
    int waiting_time[n];
    float response_ratio[n];

    int turnarround_time[n];
    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
        response_ratio[i] = 0;
        turnarround_time[i] = 0;
    }
    int t = 0;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (number_of_burst[i] == 0)
            {
                response_ratio[i] = 0;
                continue;
            }
            else{
                waiting_time[i] = t - arrivals[i];
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (number_of_burst[i] == 0)
            {
                continue;
            }
            if (arrivals[i] <= t)
            {
                
                response_ratio[i] = (float)waiting_time[i] / (float)number_of_burst[i];
                
            }
        }
        // for(int i =0 ;i<n;i++){
        //     printf("re[%d]:%f\twaiting : %d\n",i,response_ratio[i],waiting_time[i]);
        // }
        index_max_burst = index_max(response_ratio, n);
        printf("process %d is executed at %d\n", index_max_burst, t);
        t += number_of_burst[index_max_burst];
        number_of_burst[index_max_burst] = 0;
        // printf("t:%d",t);
        
    }
    // printf("Process    Burst Time    Waiting Time   Turnaround Time\n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("p%d\t\t", i + 1);
    //     printf("%d\t\t", number_of_tburst[i]);
    //     printf("%d\t\t", waiting_time[i]);
    //     printf("%d\t\t", turnarround_time[i]);
    //     printf("\n");
    // }
    printf("average waiting time: %.3f\n", (float)sum(waiting_time, n) / n);
    // printf("Average Turnaround Time : %.2f\n", (float)sum(turnarround_time, n) / n);
    return 0;
}