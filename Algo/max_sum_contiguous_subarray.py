def find_max_sum_subarray(arr):
    n=len(arr)
    max_sum=arr[0]
    left=0
    right=0
    for i in range(1,n):
        if(arr[i]>arr[i]+max_sum): # compare the max sum subarray ending at index i-1 with that subarry+ arr[i]
            max_sum=arr[i]
            left=i
            right=i
        else:
            max_sum+=arr[i]
            right=i
    return (max_sum,left,right)
print(find_max_sum_subarray([1,2,-10,4,6]))
