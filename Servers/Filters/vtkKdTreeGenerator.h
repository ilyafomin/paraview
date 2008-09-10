/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile: vtkKdTreeGenerator.h,v $

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkKdTreeGenerator - given a KdTree paritition, this class
// generates the KdTree
// .SECTION Description
// vtkKdTreeGenerator is used to generate a KdTree using the parititioning
// information available in an input data object. This class uses the 
// extent translator from the producer of the data to determine the paritioning
// of the structured data among several processes.
// The algorithm used can be summarized as under:
// \li Inputs: * Extent Translator, * Number of Pieces
// \li Determine the bounds for every piece/region using the extent translator.
// \li Given a set of pieces (number of pieces > 1), we iteratively determine 
//     the plane along which the the pieces can be split into two 
//     non-intersecting non-empty groups. 
// \li If number of pieces in a set of regions = 1, then we create a leaf node
//     representing that region.
// \li If number of pieces > 1, a new non-leaf node is creates with children
//     as the subtree generated by repeating the same process on the 
//     two non-intersecting, non-empty groups of pieces.
//  
//  vtkKdTreeGenerator also needs to determine the assignment of regions to 
//  the processors. Since vtkPKdTree assigns Ids to the leaf nodes in inorder,
//  we can determine the assignment by assigning temporary ids to all
//  leaf nodes indication the piece number they represent and simply
//  traversing the tree in inorder, and recording only the leaf
//  IDs.

#ifndef __vtkKdTreeGenerator_h
#define __vtkKdTreeGenerator_h

#include "vtkObject.h"

class vtkDataObject;
class vtkExtentTranslator;
class vtkKdNode;
class vtkKdTreeGeneratorVector;
class vtkPKdTree;

class VTK_EXPORT vtkKdTreeGenerator : public vtkObject
{
public:
  static vtkKdTreeGenerator* New();
  vtkTypeRevisionMacro(vtkKdTreeGenerator, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get/Set the kdtree which is updated in BuildTree.
  void SetKdTree(vtkPKdTree*);
  vtkGetObjectMacro(KdTree, vtkPKdTree);

  // Description:
  // Builds the KdTree using the partitioning of the data.
  int BuildTree(vtkDataObject* data);

  // Description:
  // Get/Set the number of pieces.
  vtkSetMacro(NumberOfPieces, int);
  vtkGetMacro(NumberOfPieces, int);
protected:
  vtkKdTreeGenerator();
  ~vtkKdTreeGenerator();

  // Description:
  // Get/Set the extent translator.
  void SetExtentTranslator(vtkExtentTranslator*);
  vtkGetObjectMacro(ExtentTranslator, vtkExtentTranslator);

  // Description:
  // Get/Set the whole extent of the data.
  vtkSetVector6Macro(WholeExtent, int);
  vtkGetVector6Macro(WholeExtent, int);

  // Description:
  // Obtains information from the extent translator about the partitioning of
  // the input dataset among processes.
  void FormRegions();

  int FormTree(vtkKdNode* parent, vtkKdTreeGeneratorVector& regions_ids);
  int CanPartition(int division_point, int dimension,
  vtkKdTreeGeneratorVector& ids,
  vtkKdTreeGeneratorVector& left, vtkKdTreeGeneratorVector& right);

  // Converts extents to bounds in the kdtree.
  bool ConvertToBounds(vtkDataObject* data, vtkKdNode* node);

  vtkPKdTree* KdTree;
  vtkExtentTranslator* ExtentTranslator;
  int WholeExtent[6];
  int NumberOfPieces;

  int *Regions;
private:
  vtkKdTreeGenerator(const vtkKdTreeGenerator&); // Not implemented.
  void operator=(const vtkKdTreeGenerator&); // Not implemented.
};


#endif
