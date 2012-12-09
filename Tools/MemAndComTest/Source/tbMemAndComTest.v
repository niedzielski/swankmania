/*******************************************************************************
swankmania_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   Saturday, October 6, 2007 [Stephen Niedzielski]
// Modified:  Saturday, October 6, 2007 [Stephen Niedzielski]
module tbswankmania_HDL;

  // Generate clock signals.
  wire
  iClk27,
  iClk50;
  tbClk
  #(
    .Frequency_kHz( 50_000 )
  )
  tbClk0
  (
    ._oClk( iClk50 )
  );

  tbClk
  #(
    .Frequency_kHz( 27_000 )
  )
  tbClk1
  (
    ._oClk( iClk27 )
  );

  swankmania_HDL
  swankmania_HDL0
  (
    .iClk27( iClk27 ),
    .iClk50( iClk50 ),
    
    // Switches and buttons.
    .iSwitch(  ),
    .iButton_(  ),

    // LEDs.
    .oLEDR(  ),
    .oLEDG(  ),

    // Seven segment LED matrix display (hexadecimal).
    .oHex7(  ),
    .oHex6(  ),
    .oHex5(  ),
    .oHex4(  ),
    .oHex3(  ),
    .oHex2(  ),
    .oHex1(  ),
    .oHex0(  ),

    // Communication.
    .ioGPIO0(  ),

    // Sony ACX705AKM.
    .ioGPIO1(  ),

    // SRAM.
    .oSRAM_A(  ),
    .ioSRAM_IO(  ),
    .oSRAM_CE_(  ),
    .oSRAM_WE_(  ),
    .oSRAM_LB_(  ),
    .oSRAM_UB_(  ),
    .oSRAM_OE_(  )
  );
  
  initial
  begin
    #5000000 $finish;
  end

endmodule
