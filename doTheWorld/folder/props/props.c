

DtwFolderProps DtwFolderProps_create_props(DtwFolderProps *props){

    DtwFolderProps result = {0};

    if(props){
        result = *props;
    }

    if(!result.garbage){
        result.garbage = DTW_ALLOW_GARBAGE;
    }


    return result;

}

