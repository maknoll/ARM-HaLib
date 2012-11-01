#pragma once

#include <stdint.h>

namespace arm_halib{
  namespace regmaps{
    namespace local{
      namespace sam3s4b{
        struct Uart0 : public base::LocalRegMap{
          private:
            uint8_t __base [0x400E0600];
          public:
            union {
              int cr;
              struct {
                int         :  2;
                bool rstrx  :  1;
                bool rsttx  :  1;
                bool rxen   :  1;
                bool rxdis  :  1;
                bool txen   :  1;
                bool txdis  :  1;
                bool rststa :  1;
              };
            };
            union {
              int mr;
              struct {
                int        :  9;
                int par    :  3;
                int        :  2;
                int chmode :  2;
              };
            };
            struct {
              bool rxrdy   :  1;
              bool txrdy   :  1;
              bool         :  1;
              bool endrx   :  1;
              bool endtx   :  1;
              bool ovre    :  1;
              bool frame   :  1;
              bool pare    :  1;
              bool         :  1;
              bool txempty :  1;
              bool         :  1;
              bool txbufe  :  1;
              bool rxbuff  :  1;
            } ier;
            struct {
              bool rxrdy   :  1;
              bool txrdy   :  1;
              bool         :  1;
              bool endrx   :  1;
              bool endtx   :  1;
              bool ovre    :  1;
              bool frame   :  1;
              bool pare    :  1;
              bool         :  1;
              bool txempty :  1;
              bool         :  1;
              bool txbufe  :  1;
              bool rxbuff  :  1;
            } idr;
            struct {
              bool rxrdy   :  1;
              bool txrdy   :  1;
              bool         :  1;
              bool endrx   :  1;
              bool endtx   :  1;
              bool ovre    :  1;
              bool frame   :  1;
              bool pare    :  1;
              bool         :  1;
              bool txempty :  1;
              bool         :  1;
              bool txbufe  :  1;
              bool rxbuff  :  1;
            } imr;
            struct {
              bool rxrdy   :  1;
              bool txrdy   :  1;
              bool         :  1;
              bool endrx   :  1;
              bool endtx   :  1;
              bool ovre    :  1;
              bool frame   :  1;
              bool pare    :  1;
              bool         :  1;
              bool txempty :  1;
              bool         :  1;
              bool txbufe  :  1;
              bool rxbuff  :  1;
            } sr;
            int rhr;
            int thr;
            int brgr;
        }__attribute__((packed));
      }
    }
  }
}
