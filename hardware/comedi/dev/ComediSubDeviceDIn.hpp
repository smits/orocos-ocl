/***************************************************************************
  tag: Peter Soetens  Mon Jan 19 14:11:20 CET 2004  ComediSubDeviceDIn.hpp

                        ComediSubDeviceDIn.hpp -  description
                           -------------------
    begin                : Mon January 19 2004
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

// $Id: ComediSubDeviceDIn.hpp,v 1.6 2003/08/14 09:17:13 kgadeyne Exp $
#ifndef COMEDISUBDEVICEDIN_HPP
#define COMEDISUBDEVICEDIN_HPP

#include <rtt/dev/DigitalInInterface.hpp>
#include "ComediDevice.hpp"

namespace OCL
{

  /**
   * This logical device represents one 'Digital Input' subdevice of a Comedi device.
   * The standard constructors assumes the whole subdevice is already configured for input.
   * For DIO (reconfigurable IO devices) use the extra constructor argument to specify
   * that this should not be assumed and use the useBit() method to indicate which bits
   * should be used as input bits.
   *
   */
  class ComediSubDeviceDIn
    : public RTT::DigitalInInterface
  {

  public:
    /**
     * Create a new ComediSubDeviceDIn with a given ComediDevice, subdevice number and
     * a name for this sub device.
     *
     * @param cd The ComediDevice to use for output
     * @param subdevice The subdevice number for this comedi device
     * @param name The name of this instance
     * @param configure_all_bits Set to false to not configure all bits of this subdevice as inputs.
     * @see useBit() for configuring bit-per-bit.
     */
    ComediSubDeviceDIn( ComediDevice* cd, const std::string& name, unsigned int subdevice, bool configure_all_bits = true );

    ComediSubDeviceDIn( ComediDevice* cd, unsigned int subdevice, bool configure_all_bits = true);

    /**
     * If \a configure_all_bits was false, use this method (for each bit) to specify
     * which bits must be configured as input.
     */
    bool useBit( unsigned int bit );

    virtual bool isOn( unsigned int bit = 0) const;

    virtual bool isOff( unsigned int bit = 0) const;

    virtual bool readBit( unsigned int bit = 0) const;

    virtual unsigned int nbOfInputs() const;

    virtual unsigned int readSequence(unsigned int start_bit, unsigned int stop_bit) const;

  protected:

      void init(bool all_bits);

      /**
       * The output device to write to
       */
      ComediDevice* myCard;

      /**
       * The subdevice number of this instance in \a myCard
       */
      unsigned int _subDevice;

      bool error;
    };

  };

#endif
