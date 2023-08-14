
DtwPathModule newDtwPathModule(){
    DtwPathModule  self = {0};
    self.newPath = newDtwPath;
    self.changed =DtwPath_changed;
    self.get_full_name = DtwPath_get_full_name;
    self.get_name = DtwPath_get_name;
    self.get_extension = DtwPath_get_extension;
    self.get_path = DtwPath_get_path;
    self.get_dir = DtwPath_get_dir;

    self.set_extension = DtwPath_set_extension;
    self.set_name = DtwPath_set_name;
    self.set_dir = DtwPath_set_dir;
    self.set_full_name =DtwPath_set_full_name;
    self.set_path = DtwPath_set_path;

    self.add_start_dir =DtwPath_add_start_dir;
    self.add_end_dir = DtwPath_add_end_dir;
    self.represent = DtwPath_represent;
    self.free = DtwPath_free;

    return self;
}