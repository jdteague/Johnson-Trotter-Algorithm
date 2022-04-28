//   JAROD TEAGUE
//   CSC 2400 
//   PROGRAM 2
//   APRIL CROCKETT

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

// primary functions
void JohnsonTrotter(char* P, bool* Pm, int size);
void Lexicographic(char* P, int size);

// Lexicographic functions
bool consecutive_vars(char* P, int size);
int largest_i(char* P, int size);
int largest_j(char* P, const int size, const int i);
void reverse(char* P, const int size, const int i);

// Johnson Trotter functions
bool hasMobileElement(char* P, bool* Pm, int size);
int largestMobileElement(char* P, bool* Pm, int size);
int direction(bool d);
void reverseArrows(char* P, bool* Pm, int size, int active);

// print functions
void printLex(char* P, const int size, const int i, const int j, const int num);
void printPerm(char* P, bool* Pm, int size, int num);

int main()
{
	string input;
	cout << "enter array: ";
	cin >> input;
	cout << endl;
	
	int arraySize = input.length();
	char c1[arraySize];
	char c2[arraySize];
	bool direction[arraySize];
	
	strcpy(c1, input.c_str());// get our character array
	strcpy(c2, input.c_str());// get our character array
	
	for(int i = 0; i < arraySize; i++)
		direction[i] = 1;
	
	JohnsonTrotter(c1, direction, arraySize);
	Lexicographic(c2, arraySize);
	
	return 0;
}

// a useful visual guide:
// <-  = 1   ->  = 0
//  A		  A

//---------------------------------------- Lexicographic Algorithm ----------------------------------------\\

void Lexicographic(char* P, int size)
{
	int i = 0;
	int j = 0;
	int num = 1;
	char temp_i;
	cout << " --- Lexicographic Algorithm --- " << endl << endl;
	while(consecutive_vars(P,size))
	{
		
		i = largest_i(P, size);
		j = largest_j(P, size, i);
		
		printLex(P, size, i, j, num);
		
		//swap
		temp_i = P[i];
		P[i] = P[j];
		P[j] = temp_i;
		
		// reverse
		reverse(P,size,i);

		num++;
	}
	
	printLex(P, size, -1, -1, num);
	
	cout << endl << endl;
}

bool consecutive_vars(char* P, int size)
{
	for(int i = 0; i < size; i++)
	{
		if((i+1) >= size)
		{
			break;
		}
		
		if(P[i] < P[i+1])
		{
			return true;
		}
	}
	return false;
}

int largest_i(char* P, int size)
{
	int i = 0;
	int largest = 0;
	bool flag = true;// run-once bool 
	while(i < size)
	{
		if((i+1) >= size)
		{
			break;
		}
		
		if(P[i] < P[i+1])
		{
			if(flag)
			{
				largest = i;
				flag = false;
			}
			
			if(i > largest)
			{
				largest = i;
			}
		}
		
		i++;
	}
	
	return largest;
}

int largest_j(char* P, const int size, const int i)
{
	int j = 0;
	int largest = 0;
	bool flag = true;// run-once bool 
	
	while(j < size)
	{
		if(P[j] > P[i])
		{
			if(flag)
			{
				largest = j;
				flag = false;
			}
			
			if(j > largest)
			{
				largest = j;
			}
		}
		
		j++;
	}
	
	return largest;
}

void reverse(char* P, const int size, const int i)
{
	int start = i + 1;
	int end = size - 1;
	char temp;
	while(start < end)
	{
		//cout << "swapping " << P[start] << " and " << P[end] << endl;
		//cout << "vals are " << start << " and " << end << endl;
		temp = P[start];
		P[start] = P[end];
		P[end] = temp;
		start++;
		end--;
	}
}

void printLex(char* P, const int size, const int i, const int j, const int num)
{
	cout << num << ": ";
	for(int p = 0; p < size; p++)// characters
	{
		cout << P[p];
	}
	
	if( i != -1)
	{
		cout << "    i = " << i << " j = " << j << endl;
	}
}

