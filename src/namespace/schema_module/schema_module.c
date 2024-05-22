

DtwSchemaModule newDtwSchemaModule(){
    DtwSchemaModule  self = {0};
    self.sub_schema = DtwSchema_new_sub_schema;
    self.add_primary_key = DtwSchema_add_primary_key;

    return  self;
}