#!/usr/bin/env python3
import sys
input = sys.stdin.buffer.readline
import random
random.seed('codeforces!!111!')
#print(random.random())


#For demo
#f = open("t0", "r")
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
    
    
    @property
    def left(self):
        return self._left
        
    @left.setter
    def left(self, l):
        self._left = l
        if l is not None:
            l.parent = self # not self._parent!
            
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
        
        
    def _print(self, t):
            if t:                
                print(f"({t.key},{t.prior})"
                     f"({t.left.key if t.left else None}, {t.left.prior if t.left else None})" 
                     f"({t.right.key if t.right else None}, {t.right.prior if t.right else None})")
                self._print(t.left)
                self._print(t.right) 

                
class Treap:
    def __init__(self, key, prior):
        self.root = TreapNode(key, prior)
        #self.split(self.root, "100500")
    
    def insert(self, key, prior):
        self.root = self._insert(self.root, TreapNode(key, prior))
        
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
        
        
        
n = read_int()   
kpis = []
for i in range(n):
    k, p = read_int_array()
    kpis.append((i+1, k, -p))

kpis.sort(key = lambda kpi: kpi[2])

t = TreapIndexed(*kpis[0])
for kpi in kpis[1:]:
  t.insert(*kpi)  
    
#t.root._print(t.root)
t.root.parent = None
print("YES")
for node in sorted(t.nodes, key=lambda node: node.idx):
    print(f"{node.parent.idx if node.parent else 0} {node.left.idx if node.left else 0} {node.right.idx if node.right else 0}")
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            