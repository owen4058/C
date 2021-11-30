#include <iostream>

using namespace std;

class myMatrix {
private:
    void allocateMemory();
    void deleteMomory();
    void errorMessage(string msg) const;

public:
    int rows;
    int cols;
    int **pData;

    myMatrix(int nRows =1, int nCols =1, int initValue=0);
    myMatrix(int nRows, int nCols, int *data);
    myMatrix(int nRows, int nCols, int **data);
    myMatrix(const myMatrix& mat);
    ~myMatrix();

    int getRows() const;
    int getCols() const;
    int* operator[] (int i) const;
    int& operator() (int i, int j) const;

    myMatrix& operator =(const myMatrix& mat);
    myMatrix& operator +=(const myMatrix& mat);
    myMatrix& operator -=(const myMatrix& mat);
    myMatrix& operator *=(const myMatrix& mat);
    myMatrix& operator *=(int value);
    myMatrix operator *(const myMatrix& mat) const;


    friend bool operator==(const myMatrix& a, const myMatrix&b);

    myMatrix operator -() const;

    myMatrix& transpose();

    friend ostream& operator <<(ostream &outStream, const myMatrix& mat);
    friend istream& operator >>(istream &inStream, myMatrix& mat);
};

myMatrix::myMatrix(int nRows, int nCols, int initValue) : rows(nRows), cols(nCols), pData(nullptr){
    allocateMemory();
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j]= initValue;
}
myMatrix::myMatrix(int nRows, int nCols, int *data) : rows(nRows), cols(nCols), pData(nullptr){
    allocateMemory();
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j] = data[i*cols+j];
}
myMatrix::myMatrix(int nRows, int nCols, int **data) :rows(nRows), cols(nCols), pData(nullptr){
    allocateMemory();
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j] = data[i][j];
}
myMatrix::~myMatrix(){
    if (pData !=nullptr)
        deleteMomory();
}

myMatrix::myMatrix(const myMatrix& mat) :
        rows(mat.rows), cols(mat.cols), pData(nullptr){
    allocateMemory();
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j] = mat.pData[i][j];
}

int myMatrix::getRows() const {return rows;}
int myMatrix::getCols() const {return cols;}
int *myMatrix::operator [] (int i) const {
    if((i<0) || (i>=rows))
        errorMessage("Accessing out-of-bound value of a matrix");
    return pData[i];
}
int & myMatrix::operator () (int i, int j) const {
    if((i<0) || (i>=rows) || (j <0) || (j>=cols))
        errorMessage("Accessing out-of-bound value of a matrix");
    return pData[i][j]; // m9 오류 , //m2 오류
}

myMatrix& myMatrix::operator+=(const myMatrix& mat){
    if((rows != mat.rows) || (cols != mat.cols))
        errorMessage("Accessing out-of-bound value of a matrix"); //만약 행과 열이 다르다면 에러메세지 출력
    else{

        for(int i=0; i<mat.rows; i++)
            for(int j=0; j<mat.cols; j++)
                pData[i][j] += mat(i,j);
    }

// fill in
    return *this;
} //덧셈 연산자
myMatrix& myMatrix::operator-=(const myMatrix& mat){
    if((rows !=mat.rows) || (cols != mat.cols))
        errorMessage("cannot do subtraction between two matrices of different size");

    else{
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                pData[i][j] -= mat(i,j);
    }
    // fill in
    return *this;
} //뺄셈 연산자
myMatrix& myMatrix::operator *=(const myMatrix& mat)
{
    myMatrix tmp(this->rows, mat.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < mat.cols; j++)
            for (int k = 0; k < cols; k++)
                tmp.pData[i][j] += this->pData[i][k] * mat.pData[k][j];
    (*this) = tmp;
    return *this;
}


myMatrix& myMatrix::operator*=(int value){
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j] = pData[i][j] * value;
    //fill in
    return *this;
} //상수 곱셈연산


myMatrix& myMatrix::operator=(const myMatrix& mat){
    if(&mat ==this)
        return *this;
    else if((rows !=mat.rows) || (cols != mat.cols))
    {
        rows=mat.rows;
        cols=mat.cols;
        allocateMemory();
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                pData[i][j] = mat.pData[i][j];
        return *this;

    } //길이가 다르면
    else{
        for(int i= 0; i< rows; i++)
            for(int j=0; j <cols; j++)
                pData[i][j] = mat.pData[i][j];
        return *this;
    }

//fill in

    return *this;
} // 대입 연산자

