/*******************************************************************************
swankmania_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   Wednesday, October 31, 2007 [Stephen Niedzielski]
// Modified:  Thursday, November 1, 2007 [Stephen Niedzielski]
module Debounce
(
  input   iClk,
  input   iD,
  output  oQ
);

  reg _Q;
  initial _Q = 1'b0;
  
  reg _Bounce;
  initial _Bounce = 1'b0;

  assign oQ = _Q;
  // Note: oQ = iD & !_Bounce may provide output shorter than one clock length.
    
  always_ff @( posedge iClk )
  begin
    _Bounce <= iD;
    _Q <= iD & !_Bounce;
  end

endmodule
