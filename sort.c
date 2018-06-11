#include <stdio.h>
void print(int a[], int n){
    for(int j= 0; j<n; j++){
        printf("%d ",a[j]);
    }
    printf("\n");
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*插入排序(Insertion Sort) 1
* 直接插入排序(Straight Insertion Sort):
* 将一个记录插入到已排序好的有序表中，从而得到一个新，记录数增1的有序表。即：先将序列的第1个记录看成是一个有序的子序列，
* 然后从第2个记录逐个进行插入，直至整个序列有序为止。
* 要点：设立哨兵，作为临时存储和判断数组边界之用。
*/
void StraightInsertSort(int A[], int n)
{
    if (n < 2) return;
    for(int i= 1; i<n; i++){
        if(A[i] < A[i-1]){     //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j= i-1;
            int x = A[i];      //复制为哨兵，即存储待排序元素
            A[i] = A[i-1];     //先后移一个元素
            while(x < A[j]){   //查找在有序表的插入位置
                A[j+1] = A[j];
                j--;           //元素后移
            }
            A[j+1] = x;        //插入到正确位置
        }
    }
}

/*插入排序(Insertion Sort) 2
* 希尔排序（Shell`s Sort）:
* 基本思想：
* 先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。
* 操作方法：
* 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；
* 按增量序列个数k，对序列进行k 趟排序；
* 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m的子序列，分别对各子表进行直接插入排序。仅增量因子为1时，整个序列作为一个表来处理，表长度即为整个序列的长度。
*/
void ShellSort(int A[], int n){
    if (n < 2) return;
    int dk = n/2;
    while( dk >= 1  ){
        for(int i= dk; i<n; ++i){
            if(A[i] < A[i-dk]){          //若第i个元素大于i-dk元素，直接插入。小于的话，移动有序表后插入
                int j = i-dk;
                int x = A[i];           //复制为哨兵，即存储待排序元素
                A[i] = A[i-dk];         //首先后移一个元素
                while(x < A[j]){     //查找在有序表的插入位置
                    A[j+dk] = A[j];
                    j -= dk;             //元素后移
                }
                A[j+dk] = x;            //插入到正确位置
            }
        }
        dk = dk/2;
    }
}

/*选择排序(Selection Sort) 1
* 简单选择排序(Simple Selection Sort)
* 在要排序的一组数中，选出最小（或者最大）的一个数与第1个位置的数交换；然后在剩下的数当中再找最小（或者最大）的与第2个位置的数交换，
* 依次类推，直到第n-1个元素（倒数第二个数）和第n个元素（最后一个数）比较为止。
*/
void SimpleSelectSort(int A[], int n){
    if (n < 2) return;
    int key = 0, tmp = 0;
    for(int i = 0; i< n; ++i) {
        for(int j= i+1; j<n; ++j){  ////选择最小的元素
            if(A[key] > A[j])
                key = j;
        }
        if(key != i){
            swap(&A[key], &A[i]); //最小元素与第i位置元素互换
        }
    }
}

/*选择排序(Selection Sort) 1.1
* 二元选择排序(Dualistic Selection Sort)
* 简单选择排序，每趟循环只能确定一个元素排序后的定位。我们可以考虑改进为每趟循环确定两个元素（当前趟最大和最小记录）的位置,从而减少排序所需的循环次数。
* 改进后对n个数据进行排序，最多只需进行[n/2]趟循环即可。具体实现如下：
*/
void DualisticSelectSort(int A[],int n) {
    if (n < 2) return;
    int i , j, min, max, tmp;
    for (i=1 ;i <= n/2;i++) {
        // 做不超过n/2趟选择排序
        min = i; max = i; //分别记录最大和最小关键字记录位置
        for (j= i+1; j<= n-i; j++) {
            if (A[j] > A[max]) {
                max = j;
                continue;
            }
            if (A[j]< A[min]) {
                min = j;
            }
      }
      //该交换操作还可分情况讨论以提高效率
      swap(&A[i-1], &A[min]);
      swap(&A[n-i], &A[max]);
    }
}



/*
 选择排序—堆排序（Heap Sort）
堆排序是一种树形选择排序，是对直接选择排序的有效改进。
基本思想：
* 若以一维数组存储一个堆，则堆对应一棵完全二叉树，且所有非叶结点的值均不大于(或不小于)其子女的值，根结点（堆顶元素）的值是最小(或最大)的。
* 初始时把要排序的n个数的序列看作是一棵顺序存储的二叉树（一维数组存储二叉树），调整它们的存储序，使之成为一个堆，将堆顶元素输出，得到n个元素中最小(或最大)的元素，
* 这时堆的根节点的数最小（或者最大）。然后对前面(n-1)个元素重新调整使之成为堆，输出堆顶元素，得到n 个元素中次小(或次大)的元素。依此类推，
* 直到只有两个节点的堆，并对它们作交换，最后得到有n个节点的有序序列。称这个过程为堆排序。
*/

/**
* 已知H[s…m]除了H[s] 外均满足堆的定义
* 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,
*
* @param H是待调整的堆数组
* @param s是待调整的数组元素的位置
* @param length是数组的长度
*
*/
void HeapAdjust(int A[],int s, int n)
{
    int tmp  = A[s];
    int child = 2*s+1; //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)
    while (child < n) {
        if(child+1 <n && A[child]<A[child+1]) { // 如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)
            ++child ;
        }
        if(A[s]<A[child]) {  // 如果较大的子结点大于父结点
            A[s] = A[child]; // 那么把较大的子结点往上移动，替换它的父结点
            s = child;       // 重新设置s ,即待调整的下一个结点的位置
            child = 2*s+1;
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出
             break;
        }
        A[s] = tmp;         // 当前待调整的结点放到比其大的孩子结点位置上
    }
}
/**
* 初始堆进行调整
* 将H[0..length-1]建成堆
* 调整完之后第一个元素是序列的最小的元素
*/
void BuildingHeap(int A[], int n)
{
    //最后一个有孩子的节点的位置 i=  (length -1) / 2
    for (int i = (n -1) / 2 ; i >= 0; --i)
        HeapAdjust(A,i,n);
}
/**
* 堆排序算法
*/
void HeapSort(int A[],int n)
{
    if (n < 2) return;
    //初始堆
    BuildingHeap(A, n);
    //从最后一个元素开始对序列进行调整
    for (int i = n - 1; i > 0; --i)
    {
        //交换堆顶元素H[0]和堆中最后一个元素
        swap(&A[i], &A[0]);
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整
        HeapAdjust(A,0,i);
  }
}


/*交换排序(Swap Sort) 1
* 交换排序—冒泡排序（Bubble Sort):
* 在要排序的一组数中，对当前还未排好序的范围内的全部数，自上而下对相邻的两个数依次进行比较和调整，让较大的数往下沉，较小的往上冒。
* 即：每当两相邻的数比较后发现它们的排序与排序要求相反时，就将它们互换。
*/
void BubbleSort(int A[], int n){
    if (n < 2) return;
    for(int i =0 ; i< n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(A[j] > A[j+1])
            {
                swap(&A[j], &A[j+1]); //swap
            }
        }
    }
}
/*
* 对冒泡排序常见的改进方法是加入一标志性变量exchange，用于标志某一趟排序过程中是否有数据交换，如果进行某一趟排序时并没有进行数据交换，
* 则说明数据已经按要求排列好，可立即结束排序，避免不必要的比较过程。本文再提供以下两种改进算法：
* 1．设置一标志性变量pos,用于记录每趟排序中最后一次进行交换的位置。由于pos位置之后的记录均已交换到位,故在进行下一趟排序时只要扫描到pos位置即可。
*/
void BubbleSort_1 ( int A[], int n) {
    if (n < 2) return;
    int i= n -1;  //初始时,最后位置保持不变
    while ( i> 0) {
        int pos= 0; //每趟开始时,无记录交换
        for (int j= 0; j< i; j++)
            if (A[j]> A[j+1]) {
                pos= j; //记录交换的位置
                swap(&A[j], &A[j+1]); //swap
            }
        i= pos; //为下一趟排序作准备
     }
}
/*
* 2．传统冒泡排序中每一趟排序操作只能找到一个最大值或最小值,我们考虑利用在每趟排序中进行正向和反向两遍冒泡的方法一次可以得到两个最终值(最大者和最小者) ,
* 从而使排序趟数几乎减少了一半。
*/
void BubbleSort_2 ( int A[], int n){
    if (n < 2) return;
    int low = 0;
    int high= n -1; //设置变量的初始值
    int tmp,j;
    while (low < high) {
        for (j= low; j< high; ++j){  //正向冒泡,找到最大者
            if (A[j]> A[j+1]) {
                swap(&A[j], &A[j+1]); //swap
            }
        }
        --high;                 //修改high值, 前移一位
        for ( j=high; j>low; --j){  //反向冒泡,找到最小者
            if (A[j]<A[j-1]) {
                swap(&A[j], &A[j-1]); //swap
            }
        }
        ++low;                  //修改low值,后移一位
    }
}

