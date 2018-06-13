/*
    Copyright (c) 2015 Md Imam Hossain

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
#include <stdlib.h>
#include <string.h>

#include <imamll.h>

struct imamLL *product_list = NULL;
struct imamLL_element *element = NULL;
struct imamLL_element *temp = NULL;

char product[128];

int main (int argc, char** argv)
{
    
    product_list = imamLL_list_create ();
    
    if (product_list == NULL) {
        printf ("Can not create list\n");
        exit (EXIT_FAILURE);
    }

    strcpy (product, "Bearing");
    element = imamLL_element_add (product_list, strlen (product) + 1, AT_END);
    if (element == NULL) printf ("Error allocating memory for Bearing element\n");
    strcpy ((char *)element->data, product);
       
    strcpy (product, "Switch");
    element = imamLL_element_add (product_list, strlen (product) + 1, AT_END);
    if (element == NULL) printf ("Error allocating memory for Switch element\n");
    strcpy ((char *)element->data, product);
    
    strcpy (product, "Nozzle");
    element = imamLL_element_add (product_list, strlen (product) + 1, AT_END);
    if (element == NULL) printf ("Error allocating memory for Nozzle element\n");
    strcpy ((char *)element->data, product);
    
    imamLL_list_rewind (product_list);
    while (1) {
        element = imamLL_element_get_next (product_list);
        if (element == NULL) break;
        else printf ("%s\n", (char *)element->data);
    }
    
    printf ("There are %ld elements in the list\n", product_list->number_of_elements);
    printf ("Total memory allocated %ld bytes\n", product_list->size);
    
    strcpy (product, "Nozzle");
    element = imamLL_element_get (product_list, product, strlen (product) + 1);
    
    if (element == NULL) printf ("Error getting the Nozzle element");
    else {
        if (imamLL_element_remove (product_list, element) != 1) printf ("Error removing the Nozzle element\n");
    }
    
    imamLL_list_rewind (product_list);
    while (1) {
        element = imamLL_element_get_next (product_list);
        if (element == NULL) break;
        else printf ("%s\n", (char *)element->data);
    }
    
    printf ("There are %ld elements in the list\n", product_list->number_of_elements);
    printf ("Total memory allocated %ld bytes\n", product_list->size);
    
    if (imamLL_list_destroy (product_list) == -1) printf ("Can not free memory\n");
    
    return EXIT_SUCCESS;
}
