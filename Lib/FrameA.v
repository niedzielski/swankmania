// megafunction wizard: %RAM: 1-PORT%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: altsyncram 

// ============================================================
// File Name: FrameA.v
// Megafunction Name(s):
// 			altsyncram
//
// Simulation Library Files(s):
// 			altera_mf
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 7.2 Build 151 09/26/2007 SJ Web Edition
// ************************************************************


//Copyright (C) 1991-2007 Altera Corporation
//Your use of Altera Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Altera Program License 
//Subscription Agreement, Altera MegaCore Function License 
//Agreement, or other applicable license agreement, including, 
//without limitation, that your use is for the sole purpose of 
//programming logic devices manufactured by Altera and sold by 
//Altera or its authorized distributors.  Please refer to the 
//applicable agreement for further details.


// synopsys translate_off
`timescale 1 ps / 1 ps
// synopsys translate_on
module FrameA (
	address,
	data,
	inclock,
	outclock,
	wren,
	q);

	input	[15:0]  address;
	input	[8:0]  data;
	input	  inclock;
	input	  outclock;
	input	  wren;
	output	[8:0]  q;

	wire [8:0] sub_wire0;
	wire [8:0] q = sub_wire0[8:0];

	altsyncram	altsyncram_component (
				.wren_a (wren),
				.clock0 (inclock),
				.clock1 (outclock),
				.address_a (address),
				.data_a (data),
				.q_a (sub_wire0),
				.aclr0 (1'b0),
				.aclr1 (1'b0),
				.address_b (1'b1),
				.addressstall_a (1'b0),
				.addressstall_b (1'b0),
				.byteena_a (1'b1),
				.byteena_b (1'b1),
				.clocken0 (1'b1),
				.clocken1 (1'b1),
				.clocken2 (1'b1),
				.clocken3 (1'b1),
				.data_b (1'b1),
				.eccstatus (),
				.q_b (),
				.rden_a (1'b1),
				.rden_b (1'b1),
				.wren_b (1'b0));
	defparam
		altsyncram_component.clock_enable_input_a = "BYPASS",
		altsyncram_component.clock_enable_output_a = "BYPASS",
`ifdef NO_PLI
		altsyncram_component.init_file = "../startup.rif"
`else
		altsyncram_component.init_file = "../startup.hex"
`endif
,
		altsyncram_component.intended_device_family = "Cyclone II",
		altsyncram_component.lpm_type = "altsyncram",
		altsyncram_component.numwords_a = 38400,
		altsyncram_component.operation_mode = "SINGLE_PORT",
		altsyncram_component.outdata_aclr_a = "NONE",
		altsyncram_component.outdata_reg_a = "CLOCK1",
		altsyncram_component.power_up_uninitialized = "FALSE",
		altsyncram_component.widthad_a = 16,
		altsyncram_component.width_a = 9,
		altsyncram_component.width_byteena_a = 1;


endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: ADDRESSSTALL_A NUMERIC "0"
// Retrieval info: PRIVATE: AclrAddr NUMERIC "0"
// Retrieval info: PRIVATE: AclrByte NUMERIC "0"
// Retrieval info: PRIVATE: AclrData NUMERIC "0"
// Retrieval info: PRIVATE: AclrOutput NUMERIC "0"
// Retrieval info: PRIVATE: BYTE_ENABLE NUMERIC "0"
// Retrieval info: PRIVATE: BYTE_SIZE NUMERIC "9"
// Retrieval info: PRIVATE: BlankMemory NUMERIC "0"
// Retrieval info: PRIVATE: CLOCK_ENABLE_INPUT_A NUMERIC "0"
// Retrieval info: PRIVATE: CLOCK_ENABLE_OUTPUT_A NUMERIC "0"
// Retrieval info: PRIVATE: Clken NUMERIC "0"
// Retrieval info: PRIVATE: DataBusSeparated NUMERIC "1"
// Retrieval info: PRIVATE: IMPLEMENT_IN_LES NUMERIC "0"
// Retrieval info: PRIVATE: INIT_FILE_LAYOUT STRING "PORT_A"
// Retrieval info: PRIVATE: INIT_TO_SIM_X NUMERIC "0"
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Cyclone II"
// Retrieval info: PRIVATE: JTAG_ENABLED NUMERIC "0"
// Retrieval info: PRIVATE: JTAG_ID STRING "NONE"
// Retrieval info: PRIVATE: MAXIMUM_DEPTH NUMERIC "0"
// Retrieval info: PRIVATE: MIFfilename STRING "../startup.hex"
// Retrieval info: PRIVATE: NUMWORDS_A NUMERIC "38400"
// Retrieval info: PRIVATE: RAM_BLOCK_TYPE NUMERIC "0"
// Retrieval info: PRIVATE: READ_DURING_WRITE_MODE_PORT_A NUMERIC "3"
// Retrieval info: PRIVATE: RegAddr NUMERIC "1"
// Retrieval info: PRIVATE: RegData NUMERIC "1"
// Retrieval info: PRIVATE: RegOutput NUMERIC "1"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
// Retrieval info: PRIVATE: SingleClock NUMERIC "0"
// Retrieval info: PRIVATE: UseDQRAM NUMERIC "1"
// Retrieval info: PRIVATE: WRCONTROL_ACLR_A NUMERIC "0"
// Retrieval info: PRIVATE: WidthAddr NUMERIC "16"
// Retrieval info: PRIVATE: WidthData NUMERIC "9"
// Retrieval info: PRIVATE: rden NUMERIC "0"
// Retrieval info: CONSTANT: CLOCK_ENABLE_INPUT_A STRING "BYPASS"
// Retrieval info: CONSTANT: CLOCK_ENABLE_OUTPUT_A STRING "BYPASS"
// Retrieval info: CONSTANT: INIT_FILE STRING "../startup.hex"
// Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "Cyclone II"
// Retrieval info: CONSTANT: LPM_TYPE STRING "altsyncram"
// Retrieval info: CONSTANT: NUMWORDS_A NUMERIC "38400"
// Retrieval info: CONSTANT: OPERATION_MODE STRING "SINGLE_PORT"
// Retrieval info: CONSTANT: OUTDATA_ACLR_A STRING "NONE"
// Retrieval info: CONSTANT: OUTDATA_REG_A STRING "CLOCK1"
// Retrieval info: CONSTANT: POWER_UP_UNINITIALIZED STRING "FALSE"
// Retrieval info: CONSTANT: WIDTHAD_A NUMERIC "16"
// Retrieval info: CONSTANT: WIDTH_A NUMERIC "9"
// Retrieval info: CONSTANT: WIDTH_BYTEENA_A NUMERIC "1"
// Retrieval info: USED_PORT: address 0 0 16 0 INPUT NODEFVAL address[15..0]
// Retrieval info: USED_PORT: data 0 0 9 0 INPUT NODEFVAL data[8..0]
// Retrieval info: USED_PORT: inclock 0 0 0 0 INPUT NODEFVAL inclock
// Retrieval info: USED_PORT: outclock 0 0 0 0 INPUT NODEFVAL outclock
// Retrieval info: USED_PORT: q 0 0 9 0 OUTPUT NODEFVAL q[8..0]
// Retrieval info: USED_PORT: wren 0 0 0 0 INPUT NODEFVAL wren
// Retrieval info: CONNECT: @address_a 0 0 16 0 address 0 0 16 0
// Retrieval info: CONNECT: q 0 0 9 0 @q_a 0 0 9 0
// Retrieval info: CONNECT: @clock0 0 0 0 0 inclock 0 0 0 0
// Retrieval info: CONNECT: @clock1 0 0 0 0 outclock 0 0 0 0
// Retrieval info: CONNECT: @data_a 0 0 9 0 data 0 0 9 0
// Retrieval info: CONNECT: @wren_a 0 0 0 0 wren 0 0 0 0
// Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA.inc FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA.bsf FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA_inst.v FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA_bb.v FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA_waveforms.html FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL FrameA_wave*.jpg FALSE
// Retrieval info: LIB_FILE: altera_mf