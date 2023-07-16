//
// Created by jurandi on 06-07-2023.
//

long DtwFolder_get_long_file(struct DtwFolder *self, const char *name){
    char *result = self->get_string_file(self, name, &dtw_no_store);

    if(result){
        long result_converted;
        int test = sscanf(result,"%li",&result_converted);
        free(result);
        if(test == 0){
            self->error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;
    }

    return 0;
}

void DtwFolder_set_long_file(struct DtwFolder *self, const char *name, long value){
    char result[20] = {0};
    sprintf(result,"%li",value);
    self->set_string_file(self, name, result);
}