#!/usr/bin/env python3

import sys

def cat(files):
    for fn in files:
        with open(fn) as f:
            for line in f:
                yield line.rstrip('\n')

def main():
    for line in  cat(sys.argv[1:]):
        print(line)

if __name__ == '__main__':
    main()
