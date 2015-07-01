/******************************************************************************

Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

******************************************************************************
File Name     :
Version       :
Author        :
Created       : 2013/9
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2013/9
Author      :
Modification: Created file

******************************************************************************/
#include "FileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    FILE_TYPE_FILE = 1,
    FILE_TYPE_DIR  = 2
}FileType;

typedef struct tagFileNode
{
    char *name;
    FileType type;
    /* total number of files including subdirectories */
    unsigned long fileNum;
    struct tagFileNode *parent;
    /* children list to represent the first node children list */
    struct tagFileNode *children;
    /* pointing to next sibling */
    struct tagFileNode *next;
}FileNode;

typedef struct tagNameNode
{
    char *name;
    struct tagFileNode *node;
    struct tagNameNode *next;
}NameNode;

char *gRootName = "root";
FileNode gRootNode = { gRootName, FILE_TYPE_DIR, 0, NULL, NULL, NULL };
NameNode gDirList  = { gRootName, &gRootNode, NULL };
NameNode gFileList = { "", NULL, NULL };

struct tagFileNode *findFileNode(const char *name, FileType type)
{
    NameNode *list = (type == FILE_TYPE_DIR) ? &gDirList : &gFileList;

    while ( list )
    {
        if ( strcmp( list->name, name ) == 0 )
            return list->node;
        list = list->next;
    }

    return NULL;
}

void adjustFileNumber(struct tagFileNode *parent, int val)
{
    struct tagFileNode *pParent = parent;

    while ( pParent )
    {
        pParent->fileNum += val;
        pParent = pParent->parent;
    }
}

void addFileNode(struct tagFileNode *parent, struct tagFileNode *newChild)
{
    struct tagFileNode *child = parent->children;
    struct tagFileNode *prev  = child;

    while ( child )
    {
        prev = child;
        child = child->next;
    }

    /* the parent node has children already */
    if ( prev )
        prev->next       = newChild;
    else
        parent->children = newChild; /* the parent node has no child yet */

    newChild->parent = parent;

    adjustFileNumber(parent, 1+newChild->fileNum);
}

void addNameNode(NameNode *nameNode, FileType type)
{
    NameNode *nameList = (type == FILE_TYPE_DIR) ? &gDirList : &gFileList;

    NameNode *prev = nameList;

    while ( nameList )
    {
        prev = nameList;
        nameList = nameList->next;
    }

    prev->next = nameNode;
}

int addChild(const char *parentName, const char *childName, FileType type)
{
    char *pName = NULL;
    int len = 0;
    NameNode *pNameNode = NULL;
    struct tagFileNode *parent = NULL;
    struct tagFileNode *pFileNode = NULL;

    /* arguments validation */
    if ( parentName == NULL || *parentName == '\0' ||
        childName == NULL || *childName == '\0' )
            return -1;

    parent = findFileNode(parentName, FILE_TYPE_DIR);

    /* parent does not exist or this file exists already */
    if ( parent == NULL || findFileNode(childName, type) != NULL )
        return -1;

    len = strlen(childName);
    pName = (char *) malloc ( len * sizeof(char) + 1);
    pNameNode = (NameNode *) malloc ( sizeof(NameNode) );
    pFileNode = (struct tagFileNode *) malloc ( sizeof(struct tagFileNode) );

    if ( pName == NULL || pNameNode == NULL || pFileNode == NULL )
        return -1;

    strncpy(pName, childName, len);
    pName[len] = '\0';

    pFileNode->name     = pName;
    pFileNode->type     = type;
    pFileNode->parent   = parent;
    pFileNode->fileNum  = 0;
    pFileNode->children = NULL;
    pFileNode->next     = NULL;

    pNameNode->name     = pName;
    pNameNode->node     = pFileNode;
    pNameNode->next     = NULL;

    addFileNode(parent, pFileNode);
    addNameNode(pNameNode, type);

    return 0;
}

