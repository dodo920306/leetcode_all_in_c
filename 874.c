#include <stdio.h>
#include <stdbool.h>
#include "uthash/include/uthash.h"

enum direction {
    North,
    East,
    South,
    West
};

struct coordinate {
    int x, y;
};

struct coordinateSet {
    struct coordinate key;
    UT_hash_handle hh;
};

struct robot {
    enum direction direction;
    struct coordinate coordinate;
};

int square(int k);
int squaredDistance(struct coordinate self);
void rotate(struct robot *self, bool isLeft);
bool move(struct robot *self, struct coordinateSet *set);
void insertCoordinateSet(struct coordinateSet **set, int x, int y);
struct robot *newRobot();
void freeCoordinateSet(struct coordinateSet *set);
int robotSim(int *commands, int commandsSize, int **obstacles, int obstaclesSize, int *obstaclesColSize);

int square(int k)
{
    return k * k;
}

int squaredDistance(struct coordinate self)
{
    return square(self.x) + square(self.y);
}

void rotate(struct robot *self, bool isLeft)
{
    if (isLeft)
        self->direction--;
    else
        self->direction++;

    self->direction %= 4;
    return;
}

bool move(struct robot *self, struct coordinateSet *set)
{
    struct coordinateSet *isObstacle = NULL;
    struct coordinate coordinate = self->coordinate;
    switch (self->direction) {
        case North:
            coordinate.y++;
            break;
        case South:
            coordinate.y--;
            break;
        case East:
            coordinate.x++;
            break;
        case West:
            coordinate.x--;
        default:
            break;
    }

    HASH_FIND(hh, set, &coordinate, sizeof(struct coordinate), isObstacle);
    if (!isObstacle)
        self->coordinate = coordinate;
    return !isObstacle;
}

void insertCoordinateSet(struct coordinateSet **set, int x, int y)
{
    struct coordinateSet *element = NULL;
    struct coordinate _coordinate = {x, y};
    HASH_FIND(hh, *set, &_coordinate, sizeof(struct coordinate), element);
    if (element)    return;

    element = (struct coordinateSet *)malloc(sizeof(struct coordinateSet));
    if (!element) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return;
    }

    element->key = _coordinate;
    HASH_ADD(hh, *set, key, sizeof(struct coordinate), element);
}

struct robot *newRobot()
{
    struct robot *res = (struct robot *)malloc(sizeof(struct robot));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    res->direction = North;
    res->coordinate.x = 0;
    res->coordinate.y = 0;
    return res;
}

void freeCoordinateSet(struct coordinateSet *set)
{
    struct coordinateSet *iter, *next;

    HASH_ITER(hh, set, iter, next) {
        // HASH_DEL(set, iter);
        free(iter);
    }
}

int robotSim(int *commands, int commandsSize, int **obstacles, int obstaclesSize, int *obstaclesColSize)
{
    int res = 0;
    struct coordinateSet **set = (struct coordinateSet **)malloc(sizeof(struct coordinateSet *));
    struct robot *robot = newRobot();
    if (!(set && robot)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }
    *set = NULL;

    for (int i = 0; i < obstaclesSize; i++)
        insertCoordinateSet(set, obstacles[i][0], obstacles[i][1]);

    for (int i = 0, distance; i < commandsSize; i++)
        if (commands[i] < 0)
            rotate(robot, (commands[i] == -2));
        else {
            for (int j = 0; j < commands[i]; j++)
                if (!move(robot, *set)) break;
            distance = squaredDistance(robot->coordinate);
            if (res < distance) res = distance;
        }

    freeCoordinateSet(*set);
    free(robot);
    free(set);
    return res;
}

int main()
{
    int commands[] = {4, -1, 4, -2, 4}, obstacle[] = {2, 4}, *obstacles[] = {obstacle}, obstaclesColSize[] = {2};
    printf("%d\n", robotSim(commands, 5, obstacles, 1, obstaclesColSize));
    return 0;
}
