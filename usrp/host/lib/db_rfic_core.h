#ifndef DB_RFIC_CORE_H
#define DB_RFIC_CORE_H

#include "usrp/db_rfic.h"
#include "db_base_impl.h"

struct rfic_key {
  std::string serial_no;
  int which;

  bool operator==(const rfic_key &x) {
    return x.serial_no ==serial_no && x.which == which;
  }
};


struct rfic {

  usrp_basic *d_raw_usrp;
  int d_which;
  bool d_is_shutdown;

  int d_spi_format, d_spi_enable,d_spi_format_no_header;

  int Ngt3, NorNdiv4, RorFrNpRdiv4_25to18, RorFrNpRdiv4_17to10;
  int RorFrNpRdiv4_9to2, RorFrNpRdiv4_1to0, Qu_tx_Ngt3;
  int NorNdiv4_phsh, RorFrNpRdiv4_phsh_25to18, RorFrNpRdiv4_phsh_17to10;
  int RorFrNpRdiv4_phsh_9to2;
  int RorFrNpRdiv4_phsh_1to0, Passthru_ref_clk, Byp_ram, Dis_adr_dith;
  int Dis_p5G_dith, Byp_fine, Exclude32, Dis_risedge;
  int Dis_faledge, Spr_puls_en, Spr_puls_val_a_9to3, Spr_pulse_val_2to0;
  int Spr_puls_val_b_9to2, Spr_puls_val_b_1to0;
  int Thru_ris_en, Thru_ris_tap_11to6, Thru_ris_tap_5to0, Thru_fal_en;
  int Thru_fal_tap_11to6, Thru_fal_tap_5to0;
  int Dig_delay, Clk_driver_en, qu_reg_en, qq_reg_en, win_rst, fineEn, fineEnb;
  int rsffEn, dl_en, cp_en, forceCpUpb;
  int forceCpDn, pdUpTune_1to0, pdDnTune_1to0, cpUpTune_2to0;
  int cpDnTune_2to0, pdEn;
  int digClkPhase_7to0, Rst_n_async;
  
  std::string L1_lup00_15to8; //Read-only
  std::string L1_lup90_15to8; //Read-only
  std::string Merg_ris_fin;   //Read-only
  std::string Merg_fal_fin;   //Read-only
    
  int Qg00degDelay_0to4 ,Qg90degDelay_0to4, Qg180degDelay_0to4;
  int Qg270degDelay_0to4, DischargeTap16_0to3;
  int ChargeTap16_0to3, DischargeTapn_0to3, ChargeTapn16_0to3, X1sel_32to39;
  int X1sel_40to47,X2sel_32to36, X2sel_37to41;
  int X4sel_32to36, X4sel_37to41, X8sel_32to36, X8sel_41, X8sel_37to40;
  int qutx_fwd_180Cal_en, qutx_fwd_0Cal_en;

  //----------------------------------------------
  // TRANSMIT FEEDBACK QuIET FREQUENCY GENERATOR
  //----------------------------------------------

  int Ngt3_2, NorNdiv4_2, RorFrNpRdiv4_25to18_2, RorFrNpRdiv4_17to10_2;
  int RorFrNpRdiv4_9to2_2, RorFrNpRdiv4_1to0_2;
  int Qu_tx_Ngt3_2, NorNdiv4_phsh_2, RorFrNpRdiv4_phsh_25to18_2;
  int RorFrNpRdiv4_phsh_17to10_2, RorFrNpRdiv4_phsh_9to2_2;
  int RorFrNpRdiv4_phsh_1to0_2, Passthru_ref_clk_2, Byp_ram_2, Dis_adr_dith_2;
  int Dis_p5G_dith_2, Byp_fine_2;
  int Exclude32_2, Dis_risedge_2, Dis_faledge_2, Spr_puls_en_2;
  int Spr_puls_val_a_9to3_2, Spr_pulse_val_2to0_2;
  int Spr_puls_val_b_9to2_2, Spr_puls_val_b_1to0_2, Thru_ris_en_2;
  int Thru_ris_tap_11to6_2, Thru_ris_tap_5to0_2;
  int Thru_fal_en_2, Thru_fal_tap_11to6_2, Thru_fal_tap_5to0_2, Dig_delay_2;
  int Clk_driver_en_2, qu_reg_en_2;
  int qq_reg_en_2, win_rst_2 , fineEn_2, fineEnb_2, rsffEn_2, dl_en_2, cp_en_2;
  int forceCpUpb_2, forceCpDn_2;
  int pdUpTune_1to0_2, pdDnTune_1to0_2, cpUpTune_2to0_2;
  int cpDnTune_2to0_2, pdEn_2;
  int digClkPhase_7to0_2, Rst_n_async_2;
  
