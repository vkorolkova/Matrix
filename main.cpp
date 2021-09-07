#include<iostream>
using namespace std;

class Fraction {
private:
	int numerator; 
	int denominator; 
public:
	
	Fraction() {
		numerator = 0;
		denominator = 1;
	}
	
	Fraction(int n, int d) {
		numerator = n;
		denominator = d;
	}

	Fraction(int p) {
		numerator = p;
		denominator = 1;
	}

	~Fraction() {}

	
	Fraction Cancellation(Fraction &a)
	{
		if (a.numerator != 0)
		{
			if (a.numerator < 0) {
				a.numerator *= (-1);
			}
			int n = a.numerator,
				m = a.denominator;
			
			while (n != m) {
				if (n > m) {
					n -= m;
				}
				else {
					m -= n;
				}
			}
			if (n*m>1) {
				a.numerator /= n;
				a.denominator /= n;
			}
			return a;
		}
		else {
			a.denominator = 1;
			return a;
		}
	}

	Fraction mod(Fraction &a) {
		if (a.numerator < 0) {
			a.numerator = a.numerator*(-1);
		}
		return a;
	}

	Fraction& operator = (Fraction &a) {
		numerator = a.numerator;
		denominator = a.denominator;
		return *this;
	}

	
	bool operator == (const Fraction a) {
		if (numerator * a.denominator != denominator * a.numerator)
			return false;
		return true;
	}

	bool operator != (const Fraction &a) {
		if (numerator * a.denominator == denominator * a.numerator)
			return false;
		return true;
	}

	bool operator > (const Fraction a) {
		if (numerator * a.denominator <= denominator * a.numerator)
			return false;
		return true;
	}

	bool operator < (const Fraction a) {
		if (numerator * a.denominator >= denominator * a.numerator)
			return false;
		return true;
	}

	Fraction operator + (Fraction &a) {
		Fraction res;
		res.numerator = numerator * a.denominator + a.numerator * denominator;
		res.denominator = denominator * a.denominator;
		Cancellation(res);
		return res;
	}

	Fraction operator - (Fraction &a) {
		Fraction res;
		res.numerator = numerator * a.denominator - a.numerator * denominator;
		res.denominator = denominator * a.denominator;
		Cancellation(res);
		return res;
	}

	Fraction operator * (Fraction &a) {
		Fraction res;
		res.numerator = numerator * a.numerator;
		res.denominator = denominator * a.denominator;
		Cancellation(res);
		return res;
	}

	Fraction operator / (Fraction & a) {
		Fraction res;
		if (a.numerator != 0) {
			res.numerator = numerator * a.denominator;
			res.denominator = denominator * a.numerator;
			Cancellation(res);
		}
		else {
			cout << "error";
			exit(1);
		}
		return res;
	}

	friend ostream& operator << (ostream& out, Fraction& a) {
		// çíàìåíàòåëü ïå÷àòàåòñÿ, åñëè ÷èñëèòåëü íå ðàâåí 0
		if (a.numerator == 0) {
			out << "0";
		}
		else {
			if (a.denominator == 1) {
				out << a.numerator;
			}
			else
				if (a.numerator == a.denominator)
					out << "1";
				else
					out << a.numerator << "/" << a.denominator;
		}
		return out;
	}

	friend istream& operator >> (istream& fin, Fraction& a) {
		char buf = ' ';
		fin >> a.numerator;
		while (buf != '/')
			fin >> buf;
		fin >> a.denominator;
		if (a.denominator == 0)
			exit(1);
		return fin;
	}

	void set_numerator(int a) {
		numerator = a;
	}

	int get_numerator() const {
		return numerator;
	}

	void set_denominator(int a) {
		denominator = a;
	}

	int get_denominator() const {
		return denominator;
	}
};

class Matrix {
	int n;
	int m;
	Fraction **ar;
public:
	Matrix() {
		n = 0;
		m = 0;
		ar = nullptr;
	}

	Matrix(int n_, int m_) {
		n = n_;
		m = m_;
		ar = new Fraction*[n];
		for (int i = 0; i < n; i++) {
			ar[i] = new Fraction[m];
		}
	}

