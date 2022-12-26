def num_digits(n):
    digits = 1
    while(n>=9):
        digits+=1
        n = n/10
    print(digits)

num_digits(100000)

 