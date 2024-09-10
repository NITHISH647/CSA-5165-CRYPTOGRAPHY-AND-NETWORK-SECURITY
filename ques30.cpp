#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16

void xor_blocks(uint8_t *block1, const uint8_t *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block1[i] ^= block2[i];
    }
}

void encrypt_block(const uint8_t *key, uint8_t *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void cbc_mac(const uint8_t *key, const uint8_t *message, size_t length, uint8_t *mac) {
    uint8_t block[BLOCK_SIZE] = {0};
    size_t num_blocks = length / BLOCK_SIZE;
    size_t last_block_size = length % BLOCK_SIZE;

    for (size_t i = 0; i < num_blocks; i++) {
        xor_blocks(block, message + i * BLOCK_SIZE);
        encrypt_block(key, block);
    }

    if (last_block_size > 0) {
        uint8_t last_block[BLOCK_SIZE] = {0};
        memcpy(last_block, message + num_blocks * BLOCK_SIZE, last_block_size);
        xor_blocks(block, last_block);
        encrypt_block(key, block);
    }

    memcpy(mac, block, BLOCK_SIZE);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {'s', 'e', 'c', 'r', 'e', 't', 'k', 'e', 'y', 's', 'e', 'c', 'r', 'e', 't', 'k'};
    uint8_t message_oneblock[BLOCK_SIZE] = {'m', 'e', 's', 's', 'a', 'g', 'e', 'b', 'l', 'o', 'c', 'k', '1', '\0', '\0', '\0'};
    uint8_t mac[BLOCK_SIZE];

    cbc_mac(key, message_oneblock, BLOCK_SIZE, mac);

    printf("CBC MAC for one-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    uint8_t message_two_blocks[BLOCK_SIZE * 2] = {'m', 'e', 's', 's', 'a', 'g', 'e', 'b', 'l', 'o', 'c', 'k', '1', '\0', '\0', '\0',
                                                  'm', 'e', 's', 's', 'a', 'g', 'e', 'b', 'l', 'o', 'c', 'k', '2', '\0', '\0', '\0'};
    uint8_t mac_two_blocks[BLOCK_SIZE];

    cbc_mac(key, message_two_blocks, BLOCK_SIZE * 2, mac_two_blocks);

    printf("CBC MAC for two-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac_two_blocks[i]);
    }
    printf("\n");

    return 0;
}
