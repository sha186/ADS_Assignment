class Node:
    def __init__(self, key, value = []):
        self.key = key
        self.value = value 
        self.left = None
        self.right = None


class Dictionary:
    def __init__(self, root = None):
        self.root = root

    def insert(self, key, value = None):
        r = self.root
        p = None
        direction = 0
       
        while(r):
            p = r
            if(r.key > key):
                r = r.left
                direction = -1
            elif(r.key < key):
               
                r = r.right
                direction = 1
            else:
                direction = 0
                break
        
        if(direction == -1):
            if(value):
                n = Node(key, [value])
            else:
                n = Node(key)
            p.left = n
        elif(direction == 1):
            if(value):
                n = Node(key, [value])
            else:
                n = Node(key)
            p.right = n
    
        elif(self.root == None):
            if(value):
                n = Node(key, [value])
            else:
                n = Node(key)
            self.root = n
        elif(direction == 0):
            r.value.append(value)

    def delete(self, key):
        r = self.root
        p = None
        direction = 0
        while(r != None and r.key != key):
            p = r
            if(r.key > key):
                r = r.left
                direction = -1
            elif(r.key < key):
                r = r.right
                
                direction = 1
            else:
                break
            
        if(r and r.key == key):
            if(r.left == None and r.right == None):
                #leaf node
                if(direction == -1):
                    p.left = None
                elif(direction == 1):
                    p.right = None
                elif(r == self.root):
                    self.root = None
                del r
            elif(r.left):
                #replace r with rightmost 
                x = r.left
                y = None
                while(x and x.right):
                    y = x
                    x = x.right
                r.key = x.key
                r.value = x.value[:]
                if(y):
                    y.right = None
                if(x == r.left):
                    r.left = None
                del x
            elif(r.right):
                x = r.right
                y = None
                while(x and x.left):
                    y = x
                    x = x.left
                r.key = x.key
                r.value = x.value[:]
                if(y):
                    y.left = None
                if(x == r.right):
                    r.right = None
                del x
            else:
                pass

    def __contains__(self, key):
        x = self.search(key)
        return x

    def search(self, key):
        r = self.root
        flag = 0
        while(r):
            if(key < r.key):
                r = r.left
            elif(key > r.key):
                r = r.right
            else:
                flag = 1
                break
        if(flag == 1):
            return True
        return False

    def printd(self):
        def inorder(root):
            if(root == None):
                return 
            inorder(root.left)
            print(f"{root.key}: {root.value}")
            inorder(root.right)
        inorder(self.root)
        
        


d = Dictionary()
d.insert("abc", 1) 
d.insert("abc", 2)
d.insert("def", 5)
d.delete("abc")
d.delete("def")
d.printd()              




