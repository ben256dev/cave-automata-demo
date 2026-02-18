#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SMOOTHING_ITERATIONS 14
#define LAND_PERCENTAGE 50
#define MAP_SIZE_X 100
#define MAP_SIZE_Y 50
#define CELL_TOP_LEFT 0
#define CELL_TOP 1
#define CELL_TOP_RIGHT 2
#define CELL_RIGHT 3
#define CELL_BOTTOM_RIGHT 4
#define CELL_BOTTOM 5
#define CELL_BOTTOM_LEFT 6
#define CELL_LEFT 7
#define CELL_NEIGHBORS 8

int map_index(int *map, int x, int y) {
    x = ((x % MAP_SIZE_X) + MAP_SIZE_X) % MAP_SIZE_X;
    y = ((y % MAP_SIZE_Y) + MAP_SIZE_Y) % MAP_SIZE_Y;
    return map[y * MAP_SIZE_X + x];
}

void map_set(int *map, int x, int y, int value) {
    map[y * MAP_SIZE_X + x] = value;
}

void init_map(int *map)
{
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            if (rand() % 100 < LAND_PERCENTAGE)
                map_set(map, x, y, 1);
            else
                map_set(map, x, y, 0);
        }
    }
}

void print_map(int *map)
{
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            if (map_index(map, x, y))
                printf("\033[42m \033[0m");
            else
                printf("\033[44m \033[0m");
        }
        printf("\033[0m\n");
    }
}

int get_viscinity_sum(int *map, int x, int y) {
    int viscinity_sum = 0;
    viscinity_sum += map_index(map, x-1, y+1);
    viscinity_sum += map_index(map, x  , y+1);
    viscinity_sum += map_index(map, x+1, y+1);
    viscinity_sum += map_index(map, x-1, y  );
    viscinity_sum += map_index(map, x  , y  );
    viscinity_sum += map_index(map, x+1, y  );
    viscinity_sum += map_index(map, x-1, y-1);
    viscinity_sum += map_index(map, x  , y-1);
    viscinity_sum += map_index(map, x+1, y-1);

    return viscinity_sum;
}

void smooth_map(int *map1, int *map2) {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            int viscinity_sum = get_viscinity_sum(map1, x, y);
            if (viscinity_sum >= 5)
                map_set(map2, x, y, 1);
            else
                map_set(map2, x, y, 0);
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int *map1 = malloc(sizeof(int) * MAP_SIZE_X * MAP_SIZE_Y);
    int *map2 = malloc(sizeof(int) * MAP_SIZE_X * MAP_SIZE_Y);
    int *map = map1;

    init_map(map);

    int *map_to_swap;

    for (int i = 0; i < SMOOTHING_ITERATIONS; i++) {
        map_to_swap = (map == map1) ? map2 : map1;
        smooth_map(map, map_to_swap);
        map = map_to_swap;
    }

    print_map(map);

    free(map1);
    free(map2);

	return 0;
}
