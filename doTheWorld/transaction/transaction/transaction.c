

DtwTransaction * newDtwTransaction(){
    DtwTransaction *self = (DtwTransaction*) malloc(sizeof(DtwTransaction));
    self->actions = (DtwActionTransaction **) malloc(sizeof (DtwActionTransaction **));
    self->size = 0;
    self->append_action =DtwTransaction_append_action;
    self->write_any = DtwTransaction_write_any;
    self->write_string = DtwTransaction_write_string;
    self->move_any = DtwTransaction_move_any;
    self->copy_any = DtwTransaction_copy_any;
    self->delete_any = DtwTransaction_delete_any;
    self->commit = DtwTransaction_commit;
    self->represent = DtwTransaction_represent;
    self->free = DtwTransaction_free;
}

void DtwTransaction_append_action(struct DtwTransaction *self,struct DtwActionTransaction  *action){
    self->actions =  (DtwActionTransaction**) realloc(self->actions,sizeof (DtwActionTransaction**) * self->size+1);
    self->actions[self->size] = action;
    self->actions++;
}
void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary){
    DtwActionTransaction * action = DtwActionTransaction_write_any(path,content,size,is_binary);
    self->append_action(self,action);
}

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content){
    DtwActionTransaction * action = DtwActionTransaction_write_any(path,(unsigned char*)content, strlen(content),false);
    self->append_action(self,action);
}

void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest){
    DtwActionTransaction * action = DtwActionTransaction_move_any(source,dest);
    self->append_action(self,action);
}
void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest){
    DtwActionTransaction * action = DtwActionTransaction_copy_any(source,dest);
    self->append_action(self,action);
}

void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source){
     DtwActionTransaction  *action = DtwActionTransaction_delete_any(source);
     self->append_action(self,action);
}

void DtwTransaction_represent(struct DtwTransaction *self){
    for(int i = 0; i < self->size; i++){
        DtwActionTransaction_represent(self->actions[i]);
    }
}

void DtwTransaction_free(struct DtwTransaction *self){
    for(int i =0; i < self->size; i++){
        DtwActionTransaction_free(self->actions[i]);
    }
    free(self);
}