  std::string L1_lup00_15to8_2;  //Read-only
  std::string L1_lup90_15to8_2;  //Read-only
  std::string Merg_ris_fin_2;    //Read-only
  std::string Merg_fal_fin_2;    //Read-only
  std::string Decod_in_0deg; 
  std::string L1_lup00_15to8_3; 
  std::string L1_lup90_15to8_3; 
  std::string Merg_ris_fin_3; 
  std::string Merg_fal_fin_3; 
  
  int Qg00degDelay_0to4_2, Qg90degDelay_0to4_2, Qg180degDelay_0to4_2;
  int Qg270degDelay_0to4_2, DischargeTap16_3to0;

  int ChargeTap16_3to0, DischargeTapn_3to0 , ChargeTapn16_3to0, X1sel_32to39_2;
  int X1sel_40to47_2, X2sel_32to36_2, X2sel_37to41_2, X4sel_32to36_2;
  int X4sel_37to41_2, X8sel_32to36_2, X8sel_41_2;
  int X8sel_37to40_2, qutx_fb_180Cal_en, qutx_fb_0Cal_en, qutx_fb_180Rsff_en;
  int qutx_fb_0Rsff_en, N, R_11to8;
  int R_7to0, Asyncrst_n, Cp_sel_6to0, Cp_sel_8to7;
  int ForceFout, ForceFoutb, Out_en;
  int Dll_en, Ana_en, Ngt3_3;
  int NorNdiv4_3, RorFrNpRdiv4_25to18_3, RorFrNpRdiv4_17to10_3;
  int RorFrNpRdiv4_9to2_3, RorFrNpRdiv4_1to0_3;
  int Qu_tx_Ngt3_3, NorNdiv4_phsh_3, RorFrNpRdiv4_phsh_25to18_3;
  int RorFrNpRdiv4_phsh_17to10_3, RorFrNpRdiv4_phsh_9to2_3;
  int RorFrNpRdiv4_phsh_1to0_3, Passthru_ref_clk_3, Byp_ram_3, Dis_adr_dith_3;
  int Dis_p5G_dith_3, Byp_fine_3;
  int Exclude32_3, Dis_risedge_3, Dis_faledge_3, Spr_puls_en_3;
  int Spr_puls_val_a_9to3_3, Spr_pulse_val_2to0_3;
  int Spr_puls_val_b_9to2_3, Spr_puls_val_b_1to0_3, Thru_ris_en_3;
  int Thru_ris_tap_11to6_3, Thru_ris_tap_5to0_3;
  int Thru_fal_en_3, Thru_fal_tap_11to6_3, Thru_fal_tap_5to0_3, Dig_delay_3;
  int Clk_driver_en_3, qu_reg_en_3;
  int qq_reg_en_3, win_rst_3, fineEn_3, fineEnb_3, rsffEn_3, dl_en_3, cp_en_3;
  int forceCpUpb_3, forceCpDn_3;
  int pdUpTune_1to0_3, pdDnTune_1to0_3, cpUpTune_2to0_3;
  int cpDnTune_2to0_3, pdEn_3;
  int digClkPhase_7to0_3, Rst_n_async_3;
  int Qg00degDelay_0to4_3, Qg90degDelay_0to4_3, Qg180degDelay_0to4_3;
  int Qg270degDelay_0to4_3, DischargeTap16_0to3_3;  
  int ChargeTap16_0to3_3, DischargeTapn_0to3_3, ChargeTapn16_0to3_3;

  int X1sel_32to39_3, X1sel_40to47_3, X2sel_32to36_3;
  int X2sel_37to41_3, X4sel_32to36_3, X4sel_37to41_3;
  int X8sel_32to36_3, X8sel_41_3, X8sel_37to40_3, qurx_180Cal_en;
  int qurx_0Cal_en, extClkEn, extClkEnBNOTD7, div2_rst, TxChClkSel, TxChClkEn;

  int tx_bb_en, tx_bb_fdbk_bw, tx_bb_fdbk_cal_en, tx_bb_fdbk_cart_err_en;
  int tx_bb_fdbk_cart_fb_en, tx_bb_fdbk_cart_fwd_en, tx_bb_fdbk_en;
  int tx_bb_fdbk_1q_sel, tx_bb_fdbk_lp, tx_bb_fdbk_statt, tx_bb_fdbk_swapi;
  int tx_bb_fdbk_swapq, tx_bb_gain_cmp, tx_bb_lp, tx_bb_swapi, tx_bb_swapq;
  int tx_butt_bw, tx_bw_trck, tx_cart_en, tx_cart_fb_bb_statt;

  int tx_cart_fb_dcoc_dac_I1, tx_cart_fb_dcoc_dac_I2;
  int tx_cart_fb_dcoc_dac_Q1, tx_cart_fb_dcoc_dac_Q2;

