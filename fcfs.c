#include<stdio.h>
#include<stdlib.h>
//---------------------

int cpuData[50][700];
char *File_Name = "CPULoad.dat";
int NoOfProcess = 0;

void arrayManager() {

    FILE *fp;
    int data = 0;
    fp = fopen(File_Name, "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    while (!feof(fp)) {
        char ch = fgetc(fp);
        if (ch == '\n') {
            NoOfProcess++;
            data = 0;
        } else if (ch == ' ') {
            data++;
            cpuData[NoOfProcess][data] = 0;
        } else {
            if (ch == '(' || ch == ')') {
            } else {
                cpuData[NoOfProcess][data] = (cpuData[NoOfProcess][data] * 10) + (ch - '0');
            }
        }
    }
//    printf("Total number of enter: %d\n", NoOfProcess);
//    printf("Data in 8th NoOfProcess is: %d\n", cpuData[25][0]);
}

int getArrivalTime(int i) {
    if (i >= 0 && i < NoOfProcess) {
        return cpuData[i][1];
    }
    printf("Error in getArrivalTime");
}

int getBurstTime(int i) {
    if (i >= 0 && i < NoOfProcess) {
        return cpuData[i][2];
    }
    printf("Error in getBurstTime");
}

//---------------------
struct Process {
    int proc_ID;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
} p[20];

struct ghantt_chart {
    int process_ID;
    int start_time;
    int end_time;
} ghantt[20];

int ghantt_counter = 0;

void print_ghantt() {
    printf("\nGHANTT CHART \n\n");

    for (int i = 0; i < ghantt_counter; i++) {
        printf(" _P%d_", ghantt[i].process_ID);

        if (ghantt[i].end_time != ghantt[i + 1].start_time && i != ghantt_counter - 1) {
            printf(" _");
        }
    }
    puts("");

    for (int j = 0; j < ghantt_counter + 1; j++) {
        printf("|      ");

        if (ghantt[j].end_time != ghantt[j + 1].start_time && j != ghantt_counter - 1) {
            printf("| ");
        }
    }
    puts("");

    for (int k = 0; k < ghantt_counter; k++) {
        printf("%d      ", ghantt[k].start_time);

        if (ghantt[k].end_time != ghantt[k + 1].start_time && k != ghantt_counter - 1) {
            printf("%d ", ghantt[k].end_time);
        }
    }
    printf("%d", ghantt[ghantt_counter - 1].end_time);
}

void print_function(int proc) {
    printf("\n| Proc_Id | Waiting  Time | Response Time | Turnaround Time |\n");

    for (int i = 0; i < proc; i++) {
        printf("|    %d    |       %d       |       %d       |        %d        |\n", p[i].proc_ID, p[i].waiting_time,
               p[i].response_time, p[i].turnaround_time);

    }
}

void response_time_cal(int proc, int ghantt_counter) {
    for (int i = 0; i < proc; i++) {
        for (int j = 0; j < ghantt_counter; j++) {
            if (ghantt[j].process_ID == p[i].proc_ID) {
                p[i].response_time = ghantt[j].start_time - p[i].arrival_time;
                break;
            }
        }
    }
}

void sjf_non_preemptive(int proc) {
    int time = 0;
    int ready[proc];
    int ready_count = 0;
    int job_cmp = 0;
    int run = -1;

    while (job_cmp < proc) {
        for (int j = 0; j < proc; j++) {
            if (p[j].arrival_time == time) {
                ready[ready_count] = j;
                ready_count++;
            }
        }

        if (run != -1) {
            (p[run].burst_time)--;

            if (p[run].burst_time <= 0) {
                ghantt[ghantt_counter].end_time = time;
                ghantt_counter++;
                job_cmp++;
                p[run].turnaround_time = time - p[run].arrival_time;
                run = -1;
            }
        }
        if (run == -1 && ready_count != 0) {
            int index;

            for (int k = 0; k < ready_count; k++) {
                if (k == 0) {
                    index = k;
                }

                if (p[ready[k]].burst_time < p[ready[index]].burst_time) {
                    index = k;
                }
            }
            run = ready[index];
            ghantt[ghantt_counter].process_ID = run;
            ghantt[ghantt_counter].start_time = time;

            for (int i = index; i < ready_count - 1; i++) {
                ready[i] = ready[i + 1];
            }
            ready_count--;
        }
        for (int j = 0; j < ready_count; j++) {
            p[ready[j]].waiting_time = p[ready[j]].waiting_time + 1;
        }

        time++;
    }

}

int main() {
    arrayManager();
    printf("\n*********SJF SCHEDULING ALGORITHM IMPLEMENTATION*********\n\n");
    int proc;
    printf("\nTotal Limit of Processes entertained is 20\n");

//    INPUT:
//    printf("\nEnter no of processes you want to perform: ");
//    scanf("%d", &proc);
//
//    if (proc == 0) {
//        printf("\n*********Invalid Entry*********\nTry to make sure no of processes is not zero\n");
//        goto INPUT;
//    }
    proc= NoOfProcess;
//    if (proc < 0) {
//        printf("\n*********Invalid Entry*********\nTry to make sure that number of processes is not a negative number\n");
//        goto INPUT;
//    }

    for (int i = 0; i < proc; i++) {
        p[i].proc_ID = i;

//        ARRIVAL:
//        printf("\n\nEnter Arrival time of process %d: ", p[i].proc_ID);
//        scanf("%d", &p[i].arrival_time);
//
        p[i].arrival_time = getArrivalTime(i);  //getArrivalTime(i) is a function that returns the arrival time of the process i
//        if ((p[i].arrival_time) < 0) {
//            printf("\n*********Invalid Entry*********\nPlease Enter Valid Input\n");
//            goto ARRIVAL;
//        }
//
//        if ((p[i].arrival_time) >= 0) {
//            BURST:
//            printf("\n\nEnter Burst time of process %d: ", p[i].proc_ID);
//            scanf("%d", &p[i].burst_time);
//            if ((p[i].burst_time) < 0) {
//                printf("\n*********Invalid Entry*********\nPlease Enter Valid Input\n");
//                goto BURST;
//            }
//        }
        p[i].burst_time = getBurstTime(i);  //getBurstTime(i) is a function that returns the burst time of the process i
    }
    sjf_non_preemptive(proc);
    response_time_cal(proc, ghantt_counter);
    print_function(proc);
    print_ghantt();
}