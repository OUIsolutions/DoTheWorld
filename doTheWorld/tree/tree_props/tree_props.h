
#define DTW_NOT_MIMIFY 1
#define DTW_MIMIFY 2

#define DTW_NOT_PRESERVE 1
#define DTW_PRESERVE 2

typedef struct DtwTreeProps{
   int minification;
   int content;
   int path_atributes;
   int hadware_data;
   int content_data;
   int ignored_elements;

}DtwTreeProps;



DtwTreeProps DtwJsonTreeProps_format_props( DtwTreeProps *props);
