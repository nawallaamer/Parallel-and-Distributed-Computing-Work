#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define D 3

void general_one_to_all_bc(int d, int my_id, int source, int array[]) 
{
    int my_virtual_id = my_id ^ source;
    int mask = (1 << (2 * d)) - 1;
    for (int i = d - 1; i >= 0; i--) 
    {
        mask ^= (1 << i);
        if ((my_virtual_id & mask) == 0) 
        {
            if ((my_virtual_id & (1 << i)) == 0) 
            {
                int virtual_dest = my_virtual_id ^ (1 << i);
                printf("Process %d to Process %d\n", my_id, (virtual_dest ^ source));
                array[virtual_dest ^ source] = array[my_id];
            } 
            else 
            {
                int virtual_source = my_virtual_id ^ (1 << i);
                printf("Process %d receives from Process %d\n", my_id, (virtual_source ^ source));
            }
        }
    }

}
int main() 
{
    int processno = 1 << D; 
    int source = 0; 
    int array[8];
    array[0] = 25317;
    int r = 1;
    while (r < 8)
    {
        array[r] = 0;
        r++;
    }
    printf("Before BroadCast:\n");
    int k = 0;
    while (k < 8)
    {
        printf("%d ",array[k]);
        k++;
    }
    printf("\n");
    k = 0;
    while (k < processno) 
    {
        general_one_to_all_bc(D, k, source, array); 
        k++;
    }
    printf("After Broadcast:\n");
    int a = 0;
    while (a < 8)
    {
        printf("%d ",array[a]);
        a++;
    }
    printf("\n");
    return 0;
}
