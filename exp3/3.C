#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert binary string (e.g. "11001010") to decimal integer
int binaryToDecimal(char *bin) {
    int  i,value = 0;
    for ( i = 0; bin[i] != '\0'; i++) {
        value = value * 2 + (bin[i] - '0');
    }
    return value;
}

int main() {
    int n, sum = 0, checksum,i;
    char binary[10];
    int data[100];

    // Ask how many binary values the user will input
    printf("Enter number of binary data bytes: ");
    scanf("%d", &n);

    // Read each binary byte (as 8-bit string)
    printf("Enter each byte (8-bit binary, e.g., 11001010):\n");
    for ( i = 0; i < n; i++) {
        printf("Byte %d: ", i + 1);
        scanf("%s", binary);                  // Read binary string
        data[i] = binaryToDecimal(binary);    // Convert to integer
        sum += data[i];                       // Add to sum
    }

    // Handle 8-bit overflow: add carry if any
    while (sum > 255) {
        sum = (sum & 0xFF) + (sum >> 8);
    }

    // Calculate 1's complement of sum
    checksum = ~sum & 0xFF;

    // Print checksum in both decimal and binary
    printf("\nChecksum (decimal): %d\n", checksum);
    printf("Checksum (binary) : ");
    for (i = 7; i >= 0; i--) {
        printf("%d", (checksum >> i) & 1);
    }
    printf("\n");

    // Simulate receiver: add checksum and check final sum
    sum += checksum;
    while (sum > 255) {
        sum = (sum & 0xFF) + (sum >> 8);
    }

    // If total becomes all 1s (i.e. 0xFF), data is valid
    if (sum == 0xFF)
        printf("Data is correct.\n");
    else
        printf("Data is corrupted.\n");

    return 0;
}

