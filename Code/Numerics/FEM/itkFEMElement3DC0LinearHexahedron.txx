/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkFEMElement3DC0LinearHexahedron.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkFEMElement3DC0LinearHexahedron_txx
#define __itkFEMElement3DC0LinearHexahedron_txx

#include "vnl/vnl_math.h"

namespace itk {
namespace fem {




template<unsigned int VNumberOfDegreesOfFreedomPerNode>
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>::VectorType
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::GetIntegrationPoint(unsigned int i) const
{
  VectorType ipts(3);

  Float pt = (Float)1.0 / (Float)sqrt(3.0);

  switch(i)
  {
  case 0:
    ipts[0] = -pt;
    ipts[1] = -pt;
    ipts[2] = -pt;
    break;

  case 1:
    ipts[0] =  pt;
    ipts[1] = -pt;
    ipts[2] = -pt;
    break;

  case 2:
    ipts[0] =  pt;
    ipts[1] =  pt;
    ipts[2] = -pt;
    break;

  case 3:
    ipts[0] = -pt;
    ipts[1] =  pt;
    ipts[2] = -pt;
    break;

  case 4:
    ipts[0] = -pt;
    ipts[1] = -pt;
    ipts[2] = pt;
    break;

  case 5:
    ipts[0] =  pt;
    ipts[1] = -pt;
    ipts[2] = pt;
    break;

  case 6:
    ipts[0] =  pt;
    ipts[1] =  pt;
    ipts[2] = pt;
    break;

  case 7:
    ipts[0] = -pt;
    ipts[1] =  pt;
    ipts[2] = pt;
    break;

  default:
    // i was out of range
    throw FEMException(__FILE__, __LINE__, "FEM error");
  }

  return ipts;

}



template<unsigned int VNumberOfDegreesOfFreedomPerNode>
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>::Float
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::GetWeightAtIntegrationPoint(unsigned int) const
{
  return (Float)1.0;
}



template<unsigned int VNumberOfDegreesOfFreedomPerNode>
unsigned int
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::GetNumberOfIntegrationPoints() const
{
  return 8;
}




template<unsigned int VNumberOfDegreesOfFreedomPerNode>
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>::VectorType
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::ShapeFunctions( const VectorType& pt ) const
{
  /* Linear hexahedral element has eight shape functions  */
  VectorType shapeF(8);

  /*
   * Linear hexahedral element has local coordinates
   *  (-1,-1,-1), (1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,1), (1,-1,1), (1,1,1), (-1,1,1)
   */
  
  /* given local point x=(r,s,t), where -1 <= r,s,t <= 1 and */

  /** N_1 = ((1-r) * (1-s) * (1-t)) / 8 */
  shapeF[0] = (1 - pt[0]) * (1 - pt[1]) * (1 - pt[2]) * 0.125;

  /** N_2 = ((1+r) * (1-s) * (1-t)) / 8 */
  shapeF[1] = (1 + pt[0]) * (1 - pt[1]) * (1 - pt[2]) * 0.125;

  /** N_3 = ((1+r) * (1+s) * (1-t)) / 8 */
  shapeF[2] = (1 + pt[0]) * (1 + pt[1]) * (1 - pt[2]) * 0.125;

  /** N_4 = ((1-r) * (1+s) * (1-t)) / 8 */
  shapeF[3] = (1 - pt[0]) * (1 + pt[1]) * (1 - pt[2]) * 0.125;

  /** N_5 = ((1-r) * (1-s) * (1+t)) / 8 */
  shapeF[4] = (1 - pt[0]) * (1 - pt[1]) * (1 + pt[2]) * 0.125;

  /** N_6 = ((1+r) * (1-s) * (1+t)) / 8 */
  shapeF[5] = (1 + pt[0]) * (1 - pt[1]) * (1 + pt[2]) * 0.125;

  /** N_7 = ((1+r) * (1+s) * (1+t)) / 8 */
  shapeF[6] = (1 + pt[0]) * (1 + pt[1]) * (1 + pt[2]) * 0.125;

  /** N_8 = ((1-r) * (1+s) * (1+t)) / 8 */
  shapeF[7] = (1 - pt[0]) * (1 + pt[1]) * (1 + pt[2]) * 0.125;

  return shapeF;
}



template<unsigned int VNumberOfDegreesOfFreedomPerNode>
void
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::ShapeFunctionDerivatives( const VectorType& pt, MatrixType& shapeD ) const
{
  /** functions at directions r and s.  */
  shapeD.resize(3,8);

  // d(N_1) / d(r)
  shapeD[0][0] = (-1) * (1 - pt[1]) * (1 - pt[2]) * 0.125;
  
  // d(N_1) / d(s)
  shapeD[1][0] = (-1) * (1 - pt[0]) * (1 - pt[2]) * 0.125;

  // d(N_1) / d(t)
  shapeD[2][0] = (-1) * (1 - pt[0]) * (1 - pt[1]) * 0.125;

  // d(N_2) / d(r)
  shapeD[0][1] = (+1) * (1 - pt[1]) * (1 - pt[2]) * 0.125;
  
  // d(N_2) / d(s)
  shapeD[1][1] = (-1) * (1 + pt[0]) * (1 - pt[2]) * 0.125;

  // d(N_2) / d(t)
  shapeD[2][1] = (-1) * (1 + pt[0]) * (1 - pt[1]) * 0.125;

  // d(N_3) / d(r)
  shapeD[0][2] = (+1) * (1 + pt[1]) * (1 - pt[2]) * 0.125;
  
  // d(N_3) / d(s)
  shapeD[1][2] = (+1) * (1 + pt[0]) * (1 - pt[2]) * 0.125;

  // d(N_3) / d(t)
  shapeD[2][2] = (-1) * (1 + pt[0]) * (1 + pt[1]) * 0.125;

  // d(N_4) / d(r)
  shapeD[0][3] = (-1) * (1 + pt[1]) * (1 - pt[2]) * 0.125;
       
  // d(N_4) / d(s)
  shapeD[1][3] = (+1) * (1 - pt[0]) * (1 - pt[2]) * 0.125;

  // d(N_4) / d(t)
  shapeD[2][3] = (-1) * (1 - pt[0]) * (1 + pt[1]) * 0.125;

  // d(N_5) / d(r)
  shapeD[0][4] = (-1) * (1 - pt[1]) * (1 + pt[2]) * 0.125;
  
  // d(N_5) / d(s)
  shapeD[1][4] = (-1) * (1 - pt[0]) * (1 + pt[2]) * 0.125;

  // d(N_5) / d(t)
  shapeD[2][4] = (+1) * (1 - pt[0]) * (1 - pt[1]) * 0.125;

  // d(N_6) / d(r)
  shapeD[0][5] = (+1) * (1 - pt[1]) * (1 + pt[2]) * 0.125;
  
  // d(N_6) / d(s)
  shapeD[1][5] = (-1) * (1 + pt[0]) * (1 + pt[2]) * 0.125;

  // d(N_6) / d(t)
  shapeD[2][5] = (+1) * (1 + pt[0]) * (1 - pt[1]) * 0.125;

  // d(N_7) / d(r)
  shapeD[0][6] = (+1) * (1 + pt[1]) * (1 + pt[2]) * 0.125;
  
  // d(N_7) / d(s)
  shapeD[1][6] = (+1) * (1 + pt[0]) * (1 + pt[2]) * 0.125;

  // d(N_7) / d(t)
  shapeD[2][6] = (+1) * (1 + pt[0]) * (1 + pt[1]) * 0.125;

  // d(N_8) / d(r)
  shapeD[0][7] = (-1) * (1 + pt[1]) * (1 + pt[2]) * 0.125;
  
  // d(N_8) / d(s)
  shapeD[1][7] = (+1) * (1 - pt[0]) * (1 + pt[2]) * 0.125;

  // d(N_8) / d(t)
  shapeD[2][7] = (+1) * (1 - pt[0]) * (1 + pt[1]) * 0.125;

}




template<unsigned int VNumberOfDegreesOfFreedomPerNode>
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>::VectorType
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::GetLocalFromGlobalCoordinates( const VectorType& pt ) const
{

  Float x1, x2, x3, x4, y1, y2, y3, y4, xce, yce, xb, yb, xcn, ycn,
        A, J1, J2, x0, y0, dx, dy, be, bn, ce, cn;

  VectorType lpt(2);

  // FIXME!

//   x1 = this->m_node[0]->GetCoordinates()[0];   y1 = this->m_node[0]->GetCoordinates()[1];
//   x2 = this->m_node[1]->GetCoordinates()[0];   y2 = this->m_node[1]->GetCoordinates()[1];
//   x3 = this->m_node[2]->GetCoordinates()[0];   y3 = this->m_node[2]->GetCoordinates()[1];
//   x4 = this->m_node[3]->GetCoordinates()[0];   y4 = this->m_node[3]->GetCoordinates()[1];

//   xb = x1 - x2 + x3 - x4;
//   yb = y1 - y2 + y3 - y4;

//   xce = x1 + x2 - x3 - x4;
//   yce = y1 + y2 - y3 - y4;

//   xcn = x1 - x2 - x3 + x4;
//   ycn = y1 - y2 - y3 + y4;

//   A  = 0.5 * (((x3 - x1) * (y4 - y2)) - ((x4 - x2) * (y3 - y1)));
//   J1 = ((x3 - x4) * (y1 - y2)) - ((x1 - x2) * (y3 - y4));
//   J2 = ((x2 - x3) * (y1 - y4)) - ((x1 - x4) * (y2 - y3));

//   x0 = 0.25 * (x1 + x2 + x3 + x4);
//   y0 = 0.25 * (y1 + y2 + y3 + y4);

//   dx = pt[0] - x0;
//   dy = pt[1] - y0;

//   be =  A - (dx * yb) + (dy * xb);
//   bn = -A - (dx * yb) + (dy * xb);
//   ce = (dx * yce) - (dy * xce);
//   cn = (dx * ycn) - (dy * xcn);

//   lpt[0] = (2 * ce) / (-sqrt((be * be) - (2 * J1 * ce)) - be);
//   lpt[1] = (2 * cn) / ( sqrt((bn * bn) + (2 * J2 * cn)) - bn);

  return lpt;
}




/*
 * Draw the element on device context pDC.
 */
#ifdef FEM_BUILD_VISUALIZATION
template<unsigned int VNumberOfDegreesOfFreedomPerNode>
void
Element3DC0LinearHexahedron<VNumberOfDegreesOfFreedomPerNode>
::Draw(CDC* pDC, Solution::ConstPointer sol) const 
{

  int x1=m_node[0]->GetCoordinates()[0]*DC_Scale;
  int y1=m_node[0]->GetCoordinates()[1]*DC_Scale;
  int z1=m_node[0]->GetCoordinates()[2]*DC_Scale;

  int x2=m_node[1]->GetCoordinates()[0]*DC_Scale;
  int y2=m_node[1]->GetCoordinates()[1]*DC_Scale;
  int z2=m_node[1]->GetCoordinates()[2]*DC_Scale;
  
  int x3=m_node[2]->GetCoordinates()[0]*DC_Scale;
  int y3=m_node[2]->GetCoordinates()[1]*DC_Scale;
  int z3=m_node[2]->GetCoordinates()[2]*DC_Scale;
  
  int x4=m_node[3]->GetCoordinates()[0]*DC_Scale;
  int y4=m_node[3]->GetCoordinates()[1]*DC_Scale;
  int z4=m_node[3]->GetCoordinates()[2]*DC_Scale;

  int x5=m_node[4]->GetCoordinates()[0]*DC_Scale;
  int y5=m_node[4]->GetCoordinates()[1]*DC_Scale;
  int z5=m_node[4]->GetCoordinates()[2]*DC_Scale;

  int x6=m_node[5]->GetCoordinates()[0]*DC_Scale;
  int y6=m_node[5]->GetCoordinates()[1]*DC_Scale;
  int z6=m_node[5]->GetCoordinates()[2]*DC_Scale;
  
  int x7=m_node[6]->GetCoordinates()[0]*DC_Scale;
  int y7=m_node[6]->GetCoordinates()[1]*DC_Scale;
  int z7=m_node[6]->GetCoordinates()[2]*DC_Scale;
  
  int x8=m_node[7]->GetCoordinates()[0]*DC_Scale;
  int y8=m_node[7]->GetCoordinates()[1]*DC_Scale;
  int z8=m_node[7]->GetCoordinates()[2]*DC_Scale;

  x1+=sol->GetSolutionValue(this->m_node[0]->GetDegreeOfFreedom(0))*DC_Scale;
  y1+=sol->GetSolutionValue(this->m_node[0]->GetDegreeOfFreedom(1))*DC_Scale;
  z1+=sol->GetSolutionValue(this->m_node[0]->GetDegreeOfFreedom(2))*DC_Scale;

  x2+=sol->GetSolutionValue(this->m_node[1]->GetDegreeOfFreedom(0))*DC_Scale;
  y2+=sol->GetSolutionValue(this->m_node[1]->GetDegreeOfFreedom(1))*DC_Scale;
  z2+=sol->GetSolutionValue(this->m_node[1]->GetDegreeOfFreedom(2))*DC_Scale;

  x3+=sol->GetSolutionValue(this->m_node[2]->GetDegreeOfFreedom(0))*DC_Scale;
  y3+=sol->GetSolutionValue(this->m_node[2]->GetDegreeOfFreedom(1))*DC_Scale;
  z3+=sol->GetSolutionValue(this->m_node[2]->GetDegreeOfFreedom(2))*DC_Scale;

  x4+=sol->GetSolutionValue(this->m_node[3]->GetDegreeOfFreedom(0))*DC_Scale;
  y4+=sol->GetSolutionValue(this->m_node[3]->GetDegreeOfFreedom(1))*DC_Scale;
  z4+=sol->GetSolutionValue(this->m_node[3]->GetDegreeOfFreedom(2))*DC_Scale;

  x5+=sol->GetSolutionValue(this->m_node[4]->GetDegreeOfFreedom(0))*DC_Scale;
  y5+=sol->GetSolutionValue(this->m_node[4]->GetDegreeOfFreedom(1))*DC_Scale;
  z5+=sol->GetSolutionValue(this->m_node[4]->GetDegreeOfFreedom(2))*DC_Scale;

  x6+=sol->GetSolutionValue(this->m_node[5]->GetDegreeOfFreedom(0))*DC_Scale;
  y6+=sol->GetSolutionValue(this->m_node[5]->GetDegreeOfFreedom(1))*DC_Scale;
  z6+=sol->GetSolutionValue(this->m_node[5]->GetDegreeOfFreedom(2))*DC_Scale;

  x7+=sol->GetSolutionValue(this->m_node[6]->GetDegreeOfFreedom(0))*DC_Scale;
  y7+=sol->GetSolutionValue(this->m_node[6]->GetDegreeOfFreedom(1))*DC_Scale;
  z7+=sol->GetSolutionValue(this->m_node[6]->GetDegreeOfFreedom(2))*DC_Scale;

  x8+=sol->GetSolutionValue(this->m_node[7]->GetDegreeOfFreedom(0))*DC_Scale;
  y8+=sol->GetSolutionValue(this->m_node[7]->GetDegreeOfFreedom(1))*DC_Scale;
  z8+=sol->GetSolutionValue(this->m_node[7]->GetDegreeOfFreedom(2))*DC_Scale;

  // FIXME: this isn't the correct drawing scheme
  pDC->MoveTo(x1,y1,z1);
  pDC->LineTo(x2,y2,z2);
  pDC->LineTo(x3,y3,z3);
  pDC->LineTo(x4,y4,z4);
  pDC->LineTo(x5,y5,z5);
  pDC->LineTo(x6,y6,z6);
  pDC->LineTo(x7,y7,z7);
  pDC->LineTo(x8,y8,z8);

}
#endif




#ifdef _MSC_VER
// Declare a static dummy function to prevent a MSVC 6.0 SP5 from crashing.
// I have no idea why things don't work when this is not declared, but it
// looks like this declaration makes compiler forget about some of the
// troubles it has with templates.
static void Dummy( void );
#endif // #ifdef _MSC_VER

}} // end namespace itk::fem

#endif // #ifndef __itkFEMElement3DC0LinearHexahedron_txx
