
DtwLockerModule newDtwLockerModule(){
    DtwLockerModule  self = {0};
    self.newLocker = newDtwLocker;
    self.create_shared_file = DtwLocker_create_shared_file;
    self.lock = DtwLocker_lock;
    self.unlock = DtwLocker_unlock;
    self.free = DtwLocker_free;
    return self;
}