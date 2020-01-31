import math
def isprime(n):
    i=2;
    while i*i<=n:
        if n % i == 0:
            return False
        i=i+1
    return True
  
T=int(input())
for t in range(0,T):
    n,k=map(int,input().split(' '))
    ans=k
    i=2
    while i*k<=n :
        if isprime(i):
            ans=ans*i
        i=i+1
    print(ans)
