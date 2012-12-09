/*******************************************************************************
swankmania_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/


`ifndef ALDEC
  //`define ALDEC
`endif


`ifdef ALDEC
  `timescale 1 ps / 1 ps // units / accuracy
  #define always_ff     always
  #define always_comb   always @( * )
  #define always_latch  always @( * )
  #ifndef unique
  	#define unique
  #endif
`endif
