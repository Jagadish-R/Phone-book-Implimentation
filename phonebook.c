//
//  main.c
//  DSfinal
//
//  Created by kushal on 10/11/19.
//  Copyright © 2019 kushal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
enum operations {EXIT, ADD_CONTACT, DELETE_CONTACT, RESTORE_CONTACT, DISPLAY_CONTACT,
                SORT_CONTACTS, DISPLAY_CONTACT_PREFERENCEWISE};
typedef enum operations MENU;
 
typedef struct contact
{
    int PhoneNO;
    char Name[30];
    char email[30];
    char address[30];
    int MobileNo;
}CONTACT;

typedef struct node
{
    struct node *prev;
    CONTACT info;
    struct node *next;
}NODE;
 
NODE *head=NULL;
NODE *deletehead=NULL;
 
static int counter=0;

void FreeList(void);
int CountNodes(NODE *trav);
void DeleteContact(void);
void DeleteContactsFinal(void);
void AcceptData(CONTACT *contact);
void DisplayData(CONTACT contact);
NODE *CreateNode(void);
void AddtoContactlist(CONTACT contact);
void DisplayContacts(NODE *trav);
void DeleteContacts(void);
void DeleteAtFirst(NODE *temp);
void RestoreBook(void);
void RestoreAtFirst(NODE *temp);
void SortContacts(void);
void AddContactsToFile(void);
void AddRestoreContactsToFile(void);
void ReadRestoreContactsFromFile(void);
void ReadContactsFromFile(void);
void AddtoRestorelist(CONTACT contact);
void DisplayPreferenceWise(NODE *head);
 
MENU menu_function()
{
    int choice;
    printf(" 1. Add Contacts\n");
    printf(" 2. Delete Contacts\n");
    printf(" 3. Restore Contacts\n");
    printf(" 4. Display Contacts\n");
    printf(" 5. Sort Contacts\n");
    printf(" 6. Display Contacts PreferenceWise\n");
    printf(" 0. EXIT\n");
    printf(" Enter your choice::");
    scanf("%d",&choice);
    if(choice < 0 || choice > 6)
    {
        printf(" Error: Enter valid choice\n");
    }
    return choice;
}
 
void FreeList()
{
    while(CountNodes(head))
    {
        DeleteContact();
    }
    while(CountNodes(deletehead))
    {
        DeleteContactsFinal();
    }
}
 
int CountNodes(NODE *trav)
{
    int count=0;
    while(trav!=NULL)
    {
        count++;
        trav=trav->next;
    }
    return count;
}

void DeleteContact()
{
    NODE *temp=head;
    head = head->next;
    free(temp);
    temp=NULL;
}
 
void DeleteContactsFinal()
{
    NODE *temp=deletehead;
    deletehead = deletehead->next;
    free(temp);
    temp=NULL;
}
 
void AcceptData(CONTACT *contact)
{
    contact->PhoneNO=++counter;
    getchar();
    printf(" Enter Contact name::");
    scanf("%[^\n]s",&contact->Name);
    getchar();
    printf(" Enter Email::");
    scanf("%[^\n]s",&contact->email);
    getchar();
    printf(" Enter address::");
    scanf("%[^\n]s",&contact->address);
    printf(" Enter MobileNo::");
    scanf("%d",&contact->MobileNo);
}
 
void DisplayData(CONTACT contact)
{
    printf(" %d\t\t",contact.PhoneNO);
    printf(" %s\t\t",contact.Name);
    printf(" %s\t\t",contact.email);
    printf(" %s\t\t",contact.address);
    printf(" %d\t\t",contact.MobileNo);
}
 
NODE *CreateNode()
{
    NODE *temp;
    temp = (NODE *) malloc(sizeof(NODE));
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}
 
void AddtoContactlist(CONTACT contact)
{
    NODE *new_node;
    new_node=CreateNode();
    new_node->info=contact;
 
    if(head == NULL)
    {
        head=new_node;
    }
    else
    {
        new_node->next=head;
        head->prev=new_node;
        head=new_node;
    }
}
 
void DisplayContacts(NODE *trav)
{
    if(trav==NULL)
    {
        printf(" Contact list is empty...\n");
    }
    else
    {
        printf(" Available Contacts\n");
        while(trav!=NULL)
        {
            DisplayData(trav->info);
            trav=trav->next;
        }
        printf("\n");
    }
}
 
void DeleteContacts()
{
    NODE *trav=head, *prev=NULL;
    NODE *temp, *right;
    int contactId;
    printf(" Enter Contact NO::");
    scanf("%d",&contactId);
 
    while(contactId != trav->info.PhoneNO)
    {
        prev=trav;
        trav=trav->next;
        if(trav==NULL)
        {
            printf(" Contact not found...\n");
            break;
        }
    }
    if(trav==head)
    {
        temp = trav;
        head->prev=NULL;
        head = head->next;
        trav=NULL;
        DeleteAtFirst(temp);
        printf(" Contact Deleted successfully...\n");
    }
    else if(trav->next==NULL)
    {
        temp=trav;
        prev->next=NULL;
        trav->prev=NULL;
        trav=NULL;
        DeleteAtFirst(temp);
        printf(" Contact Deleted successfully...\n");
    }
    else
    {
        temp=trav;
        right=trav->next;
        prev->next=right;
        right->prev=prev;
        trav->next=NULL;
        trav->prev=NULL;
        trav=NULL;
        DeleteAtFirst(temp);
        printf(" Contact Deleted successfully...\n");
    }
 
}
 
void DeleteAtFirst(NODE *temp)
{
    if(deletehead == NULL)
    {
        deletehead=temp;
        temp->next=NULL;
        temp->prev=NULL;
        temp=NULL;
    }
    else
    {
        temp->next=deletehead;
        temp->prev=NULL;
        deletehead=temp;
        temp=NULL;
    }
}
 
