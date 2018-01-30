from ctypes import *
from pathlib import Path
from os import chdir

class LibrariesInfo(object):

    def __init__(self, root_path, plug_path, libs_extension):
        self.root_path = root_path
        self.plug_path = plug_path
        self.libs_extension = libs_extension

    def get_full_library_name(self, name):
        return str(Path(self.root_path + name + self.libs_extension).resolve())

class LibrariesLoader(object):    

    def __init__(self, root_path, plug_path, libs_extension):
        self.info = LibrariesInfo(root_path, plug_path, libs_extension)

    def load_all(self):
        chdir(str(Path(self.info.root_path).resolve()))
        self.lib = WinDLL(self.info.get_full_library_name('wot_stream'), RTLD_GLOBAL)

class WoTStream(object):

    def __init__(self, lib):
        self.lib = lib

    def initialize(self):
        self.lib.initialize()

    def start_stream(self):
        self.lib.start_stream()

    def stop_stream(self):
        self.lib.stop_stream()

    def shutdown(self):
        self.lib.shutdown()

def main():

    loader = LibrariesLoader('../../build/Debug/', 'plugins/', '.dll')
    loader.load_all()

    mod_instance = WoTStream(loader.lib)
    mod_instance.initialize()
    input()

    mod_instance.start_stream()
    input()

    mod_instance.stop_stream()
    input()

    mod_instance.shutdown()
    input()

if __name__ == "__main__":
    main()