//Collen Larsen z1930118

int find_summit(int a[], int len) 
{
    int left = 0;
    int right = len - 1;
    
    while (left < right) 
	{
        int mid = left + (right - left) / 2;

        if (a[mid] > a[mid + 1]) 
		{
            
            right = mid;
        } 
		
		else 
		{
            
            left = mid + 1;
        }
    }
    
    return a[left];
}

