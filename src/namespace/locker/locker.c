
DtwMultiFileLockerModule newDtwLockerModule(){
    DtwMultiFileLockerModule  self = {0};
    self.newLocker = newDtwMultiFileLocker;
    self.lock = DtwMultiFIleLocker_lock;
    self.unlock = DtwMultifileLocker_unlock;
    self.represemt = DtwMultiFileLocker_represemt;
    self.free = DtwMultiFileLocker_free;
    return self;
}