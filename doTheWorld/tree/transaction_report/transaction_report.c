

struct DtwTreeTransactionReport * newDtwTreeTransactionReport(){
    struct DtwTreeTransactionReport *new_report = (struct DtwTreeTransactionReport *)malloc(sizeof(struct DtwTreeTransactionReport));
    new_report->write = newDtwStringArray();
    new_report->modify = newDtwStringArray();
    new_report->remove = newDtwStringArray();
    new_report->represent = DtwTreeTransactionReport_represent;
    new_report->free = DtwTreeTransactionReport_free;
    return new_report;
}

void  DtwTreeTransactionReport_represent(struct DtwTreeTransactionReport *report){
    printf("Write:---------------------------------------\n");
    report->write->represent(report->write);
    printf("Modify:--------------------------------------\n");
    report->modify->represent(report->modify);
    printf("Remove:--------------------------------------\n");
    report->remove->represent(report->remove);
    puts("");
}

void  DtwTreeTransactionReport_free(struct DtwTreeTransactionReport *report){
    report->write->free(report->write);
    report->modify->free(report->modify);
    report->remove->free(report->remove);
    free(report);
}