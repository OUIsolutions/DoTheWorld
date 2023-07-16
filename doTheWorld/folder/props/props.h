
#define DTW_NOT_GARBAGE 1
#define DTW_ALLOW_GARBAGE 2


typedef struct DtwFolderProps{

    int garbage;

}DtwFolderProps;

DtwFolderProps DtwFolderProps_create_props(DtwFolderProps *props);


DtwFolderProps dtw_no_store= {
        .garbage =DTW_NOT_GARBAGE
};

DtwFolderProps dtw_store= {
        .garbage =DTW_ALLOW_GARBAGE
};


