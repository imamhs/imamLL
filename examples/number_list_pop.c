/*
    Copyright (c) 2023 Md Imam Hossain

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Md. Imam Hossain
    emamhd@gmail.com
*/

#include <stdio.h>
#include <imamll.h>

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
