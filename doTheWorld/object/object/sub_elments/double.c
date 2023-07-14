


double DtwObject_get_double(struct DtwObject *self, const char *name){

    char *result = self->get_string(self,name,&dtw_no_store);

    if(result){

        double result_converted;
        int test = sscanf(result,"%lf",&result_converted);
        free(result);
        if(test == 0){
            self->error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;

    }
    return 0;
}



void DtwObject_set_double(struct DtwObject *self,const char *name, double value){
    char result[20] = {0};
    sprintf(result,"%f",value);
    self->set_string(self,name,result,NULL);
}
//
// Created by jurandi on 06-07-2023.
//
