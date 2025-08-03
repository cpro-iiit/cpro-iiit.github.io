---
title: "L33: Problem Solving II : Enumerating Permutations"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
revealjs_config:
  slideNumber: true
---

# Problem Solving II : Enumerating Permutations

A permutation is represented by type Perm ( same as int* ).
A list of permutations is represented by PermList (same as int**).
The function should return the list of all permutations of numbers from 1 .. k.
Pseudo code
    - M := empty list
    - A := perm(k-1)
    - for each permutation a in A:  
        - for each position p from 0 to k
            - p' = insert k at position p in a
            - add p' to M
    - Base case: if k = 1 return list of only 1 permutation

Code available here    
[https://github.com/cpro-iiit/cpro-iiit.github.io/tree/main/web/content/docs/course_material/lectures/33/perm)](https://github.com/cpro-iiit/cpro-iiit.github.io/tree/main/web/content/docs/course_material/lectures/33/perm).

## Home Work

- Take alphabet set (for eg a b c ) and a number k as input, and print all strings of length k, which takes letters from that alphabet (if the alphabet is a b c, there are 3^k of them). Print them in [lexicographic order](https://en.wikipedia.org/wiki/Lexicographic_order#Finite_subsets).

- Given n,k, enumerate all substes of {1,2, .., n} of size k. Print them in [lexicogrphaic order](https://en.wikipedia.org/wiki/Lexicographic_order#Finite_subsets).

- Given n, k, enumerate all arrangements of k numbers from {1,2, .. n}. Print them in [lexicographic order](https://en.wikipedia.org/wiki/Lexicographic_order#Finite_subsets). 
