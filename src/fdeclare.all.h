//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.typesm.h"
//silver_chain_scope_end
//fdefine.base64.c

char *dtw_base64_encode(unsigned char *data, long input_length) ;


unsigned char *dtw_base64_decode(const char *data, long *output_length) ;



char *dtw_convert_binary_file_to_base64(const char *path);
//fdefine.sha256.c




char * calc_sha_256_returning_string(const void *input, size_t len)
;

void  calc_sha_256_from_string(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *input)
;

char * calc_sha_256_from_string_returning_string(const char *input)
;

int calc_sha_256_from_file(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *filename)
;

char * calc_sha_256_from_file_returning_string(const char *filename)
;
char * sha256_open_file(const char *filename, int *size);
//fdefine.extras.c



char * dtw_generate_sha_from_file(const char *path);

char * dtw_generate_sha_from_any(void *anything , long size);

char * dtw_generate_sha_from_string(const char *string);


long int dtw_get_entity_last_motification_in_unix(const char *path);

char * dtw_convert_unix_time_to_string(long int unix_time);

char * dtw_get_entity_last_motification_in_string(const char *path);

const char * private_dtw_convert_action_to_string(short action);

short private_dtw_convert_string_to_action(const char *action);

void private_dtw_add_end_bar_to_dirs_string_array(struct DtwStringArray * dirs);



struct DtwStringArray* private_dtw_remove_start_path(struct DtwStringArray *paths,const char *rm_path);


long dtw_get_time();
long private_dtw_convert_index(long index,long size);

char *dtw_convert_binary_to_hex(unsigned char *value,long size);


unsigned char *dtw_convert_hex_to_binary(const char *value,long *out_size);//fdefine.io.c






void dtw_create_dir_recursively(const char *path);
char *dtw_get_absolute_path(const char *path);
char *dtw_get_current_dir();



bool dtw_remove_any(const char* path) ;



unsigned char *dtw_load_any_content(const char * path,long *size,bool *is_binary);


char *dtw_load_string_file_content(const char * path);


unsigned char *dtw_load_binary_content(const char * path,long *size);


bool dtw_write_any_content(const char *path,unsigned  char *content,long size);


bool dtw_write_string_file_content(const char *path,const char *content);


int dtw_entity_type(const char *path);


int dtw_complex_entity_type(const char *path);

long dtw_get_total_itens_of_dir(const char *path);

const char *dtw_convert_entity(int entity_type);

bool dtw_copy_any(const char* src_path,const  char* dest_path,bool merge) ;

bool dtw_move_any(const char* src_path, const char* dest_path,bool merge) ;
//fdefine.string_functions.c



void private_dtw_remove_double_bars_from_string_array(struct DtwStringArray*path);

char *dtw_concat_path(const char *path1, const char *path2);

char * private_dtw_format_vaarg(const char *expresion, va_list args);

char *private_dtw_format_path(const char *path);


char * private_dtw_sub_str(const char *str, long start,long end);


bool dtw_starts_with(const char *string, const char *prefix);

bool dtw_ends_with(const char *string, const char *suffix);

char *private_dtw_replace_string_once(const char *target, const char *old_element, const char *new_element) ;

char* dtw_replace_string(const char *target, const char *old_element, const char *new_element) ;



char *private_dtw_change_beginning_of_string(const char *target,int start_element_to_remove_size, const char *new_element) ;



char *private_dtw_realoc_formatting(char *ptr,const char *format,...);
char *private_dtw_formatt(const char *format,...);
bool dtw_is_string_at_point(
        const char *str,
        long str_size,
        const char *target,
        long target_size,
        long target_point
        );

long  dtw_index_of_string(const char *str,const char *element);

double private_dtw_convert_string_to_number(const char *num, bool *its_a_number);
//fdefine.listage_wrappers.c




 DtwStringArray * dtw_list_files(const char *path, bool concat_path);

 DtwStringArray * dtw_list_dirs(const char *path, bool concat_path);

 DtwStringArray *  dtw_list_all(const char *path,  bool concat_path);
//fdefine.multidimension_listage.c



 DtwStringArray * dtw_list_dirs_recursively(const char *path,bool concat_path);



 DtwStringArray *  dtw_list_files_recursively(const char *path,bool concat_path);


 DtwStringArray * dtw_list_all_recursively(const char *path,bool concat_path);
//fdefine.numeral_io.c



long dtw_load_long_file_content_setting_error(const char *path,int *error);


