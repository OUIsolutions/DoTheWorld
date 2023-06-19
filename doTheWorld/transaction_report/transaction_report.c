

struct DtwTransactionReport * newDtwTransactionReport(){
    struct DtwTransactionReport *new_report = (struct DtwTransactionReport *)malloc(sizeof(struct DtwTransactionReport));
    new_report->write = newDtwStringArray();
    new_report->modify = newDtwStringArray();
    new_report->remove = newDtwStringArray();
    new_report->represent = DtwTransactionReport_represent;
    new_report->free = DtwTransactionReport_free;
    return new_report;
}

void  DtwTransactionReport_represent(struct DtwTransactionReport *report){
    printf("Write:---------------------------------------\n");
    report->write->represent(report->write);
    printf("Modify:--------------------------------------\n");
    report->modify->represent(report->modify);
    printf("Remove:--------------------------------------\n");
    report->remove->represent(report->remove);
    puts("");
}

void  DtwTransactionReport_free(struct DtwTransactionReport *report){
    report->write->free(report->write);
    report->modify->free(report->modify);
    report->remove->free(report->remove);
    free(report);
}