	Matrix(const Matrix &ob) {
		n = ob.n;
		m = ob.m;
		ar = new Fraction*[n];
		for (int i = 0; i < n; i++) {
			ar[i] = new Fraction[m];
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				ar[i][j] = ob.ar[i][j];
	}

	~Matrix() {
		for (int z = 0; z < n; z++)
			delete[] ar[z];
		delete[] ar;
	}

	Matrix& operator=(const Matrix &fp)
	{
		if (&fp != this) {
			delete[] ar;
			n = fp.n;
			m = fp.m;
			ar = new Fraction *[n];
			for (int i = 0; i < n; i++)
				ar[i] = new Fraction[m];
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					ar[i][j] = fp.ar[i][j];
		}
		return *this;
	}

	Fraction* operator [](int index) {
		return ar[index];
	}

	Matrix operator + (const Matrix& ob) {
		Matrix temp;
		temp.n = this->n;
		temp.m = this->m;
		int i, j;
		temp.ar = new Fraction*[temp.n];
		for (i = 0; i < temp.n; i++)
			temp.ar[i] = new Fraction[temp.m];

		for (i = 0; i < temp.n; ++i)
			for (j = 0; j < temp.m; ++j)
				temp.ar[i][j] = this->ar[i][j] + ob.ar[i][j];
		return temp;
	}

	Matrix operator - (const Matrix& ob) {
		Matrix temp;
		temp.n = this->n;
		temp.m = this->m;
		int i, j;
		temp.ar = new Fraction*[temp.n];
		for (i = 0; i < temp.n; i++)
			temp.ar[i] = new Fraction[temp.m];
		for (i = 0; i < temp.n; ++i)
			for (j = 0; j < temp.m; ++j)
				temp.ar[i][j] = this->ar[i][j] - ob.ar[i][j];
		return temp;
	}

	Matrix operator * (const Matrix& ob) {
		if (n == ob.m && m == ob.n) {
			Matrix temp;
			temp.n = this->n;
			temp.m = this->m;
			int i, j;
			temp.ar = new Fraction*[temp.n];
			for (i = 0; i < temp.n; i++)
				temp.ar[i] = new Fraction[temp.m];
			for (i = 0; i < temp.n; ++i) {
				for (j = 0; j < temp.m; ++j) {
					for (int k = 0; k < temp.m; ++k)
						temp.ar[i][j] = temp.ar[i][j] + (this->ar[i][k] * ob.ar[k][j]);
				}
			}
			return temp;
		}
		else {
			cout << "it is impossible to multiply" << endl;
			exit(1);
		}
	}

	friend istream &operator >>(istream &is, Matrix &fp) {
		fp.ar = new Fraction*[fp.n];
		for (int i = 0; i < fp.n; i++) {
			fp.ar[i] = new Fraction[fp.m];
		}

		for (int i = 0; i < fp.n; i++) {
			for (int j = 0; j < fp.m; j++)
			{
				is >> fp.ar[i][j];
			}
		}
		return is;
	}

	friend ostream &operator <<(ostream &out, Matrix &fp) {
		for (int i = 0; i < fp.n; i++) {
			for (int j = 0; j < fp.m; j++)
				out << fp.ar[i][j] << ' ';
			cout << endl;
		}
		return out;
	}

	void set_n(int a) {
		n = a;
	}

	int get_n() const {
		return n;
	}

	void set_m(int a) {
		m = a;
	}

	int get_m() const {
		return m;
	}

	void set_matrix() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> ar[i][j];
	}