long dtw_load_long_file_content(const char * path);


double dtw_load_double_file_content_setting_error(const char * path, int *error);


double dtw_load_double_file_content(const char * path);


bool dtw_load_bool_file_content_setting_error(const char * path, int *error);


bool dtw_load_bool_file_content(const char * path);



void dtw_write_long_file_content(const char *path, long value);


void dtw_write_double_file_content(const char *path,double value);


void dtw_write_bool_file_content(const char *path, bool value);
//encryption/fdefine.aesCBC_encryption.c



void privteDtwAES_CBC_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

void privteDtwAES_CBC_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size);
DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface_str(const char* key,const char *iv);
//encryption/fdefine.aesECB_encryption.c

void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface_str(const char* key);//hash/fdefine.hash.c








DtwHash * newDtwHash();

bool  DtwHash_digest_any(DtwHash *self,unsigned char *content,long size);

bool  DtwHash_digest_string(DtwHash * self, const char *content);

void DtwHash_digest_long(DtwHash * self,long content);

void DtwHash_digest_double(DtwHash * self,double content);

void DtwHash_digest_bool(DtwHash * self,bool content);

bool  DtwHash_digest_file(DtwHash * self, const char *path);

bool  DtwHash_digest_entity_last_modification(DtwHash * self, const char *path);


bool  DtwHash_digest_string_array(DtwHash *self,DtwStringArray *element);

bool  DtwHash_digest_string_array_last_modifications(DtwHash *self,DtwStringArray *element);

bool DtwHash_digest_string_array_last_modifications_adding_name(DtwHash *self,DtwStringArray *element);


bool DtwHash_digest_string_array_content(DtwHash *self,DtwStringArray *element);

bool DtwHash_digest_string_array_content_adding_name(DtwHash *self,DtwStringArray *element);


bool DtwHash_digest_folder_by_last_modification(DtwHash *self,const char *path);

bool DtwHash_digest_folder_by_content(DtwHash *self,const char *path);

void  DtwHash_free(DtwHash *self);
//path/fdefine.index.c



int DtwPath_get_total_dirs(DtwPath *self);

char *DtwPath_get_sub_dirs_from_index(DtwPath *self, int start, int end);



int private_dtw_count_dirs_before(const char *dirs,int index);

void DtwPath_insert_dir_at_index(DtwPath *self, int index, const char *dir);



void DtwPath_remove_sub_dirs_at_index(DtwPath *self, int start, int end);
//path/fdefine.meta.c



void DtwPath_insert_dir_after(DtwPath *self,const char *str,const char *dir);

void DtwPath_insert_dir_before(DtwPath *self,const char *str,const char *dir);

void DtwPath_remove_sub_dirs_at(DtwPath *self,const char *str);
//path/fdefine.getters.c




char * DtwPath_get_name(struct DtwPath *self);
char * DtwPath_get_extension(struct DtwPath *self);

char * DtwPath_get_full_name(struct DtwPath *self);

char * DtwPath_get_dir(struct DtwPath *self);

char * DtwPath_get_path(struct DtwPath *self);
//path/fdefine.setters.c




void DtwPath_set_extension(struct DtwPath *self, const char *extension);


void DtwPath_set_name(struct DtwPath * self, const char * name);



void DtwPath_set_full_name(struct DtwPath * self, const char * full_name);


void DtwPath_set_dir(struct DtwPath *self, const char *dir);


void DtwPath_set_path(struct DtwPath *self, const char *target_path) ;


void DtwPath_add_start_dir(struct DtwPath *self, const char *start_dir);

void DtwPath_add_end_dir(struct DtwPath *self, const char *end_dir);

void DtwPath_replace_dirs(DtwPath *self,const char *str,const char *dir);
//path/fdefine.basic.c




struct DtwPath * newDtwPath(const char *path) ;
bool DtwPath_changed(struct DtwPath *self);




void DtwPath_represent(struct DtwPath *self);



void DtwPath_free(struct DtwPath *self) ;
//string_array/fdefine.string_array.c




struct DtwStringArray * newDtwStringArray();

int DtwStringArray_find_position( DtwStringArray *self, const char *string);


void DtwStringArray_set_value( DtwStringArray *self, int index, const char *value);
void DtwStringArray_append_getting_ownership( DtwStringArray *self, char *string);

// Function prototypes
void DtwStringArray_append( DtwStringArray *self, const  char *string);

void DtwStringArray_pop( DtwStringArray *self, int position);

