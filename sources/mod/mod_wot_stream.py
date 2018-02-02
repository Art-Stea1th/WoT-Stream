import sys
import os

from ctypes import *

current_path = os.path.dirname(os.path.abspath(__file__))
dbg_path = os.path.abspath(current_path + '/../../build/Debug/')

print dbg_path
#ctypes_path = os.path.join(current_path, 'ctypes')

class WoTStreamController(object):

    def __init__(self, lib_full_name):
        self.lib = WinDLL(lib_full_name, RTLD_GLOBAL)

    def initialize(self):
        self.lib.initialize()

    def start_stream(self):
        self.lib.start_stream()

    def stop_stream(self):
        self.lib.stop_stream()

    def shutdown(self):
        self.lib.shutdown()

def main():

    lib_path = '../../build/Debug/'
    lib_name = 'wot_stream.dll'

    lib_full_path = os.path.abspath(lib_path)
    lib_full_name = os.path.abspath(lib_path + '/' + lib_name)

    os.chdir(str(lib_full_path))

    controller = WoTStreamController(lib_full_name)
    controller.initialize()
    raw_input()

    controller.start_stream()
    raw_input()

    controller.stop_stream()
    raw_input()

    controller.shutdown()

if __name__ == "__main__":
    main()