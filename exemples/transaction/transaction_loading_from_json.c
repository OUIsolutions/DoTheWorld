//
// Created by mateusmoutinho on 24/07/23.
//
#include "doTheWorld.h"

int main(){
    DtwTransaction *t = newDtwTransaction_from_json_file("tests/target/transaction.json");
    t->represent(t);
    t->free(t);
}