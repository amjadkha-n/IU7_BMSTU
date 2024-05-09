#ifndef MY_MOD_H
#define MY_MOD_H

#include <stdio.h>

size_t get_file_size(FILE *file);
int gen_rand_num(char *filename, int cnumber);
int print_numbers(char *filename);
int get_number_by_position(FILE *file, size_t position);
void put_number_by_position(FILE *file, size_t position, int number);
void swap_numbers(FILE *file, size_t position1, size_t position2);
int sort_numbers(char *filename);
int text_to_bin(char *filename);
int bin_to_text(char *filename);

#endif /* MY_MOD_H */
