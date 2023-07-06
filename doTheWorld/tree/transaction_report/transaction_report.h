
typedef struct DtwTreeTransactionReport{
    struct DtwStringArray *write;
    struct DtwStringArray *modify;
    struct DtwStringArray *remove;
    void (*represent)(struct DtwTreeTransactionReport *report);
    void (*free)(struct DtwTreeTransactionReport *report);
}DtwTreeTransactionReport;

struct DtwTreeTransactionReport * newDtwTreeTransactionReport();
void  DtwTreeTransactionReport_represent(struct DtwTreeTransactionReport *report);
void  DtwTreeTransactionReport_free(struct DtwTreeTransactionReport *report);