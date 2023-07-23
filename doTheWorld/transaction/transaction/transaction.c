

DtwTransaction * newDtwTransaction(){

    DtwTransaction *self = (DtwTransaction*) malloc(sizeof(DtwTransaction));

    self->write_any = DtwTransaction_write_any;
    self->write_string = DtwTransaction_write_string;
    self->move_any = DtwTransaction_move_any;
    self->copy_any = DtwTransaction_copy_any;
    self->delete_any = DtwTransaction_delete_any;
    self->free = DtwTransaction_free;

}
