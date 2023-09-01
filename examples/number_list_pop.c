#include <stdio.h>
#include "imamll.h"

struct imamLL *number_list = NULL;
struct imamLL_element *element = NULL;
long number;
char enter = 0;

int main (void)
{

    number_list = imamLL_list_create ();

    if (number_list == NULL) {
        printf ("Can not create list\n");
        exit (EXIT_FAILURE);
    }

    for (number = 0; number < 10; number++) {
        element = imamLL_element_add (number_list, sizeof (number), AT_CURRENT);
        if (element == NULL) printf ("Error allocating memory for a number\n");
        else memcpy (element->data, &number, sizeof(number));
    }

    printf ("There are %lu numbers in the list\n", number_list->number_of_elements);
    printf ("Total memory allocated %lu bytes\n\n", number_list->size);

    imamLL_element_remove_number(number_list, FORWARD, 1, &number);

    printf ("Popped %ld\n", number);

    element = imamLL_list_rewind (number_list, BACKWARD, 0);

    while (1) {
        if (element == NULL) break;
        else printf ("%ld\n", *((long *)element->data));
        element = imamLL_element_get_next (number_list);
    }

    if (imamLL_list_destroy (number_list) == -1) printf ("Can not free memory\n");

    return 0;
}
