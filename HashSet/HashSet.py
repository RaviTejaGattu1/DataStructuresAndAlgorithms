class ListNode():
    def __init__(self, key: int):
        self.key=key
        self.next=None

class MyHashSet(object):

    def __init__(self):
        self.set=[ListNode(0) for i in range(10**4)]
      #Max no of keys we will be inserting
      #Dummynode for every position in the array
      #This will create a new list node for every position
        
        
    def add(self, key: int) -> None:
        """
        :type key: int
        :rtype: None
        """
        index = key % len(self.set)
        cur=self.set[index] #Head of the node is set now
        
       #+We have to check for duplicates
       #+Add a new next node with the key in it
        while cur.next:
            if cur.next.key==key:   #Duplicate check
                return
            cur=cur.next
        cur.next=ListNode(key)

            
    def remove(self, key: int) -> None:
        """
        :type key: int
        :rtype: None
        """
        index = key % len(self.set)
        cur=self.set[index] 
        
        while cur.next:
            if cur.next.key==key:   
                cur.next=cur.next.next
                return
            cur=cur.next
        

    def contains(self, key: int) -> bool:
        index = key % len(self.set)
        cur=self.set[index] 
        
        while cur.next:
            if cur.next.key==key:   
                return True
            cur=cur.next
        return False


# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)
    