class Node:
    def __init__(self, key, value=[]):
        self.key = key
        self.value = value
        self.left = None
        self.right = None
        self.height = 0

    def Nodeheight(self):
        hl = 0
        hr = 0
        if(self.left):
            hl = self.left.height
        if(self.right):
            hr = self.right.height
        return max(hl, hr) + 1

    def balanceFactor(self):
        hl = 0
        hr = 0
        if(self.left):
            hl = self.left.height
        if(self.right):
            hr = self.right.height
        return hl-hr


class Dictionary:
    def __init__(self, root=None):
        self.root = root
    #Right Rotation
    def RRotation(self, p):
        pl = p.left
        T2 = pl.right
        pl.right = p
        p.left = T2
        p.height = p.Nodeheight()
        pl.height = pl.Nodeheight()
        if(self.root == p):
            self.root = pl
        return pl


    #Left Rotation
    def LRotation(self,p):
        pr = p.right
        T = pr.left
        pr.left = p
        p.right = T
        p.height = p.Nodeheight()
        pr.height = pr.Nodeheight()
        if(p == self.root):
            self.root = pr
        return pr


    #Left-Right Rotation

    def LRRotation(self,p):
        p.left = self.LRotation(p.left)
        z = self.RRotation(p)
        return z


    #Right-Left Rotation
    def RLRotation(self, p):
        p.right = self.RRotation(p.right)
        z = self.LRotation(p)
        return z


    #Insert
    def insert(self, key, value = None):
        self.root = self.RInsert(self.root, key, value)

    def RInsert(self, p, key, value):
        if(p == None):
            if(value):
                temp = Node(key, [value])
            else:
                temp = Node(key)
            temp.height = 1
            return temp
        if(key < p.key):
            p.left = self.RInsert(p.left, key, value)
        elif(key > p.key):
            p.right = self.RInsert( p.right, key, value)
        elif(key == p.key):
            p.value.append(value)
            return p
        p.height = p.Nodeheight()

        if(p.balanceFactor() >= 2 and p.left.balanceFactor() == 1):
            return self.RRotation(p)
        elif(p.balanceFactor() <= -2 and p.right.balanceFactor() <= -1):
            return self.LRotation(p)
        elif(p.balanceFactor() <= -2 and p.right.balanceFactor() >= 1):
            return self.RLRotation(p)
        elif(p.balanceFactor() >= 2 and p.left.balanceFactor() == -1):
            return self.LRRotation(p)
        return p

    
    def getMinValueNode(self, root):
        if root is None or root.left is None:
            return root

        return self.getMinValueNode(root.left)

    def delete(self, key):
        self.root = self.Rdelete(self.root, key)

    
    def Rdelete(self, p, key):
        if(p == None):
            return 
        if(key < p.key):
            p.left = self.Rdelete(p.left, key)
        elif(key > p.key):
            p.right = self.Rdelete(p.right, key)
        elif(key == p.key):
            if p.left is None:
                temp = p.right
                root = None
                return temp

            elif p.right is None:
                temp = p.left
                root = None
                return temp

            temp = self.getMinValueNode(p.right)   #finding the leftmost node
            p.key = temp.key
            p.value = temp.value[:]
            root.right = self.Rdelete(p.right,
                                     temp.key)
        p.height = p.Nodeheight()

        if(p.balanceFactor() >= 2 and p.left.balanceFactor() == 1):
            return self.RRotation(p)
        elif(p.balanceFactor() <= -2 and p.right.balanceFactor() <= -1):
            return self.LRotation(p)
        elif(p.balanceFactor() <= -2 and p.right.balanceFactor() >= 1):
            return self.RLRotation(p)
        elif(p.balanceFactor() >= 2 and p.left.balanceFactor() == -1):
            return self.LRotation(p)
        return p

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
if __name__ == "__main__":
    d = Dictionary()
    d.insert("abc", 1)
    d.insert("abc", 1)
    d.insert("def", 1)
    d.insert("a")
    d.insert("a", 1)

    d.printd()

