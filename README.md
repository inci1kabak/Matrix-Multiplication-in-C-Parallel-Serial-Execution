## Parallel Matrix Multiplication with OpenMP and Performance Comparison :

This project demonstrates matrix multiplication in C using both parallel and serial approaches. The matrices are read from external files (`matrix_a.txt` and `matrix_b.txt`), and the multiplication results are written to an output file (`sonuclar.txt`). The primary goals of this project are to:  

- Utilize **OpenMP** to perform parallel matrix multiplication.  
- Measure and compare the performance (execution time) of parallel and serial matrix multiplication.  
- Handle dynamic matrix sizes as specified in the input files.  
- Ensure efficient handling of large matrices.

### How It Works

1. **Input Files**:  
   - `matrix_a.txt` and `matrix_b.txt` contain the matrices to be multiplied.  
   - Each file starts with two integers specifying the matrix dimensions (rows and columns).  
   - Subsequent lines contain the matrix elements, formatted as space-separated values.  

2. **Matrix Multiplication**:  
   - **Parallel Multiplication**: Uses OpenMP to divide the computational workload across multiple threads for faster execution.  
   - **Serial Multiplication**: Performs matrix multiplication using a single thread for comparison purposes.  

3. **Output**:  
   - The resulting matrix from the parallel computation is saved to `sonuclar.txt`.  
   - Execution times for both parallel and serial computations are printed to the console for performance comparison.  

4. **Makefile Integration**:  
   - The program is executed with three parameters:  
     - `matrix_a.txt`: First input matrix file.  
     - `matrix_b.txt`: Second input matrix file.  
     - `sonuclar.txt`: Output file for the result matrix.  
   - The Makefile ensures correct compilation and execution with parameters.
     
**How to Run**
gcc -fopenmp code.c -o code
./code matrix_a.txt matrix_b.txt sonuclar.txt 
