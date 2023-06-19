

#include "doTheWorld.c"

int main(int argc, char *argv[]){
  dtw_write_string_file_content("exemple_folder2/x.txt","hello world");
  dtw_copy_any("exemple_folder","exemple_folder2",DTW_MERGE);
  return 0;
}