#pragma once

void dtw_free_string_array(char **array, int size) {
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}