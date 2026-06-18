#include <stdio.h>
#include <stdlib.h>

int main() {
    char *file = "dayOne.txt";
    FILE *inputs = fopen(file, "r");

    if (inputs == NULL) {
        printf("Error: Can't open file '%s'.\n", file);
        exit(1);
    }

    long long password_counter = 0; // Use a long long to be safe with large inputs
    char letter;
    int clicks;
    int position = 50;
    int lineCount = 0;

    printf("--- Final Password Calculation ---\n");
    printf("Starting position: %d\n\n", position);

    while (fscanf(inputs, " %c%d", &letter, &clicks) == 2) {
        lineCount++;
        int oldPosition = position;
        int times_hit_zero = 0;

        if (letter == 'L') {
            // How many times do we cross 0 going left?
            if (clicks >= oldPosition && oldPosition != 0) {
                times_hit_zero++;
                times_hit_zero += (clicks - oldPosition) / 100;
            } else if (clicks > oldPosition && oldPosition == 0) {
                 times_hit_zero += (clicks) / 100;
            } else {
                times_hit_zero += (clicks - (clicks-oldPosition)) / 100;
            }

            // Calculate new position
            position = (oldPosition - clicks) % 100;
            if (position < 0) {
                position += 100;
            }

        } else if (letter == 'R') {
            // How many times do we cross 0 going right?
            times_hit_zero += (oldPosition + clicks) / 100;
            if (oldPosition == 0) {
                times_hit_zero -= (clicks)/100;
                times_hit_zero += (clicks-1)/100;
            }


            // Calculate new position
            position = (oldPosition + clicks) % 100;
        }

        password_counter += times_hit_zero;
        
        printf("Line %d: %c%d -> New Position: %d (Hit 0 %d times)\n",
               lineCount, letter, clicks, position, times_hit_zero);
    }

    printf("\n----------------------------------\n");
    printf("FINAL PASSWORD: %lld\n", password_counter);
    printf("----------------------------------\n");

    fclose(inputs);
    return 0;
}