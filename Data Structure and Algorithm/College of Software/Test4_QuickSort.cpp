#include <stdio.h>
const int maxn = 23333;
int numArray[maxn];
int cnt = 0, numArraySize;
int partition(int *numArray, int l, int r) {
    //将区间最左值选为基准值
    int base = numArray[l];
    //左右两端同时向中间逼近
    while (l < r) {
        //在l右边从r到小查找比基准小的第一个值
        while (l < r && numArray[r] > base)
            r--;
        //若找到，将此值赋给numArray[l]
        if (l < r)
            numArray[l] = numArray[r];
        //在r左边从l到大查找比基准大的第一个值
        while (l < r && numArray[l] < base)
            l++;
        //若找到，将此值赋给numArray[r]
        if (l < r)
            numArray[r] = numArray[l];
    }
    //将r与l重合处赋为基准值
    numArray[l] = base;
    //输出中间结果
    printf("第%d次排序结果如下：",++cnt);
    for (int i=1; i<=numArraySize; i++)
        printf("%-5d%c",numArray[i],i==numArraySize?'\n':' ');
    //返回基准值的下标
    return l;
}
void quickSort(int *numArray, int l, int r) {
    if (l < r) {
        int tmp = partition(numArray, l, r);
        //固定基准点，分治
        quickSort(numArray, l, tmp-1);
        quickSort(numArray, tmp+1, r);
    }
}
int main() {
    printf("请输入排序数组个数：");
    scanf("%d", &numArraySize);
    puts("请依次输入数组各元素值：");
    for (int i=1; i<=numArraySize; i++)
        scanf("%d", &numArray[i]);
    quickSort(numArray, 1, numArraySize);
    puts("排序完成。有序数组如下：");
    for (int i=1; i<=numArraySize; i++)
        printf("%-5d%c", numArray[i], i==numArraySize?'\n':' ');
    return 0;
}
