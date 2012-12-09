/*******************************************************************************
swankmania_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   Wednesday, October 31, 2007 [Stephen Niedzielski]
// Modified:  Thursday, November 1, 2007 [Stephen Niedzielski]
module ComCtrl
(
  input         iClk,
  
  // MCU.
  input [8:0]   iD,
  input         iGo,
  input         iCmd,

  // Draw.
  output        oGo,
  input         iDone,
  output [8:0]  oColor,  
  output [7:0]  oX0,
  output [7:0]  oY0,
  output [7:0]  oX1,
  output [7:0]  oY1,
  output [7:0]  oX2,
  output [7:0]  oY2,
  output        oFlip,
  output        oPolyline,
  output        oTriangle,

  // Debug.
  output        oDbgFull,
  output        oDbgFullPersistent,
  output [9:0]  oDbgUsed
);

  reg _FullPersistent;
  initial
    _FullPersistent = 1'b0;

  reg [8:0] _Color;
  reg _SetColor;
  initial
  begin
    _Color = 9'hxxx;
    _SetColor = 1'b0;
  end
 
  wire DebounceGo;
  
  wire FIFO_Empty;
  reg _FIFO_Pop;
  initial
    _FIFO_Pop = 1'b0;
	wire [9:0] FIFO_Q;
  wire FIFO_Cmd;
  wire [9:0] FIFO_Used;

  wire
  DecoderFlip,
  DecoderPolyline;
  
  reg [7:0] _VertexBuf[0:3];
  initial
  begin
    _VertexBuf[0] = 8'hxx;
    _VertexBuf[1] = 8'hxx;
    _VertexBuf[2] = 8'hxx;
    _VertexBuf[3] = 8'hxx;
  end
  
  reg [7:0] _Cnt;
  reg
  _Flip,
  _Go,
  _Polyline;
  initial
  begin
    _Cnt <= 8'hxx;
    _Flip <= 1'b0;
    _Go <= 1'b0;
    _Polyline = 1'b0;
  end

  // Persistent full.
  assign oDbgFullPersistent = _FullPersistent;  
  always_ff @( posedge iClk )
    if( oDbgFull )
      _FullPersistent <= 1'b1;

  // Color.
  assign oColor = _Color;
  
  // Debounce go.
  Debounce
  Debounce0
  (
    .iClk( iClk ),
    .iD( iGo ),
    .oQ( DebounceGo )
  );
  
  // Communication FIFO.
  assign FIFO_Cmd = FIFO_Q[9];
  assign oDbgUsed = FIFO_Used;
  ComFIFO
  ComFIFO0
  (
  	.clock( iClk ),
  	.data( {iCmd, iD} ),
  	.rdreq( _FIFO_Pop ),
  	.wrreq( DebounceGo ),
  	.q( FIFO_Q ),
  	.usedw( FIFO_Used ),
    .empty( FIFO_Empty ),
    .full( oDbgFull )
  );

  /*
    Commands supported:
    0:  Flip
    1:  Polyline.                 Color, verticies.
    2:  Triangle and color.       Color, triangle, color, triangle, ...
    3:  Triangle.                 Color, triangles.
    4:  Color.                    Color, ...
    5:  Dot.
  */
  wire
  DecoderColor,
  DecoderDot;
  CmdDecoder
  CmdDecoder0
  (
  	.data( FIFO_Q[3:0] ), // Limited to 16 commands for now, but protocol allows 512.
  	.eq00( DecoderFlip ),
  	.eq01( DecoderPolyline ),
  	.eq02(  ),
  	.eq03(  ),
  	.eq04( DecoderColor ),
  	.eq05( DecoderDot ),
  	.eq06(  ),
  	.eq07(  ),
  	.eq08(  ),
  	.eq09(  ),
  	.eq0a(  ),
  	.eq0b(  ),
  	.eq0c(  ),
  	.eq0d(  ),
  	.eq0e(  ),
  	.eq0f(  )
  );
    
  assign
  oX0 = _VertexBuf[0],
  oY0 = _VertexBuf[1],
  oX1 = _VertexBuf[2],
  oY1 = _VertexBuf[3];

    reg _Dot;
  initial _Dot = 0;

  assign
  oFlip = _Flip,
  oGo = _Go,
  oPolyline = _Polyline | _Dot;

  reg _Y;
  initial _Y = 1'b1;
    
  
  always_ff @( posedge iClk )
  begin
    // Defaults.
    _FIFO_Pop <= 1'b0;
    _Go <= 1'b0;

    if( !FIFO_Empty && iDone && !_Go && !_FIFO_Pop )
    begin
      // Defaults.
      _FIFO_Pop <= 1'b1;

      if( FIFO_Q[9] )
      begin
        // Defaults.
        _Cnt <= 0;
        _Y <= 1'b1;
        _Polyline <= 1'b0;
        _Dot <= 1'b0;
        _Flip <= 1'b0;
        _SetColor <= 1'b0;
      
        unique case( 1'b1 )
          DecoderFlip:
          begin
            _Flip <= 1'b1;
            _Color <= 9'h1FF; // White.
            _Go <= 1'b1;
          end
          DecoderPolyline:
          begin
            _Polyline <= 1'b1;
            _SetColor <= 1'b1;
          end
          DecoderColor:
          begin
            _Y <= _Y;
            _Cnt <= _Cnt;
            _Polyline <= _Polyline;
            _Dot <= _Dot;
            _SetColor <= 1'b1;
          end
          DecoderDot:
          begin
            _Dot <= 1'b1;
          end
        endcase 
      end
      else
      begin
        if( _SetColor )
        begin
          _Color <= FIFO_Q[8:0];
          _SetColor <= 1'b0;
        end
        else if( _Dot )
        begin
          if( !_Y )
            _VertexBuf[0] <= FIFO_Q[7:0];
          else
            _VertexBuf[1] <= FIFO_Q[7:0];
          _VertexBuf[2] <= 239;
          _VertexBuf[3] <= 159;
          _Y <= ~_Y;
          if( !_Y )
            _Go <= 1'b1;
        end
      end
    end
    
  end

endmodule
