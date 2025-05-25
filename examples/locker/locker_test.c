#include "doTheWorldOne.c"



void append_text(const char *file, char *text){
    DtwNamespace dtw = newDtwNamespace();  // Keeping this as it's the entry point, but replacing its members with pure C functions.

    DtwLocker *locker = newDtwLocker();
    while(DtwLocker_lock(locker, file));  // Replaced dtw.locker.lock with DtwLocker_lock

    char *content = dtw_load_string_file_content(file);  // Replaced dtw.load_string_file_content with dtw_load_string_file_content

    content = realloc(content, strlen(content) + strlen(text) + 2);
    strcat(content, text);

    dtw_write_string_file_content(file, content);  // Replaced dtw.write_string_file_content with dtw_write_string_file_content
    free(content);

    DtwLocker_free(locker);  // Replaced dtw.locker.free with DtwLocker_free
}

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();  // Keeping this, but replacing its members.

    const char *file = "tests/target/append.txt";
    int total_process = 10;
    // This will reset the file
    dtw_remove_any(file);  // Replaced dtw.remove_any with dtw_remove_any
    dtw_write_string_file_content(file, "");

    for(int i = 0; i < total_process; i++){
        if(fork() == 0){
            char formated_content[1000] = {0};
            sprintf(formated_content, "text of: %d process %d \n", i, getpid());
            append_text(file, formated_content);
            exit(0);
        }
    }

    // Hold the end of other processes
    for(int i = 0; i < total_process; i++){
        int status;
        wait(&status);
    }
}
