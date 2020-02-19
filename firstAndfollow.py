#!/usr/bin/env python
# coding: utf-8

# In[ ]:





# In[75]:


grammer = {'E': ['Tx'], 'x': ['+Tx', '-Tx', 'e'], 'T': ['Ry'], 'y': ['*Ry', '/Ry', 'e'], 'R': ['Fz'], 'z': ['^Fz', 'e'], 'F': ['(E)', 'I']}


# In[76]:


print(grammer)


# In[77]:


def isTerminal(A):
    nt = ['+','-','/','*','e','^','(',')','I']
    if A in nt:
        return True
    else:
        return False
    
def First(A,first_set):
    set1 = set()
    
    for rule in grammer[A]:
        
        if rule[0] == 'e':
            set1.add('e')
        elif isTerminal(rule[0]) == True and rule[0] != 'e':
            set1.add(rule[0])
        else:
            k = 0
            while(k < len(rule)):

                if first_set[rule[k]] == None:
                    first_set[rule[k]] = First(rule[k],first_set)
                    
                if 'e' not in first_set[rule[k]] or k == len(rule)-1:
                    set1 = set1.union(first_set[rule[k]])
                    break
                else:
                    set1 = set1.union(first_set[rule[k]])
                    set1.remove('e')

                k += 1
    first_set[A] = set1
    return set1
    


# In[78]:


ter = ['E','T','x','y','R','F','z']
first_set = dict()
for A in ter:
    first_set[A] = None

for A in ter:
    first_set[A] = First(A,first_set)

for key1 in first_set:
    print(key1,first_set[key1])


# In[79]:


def Follow(A,first_set,follow_set):
    
    set1 = set()
    if A == 'E':
        set1.add('$')
    
    for key1 in grammer.keys():
        for rule in grammer[key1]:
            
            if A in rule:
                index = rule.index(A)
                
                if index == len(rule)-1 and key1 != A:
                    if follow_set[key1] == None:
                        follow_set[key1] = Follow(key1,first_set,follow_set)

                    set1 = set1.union(follow_set[key1])
                else:
                    index_b = index+1
                    while(1):
                        
                        if index_b >= len(rule):
                            break
                            
                        elif isTerminal(rule[index_b]) == True:
                            set1 = set1.union(rule[index_b])
                            break 
                            
                        elif index_b == len(rule)-1:   
                            
                            first_bita = first_set[rule[index_b]]
                            if 'e' in first_bita:
                                set1 = set1.union(first_bita)
                                set1.remove('e')  
                                # need to add follow set of key1
                                if key1 != A:
                                    if follow_set[key1] == None:
                                        follow_set[key1] = Follow(key1,first_set,follow_set)

                                    set1 = set1.union(follow_set[key1])
                            else:
                                set1 = set1.union(first_bita)
                                
                        else:
                                
                            first_bita = first_set[rule[index_b]]
                            if 'e' not in first_bita:
                                set1 = set1.union(first_bita)
                                break
                            else:
                                if 'e' in set1:
                                    set1 = set1.union(first_bita)
                                else:
                                    set1 = set1.union(first_bita)
                                    set1.remove('e')
                        index_b += 1
    follow_set[A] = set1
    return set1
                                                


# In[80]:


ter = ['E','T','x','y','R','F','z']
follow_set = dict()
for A in ter:
    follow_set[A] = None

for A in ter:
    Follow(A,first_set,follow_set)

for key1 in follow_set.keys():
    print(key1,follow_set[key1])


# In[ ]:





# In[ ]:




