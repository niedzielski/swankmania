/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Converts a given number, iBCD, to the appropriate logic for a hexadecimal
// seven segment LED matrix display.
// Created:   ~Friday, June 1, 2007 [Stephen Niedzielski]
// Modified:  Thursday, November 1, 2007 [Stephen Niedzielski]
module SSHLEDMDCtrl
(
  input [3:0]   iBCD,   // Unsigned number to display.
  output [6:0]  oMatrix // Seven segment hexadecimal LED matrix display.
);

  reg [6:0] _oMatrix;
  initial
    _oMatrix = ~7'b011_1111;
  assign oMatrix = _oMatrix;

  // Update the matrix with the appropriate display logic for a given number
  // iBCD.
    always_comb
    begin
      case( iBCD )
        default: _oMatrix = ~7'b011_1111;
        4'h1: _oMatrix = ~7'b000_0110;
        4'h2: _oMatrix = ~7'b101_1011;
        4'h3: _oMatrix = ~7'b100_1111;
        4'h4: _oMatrix = ~7'b110_0110;
        4'h5: _oMatrix = ~7'b110_1101;
        4'h6: _oMatrix = ~7'b111_1101;
        4'h7: _oMatrix = ~7'b000_0111;
        4'h8: _oMatrix = ~7'b111_1111;
        4'h9: _oMatrix = ~7'b110_0111;
        4'hA: _oMatrix = ~7'b111_0111;
        4'hb: _oMatrix = ~7'b111_1100;
        4'hC: _oMatrix = ~7'b011_1001;
        4'hd: _oMatrix = ~7'b101_1110;
        4'hE: _oMatrix = ~7'b111_1001;
        4'hF: _oMatrix = ~7'b111_0001;
      endcase
    end

endmodule