void DtwStringArray_merge( DtwStringArray *self,  DtwStringArray *other);


void DtwStringArray_represent( DtwStringArray *self);

int private_dtw_string_cmp(const void *a, const void *b);

void DtwStringArray_sort(struct DtwStringArray *self) ;

 DtwStringArray * DtwStringArray_clone(DtwStringArray *self);

char * privateDtwStringArray_append_if_not_included(DtwStringArray *self,char *value);
void DtwStringArray_free(struct DtwStringArray *self);
//randonizer/fdefine.randonizer.c






DtwRandonizer * newDtwRandonizer();

int DtwRandonizer_generate_num(DtwRandonizer *self,int max) ;
char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);

void DtwRandonizer_free(struct DtwRandonizer *self);
//monodimension_listage/fdefine.monodimension_listage_win32.c



#ifdef _WIN32


bool private_dtw_verify_if_add(const int expected_type, WIN32_FIND_DATAA entry);

bool private_dtw_verify_if_skip(WIN32_FIND_DATAA *entry);

struct DtwStringArray *  dtw_list_basic(const char *path,int expected_type,bool concat_path);
#endif
//monodimension_listage/fdefine.monodimension_listage_linux.c




#if defined(__linux__) || defined(__APPLE__)

bool private_dtw_verify_if_add(const int expected_type, int d_type);
bool private_dtw_verify_if_skip(struct dirent *entry);

struct DtwStringArray * dtw_list_basic(const char *path,int expected_type,bool concat_path);

#endif
//tree/tree/fdefine.listage.c



