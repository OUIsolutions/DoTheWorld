#include "src/one.c"

DtwNamespace dtw;



int main(){
    dtw = newDtwNamespace();
    DtwTree *t  = dtw.tree.newTree();
    DtwTreePart *p = dtw.tree.part.newPartEmpty("a.txt");
    long size;
    bool isbin;
    unsigned char *v = dtw.load_any_content("tests/target/blob.png",&size,&isbin);
    dtw.tree.part.set_any_content(p,v,size,isbin);
    free(v);
    dtw.tree.add_tree_part_getting_owenership(t,p);
    dtw.tree.part.hardware_write(p,DTW_SET_AS_ACTION);

    dtw.tree.hardware_commit_tree(t);
    dtw.tree.free(t);
}