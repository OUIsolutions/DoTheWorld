
DtwResourceModule newDtwResourceModule(){
    DtwResourceModule self = {0};
    self.newResource = new_DtwResource;
    self.load = DtwResource_load;
    self.unload = DtwResource_unload;
    self.sub_resource = DtwResource_sub_resource;
    self.sub_resource_loading = DtwResource_sub_resource_loading;
    self.sub_resource_not_loading = DtwResource_sub_resource_not_loading;
    self.lock =DtwResource_lock;
    self.destroy = DtwResource_destroy;
    self.set_binary = DtwResource_set_binary;
    self.set_string = DtwResource_set_string;
    self.set_long = DtwResource_set_long;
    self.set_double = DtwResource_set_double;
    self.set_bool = DtwResource_set_bool;

    self.list = DtwResource_list;

    self.type_in_str = DtwResource_type_in_str;
    self.commit =DtwResource_commit;
    self.represent = DtwResource_represent;
    self.rename = DtwResource_rename;
    self.free  = DtwResource_free;
    return self;
}