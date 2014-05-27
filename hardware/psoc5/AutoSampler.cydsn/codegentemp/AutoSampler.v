// ======================================================================
// AutoSampler.v generated from TopDesign.cysch
// 05/22/2014 at 19:17
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PSOC4A 2
`define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17
`define CYDEV_CHIP_REV_PSOC4A_ES0 17
`define CYDEV_CHIP_DIE_PANTHER 3
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_PSOC5LP 4
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 3
`define CYDEV_CHIP_REV_EXPECT 1
`define CYDEV_CHIP_DIE_ACTUAL 3
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_MEMBER_4A 2
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_5B 4
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_FAMILY_USED 3
`define CYDEV_CHIP_MEMBER_USED 3
`define CYDEV_CHIP_REVISION_USED 1
// Component: PulseConvert_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\PulseConvert_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\PulseConvert_v1_0\PulseConvert_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\PulseConvert_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\PulseConvert_v1_0\PulseConvert_v1_0.v"
`endif

// Component: BasicCounter_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\BasicCounter_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\BasicCounter_v1_0\BasicCounter_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\BasicCounter_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\BasicCounter_v1_0\BasicCounter_v1_0.v"
`endif

// Component: CyStatusReg_v1_80
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyStatusReg_v1_80"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyStatusReg_v1_80\CyStatusReg_v1_80.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyStatusReg_v1_80"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.2\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyStatusReg_v1_80\CyStatusReg_v1_80.v"
`endif

