#include <stdio.h>
#include <string.h>

int main() {
    char in[100], out[200], des[100];
    char flag[] = "01111110";
    int inlen, i, j = 0, count = 0, k = 0;

    printf("Enter the data to be bit stuffed (only 0s and 1s):\n");
    scanf("%s", in);

    inlen = strlen(in);
    
    // Start with flag
    strcpy(out, flag);
    j = strlen(flag);

    // Bit Stuffing
    for (i = 0; i < inlen; i++) {
        out[j++] = in[i];

        if (in[i] == '1') {
            count++;
            if (count == 5) {
                out[j++] = '0';  // Stuff '0' after five 1s
                count = 0;
            }
        } else {
            count = 0;
        }
    }

    // Append flag at the end
    strcpy(&out[j], flag);
    out[j + strlen(flag)] = '\0';

    printf("\nThe bit-stuffed frame is:\n%s\n", out);

    // Destuffing - Remove flags and unstuff
    int outlen = strlen(out);
    count = 0;
    j = strlen(flag);  // Start after flag
    k = 0;

    while (j < outlen - strlen(flag)) {  // Until before ending flag
        des[k++] = out[j];

        if (out[j] == '1') {
            count++;
            if (count == 5) {
                j++;  // Skip the stuffed '0'
                count = 0;
            }
        } else {
            count = 0;
        }
        j++;
    }

    des[k] = '\0';

    printf("\nThe destuffed data is:\n%s\n", des);

    return 0;
}
