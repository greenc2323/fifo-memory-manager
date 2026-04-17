#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN  50
typedef struct{
    int pages_num;
    int curr;
    int pages[MAXLEN];
    int faults;
    int used[MAXLEN];

} memory;
memory* memory_init(int n){
    memory* m = (memory*)malloc(sizeof(memory));
    if (m == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    m->pages_num = n;
    m->curr = 0;
    m->faults = 0;

    for (int i = 0; i < MAXLEN; i++){
        m->pages[i] = -1;
        m->used[i] = 0;
    }

    return m;
}

int search_process(memory* m, int process);
void add_process(memory* m, int process);
void display_pages(memory* m);
int memory_FIFO(int num);

int search_process(memory* m, int process){
    for (int i = 0; i < m->pages_num; i++){
        if (m->pages[i] == process){
            return 1;
        }
    }
    return 0;
}

void add_process(memory* m, int process){
    printf("%02d  ", process);

    if (search_process(m, process)){
        display_pages(m);
        return;
    }

    for (int i = 0; i < m->pages_num; i++){
        if (m->pages[i] == -1){
            m->pages[i] = process;
            display_pages(m);
            return;
        }
    }

    printf("F ");
    m->pages[m->curr] = process;
    m->curr = (m->curr + 1) % m->pages_num;
    m->faults++;

    display_pages(m);
}

void display_pages(memory* m){
    for (int i = 0; i < m->pages_num; i++){
        if (m->pages[i] != -1){
            printf("%02d ", m->pages[i]);
        }
    }
    printf("\n");
}

int memory_FIFO(int num){
    memory* m = memory_init(num);
    int input;
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    while(1){
        scanf("%d", &input);
        if(input == -1)
            break;
        add_process(m, input);
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", m->faults);

    free(m);
    return 0;
}

int main(){
    int num;
    char algo[6];

    scanf("%d", &num);
    scanf("%s", algo);

    if(strcmp(algo, "FIFO") == 0)
        memory_FIFO(num);

    return 0;
}
