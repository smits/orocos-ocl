/***************************************************************************
  tag: Peter Soetens  Thu Apr 22 20:41:00 CEST 2004  Sine.hpp

                        Sine.hpp -  description
                           -------------------
    begin                : Thu April 22 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef ORO_SIGNAL_PROC_SINE_HPP
#define ORO_SIGNAL_PROC_SINE_HPP

#include "SignalGeneratorInterface.hpp"
#include <math.h>


namespace ORO_SignalProcessing
{

    /**
     * Generates a sine (or cosine if you specify phase = M_PI/2
     */
    class Sine
        : public SignalGeneratorInterface
    {
        double a,f,ph;
    public:
        /**
         * Create a sine signal generator.
         *
         * @param amplitude The amplitude of the sine.
         * @param frequence The frequence of the sine in Hz.
         * @param phase The phase shift of the sine (in radians).
         */
        Sine(double amplitude, double frequence, double phase)
            : a(amplitude), f(frequence), ph(phase)
        {}

        double result( double t )
        {
            return a*sin( (2* M_PI *f)*t + ph );
        }

        void reset() {}
    };
}

#endif
