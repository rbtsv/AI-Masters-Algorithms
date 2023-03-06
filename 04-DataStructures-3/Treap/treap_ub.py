#!/usr/bin/env python3
import sys
input = sys.stdin.buffer.readline
import random
random.seed('codeforces!!111!')
#print(random.random())


#For demo
#f = open("t_ub", "r")
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
                 
    
    def find(self, x):
        if self.key == x:
            return self
        if x > self.key:
            return self.right.find(x) if self.right else None
        if x < self.key:
            return self.left.find(x) if self.left else None
            
    def is_left(self):
        if self.parent = None:
            return False
        return (self.parent.left == self) 
        
    def is_right(self):
        if self.parent = None:
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
        if answ.left is not None:
            answ = answ.left
        return answ
    
    @property
    def max(self):
        answ = self
        if answ.right is not None:
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


class TreapIter:
    def __init__(self, treap):
        self.treap = treap
        self.cur = None # First element
    
    def __next__(self):
        if self.cur is None:
            self.treap.root is None:
                raise StopIteration
            self.cur = self.treap.root.min
            return self.cur
        if self.cur.right:
            self.cur = self.cur.right.min
        else:
            p = self.cur.parent
            while p is not None and p.is_right():
                p = p.parent
            if p.is_left():
                p = parent                
            if p is not None:
                return p
            raise StopIteration
            
        
             
                
class Treap:
    def __init__(self, key, prior):
        self.root = TreapNode(key, prior)
        #self.split(self.root, "100500")
    
    def insert(self, key, prior):
        self.root = self._insert(self.root, TreapNode(key, prior))   
        
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
            return t, t2
        else:
            t1, t2 = Treap.split(t.left, k)
            t.left = t2
            return t1, t
        
    @staticmethod
    def merge(t1, t2):
        if t1 is None:
            return t2
        if t2 is None:
            return t1
        if t1.prior > t2.prior:
            t1.right = Treap.merge(t1.right, t2)
            return t1
        else:
            t2.left = Treap.merge(t1, t2.left)
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
        
        
        
n = read_int()

treap = TreapDS()
y = None
for _ in range(n):
    s = input().decode('UTF-8')
    x = int(s[1:])
    #print(s[0], x, s)    
    if s[0] == '?':                           
        node = treap.upper_bound(x)
        y = -1 if node is None else node.key
        print(y)
    else:
        if y is not None:
            x = (x + y) % 10**9 
        y = None
        if treap.find(x) is None:
            treap.insert(x)
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            