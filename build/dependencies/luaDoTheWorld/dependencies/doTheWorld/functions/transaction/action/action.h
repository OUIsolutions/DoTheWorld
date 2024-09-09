#include "../unique.declaration_requirements.h"

DtwActionTransaction *newDtwActionTransaction();

DtwJsonTransactionError * private_dtw_validate_json_action_transaction(cJSON *json_obj);


DtwActionTransaction * private_DtwActionTransaction_parse_json_object(cJSON *json_obj);


DtwActionTransaction * DtwActionTransaction_write_any(const char *source,unsigned  char *content,long size,bool is_binary);

DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_move_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source);

short DtwActionTransaction_convert_action_to_integer(char *action);


const char * DtwActionTransaction_convert_action_to_string(int action);


cJSON *  private_DtwActionTransaction_create_json_object(DtwActionTransaction* self);


void DtwActionTransaction_commit(DtwActionTransaction* self,const char *path);

void DtwActionTransaction_represent(DtwActionTransaction* self);

void DtwActionTransaction_free(DtwActionTransaction* self);
