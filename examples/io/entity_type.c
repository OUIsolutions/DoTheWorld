#include "doTheWorldOne.c"

void print_entity(const char *name, int type) {
    if (type == DTW_FOLDER_TYPE) {
        printf("%s is a folder\n", name);
    }
    if (type == DTW_FILE_TYPE) {
        printf("%s is a file\n", name);
    }
    if (type == DTW_NOT_FOUND) {
        printf("%s not exist\n", name);
    }
}

int main(int argc, char *argv[]) {
    short type;
    const char *not_exist = "asasasas";
    type = dtw_entity_type(not_exist);
    print_entity(not_exist, type);

    const char *folder = "tests/target/";
    type = dtw_entity_type(folder);
    print_entity(folder, type);

    const char *file = "tests/target/a.txt";
    type = dtw_entity_type(file);
    print_entity(file, type);

    return 0;
}