void RestoreBook()
{
    NODE *trav=deletehead, *prev=NULL;
    NODE *temp, *right;
    int contactId;
    printf(" Enter Contact NO::");
    scanf("%d",&contactId);
 
    while(contactId != trav->info.PhoneNO)
    {
        prev=trav;
        trav=trav->next;
        if(trav==NULL)
        {
            printf(" Contact not found...\n");
            break;
        }
    }
    if(trav==deletehead)
    {
        temp = trav;
        deletehead->prev = NULL;
        deletehead = deletehead->next;
        trav=NULL;
        RestoreAtFirst(temp);
        printf(" Contact Restored successfully...\n");
    }
    else if(trav->next==NULL)
    {
        temp=trav;
        prev->next=NULL;
        trav->prev=NULL;
        trav=NULL;
        RestoreAtFirst(temp);
        printf(" Contact Restored successfully...\n");
    }
    else
    {
        temp=trav;
        right=trav->next;
        prev->next=right;
        right->prev=prev;
        trav->next=NULL;
        trav->prev=NULL;
        trav=NULL;
        RestoreAtFirst(temp);
        printf(" Contact Restored successfully...\n");
    }
}
 
void RestoreAtFirst(NODE *temp)
{
    if(head == NULL)
    {
        head=temp;
        temp->next=NULL;
        temp->prev=NULL;
        temp=NULL;
    }
    else
    {
        head->prev=temp;
        temp->next=head;
        temp->prev=NULL;
        head=temp;
        temp=NULL;
    }
}
 
void SortContacts()
{
    NODE *trav=head,*right=head->next;
    CONTACT temp;
 
    while(trav->next!=NULL)
    {
        right=trav->next;
        while(right!=NULL)
        {
            if(trav->info.PhoneNO > right->info.PhoneNO)
            {
                temp = trav->info;
                trav->info = right->info;
                right->info = temp;
            }
            right=right->next;
        }
        trav=trav->next;
    }
}
 
void AddContactsToFile()
{
    NODE *trav=head;
    FILE *fp;
    fp=fopen("Contactlist.dat","wb");
    if(fp!=NULL)
    {
        while(trav!=NULL)
        {
            fwrite(&trav->info, sizeof(CONTACT),1,fp);
            trav=trav->next;
        }
    }
    fclose(fp);
}
 
void AddRestoreContactsToFile()
{
    NODE *trav=deletehead;
    FILE *fp=deletehead;
    fp=fopen("restorelist.dat","wb");
    if(fp!=NULL)
    {
        while(trav!=NULL)
        {
            fwrite(&trav->info, sizeof(CONTACT),1,fp);
            trav=trav->next;
        }
    }
    fclose(fp);
}
 
void ReadRestoreContactsFromFile()
{
    CONTACT contact;
    FILE *fp;
    fp=fopen("restorelist.dat","rb");
    if(fp!=NULL)
    {
        while((fread(&contact,sizeof(CONTACT),1,fp))!=0)
        {
            AddtoRestorelist(contact);
        }
    }
    fclose(fp);
}
 
void ReadContactsFromFile()
{
    CONTACT contact;
    FILE *fp;
    fp=fopen("Contactlist.dat","rb");
    if(fp!=NULL)
    {
        while((fread(&contact,sizeof(CONTACT),1,fp))!=0)
        {
            AddtoContactlist(contact);
        }
    }
    fclose(fp);
}
 
void AddtoRestorelist(CONTACT contact)
{
    NODE *new_node;
    new_node=CreateNode();
    new_node->info=contact;
 
    if(deletehead == NULL)
    {
        deletehead=new_node;
    }
    else
    {
        new_node->next=deletehead;
        deletehead->prev=new_node;
        deletehead=new_node;
    }
}
 
void DisplayPreferenceWise(NODE *head)
{
    NODE *trav=head;
    char subject[30];
    printf(" Enter PREFERENCE::");
    scanf("%s",&subject);
 
    while(trav!=NULL)
    {
        if(strcmp(subject, trav->info.email)== 0)
        {
            DisplayData(trav->info);
        }
        trav=trav->next;
    }
}
 
 
int main()
{
    MENU choice;
    int data;
    CONTACT contact;
 
    ReadContactsFromFile();
    ReadRestoreContactsFromFile();
 
    while((choice=menu_function())!= EXIT)
    {
        switch(choice)
        {
        case ADD_CONTACT:
            AcceptData(&contact);
            AddtoContactlist(contact);
            printf(" Contact added to lib successfully...\n");
            break;
 
        case DELETE_CONTACT:
            if(head==NULL)
            {
                printf(" No Contacts are available now...\n");
                break;
            }
            else
            {
                DeleteContacts();
            }
            break;
 
        case RESTORE_CONTACT:
            if(deletehead==NULL)
            {
                printf(" No Contacts are Deleted...\n");
                break;
            }
            else
            {
                RestoreBook();
            }
            break;
 
        case DISPLAY_CONTACT:
            DisplayContacts(head);
//            DisplayContacts(deletehead);
            printf("\n");
            break;
 
        case SORT_CONTACTS:
            if(head==NULL)
            {
                printf(" No Contacts to sort...\n");
                break;
            }
            SortContacts();
            break;
 
        case DISPLAY_CONTACT_PREFERENCEWISE:
            if(head==NULL)
            {
                printf(" No Contacts to display...\n");
                break;
            }
            DisplayPreferenceWise(head);
            break;
        }
    }
    AddContactsToFile();
    AddRestoreContactsToFile();
    FreeList();
    return 0;
}

