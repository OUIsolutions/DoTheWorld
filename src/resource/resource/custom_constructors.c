

DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path){
    long  size = dtw_get_total_itens_of_dir(self->path);
    if(size < 0){
        size = 0;
    }
    while(true){

        char path[300] ={0};
        if(end_path){
            sprintf(path,"%ld%s",size,end_path);
        }
        else{
            sprintf(path,"%ld",size);
        }
        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }
        size = size+1;
    }
}


DtwResource * DtwResource_sub_resource_now(DtwResource *self, const char *end_path){

    bool empty_already_exist = false;


    while(true){

        long now = dtw_get_time();
        char *time = dtw_convert_unix_time_to_string(now);
        char path[1000] ={0};

        if(empty_already_exist){
            char *token = DtwRandonizer_generate_token(self->root_props->randonizer,10);
            sprintf(path,"%s--%s",time,token);
            free(token);
        }
        else{
            sprintf(path,"%s",time);
        }
        free(time);

        if(end_path){
            strcat(path,end_path);
        }

        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }
        empty_already_exist = true;
    }
}


DtwResource * DtwResource_sub_resource_now_in_unix(DtwResource *self, const char *end_path){
    bool empty_already_exist = false;

    while(true){

        long now = dtw_get_time();
        char path[1000] ={0};

        if(empty_already_exist){
            char *token = DtwRandonizer_generate_token(self->root_props->randonizer,10);
            sprintf(path,"%ld--%s",now,token);
            free(token);
        }
        else{
            sprintf(path,"%ld",now);
        }

        if(end_path){
            strcat(path,end_path);
        }

        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }
        empty_already_exist = true;
    }
}

DtwResource * DtwResource_sub_resource_random(DtwResource *self, const char *end_path){

    while(true){

        char path[1000] ={0};
        char *token = DtwRandonizer_generate_token(self->root_props->randonizer,15);
        sprintf(path,"%s",token);
        free(token);

        if(end_path){
            strcat(path,end_path);
        }

        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }

    }
}


DtwSchema * DtwResource_sub_schema(DtwResource *self, const char *name){
    DtwSchema *schema = (DtwSchema*) malloc(sizeof(DtwSchema));
    *schema = (DtwSchema){0};

    //make both reference each other
    DtwResource *master =DtwResource_sub_resource(self,"%s",name);
    master->schema = schema;
    schema->master = master;

    schema->master->schema = schema;
    schema->values_resource = DtwResource_sub_resource(self,"%s",DTW_SCHEMA_VALUES_NAME);
    schema->index_resource = DtwResource_sub_resource(self,"%s",DTW_SCHEMA_INDEX_NAME);
    schema->primary_keys = newDtwStringArray();
    return schema;
}