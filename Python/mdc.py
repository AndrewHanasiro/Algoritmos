A=333
B=555
mdc = 1
is_dividable = True
denominator = 2
i=0
while(is_dividable):
    i+=1
    print("A=%i B=%i MDC=%i deno=%i" % (A, B, mdc, denominator))
    if (A % denominator == 0 and B % denominator == 0):
        A = A / denominator
        B = B / denominator
        mdc *= denominator
    else:
        if (denominator < A and denominator < B):
            denominator += 1
        else:
            is_dividable=False

print(mdc, i)