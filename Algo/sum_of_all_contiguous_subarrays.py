def calculate_sum(arr):
    sum=0
    n=len(arr)
    for i in range(n):
        count1= n-i #Subarrays that start with arr[i] i.e number of elements on the left of arr[i] including arr[i]
        count2= (n-i)*i #Subarrays that have arr[i] in between i.e number of elements on the left of arr[i] including arr[i] * number of elements on the right
        sum+=(count1+count2)*arr[i]
    return sum
print (calculate_sum([1,2,3]))
'''
Eg.
   [1,2,3]
    subarrays that start with 1 - [1],[1,2],[1,2,3] count = (n-i) i.e (3-0)=3
    subarrays that have 1 in between - None count = (n-i)*i i.e (3-0)*0=0
    total subarrays that have 1 is 3+0 =3
    similarly total subarrays that have 2 is 2+2=4 and
    subarrays that have 3 is 1+2=3
    so sum = 3*1 + 4*2 + 3*3 = 20
'''
