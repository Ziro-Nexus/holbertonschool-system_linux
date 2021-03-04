""" write heap """

import sys

if __name__ == "__main__":
    if len(sys.argv != 4):
        exit(1)

    pid = int(sys.argv[1])
    to_search = str(sys.argv[2])
    to_replace = str(sys.argv[3])

    address = ""
    start = ""
    end = ""
    permission = ""

    try:
        with open("/proc/{}/maps".format(pid), "r") as maps:
            for line in maps.read().split('\n'):
                if line.split(' ')[-1] == "[heap]":
                    address = line.split('-')[0:2]
                    if len(address) != 2:
                        print("wrong addr format")
                        exit(1)
                    start = int(address[0], 16)
                    end = int(address[1].split(' ')[0], 16)
                    permission = address[1].split(' ')[1]
    except Exception as e:
        print(e)
        sys.exit(1)

    try:
        mem_file = open("/proc/{}/mem".format(pid), 'rb+')
        mem_file.seek(start)
        heap = mem_file.read(end - start)
        i = heap.index(bytes(to_search, "ASCII"))
        print("[*] Found '{}' at {:x}".format(to_search, i))
        print("[*] Writing '{}' at {:x}".format(to_replace, start + i))
        mem_file.seek(start + i)
        mem_file.write(bytes(to_replace, "ASCII"))
    except Exception as e:
        print(e)
        exit(1)