//listages
 DtwStringArray *DtwTree_list_files( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_dirs( DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_files_recursively( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_dirs_recursively( DtwTree *self, const char *path,bool concat_path);


 DtwStringArray *DtwTree_list_all_recursively( DtwTree *self, const char *path,bool concat_path);
//tree/tree/fdefine.json_tree.c




bool DtwTree_loads_json_tree(struct DtwTree *self, const char *all_tree);


bool DtwTree_loads_json_tree_from_file( DtwTree *self, const char *path);

char * DtwTree_dumps_tree_json( DtwTree *self, DtwTreeProps  props);

void  DtwTree_dumps_tree_json_to_file(struct DtwTree *self, const char *path, DtwTreeProps  props);
//tree/tree/fdefine.tree_finding.c



struct DtwTreePart *DtwTree_find_tree_part_by_function(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part,void *args),
        void *args
);

struct DtwTree *DtwTree_filter(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
);


 DtwTree *DtwTree_map(DtwTree *self,DtwTreePart *(*caller)( DtwTreePart *part));


 DtwTreePart *DtwTree_find_tree_part_by_name( DtwTree *self, const char *name);

 DtwTreePart *DtwTree_find_tree_part_by_path( DtwTree *self, const char *path);
//tree/tree/fdefine.tree.c





struct  DtwTree * newDtwTree();


struct DtwTree *DtwTree_get_sub_tree(struct DtwTree *self, const char *path, bool copy_content);

void DtwTree_add_tree_part_referencing(struct DtwTree *self, struct DtwTreePart *tree_part) ;

void DtwTree_add_tree_part_copy( DtwTree *self,  DtwTreePart *tree_part);

void DtwTree_remove_tree_part(struct DtwTree *self, int position);

struct DtwTreeTransactionReport * DtwTree_create_report(struct DtwTree *self);


void DtwTree_add_tree_part_getting_onwership( DtwTree *self,  DtwTreePart *tree_part);



void DtwTree_represent( DtwTree *self);

void DtwTree_add_tree_parts_from_string_array( DtwTree *self,  DtwStringArray *paths,DtwTreeProps props);


void DtwTree_add_tree_from_hardware( DtwTree *self,const char *path, DtwTreeProps props);

void DtwTree_free( DtwTree *self);
void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self);

void DtwTree_insecure_hardware_write_tree(struct DtwTree *self);

void DtwTree_hardware_commit_tree(struct DtwTree *self);
//tree/transaction_report/fdefine.transaction_report.c




struct DtwTreeTransactionReport * newDtwTreeTransactionReport();

void  DtwTreeTransactionReport_represent(struct DtwTreeTransactionReport *report);

void  DtwTreeTransactionReport_free(struct DtwTreeTransactionReport *report);
//tree/json_error/fdefine.json_error.c



DtwJsonTreeError * newDtwJsonError();

DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_cJSON(cJSON *json_tree);

 DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_content(const char *content);




void DtwJsonTreeError_represent( DtwJsonTreeError *self);

void DtwJsonTreeError_free(struct DtwJsonTreeError *self);
//tree/tree_part/fdefine.hardware_tree_part.c








void DtwTreePart_load_content_from_hardware(struct DtwTreePart *self);



bool DtwTreePart_hardware_remove(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_write(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_modify(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_commit(struct DtwTreePart *self);
//tree/tree_part/fdefine.tree_part.c




void private_DtwTreePart_set_last_modification(DtwTreePart *self,long last_modification) ;
 DtwTreePart * newDtwTreePart(const char *path, DtwTreeProps props);
char *DtwTreePart_get_content_string_by_reference(struct DtwTreePart *self);

unsigned char *DtwTreePart_get_content_binary_by_reference(struct DtwTreePart *self);


  DtwTreePart * DtwTreePart_self_copy( DtwTreePart *self);

void DtwTreePart_set_any_content( DtwTreePart *self, unsigned char *content, long content_size, bool is_binary);

void DtwTreePart_set_string_content( DtwTreePart *self, const char *content);

void DtwTreePart_set_binary_content( DtwTreePart *self, unsigned char *content, long content_size);


char *DtwTreePart_get_content_sha( DtwTreePart *self);







void DtwTreePart_represent(struct DtwTreePart *self);


void DtwTreePart_free_content(struct DtwTreePart *self);
void DtwTreePart_free(struct DtwTreePart *self);

 DtwTreePart * newDtwTreePartEmpty(const char *path);


 DtwTreePart * newDtwTreePartLoading(const char *path);
//tree/tree_props/fdefine.tree_props.c



DtwTreeProps DtwTreeProps_format_props(DtwTreeProps props);
//encryption/aesCustomCBC_v1_encryption/fdefine.aesCustomCB_v1_enrcryption .c



DtwEncriptionInterface *newDtwAES_Custom_CBC_v1_interface(const char *key);
//encryption/encryption_interface/fdefine.custom_saves.c


bool private_DtwEncriptionInterface_write_any_content_custom_mode(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size,short mode);



unsigned char *private_DtwEncriptionInterface_load_any_content_custom_mode(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary,short mode);//encryption/encryption_interface/fdefine.encryption_interface_basic.c


DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);


unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);

void DtwEncriptionInterface_free(DtwEncriptionInterface *self);//encryption/encryption_interface/fdefine.encryption_interface_hex.c





char *DtwEncriptionInterface_encrypt_buffer_hex(DtwEncriptionInterface *self, unsigned char *value,long size);



unsigned char *DtwEncriptionInterface_decrypt_buffer_hex(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);


bool DtwEncriptionInterface_write_any_content_hex(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);

bool DtwEncriptionInterface_write_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name,const char *value);

unsigned char *DtwEncriptionInterface_load_any_content_hex(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);

char *DtwEncriptionInterface_load_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name);

//encryption/encryption_interface/fdefine.encryption_interface_files.c



bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);


bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value);


unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const char *file_name,long *out_size,bool *is_binary);




char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name);

//encryption/encryption_interface/fdefine.encryption_interface_b64.c


char *DtwEncriptionInterface_encrypt_buffer_b64(DtwEncriptionInterface *self, unsigned char *value,long size);

unsigned char *DtwEncriptionInterface_decrypt_buffer_b64(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);


bool DtwEncriptionInterface_write_any_content_b64(DtwEncriptionInterface *self,const char *file_name,unsigned char *value,long size);



bool DtwEncriptionInterface_write_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name,const char *value);



unsigned char *DtwEncriptionInterface_load_any_content_b64(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);




char *DtwEncriptionInterface_load_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name);

//encryption/aesRAW_encryption/fdefine.aesRAW_encryption.c


unsigned char * privateDtwAES_RAW_EncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long entry_size,long *out_size);

unsigned char *privateDtwAES_RAW_EncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long entry_size,long *out_size);

void  privateDtwAES_RAW_EncryptionInterface_free_obj(void *obj);


DtwEncriptionInterface *newDtwAES_RAW_EncryptionInterface(const uint8_t* key,int key_size);
//transaction/transaction/fdefine.transaction_parsment.c




DtwJsonTransactionError * dtw_validate_json_transaction(cJSON *json_entry);


DtwJsonTransactionError * dtw_validate_json_transaction_file(const char *filename);


DtwTransaction * newDtwTransaction_from_json(cJSON *json_entry);