  int CartesianFeedbackpathDCOCenable, CartesianFeedbackpathenable;
  int CartesianFBpathHiResolutionDCOCenable, CartesianFBpathBW;
  int CartesianFBRFGain, CartesianFBpathSwapIandIx, CartesianFBpathSwapQandQx;
  int CartesianFBpathSwitchtoforwardSummer, tx_cart_fb_lo_select;
  int CartesianFBpathAmp1Gain, CartesianFBpathAmp2Gain;
  int CartesianFBpathAmp3Gain, CartesianFBpathAmp4Gain;
  int CartesianFBpathAmpCurrentSelect, CartesianFBpathZeroEnable;

  int tx_cart_zero_statt, tx_inbuf_bw, tx_inbuf_statt, tx_output_channel_sel;
  int tx_p1_bw, tx_pw_bw1, tx_p2_bw2;

  int PushPullBufferCurrent, tx_rf_aoc_bw, RFForwardPathEnable_toMUX;
  int RFForwardPathEnable_ExternalPinenable;

  int tx_rf_fwd_lp, tx_rf_fwd_statt1, tx_rf_fwd_statt2;

  int BBQDivideby2or4Select, BBQQuadGenEnable, BBQPolyphaseQuadGenEnable;
  int lofb_tun_s, lofb_tun_sx, lofw_tun_s2, lofw_tun_sx2;
  int reserve_tx26, reserve_tx27;

  int rx_Idac, rx_dcs, rx_den, rx_Qdac, rx_cmpen, rx_dcoc, rx_ten, rx_ren;
  int rx_dven, rx_dv, rx_extc, rx_cen;
  int rx_chck, rx_chcken, rx_fen, rx_onchen, rx_offchen, rx_foe, rx_offch;
  int rx_onchf, rx_onchc, rx_qs, rx_bqg;
  int rx_rq, rx_rv, rx_rip, rx_rfp, rx_cp_12to8, rx_gs;
  int rx_cp_7to0, rx_cv_10to3, rx_cv_2to0, rx_cc_2to0, rx_cq_9to8, rx_cq_7to0;
  int rx_lna, rx_lnab, rx_rxchen, rx_bbq_div2or4;
  int rx_Loselect, poly_en, lorx_tun_s, lorx_tun_sx;

  // I path DCOC comparator output. Output of the DCOC comparator
  // used for test purposes. Output only.
  std::string rx_Icmpo;

  // I path DCOC DAC output. Output of the DCOC DACs
  // used to read result of DCOC correction circuitry.  Output only.
  std::string rx_Iodac;

  // Q path DCOC comparator output. Output of the DCOC comparator
  // used for test purposes. Output only.
  std::string rx_Qcmpo;

  // Q path DCOC DAC output. Output of the DCOC DACs
  // Used to read result of DCOC correction circuitry. Output only.
  std::string rx_Qodac;

  std::string rx_rc;

  int shft_cml_in, vagenable1, vagenable2, TestMuxBufferEnable, TestMuxEnable;
  int TestMuxSetting, txgain;
         
  float Foutrx,Fclk,Fouttx, Foutrxb, Foutfb;
  
  //generated inside function in python code..have to be declared in c++
  int Rst_n_async2,Rst_n_async3;

  // Initialize GPIO and ATR
  // GPIO are the general-purpose IO pins on the daughterboard
  // IO_RX_06 must be used for ATR (1 = TX, 0 = RX)
  // ATR is the automatic transmit/receive switching, done in the FPGA
  // FIXME 

  usrp_basic *usrp() { return d_raw_usrp; }

  rfic(usrp_basic_sptr usrp, int which);
  ~rfic();

  //the defination may need to be changed..mask should be a hex value...
  //will rework this
  bool rx_write_io(int, int);

  bool rx_write_oe(int,int);
  bool rx_set_atr_rxval(int);
  bool rx_set_atr_txval(int);
  bool rx_set_atr_mask(int);


  void shutdown();
  void send_reg(int,int);

