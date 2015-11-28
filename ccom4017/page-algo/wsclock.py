#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# wsclock.py

from sys import argv
memory = []


if __name__ == "__main__" and len(argv) == 4:
    main()

else:
    print("Usage: $ python %s <Number of memory page requests> <tau> <access file>" % argv[0])