DtwTransaction * newDtwTransaction_from_json_file(const char *filename);

cJSON * DtwTransaction_dumps_to_json(struct DtwTransaction *self);


void DtwTransaction_dumps_to_json_file(struct DtwTransaction *self,const char *filename);

void DtwTransaction_represent(struct DtwTransaction *self);
//transaction/transaction/fdefine.transaction.c




DtwTransaction * newDtwTransaction();

void DtwTransaction_set_transaction_as_encryption_object_owner(DtwTransaction *self);

void DtwTransaction_set_encryption(DtwTransaction *self,DtwEncriptionInterface *encryption,short encryiption_mode);

void DtwTransaction_append_action(struct DtwTransaction *self,struct DtwActionTransaction  *action);


void DtwTransaction_remove_from_index(DtwTransaction *self,long index);
void DtwTransaction_filter(DtwTransaction *self,bool (*callback)(DtwActionTransaction *action));

void DtwTransaction_remove_from_source(DtwTransaction *self,const char *source);


void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary);

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content);


void DtwTransaction_write_long(struct DtwTransaction *self,const char *path,long value);

void DtwTransaction_write_bool(struct DtwTransaction *self,const char *path,bool value);

void DtwTransaction_write_double(struct DtwTransaction *self,const char *path,double value);


void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_move_any_merging(struct DtwTransaction *self,const char *source,const char *dest);


void DtwTransaction_copy_any_merging(struct DtwTransaction *self,const char *source,const char *dest);


void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source);



void DtwTransaction_commit(struct DtwTransaction *self,const char *path);



void DtwTransaction_free(struct DtwTransaction *self);
//transaction/action/fdefine.action.c




DtwActionTransaction * newDtwActionTransaction();


DtwActionTransaction * DtwActionTransaction_write_any(DtwEncriptionInterface *encryption, short encryption_mode, const char *source, unsigned  char *content,long size,bool is_binary);


DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest);


DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest);
DtwActionTransaction * DtwActionTransaction_move_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source);



void DtwActionTransaction_commit(DtwActionTransaction* self,const char *path);


void DtwActionTransaction_free(DtwActionTransaction* self);
//transaction/action/fdefine.action_parsment.c



short DtwActionTransaction_convert_action_to_integer(char *action);

const char * DtwActionTransaction_convert_action_to_string(int action);

DtwJsonTransactionError * private_dtw_validate_json_action_transaction(cJSON *json_obj);


DtwActionTransaction * private_DtwActionTransaction_parse_json_object(cJSON *json_obj);

cJSON *  private_DtwActionTransaction_create_json_object(DtwActionTransaction* self);



void DtwActionTransaction_represent(DtwActionTransaction* self);
//transaction/json_error/fdefine.json_transaction_error.c







DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path);

void DtwJsonTransactionError_represent(struct DtwJsonTransactionError *self);

void DtwJsonTransactionError_prepend_path(struct DtwJsonTransactionError *self,char *path);


void DtwJsonTransactionError_free(struct DtwJsonTransactionError *self);
//namespace/encryption/fdefine.encryption_namespace.c


DtwEncryptionNamespace newDtwEncryptionNamespace();//namespace/hash_module/fdefine.hash_module.c




DtwHashModule newDtwHashModule();
//namespace/string_array_module/fdefine.string_array_module.c



DtwStringArrayModule newDtwStringArrayModule();
//namespace/namespace/fdefine.namespace.c



DtwNamespace newDtwNamespace();
//namespace/path_module/fdefine.path_module.c



DtwPathModule newDtwPathModule();
//namespace/randonizer_module/fdefine.randonizer_module.c




DtwRandonizerModule newDtwRandonizerModule();
//namespace/locker/fdefine.locker.c



DtwLockerModule newDtwLockerModule();
//namespace/schema_module/fdefine.schema_module.c




DtwSchemaModule newDtwSchemaModule();
//namespace/database_schema_module/fdefine.database_schema_module.c




DtwDatabaseSchemaModule newDtwDatabaseSchemaModule();
//lockers/multifile_locker/fdefine.multifile_locker.c





DtwMultiFileLocker *newDtwMultiFileLocker();




int  DtwMultiFIleLocker_lock(DtwMultiFileLocker *self, const char *element) ;

void DtwMultifileLocker_unlock(DtwMultiFileLocker *self, const  char *element);


void DtwMultiFileLocker_represemt(DtwMultiFileLocker *self);

