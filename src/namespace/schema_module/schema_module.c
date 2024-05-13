

DtwSchemaModule newDtwSchemaModule(){
    DtwSchemaModule  self = {0};
    self.find_by_primary_key_with_binary = DtwSchema_find_by_primary_key_with_binary;
    self.find_by_primary_key_with_string = DtwSchema_find_by_primary_key_with_string;
    self.new_insertion = DtwSchema_new_insertion;
    self.get_values =DtwSchema_get_values;
    self.add_primary_key = DtwSchema_add_primary_key;
    self.newSchema = newDtwSchema;
    self.commit = DtwSchema_commit;
    self.find_by_nameID = DtwSchema_get_find_by_nameID;
    self.dangerous_remove_prop = DtwSchema_dangerours_remove_prop;
    self.dangerous_rename_prop = DtwSchema_dangerours_rename_prop;
    self.free = DtwSchema_free;
    return  self;
}