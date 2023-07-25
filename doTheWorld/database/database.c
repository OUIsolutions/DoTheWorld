

DtwDataBase * newDtwDataBase(const char *path){
    DtwDataBase *self = (DtwDataBase*) malloc(sizeof (DtwDataBase));
    self->path = strdup(path);
    self->data_path = dtw_concat_path(self->path,"data");
    self->cursor = newDtwTransaction();
    self->locker = newDtwLocker();
    self->save_backup = true;
    self->use_unix_time = false;

    //methods
    self->commit = DtwDataBase_commit;
    self->reconstruct =DtwDataBase_reconstruct;
    self->free =DtwDataBase_free;
    return self;
}

DtwJsonTransactionError *DtwDataBase_reconstruct(struct DtwDataBase *self);
DtwJsonTransactionError *DtwDataBase_commit(struct DtwDataBase *self){

    self->locker->lock(self->locker,self->path);
    long path_size = strlen(self->path);
    //fix pending transactions
    char *transaction_path = (char*) calloc(sizeof(char*), path_size + 50);
    sprintf(transaction_path,"%s/pending_transaction.json",self->path);
    
    DtwTransaction *pending_transaction = newDtwTransaction_from_json_file(transaction_path);



}
void DtwDataBase_free(struct DtwDataBase *self){
    free(self->path);
    free(self->data_path);
    self->cursor->free(self->cursor);
    self->locker->free(self->locker);
    free(self);
}