void DtwMultiFileLocker_free(DtwMultiFileLocker *self);
//lockers/locker/fdefine.locker.c




DtwLocker *newDtwLocker();

int DtwLocker_lock(DtwLocker *self, const  char *element);

void DtwLocker_unlock(DtwLocker *self, const  char *element);

void DtwLocker_represemt(DtwLocker *self);

void DtwLocker_free(DtwLocker *self);
//resource/database_schema/fdefine.database_schema.c



DtwDatabaseSchema *private_newDtwDtatabaseSchema();


DtwSchema * privateDtwDtatabaseSchema_get_sub_schema(DtwDatabaseSchema *self,const char *name);

DtwSchema * DtwDtatabaseSchema_new_subSchema(DtwDatabaseSchema *self,const char *name);



void private_new_DtwDtatabaseSchema_free(DtwDatabaseSchema *self);
//resource/root_props/fdefine.root_props.c




privateDtwResourceRootProps *private_newDtwResourceRootProps();


void privateDtwResourceRootProps_free(privateDtwResourceRootProps *self);
//resource/resource_array/fdefine.resource_array.c





DtwResourceArray * newDtwResourceArray();


void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element);


DtwResource* DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name);



void DtwResourceArray_represent(DtwResourceArray *self);

void DtwResourceArray_free(DtwResourceArray *self);
//resource/schema/fdefine.schema.c



DtwSchema *private_newDtwSchema(const char *name);


DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name);

DtwSchema * DtwSchema_new_subSchema(DtwSchema *self,const char *name);


void DtwSchema_add_primary_key(DtwSchema *self,const char *name);

void private_newDtwSchema_free(DtwSchema *self);
//resource/resource/fdefine.loaders_and_unloaders.c




void DtwResource_unload(DtwResource *self);

void DtwResource_load(DtwResource *self);
void DtwResource_load_if_not_loaded(DtwResource *self);
//resource/resource/fdefine.custom_constructors.c




DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path);


DtwResource * DtwResource_sub_resource_now(DtwResource *self, const char *end_path);


DtwResource * DtwResource_sub_resource_now_in_unix(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_random(DtwResource *self, const char *end_path);
//resource/resource/fdefine.sub_resource_setters.c



void DtwResource_set_any_in_sub_resource(DtwResource *self,const char *key, unsigned char *element, long size,bool is_binary) ;

void DtwResource_set_binary_in_sub_resource(DtwResource *self,const char *key, unsigned char *element, long size);

void DtwResource_set_binary_sha_in_sub_resource(DtwResource *self, const char *key, unsigned  char *value, long size);


void DtwResource_set_string_sha_in_sub_resource(DtwResource *self, const char *key, const char *value);

void DtwResource_set_string_in_sub_resource(DtwResource *self, const char *key, const  char *element);

void DtwResource_set_long_in_sub_resource(DtwResource *self, const char *key, long element);

void DtwResource_set_double_in_sub_resource(DtwResource *self, const char *key, double element);

void DtwResource_set_bool_in_sub_resource(DtwResource *self,const char *key, bool element);
//resource/resource/fdefine.constructors_and_destructors.c




DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...);
DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...);

void DtwResource_free(DtwResource *self);
//resource/resource/fdefine.getters.c



unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary);

unsigned char *DtwResource_get_any_from_sub_resource(DtwResource *self, long *size, bool *is_binary,const char *format,...);

unsigned char *DtwResource_get_binary(DtwResource *self, long *size);

unsigned char *DtwResource_get_binary_from_sub_resource(DtwResource *self, long *size,const char *format,...);


char *DtwResource_get_string(DtwResource *self);


char *DtwResource_get_string_from_sub_resource(DtwResource *self,const char *format,...);


long DtwResource_get_long(DtwResource *self);


long DtwResource_get_long_from_sub_resource(DtwResource *self,const char *format,...);


double DtwResource_get_double(DtwResource *self);

double DtwResource_get_double_from_sub_resource(DtwResource *self,const char *format,...);


bool DtwResource_get_bool(DtwResource *self);

bool DtwResource_get_bool_from_sub_resource(DtwResource *self,const char *format,...);
//resource/resource/fdefine.destroy.c



void private_DtwResurce_destroy_primary_key(DtwResource *self) ;
void private_DtwResource_destroy_all_primary_keys(DtwResource *self);
void DtwResource_destroy(DtwResource *self);

