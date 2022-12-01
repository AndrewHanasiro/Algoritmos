A=333
B=555
mmc = 1
is_dividable = True
denominator = 2
i=0
while(is_dividable):
    i = i + 1
    print("A=%i B=%i mmc=%i deno=%i" % ( A, B, mmc, denominator))
    if (A % denominator == 0 or B % denominator == 0):
        if(A % denominator == 0):
            A =  A / denominator
        if(B % denominator == 0):
            B = B / denominator
        mmc *= denominator
    else:
        if (denominator < A or denominator < B):
            denominator +=1
        else:
            is_dividable=False

print(mmc, i)