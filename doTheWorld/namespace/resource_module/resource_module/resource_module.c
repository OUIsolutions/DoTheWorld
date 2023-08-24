
DtwResourceModule newDtwResourceModule(){
    DtwResourceModule self = {0};
    self.newResource = new_DtwResource;
    self.load = DtwResource_load;
    self.unload = DtwResource_unload;
    self.sub_resource = DtwResource_sub_resource;
    self.sub_resource_ensuring_not_exist = DtwResource_sub_resource_ensuring_not_exist;
    self.lock =DtwResource_lock;
    self.destroy = DtwResource_destroy;

    self.get_any = DtwResource_get_any;
    self.get_json = DtwResource_get_json;
    self.get_string = DtwResource_get_string;
    self.get_binary = DtwResource_get_binary;
    self.get_double = DtwResource_get_double;
    self.get_long = DtwResource_get_long;
    self.get_bool = DtwResource_get_bool;

    self.set_json = DtwResource_set_json;
    self.set_binary = DtwResource_set_binary;
    self.set_string = DtwResource_set_string;
    self.set_long = DtwResource_set_long;
    self.set_double = DtwResource_set_double;
    self.set_bool = DtwResource_set_bool;


    self.list_names = DtwResource_list_names;
    self.type = DtwResource_type;
    self.type_in_str = DtwResource_type_in_str;
    self.commit =DtwResource_commit;
    self.represent = DtwResource_represent;
    self.rename = DtwResource_rename;
    self.free  = DtwResource_free;

    self.sub_resources = DtwResource_sub_resources;
    self.array = newDtwResourceArrayModule();

    return self;
}