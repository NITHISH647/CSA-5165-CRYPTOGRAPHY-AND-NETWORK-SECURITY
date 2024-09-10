#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 128
#define STATE_SIZE 25
#define CAPACITY_SIZE 10

typedef uint64_t lane_t;

void initialize_state(lane_t state[STATE_SIZE]) {
    memset(state, 0, STATE_SIZE * sizeof(lane_t));
}

void update_state(lane_t state[STATE_SIZE], const uint8_t *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] ^= block[i];
    }
}

int check_nonzero_lanes(const lane_t state[STATE_SIZE], int capacity_start, int capacity_end) {
    for (int i = capacity_start; i < capacity_end; i++) {
        if (state[i] != 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    lane_t state[STATE_SIZE];
    uint8_t block[BLOCK_SIZE];
    int rounds = 0;

    initialize_state(state);

    while (1) {
        memset(block, (rounds + 1) % 256, BLOCK_SIZE);
        update_state(state, block);
        rounds++;

        if (check_nonzero_lanes(state, STATE_SIZE - CAPACITY_SIZE, STATE_SIZE)) {
            break;
        }
    }

    printf("Rounds taken to make all capacity lanes nonzero: %d\n", rounds);

    return 0;
}
