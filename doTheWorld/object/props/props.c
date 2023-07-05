

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props){

    DtwObjectProps result = {0};
    if(props){
        result = *props;
    }

    if(!result.garbage){
        result.garbage =DTW_ALLOW_GARBAGE;
    }

    if(!result.cache){
        result.cache = DTW_ALLOW_CACHE;
    }

    if(!result.transaction){
        result.transaction = DTW_SET_AS_ACTION;
    }
    if(!result.update_cache){
        result.update_cache = DTW_NOT_UPDATE_CACHE;
    }

    return result;

}

