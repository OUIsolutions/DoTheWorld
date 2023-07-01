
#define DTW_NOT_MIMIFY 1
#define DTW_MIMIFY 2

#define DTW_HIDE 1
#define DTW_INCLUDE 2

typedef struct DtwJsonTreeProps{
   int minification;
   int content;
   int path_atributes;
   int hadware_data;
   int content_data;
   int ignored_elements;

}DtwJsonTreeProps;



DtwJsonTreeProps DtwJsonTreeProps_format_props(DtwJsonTreeProps *props);
