#include "../include/utilities.h"
#include <stdio.h>

void uint8ToChar(uint8_t value, char* buffer) {
    int i = 0;
    do {
        buffer[i++] = (value % 10) + '0'; // Convert digit to character
        value /= 10;
    } while (value && i < 10);
    
    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
    buffer[i] = '\n'; // Add newline character at the end
    buffer[i + 1] = '\0'; // Null-terminate the string
}