from ctypes import cdll
from pathlib import Path

class WoTStream:

    def __init__(self, dll_path_string):
        lib = cdll.LoadLibrary(dll_path_string) # OSError: [WinError 126] The specified module could not be found

    def initialize():
        lib.initialize()

    def start_stream():
        lib.start_stream()

    def stop_stream():
        lib.stop_stream()

    def shutdown():
        lib.shutdown()


def main():

    dll_path = Path('../../build/Debug/bin/32bit/wot_stream.dll').resolve()

    if dll_path.exists():

        dll_path_resolved_string = str(dll_path)

        print(dll_path_resolved_string)

        wot_stream = WoTStream(dll_path_resolved_string)
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