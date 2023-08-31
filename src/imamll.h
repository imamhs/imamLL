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

#ifndef IMAMLL_H
#define	IMAMLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define IMAM_LL_VERSION 15
    
enum imamLL_errors {
    MEMORY_ALLOCATION = 1,
    EMPTY_LIST = 2,
    NO_MATCHING_ELEMENT = 3
};

enum imamLL_positions {
    AT_START = 1,                       /* position new element at the beginning of a list */
    AT_CURRENT = 2,                     /* position new element after the current element  of a list */
    AT_END = 3                          /* position new element at the ending of a list */
};

enum imamLL_directions {
    BACKWARD = 1,                       /* roll backward so that first element is current */
    FORWARD = -1,                       /* roll forward so that the last element is current */
};

/* structure of an element */
struct imamLL_element {
    void *data;                         /* pointer to the data */
    size_t size;                        /* size of data in bytes */
    struct imamLL_element *prev;        /* pointer to the previous element */
    struct imamLL_element *next;        /* pointer to the next element */
};

/* structure of a list */
struct imamLL {
    uint64_t number_of_elements;        /* number of elements in the list */
    uint64_t size;                      /* total elements size in bytes */
    struct imamLL_element *first;       /* pointer to the first element */
    struct imamLL_element *last;        /* pointer to the last element */
    struct imamLL_element *current;     /* pointer to an arbitrary element, used by imamLL_element_get_* functions */
    uint8_t error;                      /* error number used by imamLL_list_error function */
};

/* creates a new list by allocating memory and returns the pointer of the list */
/* Return Value: upon successful returns pointer to newly allocated list, otherwise returns NULL*/
extern struct imamLL *imamLL_list_create (void);

/* frees the memory allocated by *list and it's elements */
/* Return Value: upon successful returns 0, otherwise returns -1*/
extern int imamLL_list_destroy (struct imamLL *list);

/* frees the memory allocated by the elements of the *list, aka removes all the elements from the list */
/* Return Value: upon successful returns the number of elements freed in a list, otherwise returns -1 and sets appropriate error no to error variable of a list*/
extern int imamLL_list_free (struct imamLL *list);

/* rewinds the current element to the first element or the last element*/
extern struct imamLL_element *imamLL_list_rewind (struct imamLL *list, int8_t direction);

/* copies last error information into *error_message */
extern void imamLL_list_error (struct imamLL *list, char *error_message);

/* allocates memory for a new element and returns the pointer of allocated element */
/* Return Value: upon successful returns pointer to newly allocated element, otherwise returns NULL and sets appropriate error no to error variable of a list*/
extern struct imamLL_element *imamLL_element_add (struct imamLL *list, size_t element_size, uint8_t position);

/* frees and removes the first matching element *element from the list */
/* Return Value: upon successful returns 1, otherwise returns 0 and -1 and sets appropriate error no to error variable of a list*/
extern int imamLL_element_remove (struct imamLL *list, struct imamLL_element *element);

/* returns the pointer of a matching element */
/* Return Value: upon successful returns pointer to first found element in a list, otherwise returns NULL and sets appropriate error no to error variable of a list*/
extern struct imamLL_element *imamLL_element_get (struct imamLL *list, const void *element_data, size_t data_size);

/* returns the pointer of the next element in the list */
/* Return Value: upon successful returns pointer to the next element in a list, otherwise returns NULL*/
extern struct imamLL_element *imamLL_element_get_next (struct imamLL *list);

/* returns the pointer of the previous element in the list */
/* Return Value: upon successful returns pointer to the previous element in a list, otherwise returns NULL*/
extern struct imamLL_element *imamLL_element_get_prev (struct imamLL *list);


#ifdef __cplusplus
}
#endif

#endif	/* IMAMLL_H */