/*BubbleSort_1 + BubbleSort_2*/
void BubbleSort_3 ( int A[], int n){
    if (n < 2) return;
    int low = 0;
    int high= n -1; //设置变量的初始值
    int tmp,j;
    int pos1= 0, pos2=0; //每趟开始时,无记录交换
    while (low < high) {
        for (j= low; j< high; ++j) {//正向冒泡,找到最大者
            if (A[j]> A[j+1]) {
                pos1 = j;
                swap(&A[j], &A[j+1]); //swap
            }
        }
        high = pos1; //修改high值, 前移
        pos2 = high;
        for ( j=high; j>low; --j) {//反向冒泡,找到最小者
            if (A[j]<A[j-1]) {
                pos2 = j;
                swap(&A[j], &A[j-1]); //swap
            }
        }
        low=pos2;   //修改low值,后移
    }
}

/*交换排序(Swap Sort) 2
* 交换排序—快速排序（Quick Sort）
* 1）选择一个基准元素,通常选择第一个元素或者最后一个元素,
* 2）通过一趟排序将待排序的记录分割成独立的两部分，其中一部分记录的元素值均比基准元素值小。另一部分记录的元素值比基准值大。
* 3）此时基准元素在其排好序后的正确位置
* 4）然后分别对这两部分记录用同样的方法继续进行排序，直到整个序列有序。
*/

void QuickSort(int A[], int n) {
  if (len < 2) return;

  int pivot = A[n / 2]; //选择一个基准元素

  int i, j;
  //将待排序的记录分割成独立的两部分
  for (i = 0, j = n - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;

    if (i >= j) break;

    swap(&A[i], &A[j]);
  }

  QuickSort(A, i); //一部分记录的元素值均比基准元素值小
  QuickSort(A + i, len - i); //一部分记录的元素值比基准值大
}

int main(){
    int a[20] = {20,13,14,3,1,5,7,15,16,17,2,4,18,9,6,19,10,8, 12, 11};
    print(a,20);
    QuickSort(a,20);
    print(a,20);
}

