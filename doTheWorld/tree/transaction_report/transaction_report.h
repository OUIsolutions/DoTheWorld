
typedef struct DtwTransactionReport{
    struct DtwStringArray *write;
    struct DtwStringArray *modify;
    struct DtwStringArray *remove;
    void (*represent)(struct DtwTransactionReport *report);
    void (*free)(struct DtwTransactionReport *report);
}DtwTransactionReport;

struct DtwTransactionReport * newDtwTransactionReport();
void  DtwTransactionReport_represent(struct DtwTransactionReport *report);
void  DtwTransactionReport_free(struct DtwTransactionReport *report);