import CToolKit as ct

def test_loading_string():
    out_put = ct.compile_project('gcc','unit_testing/io/loading_string.c')
    ct.test_binary_with_valgrind(out_put)

def test_io_operations():
    test_loading_string()