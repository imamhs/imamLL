/*
    Imam Linear List (imamLL) a simple C based linked list library
    
    Copyright (c) 2015-2023 Md Imam Hossain

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

const uint8_t imamLL_s = sizeof (struct imamLL);
const uint8_t imamLL_element_s = sizeof (struct imamLL_element);

struct imamLL *imamLL_list_create (void)
{
    struct imamLL *tmp = NULL;
    tmp = (struct imamLL *) malloc(imamLL_s);
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
    size_t count = 0;
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

struct imamLL_element *imamLL_list_rewind (struct imamLL *list, int8_t direction, size_t steps)
{
    if (steps == list->number_of_elements) return list->current;
    else if (steps == 0) {
        if (direction == BACKWARD) list->current = list->first;
        else if (direction == FORWARD) list->current = list->last;
    }
    else {
        size_t count = 0;
        struct imamLL_element *tmp = NULL;
        if (direction == BACKWARD) tmp = list->first;
        else if (direction == FORWARD) tmp = list->last;
        while ((tmp != NULL) && (count < steps)) {
            count++;
            if (direction == BACKWARD) tmp = tmp->next;
            else if (direction == FORWARD) tmp = tmp->prev;
        }
        list->current = tmp;
    }
    return list->current;
}

void imamLL_list_error (struct imamLL *list, char *error_message)
{
    if (list->error == MEMORY_ALLOCATION_FAILED) strcpy (error_message, "memory allocation for the element failed");
    else if (list->error == EMPTY_LIST) strcpy (error_message, "element list is empty");
    else if (list->error == NO_MATCHING_ELEMENT) strcpy (error_message, "element is not found");
    else strcpy (error_message, "no errors found");
}

struct imamLL_element *imamLL_element_add (struct imamLL *list, size_t element_size, uint8_t position)
{
    if (list->first == NULL) {
        list->first = (struct imamLL_element *) malloc(imamLL_element_s);
        if (list->first == NULL) {
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        list->first->data = (char *) malloc (sizeof (char) * element_size);
        if (list->first->data == NULL) {
            free (list->first);
            list->first = NULL;
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        list->first->prev = NULL;
        list->first->next = NULL;
        list->first->size = element_size;
        list->size = list->size + list->first->size;
        list->number_of_elements = list->number_of_elements + 1;
        list->last = list->first;
        list->current = list->first;
        return list->first;
    }
    else {
        struct imamLL_element *tmp = NULL;
        tmp = (struct imamLL_element *) malloc(imamLL_element_s);
        if (tmp == NULL) {
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        tmp->data = (char *) malloc (sizeof (char) * element_size);
        if (tmp->data == NULL) {
            free (tmp);
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        if (position == AT_END) {
            tmp->prev = list->last;
            tmp->next = NULL;
            list->last->next = tmp;
            list->last = tmp;
        }
        else if (position == AT_START) {
            tmp->prev = NULL;
            tmp->next = list->first;
            list->first->prev = tmp;
            list->first = tmp;
        }
        else if (position == AT_CURRENT) {
            if (list->current == NULL) {
                tmp->prev = list->last;
                tmp->next = NULL;
                list->last->next = tmp;
                list->last = tmp;
            }
            else if (list->current->next == NULL) {
                tmp->prev = list->current;
                tmp->next = NULL;
                list->current->next = tmp;
                list->last = tmp;
            }
            else {
                struct imamLL_element *next = list->current->next;
                tmp->prev = list->current;
                tmp->next = list->current->next;
                list->current->next = tmp;
                next->prev = tmp;
            }
        }
        tmp->size = element_size;
        list->size = list->size + tmp->size;
        list->number_of_elements = list->number_of_elements + 1;
        list->current = tmp;
        return tmp;
    }
}

struct imamLL_element *imamLL_element_add_number (struct imamLL *list, size_t element_size, int8_t direction, size_t num)
{
    size_t count = 0;
    struct imamLL_element *cursor = NULL;
    struct imamLL_element *tmp = NULL;
    struct imamLL_element *next = NULL;
    struct imamLL_element *prev = NULL;

    if (list->first == NULL) {
        list->first = (struct imamLL_element *) malloc(imamLL_element_s);
        if (list->first == NULL) {
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        list->first->data = (char *) malloc (sizeof (char) * element_size);
        if (list->first->data == NULL) {
            free (list->first);
            list->first = NULL;
            list->error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        list->first->prev = NULL;
        list->first->next = NULL;
        list->first->size = element_size;
        list->size = list->size + list->first->size;
        list->number_of_elements = list->number_of_elements + 1;
        list->last = list->first;
        list->current = list->first;
        return list->first;
    }

    if (num == list->number_of_elements) return list->current;

    if (direction == BACKWARD) cursor = list->first;
    else if (direction == FORWARD) cursor = list->last;

    while ((cursor != NULL) && (count < num)) {
        count++;
        if (direction == BACKWARD) cursor = cursor->next;
        else if (direction == FORWARD) cursor = cursor->prev;
    }

    next = cursor->next;
    prev = cursor->prev;

    tmp = (struct imamLL_element *) malloc(imamLL_element_s);
    if (tmp == NULL) {
        list->error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    tmp->data = (char *) malloc (sizeof (char) * element_size);
    if (tmp->data == NULL) {
        free (tmp);
        list->error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    if ((next != NULL) && (prev != NULL)) {
        tmp->next = next;
        next->prev = tmp;
    }
    else if ((next != NULL) && (prev == NULL)) {
        tmp->next = next;
        next->prev = tmp;
        list->first = cursor;
    }
    else if ((prev != NULL) && (next == NULL)) {
        tmp->next = NULL;
        list->last = tmp;
    }

    cursor->next = tmp;
    tmp->prev = cursor;
    tmp->size = element_size;
    list->current = tmp;
    list->number_of_elements = list->number_of_elements + 1;
    list->size = list->size + tmp->size;

    return tmp;
}

void imamLL_element_remove_number (struct imamLL *list, int8_t direction, size_t num, void *pop_data)
{
    size_t count = 0;
    struct imamLL_element *cursor = NULL;
    struct imamLL_element *next = NULL;
    struct imamLL_element *prev = NULL;

    if (num == list->number_of_elements) return;

    if (direction == BACKWARD) cursor = list->first;
    else if (direction == FORWARD) cursor = list->last;

    if (cursor == NULL) {
        list->error = EMPTY_LIST;
        return;
    }

    while ((cursor != NULL) && (count < num)) {
        count++;
        if (direction == BACKWARD) cursor = cursor->next;
        else if (direction == FORWARD) cursor = cursor->prev;
    }

    next = cursor->next;
    prev = cursor->prev;

    if ((next != NULL) && (prev != NULL)) {
        next->prev = prev;
        prev->next = next;
        list->current = next;
    }
    else if ((next != NULL) && (prev == NULL)) {
        next->prev = NULL;
        list->first = next;
        list->current = next;
    }
    else if ((prev != NULL) && (next == NULL)) {
        prev->next = NULL;
        list->last = prev;
        list->current = prev;
    }

    if (pop_data != NULL) memcpy (pop_data, cursor->data, cursor->size);

    list->number_of_elements = list->number_of_elements - 1;
    list->size = list->size - cursor->size;

    cursor->next = NULL;
    cursor->prev = NULL;
    cursor->size = 0;
    free (cursor->data);
    cursor->data = NULL;
    free (cursor);
}

int imamLL_element_remove (struct imamLL *list, struct imamLL_element *element, void *pop_data)
{
    if (list->number_of_elements == 0) {
        list->error = EMPTY_LIST;
        return -1;
    }

    if (element == NULL) {
        struct imamLL_element *tmp = list->current;
        struct imamLL_element *next = list->current->next;
        struct imamLL_element *prev = list->current->prev;

        if ((tmp == list->first) && (tmp == list->last)) {
            list->current = NULL;
            list->first = NULL;
            list->last = NULL;
        }
        else if (tmp == list->first) {
            list->current = next;
            list->first = next;
            list->first->prev = NULL;
        }
        else if (tmp == list->last) {
            list->current = prev;
            list->last = prev;
            list->last->next = NULL;
        }
        else {
            list->current = next;
            next->prev = prev;
            prev->next = next;
        }

        if (pop_data != NULL) memcpy (pop_data, tmp->data, tmp->size);

        list->number_of_elements = list->number_of_elements - 1;
        list->size = list->size - tmp->size;
        tmp->next = NULL;
        tmp->prev = NULL;
        tmp->size = 0;
        free (tmp->data);
        tmp->data = NULL;
        free (tmp);
        return 1;
    }
    else {
        int found = 0;
        struct imamLL_element *tmp = list->first;

        while (tmp != NULL) {
            if (memcmp (tmp, element, imamLL_element_s) == 0) {
                struct imamLL_element *next = tmp->next;
                struct imamLL_element *prev = tmp->prev;
                if ((tmp == list->first) && (tmp == list->last)) {
                    list->current = NULL;
                    list->first = NULL;
                    list->last = NULL;
                }
                else if (tmp == list->first) {
                    if (list->current == list->first) list->current = next;
                    list->first = next;
                    list->first->prev = NULL;
                }
                else if (tmp == list->last) {
                    if (list->current == list->last) list->current = prev;
                    list->last = prev;
                    list->last->next = NULL;
                }
                else {
                    if (list->current == tmp) list->current = next;
                    next->prev = prev;
                    prev->next = next;
                }

                if (pop_data != NULL) memcpy (pop_data, tmp->data, tmp->size);

                found = 1;
                list->number_of_elements = list->number_of_elements - 1;
                list->size = list->size - tmp->size;
                tmp->next = NULL;
                tmp->prev = NULL;
                tmp->size = 0;
                free (tmp->data);
                tmp->data = NULL;
                free (tmp);
                break;
            }
            tmp = tmp->next;
        }
        if (found == 0) list->error = NO_MATCHING_ELEMENT;
        return found;
    }
}

struct imamLL_element *imamLL_element_get (struct imamLL *list, const void *element_data, size_t data_size, uint8_t follow_cursor)
{
    int found = 0;
    struct imamLL_element *tmp = NULL;

    if (follow_cursor == 0) tmp = list->first;
    else tmp = list->current;

    if (tmp == NULL) {
        list->error = EMPTY_LIST;
        return NULL;
    }
    while (tmp != NULL)
    {
        if (tmp->size == data_size) {
            if (memcmp ((char *)tmp->data, (char *)element_data, tmp->size) == 0)
            {
                found = 1;
                list->current = tmp;
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