  //send register wrapper function difinations//
  void set_reg_0();
  void set_reg_1();
  void set_reg_2();
  void set_reg_3();
  void set_reg_4();
  void set_reg_5();
  void set_reg_6();
  void set_reg_7();
  void set_reg_8();
  void set_reg_9();
  void set_reg_10();
  void set_reg_12();
  void set_reg_13();
  void set_reg_14();
  void set_reg_15();
  void set_reg_16();
  void set_reg_17();
  void set_reg_18();
  void set_reg_19();
  void set_reg_20();
  void set_reg_21();
  void set_reg_22();
  void set_reg_23();
  void set_reg_24();
  void set_reg_29();
  void set_reg_30();
  void set_reg_31();
  void set_reg_32();
  void set_reg_33();
  void set_reg_34();
  void set_reg_35();
  void set_reg_36();
  void set_reg_37();
  void set_reg_38();
  void set_reg_39();
  void set_reg_40();
  void set_reg_41();
  void set_reg_42();
  void set_reg_43();
  void set_reg_48();
  void set_reg_49();
  void set_reg_50();
  void set_reg_51();
  void set_reg_52();
  void set_reg_53();
  void set_reg_54();
  void set_reg_55();
  void set_reg_56();
  void set_reg_57();
  void set_reg_58();
  void set_reg_60();
  void set_reg_61();
  void set_reg_62();
  void set_reg_63();
  void set_reg_64();
  void set_reg_65();
  void set_reg_66();
  void set_reg_67();
  void set_reg_68();
  void set_reg_69();
  void set_reg_70();
  void set_reg_71();
  void set_reg_72();
  void set_reg_77();
  void set_reg_78();
  void set_reg_79();
  void set_reg_80();
  void set_reg_81();
  void set_reg_82();
  void set_reg_83();
  void set_reg_84();
  void set_reg_85();
  void set_reg_86();
  void set_reg_87();
  void set_reg_88();
  void set_reg_89();
  void set_reg_90();
  void set_reg_91();
  void set_reg_96();
  void set_reg_97();
  void set_reg_98();
  void set_reg_99();
  void set_reg_104();
  void set_reg_105();
  void set_reg_106();
  void set_reg_107();
  void set_reg_108();
  void set_reg_109();
  void set_reg_110();
  void set_reg_111();
  void set_reg_112();
  void set_reg_113();
  void set_reg_114();
  void set_reg_116();
  void set_reg_117();
  void set_reg_118();
  void set_reg_119();
  void set_reg_120();
  void set_reg_121();
  void set_reg_122();
  void set_reg_123();
  void set_reg_124();
  void set_reg_125();
  void set_reg_126();
  void set_reg_127();
  void set_reg_128();
  void set_reg_133();
  void set_reg_134();
  void set_reg_135();
  void set_reg_136();
  void set_reg_137();
  void set_reg_138();
  void set_reg_139();
  void set_reg_140();
  void set_reg_141();
  void set_reg_142();
  void set_reg_143();
  void set_reg_144();
  void set_reg_145();
  void set_reg_146();
  void set_reg_147();
  void set_reg_152();
  void set_reg_153();
  void set_reg_156();
  void set_reg_157();
  void set_reg_158();
  void set_reg_159();
  void set_reg_160();
  void set_reg_161();
  void set_reg_162();
  void set_reg_163();
  void set_reg_164();
  void set_reg_165();
  void set_reg_166();
  void set_reg_167();
  void set_reg_168();
  void set_reg_169();
  void set_reg_170();
  void set_reg_171();
  void set_reg_172();
  void set_reg_173();
  void set_reg_174();
  void set_reg_175();
  void set_reg_176();
  void set_reg_177();
  void set_reg_178();
  void set_reg_179();
  void set_reg_180();
  void set_reg_181();
  void set_reg_192();
  void set_reg_193();
  void set_reg_194();
  void set_reg_195();
  void set_reg_196();
  void set_reg_197();
  void set_reg_198();
  void set_reg_199();
  void set_reg_200();
  void set_reg_201();
  void set_reg_202();
  void set_reg_203();
  void set_reg_204();
  void set_reg_205();
  void set_reg_206();
  void set_reg_207();
  void set_reg_220();
  void set_reg_222();

  void read_reg_25();
  void read_reg_26();
  void read_reg_27();
  void read_reg_28();
  void read_reg_73();
  void read_reg_74();
  void read_reg_75();
  void read_reg_76();
  void read_reg_100();
  void read_reg_125();
  void read_reg_129();
  void read_reg_130();
  void read_reg_131();
  void read_reg_132();
  void read_reg_208();
  void read_reg_209();
  void read_reg_210();

  char get_reg(int);
  bool set_rx_gain(float);
  bool set_tx_gain(float);
  void set_fb_gain(float);
  void calc_freq_vars(double,double,int []);
  void calc_phase_vars(double,double,double,int[]);
  struct freq_result_t set_rx_freq(double);
  struct freq_result_t set_tx_freq(double);
  bool set_fb_freq(double);

  bool set_rx_phase(int);
  bool set_tx_phase(int);
  
  bool set_fb_phase(int);
  bool set_rx_bw(float);
  bool set_tx_bw(float);
  void set_fb_bw(float);
  void enable_tx_fb();
  void disable_tx_fb();
  int RSSI_fade();
  int RSSI_clip();
  
};

#endif
