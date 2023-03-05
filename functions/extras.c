#pragma once

void dtw_free_string_array(char **array, int size) {
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

void dtw_append_string_array_in_other(char ***array, int *size, char **other_array, int other_size) {
    *array = realloc(*array, (*size + other_size) * sizeof(char *));
    for (int i = 0; i < other_size; i++) {
        (*array)[*size + i] = malloc(strlen(other_array[i]) + 1);
        strcpy((*array)[*size + i], other_array[i]);
    }
    *size += other_size;
}
