from ctypes import cdll
from pathlib import Path
from os import chdir

class WoTStream(object):

    def __init__(self, dll_path_string):
        #loader = WinDLL('Loader', RTLD_GLOBAL, None, False, False)
        self.lib = cdll.LoadLibrary(dll_path_string) # OSError: [WinError 126] The specified module could not be found #, RTLD_GLOBAL

    def initialize(self):
        self.lib.initialize()

    def start_stream(self):
        self.lib.start_stream()

    def stop_stream(self):
        self.lib.stop_stream()

    def shutdown(self):
        self.lib.shutdown()


def main():

    dll_path = '../../build/Debug/bin/32bit/'
    dll_name = 'wot_stream.dll'

    full_dll_path = Path(dll_path).resolve()
    full_dll_name = Path(dll_path + dll_name).resolve()


    if full_dll_name.exists():

        chdir(str(full_dll_path))

        string_dll_name = str(full_dll_name)


        wot_stream = WoTStream(string_dll_name)
        wot_stream.initialize()

        input()
        
        wot_stream.start_stream()

        input()
        
        wot_stream.stop_stream()
        wot_stream.shutdown()
    else:
        raise FileNotFoundError(dll_path)


if __name__ == "__main__":
    main()