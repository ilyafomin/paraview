/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkExtractSelectedLocations.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkExtractSelectedLocations - extract cells within a dataset that 
// contain the locations listen in the vtkSelection.
// .SECTION Description
// vtkExtractSelectedLocations extracts all cells whose volume contain at least 
// one point listed in the LOCATIONS content of the vtkSelection. This filter 
// adds a scalar array called vtkOriginalCellIds that says what input cell 
// produced each output cell. This is an example of a Pedigree ID which helps
// to trace back results.
// .SECTION See Also
// vtkSelection vtkExtractSelection

#ifndef __vtkExtractSelectedLocations_h
#define __vtkExtractSelectedLocations_h

#include "vtkDataSetAlgorithm.h"

class vtkSelection;

class VTK_GRAPHICS_EXPORT vtkExtractSelectedLocations : public vtkDataSetAlgorithm
{
public:
  vtkTypeRevisionMacro(vtkExtractSelectedLocations,vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object
  static vtkExtractSelectedLocations *New();

protected:
  vtkExtractSelectedLocations();
  ~vtkExtractSelectedLocations();

  //sets up output dataset
  virtual int RequestDataObject(vtkInformation* request,
                                vtkInformationVector** inputVector,
                                vtkInformationVector* outputVector);

  // Usual data generation method
  int RequestData(vtkInformation *, 
                  vtkInformationVector **, 
                  vtkInformationVector *);

  int ExtractCells(vtkSelection *sel, vtkDataSet *input, 
                   vtkDataSet *output);
  int ExtractPoints(vtkSelection *sel, vtkDataSet *input, 
                    vtkDataSet *output);

  virtual int FillInputPortInformation(int port, vtkInformation* info);

private:
  vtkExtractSelectedLocations(const vtkExtractSelectedLocations&);  // Not implemented.
  void operator=(const vtkExtractSelectedLocations&);  // Not implemented.
};

#endif
