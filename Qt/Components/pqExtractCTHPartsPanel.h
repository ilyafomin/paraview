/*=========================================================================

   Program: ParaView
   Module:    $RCSfile: pqExtractCTHPartsPanel.h,v $

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.1. 

   See License_v1.1.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#ifndef _pqExtractCTHPartsPanel_h
#define _pqExtractCTHPartsPanel_h

#include "pqAutoGeneratedObjectPanel.h"
#include "pqSMProxy.h"

class QTreeWidgetItem;
/// Custom panel for the ExtractCTHParts filter. This makes the it so that 
/// only one of the three array selection widgets can be active at a time.
/// It also makes it so that arrays with "Material Volume Fraction" are
/// are enabled at startup and no others are.
class PQCOMPONENTS_EXPORT pqExtractCTHPartsPanel : 
  public pqAutoGeneratedObjectPanel
{
  typedef pqAutoGeneratedObjectPanel Superclass;

  Q_OBJECT

public:
  pqExtractCTHPartsPanel(pqProxy* proxy, QWidget* p);
  ~pqExtractCTHPartsPanel() {};
  
protected:
  void arrayEnabled(int which);
  int enableMaterialNamedArrays(int which);

private slots:  
  void dArrayEnabled(int);
  void fArrayEnabled(int);
  void cArrayEnabled(int);
  void dArrayEnabled(QTreeWidgetItem *, int);
  void fArrayEnabled(QTreeWidgetItem *, int);
  void cArrayEnabled(QTreeWidgetItem *, int);

private:
};

#endif

