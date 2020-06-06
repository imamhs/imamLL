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

struct Student {
    char First_Name[16];
    char Last_Name[16];
    long id;
};

int selection = 1;

struct imamLL *student_list = NULL;
struct imamLL_element *element = NULL;
struct Student *student = NULL;

void print_menu (void);
void show_students (void);
void add_student (void);
void delete_student (void);
void find_student (void);

int main (int argc, char** argv)
{
    printf ("Creating student book...\n");
    
    student_list = imamLL_list_create();
    
    if (student_list == NULL) {
        printf ("Can not create student book\n");
        exit (EXIT_FAILURE);
    }
    
    printf ("There are %ld students in the book\n", student_list->number_of_elements);
    printf ("Total memory allocated %ld bytes\n", student_list->size);
    
    while (1) {
        print_menu();
        scanf ("%d", &selection);
        if (selection == 1) show_students ();
        else if (selection == 2) add_student ();
        else if (selection == 3) delete_student ();
        else if (selection == 4) find_student ();
        else if (selection == 5) break;
    }
    
    if (imamLL_list_destroy(student_list) == -1) printf ("Can not free memory allocation by student book\n");
    
    return EXIT_SUCCESS;
}

void print_menu (void)
{
    printf ("\nMenu:\n\n");
    printf ("\t1. Show students\n");
    printf ("\t2. Add a new student\n");
    printf ("\t3. Delete an existing student\n");
    printf ("\t4. Find a student\n");
    printf ("\t5. Exit\n\n");
    printf ("Select (1-5): ");
}

void show_students (void)
{
    long count = 0;
    if (student_list->number_of_elements < 1) {
        printf ("\nNo students in the book\n");
        return;
    }
    printf ("\n");
    printf ("There are %ld students in the book\n", student_list->number_of_elements);
    printf ("Total memory allocated %ld bytes\n\n", student_list->size);
    imamLL_list_rewind (student_list, 1);
    while (1) {
        element = imamLL_element_get_next (student_list);
        if (element == NULL) break;
        else {
            count++;
            student = (struct Student *) element->data;
            printf ("%ld. %s %s %ld\n", count, student->First_Name, student->Last_Name, student->id);
        }
    }
}

void add_student (void)
{
    element = imamLL_element_add (student_list, sizeof (struct Student), AT_START);
    if (element == NULL) {
        printf ("Error allocating memory for student\n");
        return;
    }
    printf ("\n");
    student = (struct Student *) element->data;
    printf ("First Name: ");
    scanf ("%s", student->First_Name);
    printf ("Last Name: ");
    scanf ("%s", student->Last_Name);
    printf ("id: ");
    scanf ("%ld", &student->id);
    printf ("\nRegistered successfully.\n");
}

void delete_student (void)
{
    long id = 0;
    if (student_list->number_of_elements < 1) {
        printf ("\nNo students in the book\n");
        return;
    }
    printf ("\n");
    printf ("Student id: ");
    scanf ("%ld", &id);
    imamLL_list_rewind (student_list, 1);
    while (1) {
        element = imamLL_element_get_next (student_list);
        if (element == NULL) break;
        else {
            student = (struct Student *) element->data;
            if (student->id == id) {
                if (imamLL_element_remove (student_list, element) != 1) {
                    printf ("Can not delete student.\n");
                    return;
                }
                printf ("Deleted.\n");
                return;
            }
        }
    }
    printf ("No student found.\n");
}

void find_student (void)
{
    long id = 0;
    if (student_list->number_of_elements < 1) {
        printf ("\nNo students in the book\n");
        return;
    }
    printf ("\n");
    printf ("Student id: ");
    scanf ("%ld", &id);
    imamLL_list_rewind (student_list, 1);
    while (1) {
        element = imamLL_element_get_next (student_list);
        if (element == NULL) break;
        else {
            student = (struct Student *) element->data;
            if (student->id == id) {
                printf ("Found:\n\n");
                printf ("First Name: %s\n", student->First_Name);
                printf ("Last Name: %s\n", student->Last_Name);
                return;
            }
        }
    }
    printf ("No student found.\n");
}
