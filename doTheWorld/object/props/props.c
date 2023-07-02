

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

    return result;

}


DtwObjectProps no_garbage = {
        .garbage = DTW_NOT_GARBAGE
};


DtwObjectProps no_cache= {
        .cache =DTW_NOT_CACHE
};

DtwObjectProps no_store= {
        .garbage = DTW_NOT_GARBAGE,
        .cache =DTW_NOT_CACHE
};

