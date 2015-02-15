# CCOM4029 Assignment 1 Part C (Ad-hoc scanner)
# Raul Negron
# 801-13-4680

def lexer(s):

    # simple bool based error checking
    is_valid = True

    # the set of basic math operators
    operations_set = {'+', '-', '*', '/'}
    # the set of both parenthesis
    extras_set = {'(', ')'}

    # the union of the above sets is the allowed tokens set
    allowed_tokens = operations_set | extras_set

    # remove all whitespace between characters
    s = s.replace("  ", "")

    # add one whitespace between all characters
    s = " ".join(s)

    # use string splitting to tokenize the input
    pre_tokens = s.split()

    # fuse together digits
    tokens = []
    buff = []

    for char in pre_tokens:
        if char in allowed_tokens:
            tokens.append(''.join(buff))
            buff[:] = []
            tokens.append(char)
        else:
            buff.append(char)
            
    # flush the buffer
    tokens.append(''.join(buff))

    # remove those annoying empty chars from list
    while '' in tokens:
        tokens.remove('')

    # for each token, check if it is allowed and print error if not
    for token in tokens:
        if not token.isdigit() and token not in allowed_tokens:
            is_valid = False
            print "ERROR! %s is not a valid token!" % (token)

    # if all tokens passed the above test, return the tokenized list
    if is_valid:
        return tokens


def main():
    inp = raw_input("Enter expression: ")
    print lexer(inp)

if __name__ == "__main__":
    main()
