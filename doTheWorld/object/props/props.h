
#define DTW_NOT_GARBAGE 1
#define DTW_ALLOW_GARBAGE 2


typedef struct DtwObjectProps{

    int garbage;

}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);


DtwObjectProps dtw_no_store= {
        .garbage =DTW_NOT_GARBAGE
};

DtwObjectProps dtw_store= {
        .garbage =DTW_ALLOW_GARBAGE
};