void DtwResource_destroy_sub_resource(DtwResource *self, const char *key);
//resource/resource/fdefine.schema.c



bool private_DtwResource_its_a_pk(DtwResource *self);

void privateDtwResource_ensure_its_possible_to_sub_resource(DtwResource *self);


DtwResource * DtwResource_new_schema_insertion(DtwResource *self);

DtwResource  *DtwResource_find_by_name_id(DtwResource *self, const char *name);
DtwResource * DtwResource_find_by_primary_key_with_binary(DtwResource *self, const char *primary_key, unsigned  char *value, long size);



DtwResource * DtwResource_find_by_primary_key_with_string(DtwResource *self, const char *key, const char *value);


void DtwResource_dangerous_remove_schema_prop(DtwResource*self,const char *prop);


void DtwResource_dangerous_rename_schema_prop(DtwResource*self,const char *prop,const char *new_name);



DtwDatabaseSchema * DtwResource_newDatabaseSchema(DtwResource *self);
//resource/resource/fdefine.resource_array.c


#include <time.h>


DtwResourceArray * DtwResource_get_schema_values(DtwResource *self);


DtwResourceArray * DtwResource_sub_resources(DtwResource *self);
//resource/resource/fdefine.setters.c




void private_dtw_resource_set_primary_key(DtwResource *self, unsigned  char *element, long size);
void DtwResource_set_any(DtwResource *self, unsigned char *element, long size,bool is_binary);
void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);

void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_binary_sha(DtwResource *self, unsigned  char *value, long size);

void DtwResource_set_string_sha(DtwResource *self,const char *value);








void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_bool( DtwResource *self,bool element);
//resource/resource/fdefine.extras.c





bool DtwResource_error(DtwResource *self);

void DtwResource_set_encryption(DtwResource *self,DtwEncriptionInterface *encryption_interface,short mode);

int DtwResource_get_error_code(DtwResource *self);
char * DtwResource_get_error_path(DtwResource *self);


char * DtwResource_get_error_message(DtwResource *self);
void  DtwResource_clear_errors(DtwResource *self);


void  private_DtwResource_raise_error(DtwResource *self, int error_code, const char *format,...);

void DtwResource_rename(DtwResource *self,const char *new_name);

void DtwResource_rename_sub_resource(DtwResource *self,const char *old_name,const  char *new_name);

int DtwResource_lock(DtwResource *self);

void DtwResource_unlock(DtwResource *self);


void DtwResource_set_Resource_as_encryption_object_owner(DtwResource *self);
void DtwResource_commit(DtwResource *self);

long DtwResource_size(DtwResource *self);



DtwStringArray *DtwResource_list_names(DtwResource *self);

int DtwResource_type(DtwResource *self);
bool DtwResource_is_file(DtwResource *self);

const char * DtwResource_type_in_str(DtwResource *self);

void DtwResource_represent(DtwResource *self);
//namespace/resource_module/resource_module/fdefine.resource_module.c



DtwResourceModule newDtwResourceModule();
//namespace/resource_module/resource_array_module/fdefine.resource_array_module.c



DtwResourceArrayModule newDtwResourceArrayModule();
//namespace/tree_module/tree/fdefine.tree.c



DtwTreeModule newDtwTreeModule();
//namespace/tree_module/transaction_report/fdefine.transaction_report_module.c



DtwTreeTransactionReportModule newDtwTreeTransactionReportModule();
//namespace/tree_module/json_error/fdefine.json_error.c



DtwJsonTreeErrorModule newDtwJsonTreeErrorModule();
//namespace/tree_module/tree_part_module/fdefine.tree_part_module.c




DtwTreePartModule newDtwTreePartModule();
//namespace/transaction_module/json_error_module/fdefine.json_error_module.c



DtwJsonTransactionErrorModule newDtwJsonTransactionErrorModule();
//namespace/transaction_module/action/fdefine.action.c



DtwActionTransactionModule newDtwActionTransactionModule();
//namespace/transaction_module/transaction_module/fdefine.transaction_module.c




DtwTransactionModule newDtwTransactionModule();
//lockers/flock_locker/flock_locker/fdefine.flock_locker.c


#if defined(__linux__) || defined(__APPLE__)

DtwFlockLocker * newFlockLocker();
int  DtwFlockLocker_lock(DtwFlockLocker *self, const char *filename) ;

