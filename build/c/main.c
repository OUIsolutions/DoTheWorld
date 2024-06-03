
#include "lua_code.h"
#include "dependencies/luaCEmbed/one.c"
#include "dependencies/doTheWorld/one.c"

LuaCEmbedNamespace lua;
DtwNamespace dtw;
#include "dependencies/luadoTheWorld/one.c"

int lua_exit = 0;

#include "callbacks/declaration.h"

#include "callbacks/definition.h"

void add_callbacks(LuaCEmbed *main_obj){
    LuaCEmbedTable *clib = lua.globals.new_table(main_obj,"clib");
    lua.tables.set_method(clib,"print",custom_print);
    lua.tables.set_method(clib,"exit",generate_exit);
    lua.tables.set_method(clib,"get_str_size",lua_get_str_size);
    lua.tables.set_method(clib,"get_char",lua_get_char);

}


int main(int argc,char *argv[]){
    lua  = newLuaCEmbedNamespace();
    dtw = newDtwNamespace();
    LuaCEmbed * main_obj = lua.newLuaEvaluation();
    add_callbacks(main_obj);
    start_dtw(main_obj->state);
    lua_setglobal(main_obj->state,"dtw");

    lua.set_timeout(main_obj,-1);
    lua.evaluate(main_obj,lua_code);
    if(lua.has_errors(main_obj)){
        char *error = lua.get_error_message(main_obj);
        if(strcmp(error,"") != 0){
            printf("%s\n",error);
        }
        lua.free(main_obj);
        return lua_exit;
    }
    lua.free(main_obj);
    return 0;
}