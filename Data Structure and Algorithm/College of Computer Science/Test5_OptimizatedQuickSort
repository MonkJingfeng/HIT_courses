#include <bits/stdc++.h>
using namespace std;

//取待排序序列中low、mid、high三个位置上数据，选取他们中间的那个数据作为枢轴,消除了预排序输入的不好情形
int SelectPivotMedianOfThree(int arr[],int low,int high)
{
    int mid = low + ((high - low) >> 1);//计算数组中间的元素的下标

    //使用三数取中法选择枢轴
    if (arr[mid] > arr[high])//目标: arr[mid] <= arr[high]
    {
        swap(arr[mid],arr[high]);
    }
    if (arr[low] > arr[high])//目标: arr[low] <= arr[high]
    {
        swap(arr[low],arr[high]);
    }
    if (arr[mid] > arr[low]) //目标: arr[low] >= arr[mid]
    {
        swap(arr[mid],arr[low]);
    }
    //此时，arr[mid] <= arr[low] <= arr[high]
    //low的位置上保存这三个位置中间的值
    //分割时可以直接使用low位置的元素作为枢轴，而不用改变分割函数了
    return arr[low];
}

//普通插入排序
void InsertSort(int arr[], int low, int high)
{
    for (int i=low; i<=high; i++)
    {
        if (arr[i-1] > arr[i])
        {
            int tmp = arr[i];
            int j = i;
            while (j > 0 && arr[j-1] > tmp)
            {
                arr[j] = arr[j-1];
                j--;
            }
            arr[j] = tmp;
        }
    }
}

void QSort(int arr[],int low,int high)
{
    int first = low;
    int last = high;

    int left = low;
    int right = high;

    int leftLen = 0;
    int rightLen = 0;

    if (high - low + 1 < 10)  //对于很小的数组，插入排序效果较好
    {
        InsertSort(arr,low,high);
        return;
    }

    //一次分割
    int key = SelectPivotMedianOfThree(arr,low,high);//使用三数取中法选择枢轴

    while(low < high)
    {
        while(high > low && arr[high] >= key)
        {
            if (arr[high] == key)//处理相等元素，在划分过程中，把与key相等元素放入数组的两端
            {
                swap(arr[right],arr[high]);
                right--;
                rightLen++;
            }
            high--;
        }
        arr[low] = arr[high];
        while(high > low && arr[low] <= key)
        {
            if (arr[low] == key)
            {
                swap(arr[left],arr[low]);
                left++;
                leftLen++;
            }
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = key;

    //一次快排结束
    //把与枢轴key相同的元素移到枢轴最终位置周围，继续下次分割时，不用再对与key相等元素分割
    int i = low - 1;
    int j = first;
    while(j < left && arr[i] != key)
    {
        swap(arr[i],arr[j]);
        i--;
        j++;
    }
    i = low + 1;
    j = last;
    while(j > right && arr[i] != key)
    {
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    QSort(arr,first,low - 1 - leftLen);
    QSort(arr,low + 1 + rightLen,last);
}

//传统快排
void plainQSort(int arr[], int l, int r)
{
    int i = l, j = r, mid = arr[l];
    while (i <= j) {
        while (arr[i] < mid) i++;
        while (arr[j] > mid) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++, j--;
        }
    }
    if (l < j) plainQSort(arr, l, j);
    if (i < r) plainQSort(arr, i, r);
}

int t = 4, n, a[100005], b[100005], Start, End;
int main()
{
    freopen("large_in.txt","r",stdin);
    while (t--) {
        if (t) {
            scanf("%d", &n);
            for (int i=0; i<n; i++) scanf("%d", &a[i]);
            for (int i=0; i<n; i++) b[i] = a[i];
        } else {
            scanf("%d", &n);
            for (int i=0; i<n; i++) a[i] = b[i] = 10;
        }
        switch (t) {
        case 3:printf("%d 随机数据\n",n);break;
        case 2:printf("%d 正序数据\n",n);break;
        case 1:printf("%d 逆序数据\n",n);break;
        case 0:printf("%d 重复数据\n",n);break;
        }
        Start = clock();
        plainQSort(a, 0, n - 1);
        End = clock();
        printf("传统快排： %dms\n",End - Start);
        Start = clock();
        QSort(b, 0, n - 1);
        End = clock();
        printf("优化快排： %dms\n",End - Start);
    }
    return 0;
}
