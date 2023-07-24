//
// Created by mateusmoutinho on 24/07/23.
//
#include "../../../doTheWorld_test.h"

int main(){
    DtwTransaction *t = newDtwTransaction();
    t->write_string(t,"b.txt","aaaaa");
    t->move_any(t,"a.txt","c.txt");
    t->delete_any(t,"blob.png");
    t->copy_any(t,"sub_folder","sub_folder2");
    t->commit(t,"tests/target");
    t->free(t);
}