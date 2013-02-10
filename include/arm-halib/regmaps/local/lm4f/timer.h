#pragma once

#include <stdint.h>
#include <arm-halib/regmaps/base/localRegMap.h>

namespace arm_halib{
namespace regmaps{
namespace local{
namespace lm4f
{
        template<uint8_t i>
        struct Timer : public base::LocalRegMap
        {
            enum{index = i};
            union
            {           
              struct
              {
                uint8_t __base0[0x40030000+i*0x1000];
                union
                {
                    struct
                    {
                        uint8_t __offset0[0x0];
                        uint8_t config : 4;
                    };

                    union
                    {
                            struct
                            {
                                uint8_t __offset1[0x4];
                                uint8_t mr    : 2;
                                uint8_t cmr   : 1;
                                uint8_t ams   : 1;
                                uint8_t cdir  : 1;
                                uint8_t mie   : 1;
                                uint8_t wot   : 1;
                                uint8_t snaps : 1;
                                uint8_t ild   : 1;
                                uint8_t wmie  : 1;
                                uint8_t mrsu  : 1;
                                uint8_t plo   : 1;
                            };
                            
                            struct
                            {
                                uint8_t __offset2[0xc];
                                uint8_t en    : 1;
                                uint8_t stbll : 1;
                                uint8_t event : 2;
                                uint8_t rtcen : 1;
                                uint8_t ote   : 1;
                                uint8_t pwml  : 1;
                            };

                            struct
                            {
                                uint8_t __offset3[0x28];
                                uint32_t interval;
                            };

                            struct
                            {
                                uint8_t __offset4[0x30];
                                uint32_t match;
                            };

                            struct
                            {
                                uint8_t __offset5[0x38];
                                uint32_t prescaler;
                            };

                            struct
                            {
                                uint8_t __offset6[0x40];
                                uint32_t prescalerMatch;
                            };

                            struct
                            {
                                uint8_t __offset7[0x48];
                                uint32_t value;
                            };
                    } a;

                    union
                    {
                            struct
                            {
                                uint8_t __offset1[0x8];
                                uint8_t mr    : 2;
                                uint8_t cmr   : 1;
                                uint8_t ams   : 1;
                                uint8_t cdir  : 1;
                                uint8_t mie   : 1;
                                uint8_t wot   : 1;
                                uint8_t snaps : 1;
                                uint8_t ild   : 1;
                                uint8_t wmie  : 1;
                                uint8_t mrsu  : 1;
                                uint8_t plo   : 1;
                            };
                            
                            struct
                            {
                                uint8_t __offset2[0xc];
                                uint8_t       : 8;
                                uint8_t en    : 1;
                                uint8_t stbll : 1;
                                uint8_t event : 2;
                                uint8_t rtcen : 1;
                                uint8_t ote   : 1;
                                uint8_t pwml  : 1;
                            };

                            struct
                            {
                                uint8_t __offset3[0x2c];
                                uint32_t interval;
                            };

                            struct
                            {
                                uint8_t __offset4[0x34];
                                uint32_t match;
                            };

                            struct
                            {
                                uint8_t __offset5[0x3c];
                                uint32_t prescaler;
                            };

                            struct
                            {
                                uint8_t __offset6[0x44];
                                uint32_t prescalerMatch;
                            };

                            struct
                            {
                                uint8_t __offset7[0x4C];
                                uint32_t value;
                            };
                    } b;
                };
              };
            struct
            {
                uint8_t __base1[0x400FE604];
                uint8_t enable : 6;
            };

            struct
            {
                uint8_t __base2[0xE000E100];
                uint8_t intEnable : 6;
            };
            };
        };
}
}
}
}
