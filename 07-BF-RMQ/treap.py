#!/usr/bin/env python3
import sys
input = sys.stdin.buffer.readline
import random
random.seed('codeforces!!111!')
#print(random.random())


#For demo
#f = open("./tests/02", "r")
#input = f.readline


def read_int():
    return int(input())


def read_array(sep=None, maxsplit=-1):
    return input().split(sep, maxsplit)

    
def read_int_array(sep=None, maxsplit=-1):
    return [int(x) for x in input().split(sep, maxsplit)]
    

def write(*args, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in args) + end)


def write_array(array, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in array) + end)
    
    
    
class TreapNode:
    def __init__(self, key, prior):
      self.key = key 
      self.prior = prior
      self._left = None
      self._right = None
      self._parent = None
      self.data = None
     
    def update_data(self):
        pass
            
    
    @property
    def next(self):
        if self.right:
            self = self.right.min
            return self
                
        p = self
        while (p is not None) and (p.is_right()):
            p = p.parent
        if p is not None and p.is_left():
            return p.parent                     
        return None
                 
    
    def find(self, x):
        if self.key == x:
            return self
        if x > self.key:
            return self.right.find(x) if self.right else None
        if x < self.key:
            return self.left.find(x) if self.left else None
            
    def is_left(self):
        if self.parent is None:
            return False
        return (self.parent.left == self) 
        
    def is_right(self):
        if self.parent is None:
            return False
        return (self.parent.right == self)       
    
    @property
    def left(self):
        return self._left
        
    @left.setter
    def left(self, l):
        self._left = l
        if l is not None:
            l.parent = self # not self._parent!
            
    @property
    def min(self):
        answ = self
        while answ.left is not None:
            answ = answ.left
        return answ
    
    @property
    def max(self):
        answ = self
        while answ.right is not None:
            answ = answ.right
        return answ
            
    @property
    def right(self):
        return self._right
        
    @right.setter
    def right(self, r):
        self._right = r
        if r is not None:
            r.parent = self # not self._parent!
            
    @property
    def parent(self):
        return self._parent
        
    @parent.setter
    def parent(self, p):
        self._parent = p
                
    @property    
    def children(self):
        if self.left:
            yield self.left
        if self.right:
            yield self.right    
            
    @staticmethod            
    def _lnr_traversal(node):
        if node is None:
            return []
        return TreapNode._lnr_traversal(node.left) + [node] + TreapNode._lnr_traversal(node.right)
    
    def lnr_traversal(self):
        return self._lnr_traversal(self)
        
        
        
    def _print(self, t): # nlr
            if t:                
                print(f"({t.key},{t.prior})"
                     f"({t.left.key if t.left else None}, {t.left.prior if t.left else None})" 
                     f"({t.right.key if t.right else None}, {t.right.prior if t.right else None})")
                self._print(t.left)
                self._print(t.right) 


class TreapIterator:
    def __init__(self, treap, cur=None):
        self.treap = treap
        self.cur = cur # First element
    
    def __next__(self):
        if self.cur is None:
            if self.treap.root is None:
                raise StopIteration
            self.cur = self.treap.root.min
            return self.cur 
        _ncur = self.cur.next
        if _ncur:
            self.cur = _ncur
            return self.cur                                   
                                        
        raise StopIteration
            
        
             
                
class Treap:
    def __init__(self, key, prior):
        self.root = TreapNode(key, prior)
        #self.split(self.root, "100500")
    
    def insert(self, key, prior):
        self.root = self._insert(self.root, TreapNode(key, prior))  
        

    def __iter__(self):
        return TreapIterator(self)
        
    def find(self, k):
        if self.root is None:
            return None
        return self.root.find(k)
    
    def upper_bound(self, k):
        if self.root is None:
            return None
            
        t1, t2 = self.split(self.root, k)
        if t2 is None:
            self.root = t1
            return None
            
        answ = t2
        while answ.left is not None:
            answ = answ.left
            
        self.root = self.merge(t1,t2)
        return answ
        
    @staticmethod # no self
    def split(t, k):
        if t is None:
            return None, None
        if k > t.key:
            t1, t2 = Treap.split(t.right, k)
            t.right = t1
            t.update_data()
            return t, t2
        else:
            t1, t2 = Treap.split(t.left, k)
            t.left = t2
            t.update_data()
            return t1, t
        
    @staticmethod
    def merge(t1, t2):
        if t1 is None:
            return t2
        if t2 is None:
            return t1
        if t1.prior > t2.prior:
            t1.right = Treap.merge(t1.right, t2)
            t1.update_data()
            return t1
        else:
            t2.left = Treap.merge(t1, t2.left)
            t2.update_data()
            return t2
          
      
    @staticmethod 
    def _insert(t, tk):
        t1, t2 = Treap.split(t, tk.key)
        return Treap.merge(Treap.merge(t1, tk), t2)
  

class TreapNodeDS(TreapNode):  
    def __init__(self, key, value=None):
        super().__init__(key, random.random())
        self.value = value
  
class TreapDS(Treap): 
    def __init__(self, key=None, value=None, treap_node_class=TreapNodeDS):
        self.treap_node_class = treap_node_class
        self.root = None if key is None else self.treap_node_class(key, value)
        
    def insert(self, key, val=None):
        node = self.treap_node_class(key, val)
        if self.root is None:
            self.root = node
        else:
            self.root = self._insert(self.root, node)                

class TreapNodeDSmin(TreapNodeDS):  
    def __init__(self, key, value):
        super().__init__(key, value)        
        self.update_data()
    
    def update_data(self):
        self.data = self.value
        for child in self.children:
            self.data = min(self.data, child.data)
        
class TreapDSminQ(TreapDS):
    def __init__(self, key=None, value=None, treap_node_class=TreapNodeDSmin): 
        super().__init__(key, value, treap_node_class)                
        
    def RMQ(self, l, r):
        t1, t2 = self.split(self.root, l)
        t3, t4 = self.split(t2, r+0.5)
        answ = t3.data
        t2 = self.merge(t3, t4)
        self.root = self.merge(t1, t2)
        return answ
        
        
class TreapNodeIndexed(TreapNode):
    def __init__(self, idx, key, prior):
        super().__init__(key, prior)
        self.idx = idx
 
class TreapIndexed(Treap):
    def __init__(self, idx, key, prior):
        self.root = TreapNodeIndexed(idx, key, prior)
        self.nodes = [self.root]
        #self.split(self.root, "100500")
    
    def insert(self, idx, key, prior):
        t = TreapNodeIndexed(idx, key, prior)
        self.nodes.append(t)
        self.root = self._insert(self.root, t)        
        

tRMQ = TreapDSminQ()

n = read_int()   

for i, ai in enumerate(read_int_array()):
    tRMQ.insert(i+1, ai)
        
for _ in range(read_int()):
    l, r = read_int_array()
    print(tRMQ.RMQ(l, r))
    
#tRMQ.root._print(tRMQ.root)

