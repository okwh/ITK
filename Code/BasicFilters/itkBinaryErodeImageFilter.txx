/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkBinaryErodeImageFilter.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef __itkBinaryErodeImageFilter_txx
#define __itkBinaryErodeImageFilter_txx

#include "itkBinaryErodeImageFilter.h"

namespace itk {

template<class TInputImage, class TOutputImage, class TKernel>
BinaryErodeImageFilter<TInputImage, TOutputImage, TKernel>
::BinaryErodeImageFilter()
{
  m_ErodeValue = NumericTraits<PixelType>::NonpositiveMin();
}

template<class TInputImage, class TOutputImage, class TKernel>
BinaryErodeImageFilter<TInputImage, TOutputImage, TKernel>::PixelType
BinaryErodeImageFilter<TInputImage, TOutputImage, TKernel>
::Evaluate(const SmartNeighborhoodIteratorType &nit,
           const KernelType &kernel)
{
  PixelType min = NumericTraits<PixelType>::max();

  bool erode = false;               // do some sort of erosion
  bool completelyBackground = true; // structuring element is completely
                                    // over background pixels
  
  SmartNeighborhoodIteratorType::ConstIterator neigh_it;
  KernelIteratorType kernel_it;
  const KernelIteratorType kernelEnd = kernel.End();

  neigh_it = nit.Begin();
  for (kernel_it=kernel.Begin(); kernel_it<kernelEnd; ++kernel_it, ++neigh_it)
    {
    // if structuring element is positive, use the pixel under that element
    // in the image
    if (*kernel_it > 0)
      {
      // if the image pixel is not the erode value, 
      if (**neigh_it != m_ErodeValue)
        {
        erode = true;
        
        // if the image pixel is less than current min
        if (min > **neigh_it)
          {
          min = **neigh_it;
          }
        }
      else
        {
        // at least one pixel in structuring element is the foreground
        completelyBackground = false;
        }
      }
    }

  // Four cases for the return value:
  // 1) If nothing in structuring element is the ErodeValue (foreground)
  //      then leave pixel unchanged
  // 2) If all of structuring element is the ErodeValue (foreground)
  //      then return ErodeValue
  // 3) If part of the structuring elemene is over background, and the
  //       center pixel of the structuring element is "on", then
  //       return the minimum of all the background values visited
  // 4) If part of the structuring element is over background, and the
  //       center pixel of the structuring element is "off", then
  //       leave pixel unchanged
  if (completelyBackground)
    {
    // case #1
    return nit.GetCenterPixel();
    }
  else
    {
    if (!erode)
      {
      // case #2, don't erode
      return m_ErodeValue;
      }
    else
      {
      if (kernel.GetCenterValue() > 0)
        {
        // case #3, center pixel is "on"
        return min;
        }
      else
        {
        // case #4, center pixel is "off"
        return nit.GetCenterPixel();
        }
      }
    }
} 

template<class TInputImage, class TOutputImage, class TKernel>
void
BinaryErodeImageFilter<TInputImage, TOutputImage, TKernel>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Erode value: " << m_ErodeValue
     << std::endl;
}

}// end namespace itk
#endif