//---------------------------------------- Johnson Trotter Algorithm ----------------------------------------\\

void JohnsonTrotter(char* P, bool* Pm, int size)
{
	int i = 0;
	int k = 0;
	int dir = 0;
	char char_k;
	bool bool_k;
	
	cout << " --- Johnson Trotter Algorithm --- " << endl << endl;
	
	printPerm(P, Pm, size, i + 1);
	
	while(hasMobileElement(P, Pm, size))
	{
		//cout << "it works" << endl;
		
		k = largestMobileElement(P, Pm, size);
		
		dir = direction(Pm[k]);// establish direction
		
		char_k = P[k];// save data
		bool_k = Pm[k];
		
		P[k] = P[k + dir];// perform swap
		Pm[k] = Pm[k + dir];
		
		P[k + dir] = char_k;// finalize swap
		Pm[k + dir] = bool_k;
		
		k = k + dir;// k is now in it's new position
		
		reverseArrows(P, Pm, size, k);
		
		printPerm(P, Pm, size, i + 2);
		
		i++;
	}
}

int direction(bool d)
{
	if(d)
	{
		return -1;
	}
	
	else
	{
		return 1;
	}
}

bool hasMobileElement(char* P, bool* Pm, int size)
{
	// two conditions must be met, either P[i] > P[i+1] and Pd[i] == 1 
	int i = 0;
	int dir = 0;
	while(i <= size)
	{
		dir = direction(Pm[i]);
		//bounds checking
		if((i + dir) >= size)// ONLY occurs when it is pointing outside the last element
		{
			break;
		}
		
		if((i + dir < 0))
		{
			
		}
		else
		{
			if(P[i] > P[i+dir])// action if character is greater than the character it's pointing to
			{
				//cout << "comparing : " << i << ":" << P[i] << " to " << i+dir << ":" << P[i+dir] << endl;
				return true;
			}
		}
		i++;
	}
	
	return false;// if the element is not mobile
}

int largestMobileElement(char* P, bool* Pm, int size)// returns the position of the largest mobile element
{
	// two conditions must be met, either P[i] > P[i+1] and Pd[i] == 1 
	int i = 0;
	int dir = 0;
	int largest = 0;
	bool flag = true;// have we found a valid character yet?
	while(i <= size)
	{
		dir = direction(Pm[i]);
		//bounds checking
		if((i + dir) >= size)// ONLY occurs when it is pointing outside the last element
		{
			break;
		}
		
		if((i + dir < 0))
		{
			
		}
		else
		{
			if(P[i] > P[i+dir])// action if character is greater than the character it's pointing to
			{
				//cout << "comparing : " << i << ":" << P[i] << " to " << i+dir << ":" << P[i+dir] << endl;
				if(flag)
				{
					largest = i;
					flag = false;
				}
				
				if(P[i] > P[largest])
				{
					largest = i;
				}
			}
		}
		i++;
	}
	return largest;// if the element is not mobile
}

void reverseArrows(char* P, bool* Pm, int size, int active)
{
	char target = P[active];
	for(int i = 0; i < size; i++)
	{
		if(P[i] > target)
		{
			Pm[i] = !Pm[i];// invert the bit
		}
	}
}

void printPerm(char* P, bool* Pm, int size, int num)
{
	stringstream s;
	s << num << ":";
    string combo = s.str();
	cout << setw(5) << left << combo;
	
	for(int i = 0; i < size; i++)// arrows
	{
		if(Pm[i])
		{
			cout << " <- ";
		}
		else
		{
			cout << " -> ";
		}
	}
	
	cout << endl << setw(7);
	
	for(int i = 0; i < size; i++)// characters
	{
		cout << "  " << P[i] << " ";
	}
	
	cout << endl << endl;
}

