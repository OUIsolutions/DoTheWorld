//
typedef struct DtwObject{

    char *path;


}DtwObject;

DtwObject * newDtwObject(const char *path,const char *name);

void DtwObject_set_long(DtwObject *self, long value);
void DtwObject_set_float(DtwObject *self, float value);
void DtwObject_set_string(DtwObject *self, float value);

DtwObject * DtwObject_sub_object(DtwObject *self,char *)
