# basic coloring algorithm

Pseudocode: 

	Input: A directed cycle whose arcs are specifyes by an array S of size n and a coloring c of the vertices.
	Output: Another coloring c' of the vertices of the cycle. 
	
	begin
	for 1 <= i <= n **pardo** //Pardo stands for "do in parallel"
		 1. Set k to the least significan bit position in which c(i) and c(S(i)) disagree.
		 2. Set c'(i) := 2k + c(i)_k
	end


For further reading, chapter 2.7 "Introduction to parallel algorithms" by J. Jajá. 


Compile with flag -fopenmp. It will fail if OpenMp is not installed before. Check if -lm is necessary. 
This implementation is donde with bit-level operations and only works with GCC compiler because of the use of the function __builtin_ctz().  

Input: in order to execute the algotithm, it receives two arguments (in console):
- a positive integer n which indicates the size of the cycle (array) that will be processed.
- a positive integer m which is the seed of the random function (for random arrays without duplicates). 

Output: the output is given in table format "| v (vertex) | Binary representation | k | c'|". 
