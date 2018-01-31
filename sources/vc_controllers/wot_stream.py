from ctypes import *
from pathlib import Path
from os import chdir

class LibrariesLoader(object):    

    def __init__(self, path, name):
        self.path = str(Path(path).resolve())
        self.name = self.path + '\\' + name

    def load(self):
        chdir(self.path)
        self.lib = WinDLL(self.name, RTLD_GLOBAL)

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

    loader = LibrariesLoader('../../build/Debug', 'wot_stream.dll')
    loader.load()

    mod_instance = WoTStream(loader.lib)
    mod_instance.initialize()
    input()

    mod_instance.start_stream()
    input()

    mod_instance.stop_stream()
    input()

    mod_instance.shutdown()

if __name__ == "__main__":
    main()