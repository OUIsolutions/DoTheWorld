

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props){

    DtwObjectProps result = {0};

    if(props){
        result = *props;
    }

    if(!result.garbage){
        result.garbage = DTW_ALLOW_GARBAGE;
    }


    return result;

}

