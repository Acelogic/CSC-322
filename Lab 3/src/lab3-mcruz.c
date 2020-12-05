#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct cacheLine {
    int address;
};


int search(struct cacheLine cache[][1], int n, int ele) {
    int i;
    for (i = 0; i < n; i++) {
        if (cache[i][0].address == ele) {
            break;
        }
    }
    if (i != n) {
        return 1;
    } else {
        return 0;
    }
}

void lru(int page_request[], int n, int fsize, struct cacheLine cache[][1], int result[2]) {
    int i, j;
    int farthest;
    int k = 0;
    int l;
    int displacement;
    int index_farthest = 0, miss_count = 0, hit_count = 0;
    for (i = 0; i < n; i++) {
        printf("\n%x ", page_request[i]);
        // Cold Miss Case
        if (k < fsize) {
            if ((search(cache, k, page_request[i]) == 1)) {
                printf("H");
                hit_count++;
            } else {
                cache[i][0].address = page_request[i];
                k++;
                miss_count++;
                printf("M");
            }
        //Checking the cache when it is full to determine if there's a need for replacement
        } else {
            if ((search(cache, fsize, page_request[i]) == 1)) {
                printf("H");
                hit_count++;
            } else {
                farthest = 0;
                for (l = 0; l < fsize; l++) {
                    displacement = 0;
                    for (j = i - 1; j > -1; j--) {
                        if (page_request[j] == cache[l][0].address)
                            break;
                        else
                            displacement++;
                    }
                    if (displacement >= farthest) {
                        farthest = displacement;
                        index_farthest = l;
                    }
                }
                cache[index_farthest][0].address = page_request[i];
                miss_count++;
                printf("M");
            }
        }
    }
    result[0] = miss_count;
    result[1] = hit_count;
}


int mpow(int a, int b) {
    int result = a;
    if (b == 0) {
        return 1;
    } else {
        int i;
        for (i = 1; i < b; i++) {
            result = result * a;
        }
        return result;
    }
}

int main(int argc, char *argv[]) {
    int hit_count = 0;
    int miss_count = 0;
    int miss_rate = 0;
    int total_run_time = 0;
    // to disable error reporting by optget
    opterr = 0;

    int i;
    int arg_parameters[4];

    // Catch when there's not enough arguments
    if (argc == 1) {
        printf("\n[Error] Usage: ./cachelab -m <m> -s <s> -e <e> -b <b> -i <file> -r <algo>\n");
        exit(2);
    }
    //for parsing the command line arguments
    FILE *file_pointer;
    int get_opt_index = 0;
    while ((get_opt_index = getopt(argc, argv, "m:s:e:b:i:r:")) != -1) {
        switch (get_opt_index) {
            case 'm':
                arg_parameters[0] = atoi(optarg);
                break;
            case 's':
                arg_parameters[1] = atoi(optarg);
                break;
            case 'e':
                arg_parameters[2] = atoi(optarg);
                break;
            case 'b':
                arg_parameters[3] = atoi(optarg);
                break;
            case 'i':
                file_pointer = fopen(optarg, "r");
                break;
            case 'r':
                if (strcmp(optarg, "lru") != 0) {
                    printf("\n[Error] Only LRU supported");
                    exit(-1);
                }
                break;
            default:
                printf("\n[Error] Usage: ./cachelab -m <m> -s <s> -e <e> -b <b> -i <file> -r <algo>\n");
        }
    }

    int S = mpow(arg_parameters[1], 2);

    int result[2];
    struct cacheLine cache[S][arg_parameters[2]];
    int *pageRequest = malloc(sizeof(int));
    i = 0;

    if (file_pointer == NULL) {
        printf("\n[Error] Cannot open file");
        exit(1);
    } else {
        int a;
        // %x for unsigned hexadecimal
        while (fscanf(file_pointer, "%x", &a) != EOF) {
            pageRequest[i] = a;                // adding the addresses requested to an array
            i++;
        }
        lru(pageRequest, i, S, cache, result);   //replacing the cache elements based on lru and checking for hit or miss
    }

    miss_count = result[0];
    hit_count = result[1];
    //Calculations
    miss_rate = (int) ((miss_count) * 100 / (hit_count + miss_count));
    total_run_time = (hit_count * 1) + (miss_count * 100) + (miss_count * 1);
    printf("\n[result] hits:%d misses:%d miss rate:%d%% total running time:%d cycles\n", hit_count, miss_count,miss_rate, total_run_time);
    free(pageRequest);
}
