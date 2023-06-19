

struct DtwTransactionReport * dtw_constructor_transaction_report(){
    struct DtwTransactionReport *new_report = (struct DtwTransactionReport *)malloc(sizeof(struct DtwTransactionReport));
    new_report->write = newDtwStringArray();
    new_report->modify = newDtwStringArray();
    new_report->remove = newDtwStringArray();
    new_report->represent = private_dtw_represent_transaction;
    new_report->free_transaction = private_dtw_free_transaction;
    return new_report;
}

void  private_dtw_represent_transaction(struct DtwTransactionReport *report){
    printf("Write:---------------------------------------\n");
    report->write->represent(report->write);
    printf("Modify:--------------------------------------\n");
    report->modify->represent(report->modify);
    printf("Remove:--------------------------------------\n");
    report->remove->represent(report->remove);
    puts("");
}

void  private_dtw_free_transaction(struct DtwTransactionReport *report){
    report->write->free(report->write);
    report->modify->free(report->modify);
    report->remove->free(report->remove);
    free(report);
}