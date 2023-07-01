//
// Created by jurandi on 01-07-2023.
//

DtwTreeProps DtwTreeProps_format_props( DtwTreeProps *props){
    DtwTreeProps result = {0};

    if(props){
        result = *props;
    }
    if(!result.minification){
        result.minification = DTW_NOT_MIMIFY;
    }
    if(!result.content){
        result.content = DTW_PRESERVE;
    }
    if(!result.path_atributes){
        result.path_atributes = DTW_PRESERVE;
    }
    if(!result.hadware_data){
        result.hadware_data = DTW_PRESERVE;
    }
    if(!result.content_data){
        result.content_data = DTW_PRESERVE;
    }
    if(!result.ignored_elements){
        result.ignored_elements = DTW_NOT_PRESERVE;
    }
    return result;
}