// top
module top ;

          wire  Net_873;
          wire  Net_803;
          wire  Net_802;
          wire  Net_801;
          wire  Net_800;
          wire  Net_799;
          wire  Net_798;
          wire  Net_797;
          wire  Net_796;
          wire  Net_795;
          wire  Net_847;
          wire  Net_817;
          wire  Net_816;
          wire  Net_815;
          wire  Net_869;
          wire  Net_678;
          wire  Net_681;
          wire  Net_860;
          wire  Net_721;
          wire  Net_853;
          wire  Net_629;
          wire  Net_444;
          wire  Net_124;
          wire [7:0] Net_130;

	wire [0:0] tmpOE__Pin_Sampler_Power_net;
	wire [0:0] tmpFB_0__Pin_Sampler_Power_net;
	wire [0:0] tmpIO_0__Pin_Sampler_Power_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Sampler_Power_net;
	electrical [0:0] tmpSIOVREF__Pin_Sampler_Power_net;

	cy_psoc3_pins_v1_10
		#(.id("52f31aa9-2f0a-497d-9a1f-1424095e13e6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_Sampler_Power
		 (.oe(tmpOE__Pin_Sampler_Power_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Pin_Sampler_Power_net[0:0]}),
		  .io({tmpIO_0__Pin_Sampler_Power_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Sampler_Power_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Sampler_Power_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Pin_Sampler_Power_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Pin_Sampler_Trigger_net;
	wire [0:0] tmpFB_0__Pin_Sampler_Trigger_net;
	wire [0:0] tmpIO_0__Pin_Sampler_Trigger_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Sampler_Trigger_net;
	electrical [0:0] tmpSIOVREF__Pin_Sampler_Trigger_net;

	cy_psoc3_pins_v1_10
		#(.id("b41c8abe-876a-460f-af8a-b534f4d508e7"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_Sampler_Trigger
		 (.oe(tmpOE__Pin_Sampler_Trigger_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Pin_Sampler_Trigger_net[0:0]}),
		  .io({tmpIO_0__Pin_Sampler_Trigger_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Sampler_Trigger_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Sampler_Trigger_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Pin_Sampler_Trigger_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Pin_Sampler_Completed_Sample_net;
	wire [0:0] tmpIO_0__Pin_Sampler_Completed_Sample_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Sampler_Completed_Sample_net;
	electrical [0:0] tmpSIOVREF__Pin_Sampler_Completed_Sample_net;

	cy_psoc3_pins_v1_10
		#(.id("4c15b41e-e284-4978-99e7-5aaee19bd0ce"),
		  .drive_mode(3'b011),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Pin_Sampler_Completed_Sample
		 (.oe(tmpOE__Pin_Sampler_Completed_Sample_net),
		  .y({1'b0}),
		  .fb({Net_629}),
		  .io({tmpIO_0__Pin_Sampler_Completed_Sample_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Sampler_Completed_Sample_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Sampler_Completed_Sample_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Pin_Sampler_Completed_Sample_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Pin_Sampler_Sampler_Count_net;
	wire [0:0] tmpIO_0__Pin_Sampler_Sampler_Count_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Sampler_Sampler_Count_net;
	electrical [0:0] tmpSIOVREF__Pin_Sampler_Sampler_Count_net;

	cy_psoc3_pins_v1_10
		#(.id("e2a43758-5371-46fb-8a25-b7aa285a349d"),
		  .drive_mode(3'b011),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Pin_Sampler_Sampler_Count
		 (.oe(tmpOE__Pin_Sampler_Sampler_Count_net),
		  .y({1'b0}),
		  .fb({Net_860}),
		  .io({tmpIO_0__Pin_Sampler_Sampler_Count_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Sampler_Sampler_Count_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Sampler_Sampler_Count_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Pin_Sampler_Sampler_Count_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PulseConvert_v1_0 PulseConvert_1 (
        .p_in(Net_860),
        .p_out(Net_721),
        .sample_clk(Net_678),
        .out_clk(Net_681));

    PulseConvert_v1_0 PulseConvert_2 (
        .p_in(Net_629),
        .p_out(Net_853),
        .sample_clk(Net_444),
        .out_clk(Net_869));


	cy_clock_v1_0
		#(.id("0a6850cc-83e2-4b12-8872-94e8ff30e044"),
		  .source_clock_id("315365C3-2E3E-4f04-84A2-BB564A173261"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_3
		 (.clock_out(Net_444));



	cy_clock_v1_0
		#(.id("50671698-37c0-4e44-a007-298b77a77b15"),
		  .source_clock_id("315365C3-2E3E-4f04-84A2-BB564A173261"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_4
		 (.clock_out(Net_678));



	cy_clock_v1_0
		#(.id("a3ff0da9-0999-4372-984d-8a4f96b1e350"),
		  .source_clock_id("315365C3-2E3E-4f04-84A2-BB564A173261"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_5
		 (.clock_out(Net_124));



	cy_clock_v1_0
		#(.id("920ac626-75fc-42be-bddc-386ba9cec7f2"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("25000000000000"),
		  .is_direct(0),
		  .is_digital(1))
		SlowClock
		 (.clock_out(Net_681));


    BasicCounter_v1_0 BasicCounter_2 (
        .en(Net_721),
        .cnt(Net_130[7:0]),
        .reset(Net_853),
        .clock(Net_681));
    defparam BasicCounter_2.Width = 8;


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_SampleCounter
		 (.int_signal(Net_853));


    CyStatusReg_v1_80 BottleCount (
        .status_0(1'b0),
        .status_1(1'b0),
        .status_2(1'b0),
        .status_3(1'b0),
        .clock(Net_124),
        .status_4(1'b0),
        .status_5(1'b0),
        .status_6(1'b0),
        .status_7(1'b0),
        .intr(Net_803),
        .status_bus(Net_130[7:0]));
    defparam BottleCount.Bit0Mode = 0;
    defparam BottleCount.Bit1Mode = 0;
    defparam BottleCount.Bit2Mode = 0;
    defparam BottleCount.Bit3Mode = 0;
    defparam BottleCount.Bit4Mode = 0;
    defparam BottleCount.Bit5Mode = 0;
    defparam BottleCount.Bit6Mode = 0;
    defparam BottleCount.Bit7Mode = 0;
    defparam BottleCount.BusDisplay = 1;
    defparam BottleCount.Interrupt = 0;
    defparam BottleCount.MaskValue = 0;
    defparam BottleCount.NumInputs = 8;


	cy_clock_v1_0
		#(.id("9a0d0d46-ccae-460f-8ef5-f45bc0cc875d"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("25000000000000"),
		  .is_direct(0),
		  .is_digital(1))
		SlowClock_1
		 (.clock_out(Net_869));




endmodule

