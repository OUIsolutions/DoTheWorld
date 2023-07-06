
#define DTW_NOT_CACHE 1
#define DTW_ALLOW_CACHE 2
#define DTW_NOT_GARBAGE 1
#define DTW_ALLOW_GARBAGE 2
#define DTW_NOT_REUPDATE_CACHE 1
#define DTW_UPDATE_CACHE 2


typedef struct DtwObjectProps{

    int cache;
    int garbage;
    int transaction;
    int update_cache;

}DtwObjectProps;

DtwObjectProps DtwObjectProps_create_props(DtwObjectProps *props);


DtwObjectProps dtw_no_store= {
        .garbage = DTW_NOT_GARBAGE,
        .cache =DTW_NOT_CACHE
};

DtwObjectProps execute_now = {
        .transaction = DTW_EXECUTE_NOW
};

DtwObjectProps execute_now_and_no_store = {
        .garbage = DTW_NOT_GARBAGE,
        .cache =DTW_NOT_CACHE,
        .transaction = DTW_EXECUTE_NOW
};

