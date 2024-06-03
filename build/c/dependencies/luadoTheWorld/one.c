
#include <inttypes.h>

#include "dependecies.h"
#include "declaration.h"
#include "definition.h"


void start_lua_props(LuaCEmbed *l){

    lua.add_callback(l,LOAD_FILE,load_file);
    lua.add_callback(l,WRITE_FILE,write_file);
    lua.add_callback(l,COPY_ANY_OVERWRITING,copy_any_overwriting);
    lua.add_callback(l,COPY_ANY_MERGING,copy_any_merging);
    lua.add_callback(l,MOVE_ANY_OVERWRITING,move_any_overwriting);
    lua.add_callback(l,MOVE_ANY_MERGING,move_any_merging);
    lua.add_callback(l,REMOVE_ANY,remove_any);
    lua.add_callback(l,LIST_FILES,list_files);
    lua.add_callback(l,LIST_FILES_RECURSIVELY,list_files_recursively);
    lua.add_callback(l,LIST_DIRS,list_dirs);
    lua.add_callback(l,LIST_DIRS_RECURSIVELY,list_dirs_recursively);
    lua.add_callback(l,LIST_ALL,list_all);
    lua.add_callback(l,LIST_ALL_RECURSIVELY,list_all_recursively);
    lua.add_callback(l,BBASE_64_ENCODE_FILE,base64_encode_file);
    lua.add_callback(l,BBASE_64_ENCODE,base64_encode);
    lua.add_callback(l,BBASE_64_DECODE,base64_decode);
    lua.add_callback(l,GENERATE_SHA,generate_sha);
    lua.add_callback(l,GENERATE_SHA_FROM_FILE,generate_sha_from_file);
    lua.add_callback(l, NEW_RESOURCE, create_resource);
    lua.add_callback(l,IS_BYTE_FUNC,is_byte);
    lua.add_callback(l,IS_DIR_FUNC,is_dir);
    lua.add_callback(l,IS_FILE_FUNC,is_file);
    lua.add_callback(l, IS_FILE_BYTE, is_binary);
    lua.add_callback(l,NEW_HASHER,create_hasher);
    lua.add_callback(l,GENERATE_SHA_FROM_FOLDER_BY_CONTENT,generate_sha_from_folder_by_content);
    lua.add_callback(l,GENERATE_SHA_FROM_FOLDER_BY_LAST_MODIFICATION,generate_sha_from_folder_by_last_modification);
    lua.add_callback(l, NEW_TRANSACTION, transaction_new_transaction);
    lua.add_callback(l,NEW_TRANSACTION_FROM_JSON_STRING,create_empty_transaction_from_json_string);
    lua.add_callback(l,NEW_TRANSACTION_FROM_JSON_FILE,create_empty_transaction_from_json_file);
    lua.add_callback(l,NEW_PATH,create_path);
    lua.add_callback(l,NEW_TREE,create_empty_tree);
    lua.add_callback(l,NEW_TREE_FROM_HARWARE,create_tree_from_hardware);

}

int start_dtw(lua_State *state){

    bool set_functions_as_public  = false;
    LuaCEmbed * l  = lua.newLuaLib(state,set_functions_as_public);
    start_lua_props(l);
    return lua.perform(l);
}