void private_FlockLocker_unlock_by_index(DtwFlockLocker *self, int index);
void DtwFlockLocker_unlock(DtwFlockLocker *self, const char *filename);
void  DtwFlockLocker_represent(DtwFlockLocker *self);
void  DtwFlockLocker_free(DtwFlockLocker *self);
#endif
//lockers/flock_locker/flockarray/flock_locked_element/fdefine.flock_locked_element.c

#if defined(__linux__) || defined(__APPLE__)



privateDtwFlockLockedElement * private_new_privateDtwFlockLockedElement(const char *filename, int file_descriptor);

void privateDtwFlockLockedElement_represent(privateDtwFlockLockedElement *self);
void privateDtwFlockLockedElement_free(privateDtwFlockLockedElement *self);
#endif
//lockers/flock_locker/flockarray/flock_array/fdefine.flock_array.c

#if defined(__linux__) || defined(__APPLE__)

privateDtwFlockArray * private_new_privateFlockArray();


int  privateDtwFlockArray_index_of(privateDtwFlockArray *self, const char *filename);
void privateDtwFlockArray_append(privateDtwFlockArray *self, const char *filename, int file_descriptor);

void privateDtwFlockArray_destroy_by_index(privateDtwFlockArray *self, int position);


void privateDtwFlockArray_represent(privateDtwFlockArray *self);

void privateDtwFlockArray_free(privateDtwFlockArray *self);
#endif
//resource/resource/iterables/forEach/fdefine.foreach.c




DtwResourceForeachProps DtwResource_create_foreach_props( void(*callback)(DtwResource *item, void *args));

void DtwResource_foreach(DtwResource *self,DtwResourceForeachProps props);

void DtwResource_schema_foreach(DtwResource *self,DtwResourceForeachProps props);
//resource/resource/iterables/map/default/fdefine.default.c



DtwResourceMapProps DtwResource_create_map_props(
    void *main_array,
    void(*append)(void *main_array_arg, void *item),
    void *(*callback)(DtwResource *item, void *args)
);

int  private_dtwResource_compare(const void *item1,const void*item2);

void DtwResource_map(DtwResource *self,DtwResourceMapProps props);
void DtwResource_schema_map(DtwResource *self,DtwResourceMapProps props);
//resource/resource/iterables/map/cJSON/map_cjson_object/fdefine.map_cjson_object.c



DtwResourcecJSONObjectMapProps DtwResource_create_cJSONObjectProps(
    cJSON *(*callback)(DtwResource *item, void *args),
    char *(*key_provider_callback)(DtwResource *item,void *args)
);

void  *private_dtw_cJSONObject_callback(DtwResource *item,void *args) ;

bool private_dtw_cJSONObject_filtrage(DtwResource *item,void *args) ;

int private_dtw_cJSONObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_cJSONObject(void* object, void *item);


cJSON *DtwResource_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);

cJSON *DtwResource_schema_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);
//resource/resource/iterables/map/cJSON/map_cjson_array/fdefine.map_cjson_array.c


DtwResourcecJSONArrayMapProps DtwResource_create_cJSONArrayMapProps(cJSON *(*callback)(DtwResource *item, void *args));

void  *private_dtw_cJSONArray_callback(DtwResource *item,void *args) ;

bool private_dtw_cJSONArray_filtrage(DtwResource *item,void *args) ;

int private_dtw_cJSONArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_cJSONArray_array(void* array, void *item);

cJSON *DtwResource_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);

cJSON *DtwResource_schema_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);
//resource/resource/iterables/map/CHash/map_chash_object/fdefine.map_chash_object.c

#ifdef DTW_ALLOW_CHASH


DtwResourceCHashObjectMapProps DtwResource_createCHashObjectMapProps(
    CHash *(*callback)(DtwResource *item, void *args),
    char* (*key_provider)(DtwResource *item, void *args_filter)
);


void  *private_dtw_CHashObject_callback(DtwResource *item,void *args) ;

bool private_dtw_CHashObject_filtrage(DtwResource *item,void *args) ;

int private_dtw_CHashObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item);


CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

CHash *DtwResource_schema_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);
#endif
//resource/resource/iterables/map/CHash/map_chash_array/fdefine.map_chash_array.c

#ifdef DTW_ALLOW_CHASH

DtwResourceCHashrrayMapProps  DtwResource_create_CHashrrayMapProps(    CHash *(*callback)(DtwResource *item, void *args));

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args) ;

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args) ;

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_CHashArray_array(void* array, void *item);

CHashArray *DtwResource_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);
CHashArray *DtwResource_schema_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);
#endif
