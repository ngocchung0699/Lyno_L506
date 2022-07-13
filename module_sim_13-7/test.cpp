#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ở đây chúng ta sẽ viết hàm truyền vào là 
int a[2]={2,5};

int *timSoLonNhat(int *x, int *y)
{
   if(*(x+1) ==*y)
   {
       return x+1; // trả về địa chỉ con trỏ x trỏ tới
   }
//    if (*x != *y)
//    {
//        return y; // trả về địa chỉ con trỏ y trỏ tới
//    }
}

int main()
{
   int *result;
   int b=5;
   result = timSoLonNhat(a,&b); // truyền vào địa chỉ của a và b
   printf("So lon nhat = %d\r\n",*result);
   return 0;
}
