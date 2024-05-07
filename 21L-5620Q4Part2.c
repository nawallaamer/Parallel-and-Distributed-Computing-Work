#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void one_to_all_broadcast(int d, int my_id, int source, int X) 
{
    int my_virtual_id = my_id ^ source;
    int mask = (1 << d) - 1;
    int virtual_dest, virtual_source;
    for (int r = d - 1; r >= 0; r--) 
    {
        mask ^= (1 << r); 
        if ((my_virtual_id & mask) == 0) 
        {
            if ((my_virtual_id & (1 << r)) == 0) 
            {
                virtual_dest = my_virtual_id ^ (1 << r);
                printf("Node %d sends message %d to node %d\n", my_id, X, (virtual_dest ^ source));
            } 
            else 
            {
                virtual_source = my_virtual_id ^ (1 << r);
                printf("Node %d receives message %d from node %d\n", my_id, X, (virtual_source ^ source));
            }
        }
    }
}
int main() 
{
    int d, num_nodes, i, source, message;
    printf("Enter the Number of Nodes: ");
    scanf("%d", &num_nodes);
    printf("Enter the Source Node: ");
    scanf("%d", &source);
    printf("Enter the Message to Broadcast: ");
    scanf("%d", &message);
    for (int r = 0; r < num_nodes; r++) 
    {
        one_to_all_broadcast(log(num_nodes)/log(2), r, source, message);
    }
    return 0;
}
