const char *lua_code= "\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x76\x65\x72\x69\x66\x79\x5f\x69\x66\x5f\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\x9\x69\x66\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x3d\x20\x74\x72\x75\x65\x20\x74\x68\x65\x6e\xa\x9\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x9\x65\x6e\x64\xa\x9\x6c\x6f\x63\x61\x6c\x20\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2d\x31\x29\xa\x20\x20\x20\x20\x69\x66\x20\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x3d\x3d\x20\x27\x5c\x5c\x27\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x63\x75\x72\x72\x65\x6e\x74\x5f\x63\x68\x61\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x29\xa\x20\x20\x20\x20\x69\x66\x20\x63\x75\x72\x72\x65\x6e\x74\x5f\x63\x68\x61\x72\x20\x3d\x3d\x20\x27\x22\x27\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x65\x6e\x64\xa\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x76\x65\x72\x69\x66\x79\x5f\x69\x66\x5f\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x28\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x2c\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x3d\x20\x66\x61\x6c\x73\x65\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x6c\x61\x73\x74\x5f\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2d\x32\x29\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2d\x31\x29\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x63\x75\x72\x72\x65\x6e\x74\x5f\x63\x68\x61\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x29\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x73\x63\x61\x70\x65\x20\x3d\x20\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x3d\x3d\x20\x27\x5c\x5c\x27\x20\x61\x6e\x64\x20\x6c\x61\x73\x74\x5f\x6c\x61\x73\x74\x5f\x63\x68\x61\x72\x20\x7e\x3d\x22\x5c\x5c\x22\xa\x20\x20\x20\x20\x69\x66\x20\x63\x75\x72\x72\x65\x6e\x74\x5f\x63\x68\x61\x72\x20\x3d\x3d\x20\x27\x22\x27\x20\x61\x6e\x64\x20\x73\x63\x61\x70\x65\x20\x3d\x3d\x20\x66\x61\x6c\x73\x65\x20\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x65\x6e\x64\xa\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x63\x68\x61\x72\x5f\x74\x6f\x5f\x66\x69\x6e\x61\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\xa\x20\x20\x20\x20\x69\x66\x20\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x65\x6e\x64\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x5f\x74\x6f\x5f\x66\x69\x6e\x61\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\xa\x20\x20\x20\x20\x69\x66\x20\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x65\x6e\x64\xa\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x69\x73\x5f\x69\x6e\x63\x6c\x75\x64\x65\x5f\x70\x6f\x69\x6e\x74\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\xa\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x49\x4e\x43\x4c\x55\x44\x45\x5f\x54\x45\x58\x54\x20\x20\x3d\x20\x22\x23\x69\x6e\x63\x6c\x75\x64\x65\x22\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x63\x6f\x6e\x74\x65\x6e\x74\x5f\x73\x69\x7a\x65\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x73\x74\x72\x5f\x73\x69\x7a\x65\x28\x63\x6f\x6e\x74\x65\x6e\x74\x29\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x73\x69\x7a\x65\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x73\x74\x72\x5f\x73\x69\x7a\x65\x28\x49\x4e\x43\x4c\x55\x44\x45\x5f\x54\x45\x58\x54\x29\xa\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x64\x65\x78\x20\x2b\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x73\x69\x7a\x65\x20\x3e\x3d\x20\x63\x6f\x6e\x74\x65\x6e\x74\x5f\x73\x69\x7a\x65\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x62\x75\x66\x66\x65\x72\x20\x3d\x20\x22\x22\xa\x20\x20\x20\x20\x66\x6f\x72\x20\x69\x3d\x69\x6e\x64\x65\x78\x2c\x69\x6e\x64\x65\x78\x20\x2b\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x73\x69\x7a\x65\x20\x2d\x31\x20\x64\x6f\xa\x20\x20\x20\x20\x9\x62\x75\x66\x66\x65\x72\x20\x3d\x20\x62\x75\x66\x66\x65\x72\x2e\x2e\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x29\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x62\x75\x66\x66\x65\x72\x20\x3d\x3d\x20\x49\x4e\x43\x4c\x55\x44\x45\x5f\x54\x45\x58\x54\xa\x65\x6e\x64\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x63\x68\x61\x72\x5f\x74\x6f\x5f\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x28\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x2c\x69\x73\x5f\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x65\x6e\x64\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x6d\x61\x6b\x65\x5f\x72\x65\x63\x75\x72\x73\x69\x76\x65\x5f\x63\x61\x6c\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\x9\x69\x66\x20\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x61\x6e\x64\x20\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x9\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x9\x65\x6e\x64\xa\x65\x6e\x64\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x61\x6e\x75\x6c\x61\x74\x65\x5f\x69\x6e\x63\x6c\x75\x73\x69\x6f\x6e\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x29\xa\x20\x20\x20\x20\x69\x66\x20\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x3d\x3d\x20\x66\x61\x6c\x73\x65\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x69\x66\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x29\x20\x3d\x3d\x20\x22\x3c\x22\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x9\x72\x65\x74\x75\x72\x6e\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x65\x6e\x64\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x61\x6c\x73\x65\xa\x65\x6e\x64\xa\x2d\x2d\x2d\x40\x70\x61\x72\x61\x6d\x20\x73\x74\x61\x72\x74\x5f\x70\x6f\x69\x6e\x74\x20\x73\x74\x72\x69\x6e\x67\xa\x2d\x2d\x2d\x40\x72\x65\x74\x75\x72\x6e\x20\x73\x74\x72\x69\x6e\x67\xa\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x47\x65\x6e\x65\x72\x61\x74\x65\x5f\x61\x6d\x61\x6c\x67\x61\x6d\x61\x74\x69\x6f\x6e\x28\x73\x74\x61\x72\x74\x5f\x70\x6f\x69\x6e\x74\x29\xa\xa\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x63\x6f\x6e\x74\x65\x6e\x74\x20\x3d\x20\x63\x6c\x69\x62\x2e\x6c\x6f\x61\x64\x5f\x73\x74\x72\x69\x6e\x67\x28\x73\x74\x61\x72\x74\x5f\x70\x6f\x69\x6e\x74\x29\xa\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x73\x69\x7a\x65\x20\x3d\x20\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x73\x74\x72\x5f\x73\x69\x7a\x65\x28\x63\x6f\x6e\x74\x65\x6e\x74\x29\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x3d\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x20\x3d\x20\x22\x22\xa\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x20\x3d\x20\x22\x22\xa\x20\x20\x20\x20\x66\x6f\x72\x20\x69\x3d\x31\x2c\x73\x69\x7a\x65\x20\x64\x6f\xa\x20\x20\x20\x20\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x20\x76\x65\x72\x69\x66\x79\x5f\x69\x66\x5f\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x20\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x9\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x20\x76\x65\x72\x69\x66\x79\x5f\x69\x66\x5f\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x68\x61\x72\x28\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x2c\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\xa\xa\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x63\x68\x61\x72\x5f\x74\x6f\x5f\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x28\x69\x73\x5f\x73\x74\x61\x72\x74\x5f\x73\x74\x72\x69\x6e\x67\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x20\x3d\x20\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x2e\x2e\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x29\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x5f\x74\x6f\x5f\x66\x69\x6e\x61\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x20\x3d\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x2e\x2e\x27\x22\x27\x2e\x2e\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x2e\x2e\x27\x22\x27\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x69\x6e\x63\x6c\x75\x64\x65\x5f\x70\x6f\x69\x6e\x74\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x9\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x3d\x20\x74\x72\x75\x65\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x61\x6e\x75\x6c\x61\x74\x65\x5f\x69\x6e\x63\x6c\x75\x73\x69\x6f\x6e\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x20\x3d\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x2e\x2e\x22\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x22\xa\x20\x20\x20\x20\x20\x20\x20\x20\x9\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x3d\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x6e\x63\x6c\x75\x64\x65\x5f\x63\x68\x61\x72\x5f\x74\x6f\x5f\x66\x69\x6e\x61\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x9\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x20\x3d\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x2e\x2e\x63\x6c\x69\x62\x2e\x67\x65\x74\x5f\x63\x68\x61\x72\x28\x63\x6f\x6e\x74\x65\x6e\x74\x2c\x69\x29\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x6d\x61\x6b\x65\x5f\x72\x65\x63\x75\x72\x73\x69\x76\x65\x5f\x63\x61\x6c\x6c\x28\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x2c\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x29\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x64\x69\x72\x20\x3d\x20\x63\x6c\x69\x62\x2e\x65\x78\x74\x72\x61\x63\x74\x5f\x64\x69\x72\x28\x73\x74\x61\x72\x74\x5f\x70\x6f\x69\x6e\x74\x29\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6c\x6c\x5f\x70\x61\x74\x68\x20\x3d\x20\x63\x6c\x69\x62\x2e\x63\x6f\x6e\x63\x61\x74\x5f\x70\x61\x74\x68\x28\x64\x69\x72\x2c\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x29\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x6c\x6f\x63\x61\x6c\x20\x61\x63\x75\x6d\x75\x6c\x61\x74\x65\x64\x20\x3d\x20\x47\x65\x6e\x65\x72\x61\x74\x65\x5f\x61\x6d\x61\x6c\x67\x61\x6d\x61\x74\x69\x6f\x6e\x28\x66\x75\x6c\x6c\x5f\x70\x61\x74\x68\x29\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x20\x3d\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\x2e\x2e\x20\x61\x63\x75\x6d\x75\x6c\x61\x74\x65\x64\x2e\x2e\x22\x5c\x6e\x22\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x9\x77\x61\x69\x74\x69\x6e\x67\x5f\x69\x6e\x63\x6c\x75\x64\x65\x20\x3d\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x20\x69\x73\x5f\x65\x6e\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x74\x68\x65\x6e\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x69\x6e\x73\x69\x64\x65\x5f\x73\x74\x72\x69\x6e\x67\x20\x3d\x20\x66\x61\x6c\x73\x65\xa\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x73\x74\x72\x69\x6e\x67\x5f\x62\x75\x66\x66\x65\x72\x20\x3d\x20\x22\x22\xa\x20\x20\x20\x20\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x65\x6e\x64\xa\xa\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x66\x69\x6e\x61\x6c\x5f\x74\x65\x78\x74\xa\x65\x6e\x64\xa\xa\xa\xa\x2d\x2d\x2d\x40\x63\x6c\x61\x73\x73\x20\x43\x6c\x69\x62\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x6c\x6f\x61\x64\x5f\x73\x74\x72\x69\x6e\x67\x20\x66\x75\x6e\x28\x70\x61\x74\x68\x3a\x73\x74\x72\x69\x6e\x67\x29\x3a\x73\x74\x72\x69\x6e\x67\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x67\x65\x74\x5f\x63\x68\x61\x72\x20\x66\x75\x6e\x28\x70\x61\x74\x68\x3a\x73\x74\x72\x69\x6e\x67\x2c\x69\x3a\x6e\x75\x6d\x62\x65\x72\x29\x3a\x73\x74\x72\x69\x6e\x67\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x70\x72\x69\x6e\x74\x20\x66\x75\x6e\x28\x76\x61\x6c\x75\x65\x3a\x62\x6f\x6f\x6c\x65\x61\x6e\x20\x7c\x20\x73\x74\x72\x69\x6e\x67\x20\x7c\x20\x6e\x75\x6d\x62\x65\x72\x29\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x67\x65\x74\x5f\x73\x74\x72\x5f\x73\x69\x7a\x65\x20\x66\x75\x6e\x28\x76\x61\x6c\x75\x65\x3a\x73\x74\x72\x69\x6e\x67\x29\x3a\x20\x6e\x75\x6d\x62\x65\x72\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x63\x6f\x6e\x63\x61\x74\x5f\x70\x61\x74\x68\x20\x66\x75\x6e\x28\x70\x61\x74\x68\x3a\x73\x74\x72\x69\x6e\x67\x2c\x70\x61\x74\x68\x5f\x74\x6f\x5f\x63\x6f\x6e\x63\x61\x74\x3a\x73\x74\x72\x69\x6e\x67\x29\x3a\x73\x74\x72\x69\x6e\x67\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x65\x78\x74\x72\x61\x63\x74\x5f\x64\x69\x72\x20\x66\x75\x6e\x28\x70\x61\x74\x68\x3a\x73\x74\x72\x69\x6e\x67\x29\x3a\x73\x74\x72\x69\x6e\x67\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x77\x72\x69\x74\x65\x5f\x66\x69\x6c\x65\x20\x66\x75\x6e\x28\x66\x69\x6c\x65\x6e\x61\x6d\x65\x3a\x73\x74\x72\x69\x6e\x67\x2c\x63\x6f\x6e\x74\x65\x6e\x74\x3a\x73\x74\x72\x69\x6e\x67\x29\xa\x2d\x2d\x2d\x40\x66\x69\x65\x6c\x64\x20\x67\x65\x74\x5f\x74\x69\x6d\x65\x20\x66\x75\x6e\x28\x29\x3a\x6e\x75\x6d\x62\x65\x72\xa\xa\x2d\x2d\x2d\x40\x74\x79\x70\x65\x20\x43\x6c\x69\x62\xa\x63\x6c\x69\x62\x20\x3d\x20\x63\x6c\x69\x62\xa\xa\xa\xa\x53\x54\x41\x52\x54\x5f\x50\x4f\x49\x4e\x54\x20\x3d\x20\x22\x73\x72\x63\x2f\x6f\x6e\x65\x2e\x63\x22\xa\x45\x4e\x44\x5f\x50\x4f\x49\x4e\x54\x20\x3d\x20\x22\x64\x6f\x54\x68\x65\x57\x6f\x72\x6c\x64\x2e\x68\x22\xa\xa\xa\x6c\x6f\x63\x61\x6c\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x6d\x61\x69\x6e\x28\x29\xa\xa\x20\x20\x6c\x6f\x63\x61\x6c\x20\x61\x6d\x61\x6c\x67\x61\x6d\x61\x74\x69\x6f\x6e\x5f\x72\x65\x73\x75\x6c\x74\x20\x3d\x20\x47\x65\x6e\x65\x72\x61\x74\x65\x5f\x61\x6d\x61\x6c\x67\x61\x6d\x61\x74\x69\x6f\x6e\x28\x53\x54\x41\x52\x54\x5f\x50\x4f\x49\x4e\x54\x29\xa\x20\x20\x20\x63\x6c\x69\x62\x2e\x77\x72\x69\x74\x65\x5f\x66\x69\x6c\x65\x28\x45\x4e\x44\x5f\x50\x4f\x49\x4e\x54\x2c\x61\x6d\x61\x6c\x67\x61\x6d\x61\x74\x69\x6f\x6e\x5f\x72\x65\x73\x75\x6c\x74\x29\xa\xa\xa\xa\x65\x6e\x64\xa\x6d\x61\x69\x6e\x28\x29\xa";