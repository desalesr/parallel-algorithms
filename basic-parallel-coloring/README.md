#basic coloring algorithm

This algorit
Done with bit level operations. 


Pseudocode: 

	**Input: A directed cycle whose arcs are specifyes by an array *S* of size *n* and a coloring *c* of the vertices.**
	**Output: Another coloring *c'* of the vertices of the cycle. 
	**begin**
	**for**1 <= *i* <= *n* **pardo** //Pardo stands"do in parallel"
		 1. Set *k* to the least significan bit position in which *c(i)* and *c(S(i))* disagree.
		 2. Set *c'(i) := 2*k* + *c(i)_k*
	**end**


For further reading, chapter 2.7 "Introduction to parallel algorithms" by J. Jajá. 

