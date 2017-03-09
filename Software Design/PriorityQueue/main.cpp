#include "PriorityQueue.h"

#include <iostream>
#include <string>

using namespace std;

void show(MyPriorityQueue<int,greater<int> > *priorityObj) {
    cout << "Size = " << priorityObj->size() << endl;
	cout << "Top element = " << priorityObj->top() << endl;
	cout << "Current Heap: " << endl;
	for (int i=1; i<=priorityObj->size(); ++i) {
		cout << priorityObj->getHeap().getVec()[i] << " ";
	}
	cout << endl << endl;
}

int main() {
	const int n = 9;
	int data[n] = {0,1,2,3,4,8,9,3,5};
	MyPriorityQueue<int,greater<int> > *priorityObj1 = new MyPriorityQueue<int,greater<int> >(data,n);
	cout << "Current Heap: " << endl;
	show(priorityObj1);

	priorityObj1->pop();
	cout << "After pop one element:" << endl;
	show(priorityObj1);

	priorityObj1->pop();
	cout << "After pop one element:" << endl;
	show(priorityObj1);

	priorityObj1->push(7);
	cout << "After push one element 7:" << endl;
	show(priorityObj1);

	delete priorityObj1;
	return 0;
}
