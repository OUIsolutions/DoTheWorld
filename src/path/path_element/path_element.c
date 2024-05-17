
privateDtwPathElement * newprivateDtwPathElement(const char *value,int path_type){
    privateDtwPathElement *self = ( privateDtwPathElement *)malloc(sizeof(privateDtwPathElement));
    *self = (privateDtwPathElement){0};
    self->value = strdup(value);
    self->size = (int)strlen(value);
    self->path_type= path_type;
    return self;
}
void privateDtwPathElement_set_value(privateDtwPathElement *self,const char *value){
    free(self->value);
    self->size = (int)strlen(value);
    self->value = strdup(value);
}

void privateDtwPathElement_free(privateDtwPathElement *self){
    free(self->value);
    free(self);
}