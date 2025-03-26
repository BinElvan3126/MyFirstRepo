#include <iostream>

using namespace std;

int findMin(int arr[], int n)
{
    int low = 0, high = n - 1;
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] > arr[high])
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return arr[low];
}

int main()
{
    int nums[] = {4, 5, 6, 7, 0, 1, 2};
    int n = sizeof(nums) / sizeof(nums[0]);

    cout << "Minimum element in array: " << findMin(nums, n) << endl;

    return 0;
}
