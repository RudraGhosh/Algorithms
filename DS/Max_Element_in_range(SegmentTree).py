class SegTree:
    def __init__(self,arr):
        self.__treeSize=4*len(arr)
        self.__tree=[None]*self.__treeSize
        self.__array=arr
        self.__array_size=len(arr)
        self.__build_tree(0,len(arr)-1,0)
    def __build_tree(self,start,end,index):
        if(start==end):
            self.__tree[index]=self.__array[start]
            return
        if(start>end):
            return
        mid=(start+end)//2
        self.__build_tree(start,mid,2*index+1)
        self.__build_tree(mid+1,end,2*index+2)
        self.__tree[index]=max(self.__tree[2*index+1],self.__tree[2*index+2])
    def query(self,start,end):
        if(start>end):
            raise TypeError("Invalid range")
        return self.__query_tree(start,end,0,self.__array_size-1,0)
    def __query_tree(self,start,end,left,right,index):
        if(start<=left and end>=right):
            return self.__tree[index]
        elif(end<left or start>right):
            return -999999999999999999
        else:
            mid=(left+right)//2
            left_val=self.__query_tree(start,end,left,mid,2*index+1)
            right_val=self.__query_tree(start,end,mid+1,right,2*index+2)
            return max(left_val,right_val)
    def update(self,start,end,val):
        if(start>end):
            raise TypeError("Invalid range")
        self.__update_tree(start,end,0,self.__array_size-1,0,val)

    def __update_tree(self,start,end,left,right,index,val):
        if(end<left or start>right):
            return
        if(left==right):
            self.__tree[index]=val
            return
        mid=(left+right)//2
        self.__update_tree(start,end,left,mid,2*index+1,val)
        self.__update_tree(start,end,mid+1,right,2*index+2,val)
        self.__tree[index]=max(self.__tree[2*index+1],self.__tree[2*index+2])

segTree=SegTree([5,2,3,1,4,6])
print(segTree.query(0,5))
segTree.update(4,4,100)
print(segTree.query(0,4))
