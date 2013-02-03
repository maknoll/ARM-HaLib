#pragma once

#include <stdint.h>

namespace arm_halib{
namespace regmaps{
namespace local{
namespace lm4f
{
  struct GpioBanks
  {
    enum GpioBankType {a=0,b,c,d,e,f};
  };
  typedef GpioBanks::GpioBankType GpioBankType;

  template<GpioBankType bankInput>
  struct GpioBank
  {
    static const GpioBankType bank=bankInput;
    union
    {
        struct
        {
            uint8_t __base[0x40058000+bank*0x1000];
            union
            {
                struct
                {
                    uint8_t  __offset0[0];
                    uint32_t data[0xFF];
                };

                struct
                {
                    uint8_t  __offset1[0x400];
                    uint8_t dir;
                };

                struct
                {
                    uint8_t  __offset2[0x420];
                    uint8_t special;
                };

                struct
                {
                    uint8_t  __offset3[0x51C];
                    uint8_t active;
                };

                struct
                {
                    uint8_t  __offset4[0x52C];
                    uint32_t specialSelect;
                };
            };
        };

        struct
        {
            uint8_t  __base4[0x400FE608];
            uint8_t enableBank;
        };

        struct
        {
            uint8_t  __base5[0x400FE06C];
            uint8_t highSpeedBank;
        };


    };
  };
}
}
}
}