void deleteNameNode(const char *fileName, FileType type)
{
    NameNode *nameList = (type == FILE_TYPE_DIR) ? &gDirList : &gFileList;

    NameNode *prev = nameList;

    while ( nameList )
    {
        if ( strcmp(nameList->name, fileName) == 0 )
            break;

        prev     = nameList;
        nameList = nameList->next;
    }

    /* impossible! */
    if ( nameList == NULL )
        return;

    prev->next = nameList->next;
    free(nameList->name);
    free(nameList);
    nameList = NULL;
}

void deleteNode(struct tagFileNode *fileNode)
{
    struct tagFileNode *headChild = fileNode->children;
    struct tagFileNode *nextChild = NULL;

    while ( headChild )
    {
        nextChild = headChild->next;
        deleteNode(headChild);
        headChild = NULL;
        fileNode->children = nextChild;
        headChild = fileNode->children;
    }

    adjustFileNumber(fileNode->parent, -1);
    deleteNameNode(fileNode->name, fileNode->type);
    free(fileNode);
    fileNode = NULL;
}

void deleteFileNode(const char *fileName, FileType type)
{
    struct tagFileNode *fileNode = NULL;
    struct tagFileNode *siblings = NULL;
    struct tagFileNode *prev     = NULL;

    /* node root cannot be deleted */
    if ( type == FILE_TYPE_DIR && strcmp(fileName, gRootName) == 0 )
        return;

    fileNode = findFileNode(fileName, type);

    if ( fileNode == NULL )
        return;

    siblings = fileNode->parent->children;
    prev     = siblings;

    while ( siblings )
    {
        if (siblings == fileNode)
            break;
        prev     = siblings;
        siblings = siblings->next;   /* sibling list */
    }

    prev->next = fileNode->next;

    if ( fileNode == fileNode->parent->children )
        fileNode->parent->children = fileNode->next;

    deleteNode(fileNode);
}

/* remove srcNode itself from its parent's children list */
void removeFromParent(struct tagFileNode *srcNode)
{
    struct tagFileNode *prev     = NULL;
    struct tagFileNode *siblings = NULL;

    siblings = srcNode->parent->children;
    prev     = siblings;

    /* find the last node before srcNode */
    while ( siblings )
    {
        if ( siblings == srcNode )
            break;
        prev     = siblings;
        siblings = siblings->next;
    }

    /* alter the srcNode's parent's children list */
    if ( prev == srcNode )  /* srcNode is the head node */
        srcNode->parent->children   = srcNode->next;
    else
        prev->next                  = srcNode->next;

    srcNode->next = NULL;

    adjustFileNumber(srcNode->parent, -(1+srcNode->fileNum));
}

unsigned int GetFileNum(const char * DirName)
{
    struct tagFileNode *node = NULL;

    node = findFileNode(DirName, FILE_TYPE_DIR);

    if ( node )
        return node->fileNum;
    else
        return 0;
}

int CreateFile(const char * DirName, const char * FileName)
{
    return addChild(DirName, FileName, FILE_TYPE_FILE);
}

int CreateDir(const char * ParentDirName, const char * DirName)
{
    return addChild(ParentDirName, DirName, FILE_TYPE_DIR);
}

void DeleteFile(const char * FileName)
{
    deleteFileNode(FileName, FILE_TYPE_FILE);
}

void DeleteDir(const char * DirName)
{
    deleteFileNode(DirName, FILE_TYPE_DIR);
    return;
}

int MoveDir(const char * SrcDirName, const char * DestDirName)
{
    struct tagFileNode *srcNode  = NULL;
    struct tagFileNode *dstNode  = NULL;

    if ( strcmp(SrcDirName, DestDirName) == 0 )
        return -1;

    srcNode = findFileNode(SrcDirName,  FILE_TYPE_DIR);
    dstNode = findFileNode(DestDirName, FILE_TYPE_DIR);

    if ( srcNode == dstNode || srcNode->parent == dstNode )
        return -1;

    removeFromParent(srcNode);

    addFileNode(dstNode, srcNode);

    return 0;
}

void Clear(void)
{
    struct tagFileNode *child = NULL;
    struct tagFileNode *next  = NULL;

    child = gRootNode.children;

    while ( child )
    {
        next = child->next;
        deleteNode(child);
        child = next;
    }

    gRootNode.children = NULL;
    gRootNode.fileNum  = 0;

    return;
}
