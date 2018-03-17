#!/usr/bin/env python

import pdb

def f1(some_arg):
    print some_arg
    some_other_arg = some_arg + 1
    return f2(some_other_arg)

def f2(some_arg):
    pdb.set_trace()
    print some_arg
    some_other_arg = some_arg + 1
    return f3(some_other_arg)

def f3(some_arg):
    print some_arg
    some_other_arg = some_arg + 1
    return f4(some_other_arg)

def f4(some_arg):
    print some_arg
    some_other_arg = some_arg + 1
    return some_other_arg

if __name__ == "__main__":
    print "First line of code!"
    f1(1)
    print "Last line of code!"
