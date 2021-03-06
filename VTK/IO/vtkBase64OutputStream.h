/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkBase64OutputStream.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkBase64OutputStream - Writes base64-encoded output to a stream.
// .SECTION Description
// vtkBase64OutputStream implements base64 encoding with the
// vtkOutputStream interface.

#ifndef __vtkBase64OutputStream_h
#define __vtkBase64OutputStream_h

#include "vtkOutputStream.h"

class VTK_IO_EXPORT vtkBase64OutputStream : public vtkOutputStream
{
public:
  vtkTypeRevisionMacro(vtkBase64OutputStream,vtkOutputStream);
  static vtkBase64OutputStream *New();
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:  
  // Called after the stream position has been set by the caller, but
  // before any Write calls.  The stream position should not be
  // adjusted by the caller until after an EndWriting call.
  int StartWriting();
  
  // Description:
  // Write output data of the given length.
  int Write(const unsigned char* data, unsigned long length);
  
  // Description:
  // Called after all desired calls to Write have been made.  After
  // this call, the caller is free to change the position of the
  // stream.  Additional writes should not be done until after another
  // call to StartWriting.
  int EndWriting();
  
protected:
  vtkBase64OutputStream();
  ~vtkBase64OutputStream();  
  
  // Number of un-encoded bytes left in Buffer from last call to Write.
  unsigned int BufferLength;
  unsigned char Buffer[2];
  
  // Methods to encode and write data.
  int EncodeTriplet(unsigned char c0, unsigned char c1, unsigned char c2);
  int EncodeEnding(unsigned char c0, unsigned char c1);
  int EncodeEnding(unsigned char c0);
  
private:
  vtkBase64OutputStream(const vtkBase64OutputStream&);  // Not implemented.
  void operator=(const vtkBase64OutputStream&);  // Not implemented.
};

#endif
