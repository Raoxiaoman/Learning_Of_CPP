#include <iostream>
#include <vector>

using namespace std;
void maxHeapify(vector<int> &vect,size_t index,size_t heapSize)
{
    size_t leftIndex = 2 * index+1;
    size_t rightIndex = 2 * (index+1);
    size_t imax = index;

    if(vect[leftIndex] > vect[index] && leftIndex < heapSize){
        imax = leftIndex;
    }
    if(vect[rightIndex] > vect[imax] && rightIndex < heapSize){
        imax = rightIndex;
    }
    if (imax!=index) {
        swap(vect[index], vect[imax]);
        maxHeapify(vect,imax,heapSize);
    }
    
}

void buidlMaxHeap(vector<int>&vect){
    int iParent = vect.size()/2;
    for(int i = iParent;i>=0;i--){
        maxHeapify(vect, i,vect.size());
    }
}


void heapSort(vector<int> &vect){
    buidlMaxHeap(vect);

    int heapSize = (int)vect.size();

    for(int i = heapSize-1;i>=0;i--){
        swap(vect[i],vect[0]);
        maxHeapify(vect,0,i);
    }
}

void display(vector<int>& vect){
    for (auto i : vect) {
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    vector<int> vect = {9,7,8,11,5,3,4,1,2};
    display(vect);
    heapSort(vect);
    display(vect);

    return 0;
}
