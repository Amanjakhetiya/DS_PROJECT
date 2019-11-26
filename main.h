#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Menu.h"
#include "LinkedList.h"
#include "BinaryTree.h"

#define max 2 // This defines the number of marks needed
#include<iostream>
#include<stdio.h>

void call()
{
    int arg,option,exit=0;
     printf("***| STUDENT DATABASE MANAGEMENT SYSTEM |***"
        "\n\nPlease Select/Enter the System Structure you Want:\n"
              "\n1.Linked                     \n2.Binary\n");
     scanf("%d", &arg);

     if (arg==1)
     {
         while(exit==0)
         {


            menu();
            printf("\n\t\t\t  ** Type your Option **\n ");
            scanf("%d", &option);
            switchLinkedList(option);
         }
     }
     else if (arg==2)
     {
         while (exit==0)
         {


            menu();
            printf("\n\t\t\t  ** Type your Option **\n ");
            scanf("%d", &option);
            switchBinaryTree(option);
         }
     }
     else
     {
         printf("Please enter a valid choice!!");
         call();
     }
}
#endif // main_h
