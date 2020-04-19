#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#define PAUSE {printf("Press \"Enter\" to continue\n"); fflush(stdin); getchar(); fflush(stdin);}
using namespace std;

class Matrix;


//Simple Exception class to throw errors
class Exception
{
public:
  const char* msg;
  Exception(const char* arg)
   : msg(arg)
  {
  }
};

class Matrix
{
private:
  int rows;
  int cols;
  double** p;     // pointer to a matrix with doubles
  
public:
  // Default constructor
  Matrix()
  {
    //printf("Executing constructor Matrix() ...\n");
    // create a Matrix object without content
    p = NULL;
    rows = 0;
    cols = 0;
  }

  // Parameterized constructor
  Matrix(const int row_count, const int column_count)
  {
    // create a Matrix object with given number of rows and columns
    p = NULL;

    if (row_count > 0 && column_count > 0)
    {
      rows = row_count;
      cols = column_count;

      p = new double*[rows];
      for (int r = 0; r < rows; r++)
      {
        p[r] = new double[cols];

        // initially fill in zeros for all values in the matrix;
        for (int c = 0; c < cols; c++)
        {
          p[r][c] = 0;
        }
      }
    }
  } 
  
  // Assigning the Matrix values to pointer
  Matrix(const Matrix& a)
  {
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
      p[r] = new double[a.cols];

      // copy the values from the matrix a
      for (int c = 0; c < a.cols; c++)
      {
        p[r][c] = a.p[r][c];
      }
    }
  }
  
  // index operator
  // the indexes are one-based, not zero based.
  double& operator()(const int r, const int c)
  {
    if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
    {
      return p[r-1][c-1];
    }
    else
    {
      throw Exception("Subscript out of range");
    }
  }
  
 // assignment operator overloading
  Matrix& operator= (const Matrix& a)
  {
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
      p[r] = new double[a.cols];

      // copy the values from the matrix a
      for (int c = 0; c < a.cols; c++)
      {
        p[r][c] = a.p[r][c];
      }
    }
    return *this;
  }
  
  // multiply a double value (element wise)
  Matrix& Multiply(const double v)
  {
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++)
      {
        p[r][c] *= v;
      }
    }
     return *this;
  }
  
  // addition of Matrix with Matrix (using '+' overloading)
  friend Matrix operator+(const Matrix& a, const Matrix& b)
  {
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
      Matrix res(a.rows, a.cols);

      for (int r = 0; r < a.rows; r++)
      {
        for (int c = 0; c < a.cols; c++)
        {
          res.p[r][c] = a.p[r][c] + b.p[r][c];
        }
      }
      return res;
    }
    else
    {
      // Throws an exception
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix
    return Matrix();
  }
  
   // Multiplication of Matrix with Matrix (using '*' overloading)
  friend Matrix operator* (const Matrix& a, const Matrix& b)
  {
    // check if the dimensions match
    if (a.cols == b.rows)
    {
      Matrix res(a.rows, b.cols);

      for (int r = 0; r < a.rows; r++)
      {
        for (int c_res = 0; c_res < b.cols; c_res++)
        {
          for (int c = 0; c < a.cols; c++)
          {
            res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
          }
        }
      }
      return res;
    }
    else
    {
      // Throws an exception
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix 
    return Matrix();
  }
  
  // multiplication of Matrix with scalar 
  friend Matrix operator* (const Matrix& a, const double b)
  {
    Matrix res = a;
    res.Multiply(b);
    return res;
  }
  
  // multiplication of scalar with Matrix
  friend Matrix operator* (const double b, const Matrix& a)
  {
    Matrix res = a;
    res.Multiply(b);
    return res;
  }
  
   // print the contents of the matrix
  void Print() const
  {
    if (p != NULL)
    {
      printf("[");
      for (int r = 0; r < rows; r++)
      {
        if (r > 0)
        {
          printf(" ");
        }
        for (int c = 0; c < cols-1; c++)
        {
          printf("%.2f, ", p[r][c]);
        }
        if (r < rows-1)
        {
          printf("%.2f;\n", p[r][cols-1]);
        }
        else
        {
          printf("%.2f]\n", p[r][cols-1]);
        }
      }
    }
    else
    {
      // matrix is empty
      printf("[ ]\n");
    }
  }
  
  public:
  // destructor
  ~Matrix()
  {
    // clean up allocated memory
    for (int r = 0; r < rows; r++)
    {
      delete p[r];
    }
    delete p;
    p = NULL;
  }
};

//Main function

int main(int argc, char *argv[])
{
  
  try
  {
    // create an empty matrix of 3x3 (will initially contain zeros)
    int cols = 3;
    int rows = 3;
    Matrix A = Matrix(rows, cols);

    // fill in some values in matrix a
    int countA = 0;
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        countA ++;
        A(r, c) = countA;
      }
    }
    
     Matrix B = Matrix(rows, cols);

    // fill in some values in matrix b
    int countB = 0;
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        countB ++;
        B(r, c) = countB;
      }
    }
    
     // print the whole matrix A
    printf("A = \n");
    A.Print();
    printf("\n");
    
     // print the whole matrix B
    printf("B = \n");
    B.Print();
    printf("\n");
    
    //Addition of two Matrices A and B
    Matrix C;
    C = A + B;
    printf("A + B = \n");
    C.Print();
    printf("\n");
    
    //Creation of Vector V1
    Matrix V1 = Matrix(rows, 1);    // a vector
    int countV1 = 1;
    for (int r = 1; r <= rows; r++)
    {
      countV1 ++;
      V1(r, 1) = countV1 * 2;
    }
    //Print the Vector
    printf("V1 = \n");
    V1.Print();
    printf("\n");
    
    //Creation of Vector V2
    Matrix V2 = Matrix(rows, 1);    // a vector
    int countV2 = 1;
    for (int r = 1; r <= rows; r++)
    {
      countV2 ++;
      V2(r, 1) = countV2 * 3;
    }
    //Print the Vector
    printf("V2 = \n");
    V2.Print();
    printf("\n");
    
    //Addition of two vectors 
    Matrix V3 = Matrix(rows, 1);
    V3 = V1 + V2;
    printf("V1 + V2 = \n");
    V3.Print();
    printf("\n");
    
    //Multiplication of Matrix with Vector
    C = A * V1;
    printf("A * V1 = \n");
    C.Print();
    printf("\n");
    
    //Multiplication of Matrix with Scalar
    Matrix F;
    int K;
    cout<<"Enter the value of the scalar to be multiplied:";
    cin>>K;
    F = A * K ;
    printf("A * %d", K);
    printf(" = \n");
    F.Print();
    printf("\n");
    
    //Multiplication of Scalar with Matrix 
    int L;
    cout<<"Enter the value of the scalar to be multiplied:";
    cin>>L;
    F = L * A ;
    printf("%d * A", L);
    printf(" = \n");
    F.Print();
    printf("\n");
    
    //Multiplication of Matrices A and B 
    F = A * B ;
    printf("A * B = \n");
    F.Print();
    printf("\n");
  }
  catch (Exception err)
  {
    printf("Error: %s\n", err.msg);
  }
  catch (...)
  {
    printf("An error occured...\n");
  }

  printf("\n"); 
  PAUSE;
  return EXIT_SUCCESS;
}
    
  
  
