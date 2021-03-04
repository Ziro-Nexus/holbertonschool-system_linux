#!/usr/bin/python3
"""Overwrites a string in a process' mem file"""

from sys import argv

use = "use: read_write_heap.py pid search_string to_replace"


def get_maps_file(pid):
    """doc"""
    start = stop = None
    try:
        with open("/proc/{:d}/maps".format(pid), "r") as file:
            for line in file:
                if line.endswith("[heap]\n"):
                    start, stop = \
                        [int(x, 16) for x in line.split(" ")[0].split("-")]
    except Exception as e:
        print(e) or exit(1)
    if not start or not stop:
        print("[ERROR] Heap address not found.") or exit(1)
    print("[*] Heap starts at {:02X}".format(start))
    return start, stop


def update_mem(pid, search_string, to_replace, start, stop):
    """doc"""
    try:
        with open("/proc/{:d}/mem".format(pid), "r+b") as f:
            f.seek(start)
            data = f.read(stop - start)
            print("[*] Read {:d} bytes".format(stop - start))
            offset = data.find(search_string.encode())
            if offset > -1:
                print("[*] String found at {:02X}"
                      .format(start + offset))
                f.seek(start + offset)
                n = f.write(to_replace.encode() + b'\x00')
                print("[*] {:d} bytes".format(n))
            else:
                print(
                    "String '{:s}' not found in heap."
                    .format(search_string))
                exit(1)
    except Exception as e:
        print(e) or exit(1)

if __name__ == "__main__":
    if len(argv) < 4 or len(argv[2]) < len(argv[3]):
        print(use) or exit(1)
    start, stop = get_maps_file(int(argv[1]))
    update_mem(int(argv[1]), argv[2], argv[3], start, stop)