myMatrix operator+(myMatrix lhs, const myMatrix& mat){
    myMatrix result = myMatrix(lhs.getRows(), lhs.getCols());
    for(int i=0; i<lhs.getRows(); i++)
        for(int j=0; j<lhs.getCols(); j++)
            result(i,j) = lhs(i,j) + mat(i,j);
    return result;
}
myMatrix operator-(myMatrix lhs, const myMatrix& mat){
    myMatrix result = myMatrix(lhs.getRows(), lhs.getCols());
    for(int i=0; i<lhs.getRows(); i++)
        for(int j=0; j<lhs.getCols(); j++)
            result(i,j) = lhs(i,j) - mat(i,j);
    return result;
}
myMatrix myMatrix::operator *(const myMatrix& mat) const
{
    if (cols != mat.rows)
        errorMessage("cannot do multiplication between the given two matrices");

    myMatrix tmp(this->rows, mat.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < mat.cols; j++)
            for (int k = 0; k < cols; k++)
                tmp[i][j] += this->pData[i][k] * mat.pData[k][j];
    return tmp;
}
myMatrix operator*(myMatrix lhs, int value){
    myMatrix result = myMatrix(lhs.getRows(), lhs.getCols());
    for(int i=0; i<lhs.getRows(); i++)
        for(int j=0; j<lhs.getCols(); j++)
            result(i,j) = lhs(i,j) * value;
    return result;
}
myMatrix operator*(int value, myMatrix rhs){
    myMatrix result = myMatrix(rhs.getRows(), rhs.getCols());
    for(int i=0; i<rhs.getRows(); i++)
        for(int j=0; j<rhs.getCols(); j++)
            result(i,j) = rhs(i,j) * value;
    return result;
}


bool operator ==(const myMatrix& a, const myMatrix& b){
    if((a.rows!=b.rows) || (a.cols != b.cols))
        return false;
    else
        return true;
    //fill in
} // ==연산자

bool operator !=(const myMatrix&a, const myMatrix& b){
    return !(a==b);
}


myMatrix myMatrix::operator-() const{
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            pData[i][j] = pData[i][j]*-1;
    return *this;

    //fill in
}

myMatrix& myMatrix::transpose()
{
    myMatrix tmp(this->cols, this->rows);
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            tmp.pData[i][j] = this->pData[j][i];
    (*this) = tmp;
    return *this;
}


void myMatrix::allocateMemory(){
    if(pData != nullptr)
        deleteMomory();

    pData =new int* [rows];
    if(pData == nullptr)
        errorMessage("Memory allocation error");

    pData[0] = new int [rows*cols];
    if(pData[0] == nullptr){
        delete[] pData;
        errorMessage("Memory alloction error");
    }

    for(int i=1; i<rows; i++)
        pData[i]= pData[0] +i*cols;
}

void myMatrix::deleteMomory(){
    delete [] pData[0];
    delete [] pData;

    pData == nullptr;
}

void myMatrix::errorMessage(string str) const {
    cout << "Error: " << str << endl;
    exit(1);
}


ostream& operator <<(ostream &outStream, const myMatrix& mat){
    outStream << mat.rows <<"*"<< mat.cols <<endl;

    for(int i=0; i<mat.rows; i++){
        for (int j=0; j<mat.cols; j++)
            outStream << mat[i][j] <<" ";
        outStream << endl;
    }
    return outStream;
}

istream& operator >>(istream& inStream, myMatrix& mat){
    mat.deleteMomory();
    inStream >> mat.rows >>mat.cols;
    mat.allocateMemory();

    for(int i=0; i<mat.rows; i++)
        for(int j=0; j<mat.cols; j++)
            inStream >> mat[i][j];
    return inStream;
}

void testSimpleCase();
void testDataFromFile();
myMatrix readMatrix();

int main(void) {
    testSimpleCase();
    testDataFromFile();
}

void testSimpleCase(){
    int testData1[6] ={1, 2, 3, 4, 5, 6};
    int testData2[6] ={6, 5, 4, 3, 2, 1};

    myMatrix m1(2, 2, 1);
    myMatrix m2(2, 3, testData1);
    myMatrix m3(3, 2, testData2);
    myMatrix m4(m3);
    myMatrix m5, m6(2,3,1), m7(3,4,1), m8(4,2,1), m9;

    cout << m1.getRows() <<" "<< m1.getCols() << endl;
    m4(0,0) = 1;
    m4(0,1) = 2;
    cout << m4[0][0] <<" "<< m4[0][1] << endl;
    cout << m4(1,0) <<" " << m4(1,1) << endl;
    cout << m4[2][0] <<" "<<m4(2,1) << endl;

    m3 = m3;
    cout << m3;


    m5 = m3 + m4;
    cout << m5;

    cout << (m4==m3) <<" "<<(m4!=m3) << endl; // 0 1 이 나와야 함
    m4 = m5 - m4;
    cout << (m4==m3) <<" "<<(m4!=m3) << endl;

    m9= m6 * m7 * m8 + m1;
    cout << m9;

    m8 = m7 = m6 = m5;
    cout << m8;

    m4 = m4 * 2;
    cout << m4;

    m4 = 2 * m4;
    cout << m4;

    m5 = m2 * m3;
    m2 *= m3;
    cout << m2;


    m2 += m1;
    cout << m2;

    m2 -= m1;
    cout << m2;

    m2 = -m1 +2 * m2;
    cout << m2;

    m7 = m4;
    m8 = m7 * m4.transpose();
    cout << m8;
}

void testDataFromFile(){
    myMatrix m[4], m0;

    for(int j=0; j<4; j++)
        m[j]= readMatrix();

    m0 = m[0] * m[1] * m[2] * m[3];

    cout << m0;
    cout << m0[0][0] << " " << m0[m0.getRows()-1][m0.getCols()-1] << endl;
}

myMatrix readMatrix(){
    int *data;
    int row, col;

    cin >> row >> col;
    data = new int[row*col];
    for(int i=0; i<row*col; i++)
        cin >> data[i];

    myMatrix m(row, col, data);
    delete[] data;
    return m;
}