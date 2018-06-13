/*
    Imam Linear List (imamLL) a simple C based linked list library
    
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

    Md Imam Hossain
    emamhd@gmail.com
*/

#include "imamll.h"

struct imamLL *imamLL_list_create (void)
{
    struct imamLL *tmp = NULL;
    tmp = (struct imamLL *) malloc(sizeof (struct imamLL));
    if (tmp == NULL) return NULL;
    else {
        tmp->current = NULL;
        tmp->first = NULL;
        tmp->last = NULL;
        tmp->number_of_elements = 0;
        tmp->size = 0;
        tmp->error = 0;
        return tmp;
    }
}

int imamLL_list_destroy (struct imamLL *list)
{
    if (list != NULL) {
        if (list->number_of_elements > 0) {
            if (imamLL_list_free (list) > 0) free (list);
            else return -1;
        }
        else free (list);
        return 0;
    }
    else return -1;
}

int imamLL_list_free (struct imamLL *list)
{
    struct imamLL_element *tmp = list->last;
    register int count = 0;
    if (tmp == NULL) {
        list->error = EMPTY_LIST;
        return -1;
    }
    while (tmp != NULL)
    {
        struct imamLL_element *prev = tmp->prev;
        tmp->prev = NULL;
        tmp->next = NULL;
        tmp->size = 0;
        free (tmp->data);
        tmp->data = NULL;
        free (tmp);
        tmp = prev;
        count++;
    }
    list->current = NULL;
    list->last = NULL;
    list->first = NULL;
    list->number_of_elements = 0;
    list->size = 0;
    list->error = 0;
    return count;
}

void imamLL_list_rewind (struct imamLL *list)
{
    list->current = NULL;
}

void imamLL_list_error (struct imamLL *list, char *error_message)
{
    if (list->error == MEMORY_ALLOCATION) strcpy (error_message, "Memory allocation for element failed");
    else if (list->error == EMPTY_LIST) strcpy (error_message, "Element list is empty");
    else if (list->error == NO_MATCHING_ELEMENT) strcpy (error_message, "Element is not found");
    else strcpy (error_message, "No error is found");
}

struct imamLL_element *imamLL_element_add (struct imamLL *list, unsigned long element_size, uint32_t position)
{
    if (list->first == NULL)
    {
        list->first = (struct imamLL_element *) malloc(sizeof (struct imamLL_element));
        if (list->first == NULL) {
            list->error = MEMORY_ALLOCATION;
            return NULL;
        }
        list->first->data = (char *) malloc (sizeof (char) * element_size);
        if (list->first->data == NULL) {
            free (list->first);
            list->error = MEMORY_ALLOCATION;
            return NULL;
        }
        list->first->prev = NULL;
        list->first->next = NULL;
        list->first->size = element_size;
        list->size = list->size + list->first->size;
        list->number_of_elements = list->number_of_elements + 1;
        list->last = list->first;
        return list->first;
    }
    else
    {
        struct imamLL_element *tmp = NULL;
        tmp = (struct imamLL_element *) malloc(sizeof (struct imamLL_element));
        if (tmp == NULL) {
            list->error = MEMORY_ALLOCATION;
            return NULL;
        }
        tmp->data = (char *) malloc (sizeof (char) * element_size);
        if (tmp->data == NULL) {
            free (tmp);
            list->error = MEMORY_ALLOCATION;
            return NULL;
        }
        if (position == AT_END) {
            tmp->prev = list->last;
            tmp->next = NULL;
            tmp->size = element_size;
            list->size = list->size + tmp->size;
            list->number_of_elements = list->number_of_elements + 1;
            list->last->next = tmp;
            list->last = tmp;
        }
        else if (position == AT_START) {
            tmp->prev = NULL;
            tmp->next = list->first;
            tmp->size = element_size;
            list->size = list->size + tmp->size;
            list->number_of_elements = list->number_of_elements + 1;
            list->first->prev = tmp;
            list->first = tmp;
        }
        else if (position == AT_CURRENT) {
            if (list->current == NULL) {
                tmp->prev = list->last;
                tmp->next = NULL;
                tmp->size = element_size;
                list->size = list->size + tmp->size;
                list->number_of_elements = list->number_of_elements + 1;
                list->last->next = tmp;
                list->last = tmp;
            }
            else {
                tmp->prev = list->current;
                tmp->next = list->current->next;
                tmp->size = element_size;
                list->size = list->size + tmp->size;
                list->number_of_elements = list->number_of_elements + 1;
                list->current->next = tmp;
                list->current->next->prev = tmp;
            }
        }
        return tmp;
    }
}

int imamLL_element_remove (struct imamLL *list, struct imamLL_element *element)
{
    int found = 0;
    struct imamLL_element *tmp = list->first;
    if (tmp == NULL) {
        list->error = EMPTY_LIST;
        return -1;
    }
    while (tmp != NULL)
    {
        if (memcmp (tmp, element, sizeof (struct imamLL_element)) == 0)
        {
            struct imamLL_element *next = tmp->next;
            struct imamLL_element *prev = tmp->prev;
            found = 1;
            list->number_of_elements = list->number_of_elements - 1;
            list->size = list->size - tmp->size;
            if ((tmp == list->first) && (tmp == list->last))
            {
                list->current = NULL;
                list->first = NULL;
                list->last = NULL;
                tmp->next = NULL;
                tmp->prev = NULL;
                tmp->size = 0;
                free (tmp->data);
                tmp->data = NULL;
                free (tmp);
                break;
            } 
            else if (tmp == list->first)
            {
                if (list->current == list->first) list->current = next;
                list->first = next;
                list->first->prev = NULL;
                tmp->next = NULL;
                tmp->prev = NULL;
                tmp->size = 0;
                free (tmp->data);
                tmp->data = NULL;
                free (tmp);
                break;
            }
            else if (tmp == list->last)
            {
                if (list->current == list->last) list->current = prev;
                list->last = prev;
                list->last->next = NULL;
                tmp->next = NULL;
                tmp->prev = NULL;
                tmp->size = 0;
                free (tmp->data);
                tmp->data = NULL;
                free (tmp);
                break;
            }
            else
            {
                if (list->current == tmp) list->current = next;
                next->prev = prev;
                prev->next = next;
                tmp->next = NULL;
                tmp->prev = NULL;
                tmp->size = 0;
                free (tmp->data);
                tmp->data = NULL;
                free (tmp);
                break;
            }
        }
        tmp = tmp->next;
    }
    if (found == 0) list->error = NO_MATCHING_ELEMENT;
    return found;
}

struct imamLL_element *imamLL_element_get (struct imamLL *list, void *element_data, uint64_t data_size)
{
    int found = 0;
    struct imamLL_element *tmp = list->first;
    if (tmp == NULL) return NULL;
    while (tmp != NULL)
    {
        if (tmp->size == data_size) {
            if (memcmp ((char *)tmp->data, (char *)element_data, tmp->size) == 0)
            {
                found = 1;
                break;
            }
        }
        tmp = tmp->next;
    }
    if (found == 1) return tmp;
    else {
        list->error = NO_MATCHING_ELEMENT;
        return NULL;
    }
}

struct imamLL_element *imamLL_element_get_next (struct imamLL *list)
{
    if (list->current == NULL) list->current = list->first;
    else list->current = list->current->next;
    if (list->current == NULL) return NULL;
    return list->current;
}

struct imamLL_element *imamLL_element_get_prev (struct imamLL *list)
{
    if (list->current == NULL) list->current = list->last;
    else list->current = list->current->prev;
    if (list->current == NULL) return NULL;
    return list->current;
}
