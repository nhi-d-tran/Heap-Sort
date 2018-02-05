#include <iostream>
#include <fstream>
using namespace std;

class heapSort
{
public:
	int rootIndex;
	int fatherIndex;
	int leftKidIndex;
	int rightKidIndex;
	int minKidIndex;
	int *heapAray;

	//constructor
	heapSort(int count)
	{
		rootIndex = 1;
		heapAray = new int[count+1];
		heapAray[0] = 0;
	}

	// buildHeap
	void buildHeap(char** argv, ofstream& outFile)
	{
		try
		{
			ifstream inFile;
			rootIndex = 1;
			inFile.open(argv[1]);

			if(!inFile.is_open())
			{
				cout << "ARG ERROR." <<endl;
			}
			else
			{
				int data;
				int kidIndex;

				while(inFile >> data)
				{
					insertOneDataItem(data);
					kidIndex = heapAray[0];		// last index
					bubbleUp(kidIndex);
					printHeap(outFile);				//outFile1
				}
			}
		}
		catch(exception &e)
		{
			cout << "Standard exception: " << e.what() << endl;
		}
	}

	// deleteHeap
	void deleteHeap(ofstream &outFile1, ofstream &outFile2)
	{
		try
		{
			outFile2 << getRoot() << endl;
			deleteRoot();
			fatherIndex = rootIndex;
			bubbleDown(fatherIndex);
			printHeap(outFile1);
		}
		catch(exception &e)
		{
			cout << "Standard exception: " << e.what() << endl;
		}
	}

	// insert data
	void insertOneDataItem(int data)
	{
		heapAray[0]++;
		heapAray[heapAray[0]] = data;
	}

	//get Root - return the data in the root
	int getRoot()
	{
		return heapAray[1];
	}

	//delete Root - move the last item in headAry to root
	void deleteRoot()
	{
		heapAray[1] = heapAray[heapAray[0]];
		heapAray[0]--;
	}

	// bubble up
	void bubbleUp(int kidIndex)
	{
		if(isRoot(kidIndex))
		{
			return;
		}
		else
		{
			fatherIndex = kidIndex/2;

			if(heapAray[kidIndex] < heapAray[fatherIndex])
			{
				int temp = heapAray[fatherIndex];
				heapAray[fatherIndex] = heapAray[kidIndex];
				heapAray[kidIndex] = temp;
				bubbleUp(fatherIndex);
			}
		}
	}

	// bubble down
	void bubbleDown(int fatherIndex)
	{
		if(isLeaf(fatherIndex))
		{
			return;
		}
		else
		{
			leftKidIndex = fatherIndex * 2;
			rightKidIndex = fatherIndex * 2 + 1;

			findMinKidIndex(fatherIndex);
			int temp;

			if(heapAray[minKidIndex] < heapAray[fatherIndex])
			{
				temp = heapAray[minKidIndex];
				heapAray[minKidIndex] = heapAray[fatherIndex];
				heapAray[fatherIndex] = temp;
				bubbleDown(minKidIndex);
			}
		}
	}

	// check if it is leaf -  returns true, if both kids' index are out of range
	bool isLeaf(int index)
	{
		return index == 0;
	}

	// check if it is root
	bool isRoot(int index)
	{
		return index == 1;
	}

	// find min index
	void findMinKidIndex(int fatherIndex)
	{
		leftKidIndex = fatherIndex * 2;
		rightKidIndex = fatherIndex * 2 + 1;

		if(leftKidIndex <= heapAray[0] && rightKidIndex <= heapAray[0])
		{
			if(heapAray[leftKidIndex] <= heapAray[rightKidIndex])
			{
				minKidIndex = leftKidIndex;
			}
			else
			{
				minKidIndex = rightKidIndex;
			}
		}
		else if(leftKidIndex <= heapAray[0])
		{
			minKidIndex = leftKidIndex;
		}
		else if(rightKidIndex <= heapAray[0])
		{
			minKidIndex = rightKidIndex;
		}
	}

	// check if heap is empty
	bool isEmpty()
	{
		return heapAray[0] == 0;
	}

	// check if heap is full
	bool isFull()
	{
		return heapAray[0] == sizeof(heapAray);
	}

	// print Heap
	void printHeap(ofstream &outFile)
	{
		for(int i = 0; i <= heapAray[0]; i++)
		{
			outFile << heapAray[i] << " ";
		}
		outFile << endl;
	}
};

int main(int argc, char **argv)
{
	try
	{
		ifstream inFile;
		ofstream outFile1;
		ofstream outFile2;

		inFile.open(argv[1]);

		if(!inFile.is_open())
		{
			cout << "The file is not open!" << endl;
		}
		else
		{
			int count = 0; 	// count the number of data in items
			int number;
			while(inFile >> number)
			{
				count++;
			}
			heapSort* theHeap = new heapSort(count);

			// open files for writing
			outFile1.open(argv[2]);		// text file contain debugging output
			outFile2.open(argv[3]);		// text file contain the sorted input numbers

			//call buildHeap
			theHeap->buildHeap(argv, outFile1);

			//call deleteHeap
			while(!theHeap->isEmpty())
			{
				theHeap->deleteHeap(outFile1, outFile2);
			}
		}
	}
	catch(exception &e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}

	return 0;
}
