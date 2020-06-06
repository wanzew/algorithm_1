#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;


template<typename Item>
class MaxHeap{

private:
    Item *data;
    int count;
    int capacity;

    void shiftUp(int k){
        while( k > 1 && data[k/2] < data[k] ){
            swap( data[k/2], data[k] );
            k /= 2;
        }
    }
    /*
    那么对于数组我们怎么操作父结点和左右子结点呢？对于完全二叉树采用顺序存储表示，那么对于任意一个下标为i(1 ≤ i ≤ n)的结点：
    （1）、父结点为：i / 2（i ≠ 1），若i = 1，则i是根节点。
    （2）、左子结点：2i（2i ≤ n）， 若不满足则无左子结点。
    （3）、右子结点：2i + 1(2i + 1 ≤ n)，若不满足则无右子结点。
    */
    void shiftDown(int k){
        while( 2*k <= count ){
            int j = 2*k; // 在此轮循环中,data[k]和data[j]交换位置
            if( j+1 <= count && data[j+1] > data[j] )
                j ++;
            // data[j] 是 data[2*k]和data[2*k+1]中的最大值

            if( data[k] >= data[j] ) break;
            swap( data[k] , data[j] );
            k = j;
        }
    }

public:
    // 构造函数, 构造一个空堆, 可容纳capacity个元素
    MaxHeap(int capacity){
        data = new Item[capacity+1];
        count = 0;
        this->capacity = capacity;
    }

    ~MaxHeap(){
        delete[] data;
    }

    // 返回堆中的元素个数
    int size(){
        return count;
    }

    // 返回一个布尔值, 表示堆中是否为空
    bool isEmpty(){
        return count == 0;
    }

    // 像最大堆中插入一个新的元素 item
    void insert(Item item){
        assert( count + 1 <= capacity );
        data[count+1] = item;
        shiftUp(count+1);
        count ++;
    }

    // 从最大堆中取出堆顶元素, 即堆中所存储的最大数据
    Item extractMax(){
        assert( count > 0 );
        Item ret = data[1];

        swap( data[1] , data[count] );
        count --;
        shiftDown(1);

        return ret;
    }

    // 获取最大堆中的堆顶元素
    Item getMax(){
        assert( count > 0 );
        return data[1];
    }

};


// 测试最大堆
int main() {

    MaxHeap<int> maxheap = MaxHeap<int>(100);

    srand(time(NULL));
    int n = 100;    // 随机生成n个元素放入最大堆中
    for( int i = 0 ; i < n ; i ++ ){
        maxheap.insert( rand()%100 );
    }

    int* arr = new int[n];
    // 将maxheap中的数据逐渐使用extractMax取出来
    // 取出来的顺序应该是按照从大到小的顺序取出来的
    for( int i = 0 ; i < n ; i ++ ){
        arr[i] = maxheap.extractMax();
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    // 确保arr数组是从大到小排列的
    for( int i = 1 ; i < n ; i ++ )
        assert( arr[i-1] >= arr[i] );

    delete[] arr;


    return 0;
}