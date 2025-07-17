#include <stdio.h>

int main() {
    int data[7]; // 7-bit Hamming code
    int i;

    printf("Enter 4 bits of data (D1, D2, D3, D4):\n");

    // Input D1, D2, D3, D4
    scanf("%d", &data[2]); // D1
    scanf("%d", &data[4]); // D2
    scanf("%d", &data[5]); // D3
    scanf("%d", &data[6]); // D4

    // Calculate parity bits for even parity
    data[0] = data[2] ^ data[4] ^ data[6]; // P1
    data[1] = data[2] ^ data[5] ^ data[6]; // P2
    data[3] = data[4] ^ data[5] ^ data[6]; // P3

    printf("\nEncoded 7-bit Hamming code is:\n");
    for (i = 0; i < 7; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
