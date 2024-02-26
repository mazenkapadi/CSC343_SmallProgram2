/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   fsmore.c
 * Author: mazenkapadi
 *
 * Created on February 12, 2024, 6:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void print_screen(FILE *file) {
    char buffer[BUFFER_SIZE];
    int lines_left = 0;
    int orig_lines_left;

    const char *lines_env = getenv("LINES");
    if (lines_env) {
        lines_left = atoi(lines_env);
    } else {
        lines_left = 24;
    }
    orig_lines_left = lines_left;

    int ch;
    while (1) {
        if (fgets(buffer, BUFFER_SIZE, file) != NULL) {
            printf("%s", buffer);
            if (buffer[strlen(buffer) - 1] == '\n') {
                lines_left--;
            }
        } else {
            break; // End of file reached
        }

        // Check if more lines need to be printed
        if (lines_left == 0) {
            printf("\n-- More -- Press Enter to continue --\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {
                // Empty loop to wait for Enter key
            }
            lines_left = orig_lines_left;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        exit(0); // Exit if no files are specified
    }

    FILE *fp;
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "fsmore: Cannot open file '%s'\n", argv[i]);
            continue;
        }

        print_screen(fp);
        fclose(fp);
    }
    return EXIT_SUCCESS;
}