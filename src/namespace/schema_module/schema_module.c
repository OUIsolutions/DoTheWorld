

DtwSchemaModule newDtwSchemaModule(){
        DtwSchemaModule  self = {0};
        self.find_by_primary_key_with_any = DtwSchema_find_by_primary_key_with_any;
        self.find_by_primary_key_with_string = DtwSchema_find_by_primary_key_with_string;
        self.get_values =DtwSchema_get_values;
        self.add_primary_key = DtwSchema_add_primary_key;
        self.newSchema = newDtwSchema;
        self.free = DtwSchema_free;
    return  self;
}