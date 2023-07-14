

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props){

    DtwObjectProps result = {0};

    if(props){
        result = *props;
    }


    if(!result.cache){
        result.cache = DTW_ALLOW_CACHE;
    }



    return result;

}

