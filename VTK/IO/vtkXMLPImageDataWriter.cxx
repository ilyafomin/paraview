/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkXMLPImageDataWriter.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkXMLPImageDataWriter.h"

#include "vtkErrorCode.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkObjectFactory.h"
#include "vtkXMLImageDataWriter.h"

vtkCxxRevisionMacro(vtkXMLPImageDataWriter, "$Revision: 1.8 $");
vtkStandardNewMacro(vtkXMLPImageDataWriter);

//----------------------------------------------------------------------------
vtkXMLPImageDataWriter::vtkXMLPImageDataWriter()
{
}

//----------------------------------------------------------------------------
vtkXMLPImageDataWriter::~vtkXMLPImageDataWriter()
{
}

//----------------------------------------------------------------------------
void vtkXMLPImageDataWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

//----------------------------------------------------------------------------
vtkImageData* vtkXMLPImageDataWriter::GetInput()
{
  return static_cast<vtkImageData*>(this->Superclass::GetInput());
}

//----------------------------------------------------------------------------
const char* vtkXMLPImageDataWriter::GetDataSetName()
{
  return "PImageData";
}

//----------------------------------------------------------------------------
const char* vtkXMLPImageDataWriter::GetDefaultFileExtension()
{
  return "pvti";
}

//----------------------------------------------------------------------------
void vtkXMLPImageDataWriter::WritePrimaryElementAttributes(ostream &os, vtkIndent indent)
{
  this->Superclass::WritePrimaryElementAttributes(os, indent);
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }
  
  vtkImageData* input = this->GetInput();
  this->WriteVectorAttribute("Origin", 3, input->GetOrigin());
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }
  
  this->WriteVectorAttribute("Spacing", 3, input->GetSpacing());
}

//----------------------------------------------------------------------------
vtkXMLStructuredDataWriter*
vtkXMLPImageDataWriter::CreateStructuredPieceWriter()
{  
  // Create the writer for the piece.
  vtkXMLImageDataWriter* pWriter = vtkXMLImageDataWriter::New();
  pWriter->SetInput(this->GetInput());
  return pWriter;
}

//----------------------------------------------------------------------------
int vtkXMLPImageDataWriter::FillInputPortInformation(
  int vtkNotUsed(port), vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkImageData");
  return 1;
}
