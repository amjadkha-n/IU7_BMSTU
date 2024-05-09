#ifndef MOD_H
#define MOD_H

typedef struct {
    int height;
    char surname[6];
} Student;

void add_student();
void print_students();
void remove_below_average();
void sort_students();
void erase_data();

#endif  // MOD_H
