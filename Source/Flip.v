/*******************************************************************************
swankmania_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   Wednesday, Noveember 7, 2007 [Stephen Niedzielski]
// Modified:  Wednesday, Noveember 7, 2007 [Stephen Niedzielski]
module Flip
(
  input         iClk,
  input         iGo,
  output        oDone,

  // Frame.
  output [15:0] oAdr,
  output        oWrEn
);

  reg [15:0] _Adr;
  initial _Adr = 16'hxxxx;
  reg _Done;
  initial _Done = 1'b1;
  reg _WrEn;
  initial _WrEn = 1'b0;

  assign oDone = _Done;
  assign oAdr = _Adr;
  assign oWrEn = _WrEn;

  always_ff @( posedge iClk )
  begin
    // Defaults.
    _Done <= 1'b0;
    _WrEn <= 1'b0;

    if( iGo )
    begin
      _Adr <= 16'd0;
      _WrEn <= 1'b1;
    end
    else
    begin
      if( _Adr < (38400 - 1'd1 ) )
      begin
        _Adr <= _Adr + 1'd1;
        _WrEn <= 1'b1;
      end
      else
        _Done <= 1'b1;
    end
  end

endmodule
