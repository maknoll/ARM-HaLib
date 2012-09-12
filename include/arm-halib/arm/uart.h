#pragma once

#include "../regmaps/local.h"
#include "../common/frequency.h"
//#include "../common/delay.h"
#include <stdint.h>

namespace arm_halib{
namespace drivers{

    /** \brief UART Driver
     *
     *	For reading and writing single characters over a serial connection with and without interrupt support
     **/
    struct Uart
    {
        typedef uint32_t BaudRateType;
        typedef uint8_t  DataBitType;
        typedef uint8_t  StopBitType;

        struct Parity
        {
            enum ParityType
            {
                none = 0,
                even = 1,
                odd  = 2
            };
        };
        typedef Parity::ParityType ParityType;

        struct DefaultConfig
        {
            typedef regmaps::local::Uart0      RegMap;
            typedef config::Frequency<F_CPU>   BaseClock;

            static const bool         useInterrupt = false;
            static const BaudRateType baudRate     = 9600;
            static const DataBitType  dataBits     = 8;
            static const StopBitType  stopBits     = 1;
            static const ParityType   parity       = Parity::none;
        };

        template<typename Config = DefaultConfig>
        struct configure
        {
            typedef typename Config::RegMap RegMap;
            struct Core
            {
//                struct SleepSync
//                {
//                    void sync()
//                    {
//                        delay_us(12*1000000ULL/Config::baudRate);
//                    }
//                };

                Core()
                {
                    UseRegMap(rm, RegMap);
                    
                    typedef          config::Frequency< Config::baudRate*16>          divider;
                    typedef typename Config::BaseClock::template div< divider >::type UBBRConfig;

                    //rm.ubbr  = (uint16_t)UBBRConfig::value - 1;
                    /* Configure baudrate */
                    /* Asynchronous, no oversampling */
                    rm.brgr = (uint32_t)UBBRConfig::value - 1;


                    /* Configure PIO */

                    /* Configure PMC */

                    /* Reset and disable receiver & transmitter */
                    rm.rstrx = true;
                    rm.rsttx = true;
                    rm.rxdis = true;
                    rm.txdis = true;

                    /* Configure mode */
                    rm.par = false;

                    /* Disable PDC channel */

                    /* Enable receiver and transmitter */
                    rm.rxen = true;
                    rm.txen = true;

                    SyncRegMap(rm);
                }
                
                void put(const uint8_t c)
                {
                    UseRegMap(rm, RegMap);
                    rm.thr = c;
                    SyncRegMap(rm);
                }

                bool ready()
                {
                  UseRegMap(rm, RegMap);
                  SyncRegMap(rm);
                  return rm.isr.txrdy;
                }
                
                /**	\brief	Reads a character from the input buffer
                 *	\param	c	Reference to variable which shall store the character
                 *	\return		true if a character was read
                 */
                bool get(uint8_t& c)
                {
                    UseRegMap(rm, RegMap);
                    SyncRegMap(rm);
                    if (rm.sr.txrdy)
                    {
                        c = rm.rhr;
                        return true;
                    }else
                        return false;
                }
            };
            typedef Core type;
            
            /*
            struct InterruptExtension : public Core
            {
                //TODO Include interrupt manager support

                void enableonReceive()
                {	
                    UseRegMap(rm, RegMap);
                    rm.rxcie=true;
                    SyncRegMap(rm);
                }

                void enableonReady()
                {
                    UseRegMap(rm, RegMap);
                    rm.udrie=true;
                    SyncRegMap(rm);
                }
                void disableonReceive()
                {	
                    UseRegMap(rm, RegMap);
                    rm.rxcie=false;
                    SyncRegMap(rm);
                }

                void disableonReady()
                {
                    UseRegMap(rm, RegMap);
                    rm.udrie=false;
                    SyncRegMap(rm);
                }
            };

            typedef typename boost::mpl::if_c< Config::useInterrupt, 
                                               InterruptExtension,
                                               Core
                                             >::type type;
            };
            */
    };
};
}
}
