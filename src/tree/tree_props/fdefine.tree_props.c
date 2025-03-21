//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwTreeProps DtwTreeProps_format_props(DtwTreeProps props){
    DtwTreeProps result = props;

    if(!result.minification){
        result.minification = DTW_NOT_MIMIFY;
    }
    if(!result.content){
        result.content = DTW_INCLUDE;
    }
    if(!result.path_atributes){
        result.path_atributes = DTW_INCLUDE;
    }
    if(!result.hadware_data){
        result.hadware_data = DTW_INCLUDE;
    }
    if(!result.content_data){
        result.content_data = DTW_INCLUDE;
    }
    if(!result.ignored_elements){
        result.ignored_elements = DTW_HIDE;
    }
    return result;
}
