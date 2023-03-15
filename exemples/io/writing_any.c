
#include "../../doTheWorld.c"

int main(int argc, char *argv[]){

  //load the beer image
  const char *deer_path = "../exemple_folder/deer.jpg";
  int deer_size;
  char *content = dtw_load_binary_content(deer_path,&deer_size);
  //use these functions for binary files
  if(content == NULL){
    printf("error oppening %s\n",deer_path);
    return 1;
  }
  printf("size: %d\n",deer_size);

  bool result = dtw_write_any_content("exemple/deer.jpg",content,deer_size);
  printf("result: %s\n",result ? "true" : "false");
  return 0;
}