	void get_matrix() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cout << ar[i][j];
	}

	void Gauss() {
		Matrix temp;
		int mm;
		mm = (this->m + 1);
		temp.m = mm;
		temp.n = this->n;
		int i, j;
		temp.ar = new Fraction*[temp.n];
		for (i = 0; i < temp.n; i++)
			temp.ar[i] = new Fraction[temp.m];
		for (i = 0; i < temp.n; i++) {
			for (j = 0; j < mm; j++) {
				if (j != mm - 1) {
					temp.ar[i][j] = this->ar[i][j];
				}
				else {
					cout << "Enter the element of the additional column: ";
					cin >> temp.ar[i][j];
				}
			}
		}
		cout << "Matrix with the additional column: " << endl << temp;
		if (mm == 2) {
			Fraction sol;
			int p = 0;
			sol = temp.ar[0][mm - 1];
			for (i = 1; i < n; i++) {
				if (sol == temp.ar[i][mm - 1])
					p++;
			}
			if (p == n - 1)
				cout << "Solution of the system: " << "x=" << sol << endl;
			else cout << "No solution" << endl;
		}
		Fraction *x, *y, max, mod;
		int k, index;
		Fraction eps = 1 / 100000;  
		y = new Fraction[n];
		x = new Fraction[n];
		k = 0;
		while (k < n)
		{
			max = mod.mod(temp.ar[k][k]);
			index = k;
			for (int i = k + 1; i < n; i++) {
				if (mod.mod(temp.ar[i][k]) > max) {
					max = mod.mod(temp.ar[i][k]);
					index = i;
				}
			}
			
			if (max < eps) {
				
				cout << "Solution can not be obtained due to a null column ";
				cout << index << " Matrix A" << endl;
				exit(1);
			}
			for (int j = 0; j < n; j++) {
				Fraction tem = temp.ar[k][j];
				temp.ar[k][j] = temp.ar[index][j];
				temp.ar[index][j] = tem;
			}
			Fraction tem = y[k];
			y[k] = y[index];
			y[index] = tem;
			
			for (int i = k; i < n; i++) {
				Fraction tem = temp.ar[i][k];
				if (mod.mod(tem) < eps) continue;
				for (int j = 0; j < n; j++)
					temp.ar[i][j] = temp.ar[i][j] / tem;
				y[i] = y[i] / tem;
				if (i == k)  continue; 
				for (int j = 0; j < n; j++)
					temp.ar[i][j] = temp.ar[i][j] - temp.ar[k][j];
				y[i] = y[i] - y[k];
			}
			k++;
		}
		for (k = n - 1; k >= 0; k--) {
			x[k] = y[k];
			for (int i = 0; i < k; i++) {
				y[i] = y[i] - temp.ar[i][k] * x[k];
			}
		}
		cout << "Matrix after transformation: " << endl << temp << endl;
		cout << "Solution of the system: " << endl;
		Fraction solut = 0;
		if (mm > 2) {
			for (i = 0; i < n; i++) {
				solut = temp.ar[i][mm - 1];
				if (temp.ar[n - 2][mm - 2] != 1 && temp.ar[n - 2][mm - 3] != 0) {
					for (k = mm - 2; k > i; k--) {
						solut = solut - temp.ar[i][k];
					}
					cout << "x" << i + 1 << "=" << solut << endl;
				}
			}
			if (temp.ar[n - 2][mm - 2] == 1 && temp.ar[n - 2][mm - 2] == 0)
				cout << "x" << n - 2 << "=" << solut << endl;
			if (temp.ar[n - 1][mm - 1] == 1 && temp.ar[n - 1][mm - 2] == 0)
				cout << "x" << n - 1 << "=" << "R";
		}
	}
};


int main()
{
	int n, m;
	cout << "Enter the size of matrixes (the number of rows and columns): ";
	cin >> n >> m;
	Matrix matrix1(n, m);
	cout << "Enter the elements of the matrix1: " << endl;
	cin >> matrix1;
	Matrix matrix2(n, m);
	cout << "Enter the elements of the matrix2: " << endl;
	cin >> matrix2;
	cout << endl;
	cout << "Matrix1: " << endl << matrix1 << endl;
	cout << "Matrix2: " << endl << matrix2 << endl;
	cout << "+ " << matrix1 + matrix2 << endl;
	cout << "- " << matrix1 - matrix2 << endl;
	cout << "* " << matrix1 * matrix2 << endl;
	system(" pause");
	cin.get(); cin.get();
	return 0;
}




