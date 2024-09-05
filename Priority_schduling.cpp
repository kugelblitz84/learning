#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct process{
    char process_name[10];
    int arrival_time;
    int priority;
    int cpu1, io, cpu2;
    int completion_time;  
    bool qued;          
} process;

process *process_q[100];
int q_iterator = -1;

void init(){
    for(int i = 0; i < 100; i++){
        process_q[i] = (process *)malloc(sizeof(process));
        process_q[i]->completion_time = -1;
        process_q[i]->qued = false;
    }
}

void clr(){
    for(int i = 0; i < 100; i++){
        free(process_q[i]);
    }
}

void heapify_process_que(int root){
    if(root == q_iterator) return;
    int smallest_node = root;
    int left_child = root * 2 + 1;
    int right_child = root * 2 + 2;

    if(left_child <= q_iterator &&
       process_q[left_child]->priority > process_q[smallest_node]->priority) {
        smallest_node = left_child;
    }

    if(right_child <= q_iterator &&
       process_q[right_child]->priority > process_q[smallest_node]->priority) {
        smallest_node = right_child;
    }

    if(smallest_node != root){
        process *temp = process_q[root];
        process_q[root] = process_q[smallest_node];
        process_q[smallest_node] = temp;
        heapify_process_que(smallest_node);
    }
}

void heapify_process_que_bottom_up(int child){
    if(child == 0) return;
    int root = (child - 1) >> 1;
    if(process_q[child]->priority > process_q[root]->priority){
        process* temp = process_q[root];
        process_q[root] = process_q[child];
        process_q[child] = temp;
        heapify_process_que_bottom_up(root);
    }
}

void pop_q(){
    process_q[0]->qued = false;
    process_q[0] = process_q[q_iterator--];
    heapify_process_que(0);
}

void insert_process(process *n){
    n->qued = true;
    process_q[++q_iterator] = n;
    heapify_process_que_bottom_up(q_iterator);
}

int main(){
    init();
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process process_no[100];

    printf("Enter %d process(es):\n", n);
    for(int i = 0; i < n; i++){
        printf("Enter process %d\n", i + 1);
        printf("Process name: ");
        scanf(" %s", &process_no[i].process_name);
        printf("Arrival time: ");
        scanf("%d", &process_no[i].arrival_time);
        printf("Set priority: ");
        scanf("%d", &process_no[i].priority);
        printf("Enter CPU1, I/O, and CPU2: ");
        scanf("%d %d %d", &process_no[i].cpu1, &process_no[i].io, &process_no[i].cpu2);
        process_no[i].completion_time = -1;
        process_no[i].qued = false;
    }

    for(int time = 0; time < 1000; time++){
        for(int i = 0; i < n; i++){
            if(time == process_no[i].arrival_time)
                insert_process(&process_no[i]);
            else if(time > process_no[i].arrival_time){
                if(!process_no[i].qued) {
                    if(process_no[i].io != 0)
                        process_no[i].io--;
                    else if(process_no[i].completion_time == -1)
                        insert_process(&process_no[i]);
                }
            }
        }
        if(q_iterator >= 0){
            if(process_q[0]->cpu1 != 0)
                process_q[0]->cpu1--;
            else if(process_q[0]->io != 0){
                process_q[0]->io--;
                pop_q();
            }else if(process_q[0]->cpu2 != 0){
                process_q[0]->cpu2--;
            }
            if(process_q[0]->cpu2 == 0){
                process_q[0]->completion_time = time+1;
                pop_q();
            }
        }
    }

    printf("Process_name\tCompletion_time\n");
    for(int i = 0; i < n; i++) {
        printf("%s\t\t%d\n", process_no[i].process_name, process_no[i].completion_time);
    }

    clr();
    return 0;
}
