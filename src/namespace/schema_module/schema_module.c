

DtwSchemaModule newDtwSchemaModule(){
    DtwSchemaModule  self = {0};
    self.find_by_primary_key_with_binary = DtwSchema_find_by_primary_key_with_binary;
    self.find_by_primary_key_with_string = DtwSchema_find_by_primary_key_with_string;
    self.new_insertion = DtwSchema_new_insertion;
    self.get_values =DtwSchema_get_values;
    self.add_primary_key = DtwSchema_add_primary_key;
    self.newSchema = newDtwSchema;
    self.free = DtwSchema_free;
    return  self;
}