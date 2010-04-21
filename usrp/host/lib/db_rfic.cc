#include "db_rfic_core.h"
#include <iostream>

// Forward declaration
rfic_sptr _get_or_make_rfic(usrp_basic_sptr, int);

db_rfic_base::db_rfic_base(usrp_basic_sptr usrp, int which)
  : db_base(usrp, which)
{
 /*
  * Abstract base class for all rfic boards.
  * 
  * Derive board specific subclasses from db_rfic_base_{tx,rx}
  *
  * @param usrp: instance of usrp.source_c
  * @param which: which side: 0 or 1 corresponding to side A or B respectively
  * @type which: int
  */
  
  d_rfic = _get_or_make_rfic(usrp, which);
}

db_rfic_base::~db_rfic_base()
{

}


bool
db_rfic_base::is_quadrature()
{
 /*
  * Return True if this board requires both I & Q analog channels.
  *
  * This bit of info is useful when setting up the USRP Rx mux register.
  */
  return true;
}


double
db_rfic_base::freq_min()
{
  return 2.5e6;
}


double
db_rfic_base::freq_max()
{
  return 1e8;
}


void
db_rfic_base::shutdown_common()
{
  // If the usrp_basic in the rfic is the same as the usrp_basic
  // in the daughterboard, shutdown the rfic now (when only one of Tx
  // and Rx is open, this is always true).

  if (d_rfic->usrp() == usrp()) {
    //std::cerr << "db_rfic_base::shutdown_common: same -> shutting down\n";
    d_rfic->shutdown();
  }
  else {
    //std::cerr << "db_rfic_base::shutdown_common: different -> ignoring\n";
  }
}

/******************************************************************************/

db_rfic_tx::db_rfic_tx(usrp_basic_sptr usrp, int which)
  : db_rfic_base(usrp, which)
{
	
  //select_tx_antenna(abc);
  d_rfic->set_reg_0();
  d_rfic->set_reg_1();
  d_rfic->set_reg_2();
  d_rfic->set_reg_3();
  d_rfic->set_reg_4();
  d_rfic->set_reg_5();
  d_rfic->set_reg_6();
  d_rfic->set_reg_7();
  d_rfic->set_reg_8();
  d_rfic->set_reg_9();
  d_rfic->set_reg_10();
  d_rfic->set_reg_12();
  d_rfic->set_reg_13();
  d_rfic->set_reg_14();
  d_rfic->set_reg_15();
  d_rfic->set_reg_16();
  d_rfic->set_reg_17();
  d_rfic->set_reg_18();
  d_rfic->set_reg_19();
  d_rfic->set_reg_20();
  d_rfic->set_reg_21();
  d_rfic->set_reg_22();
  d_rfic->set_reg_23();
  d_rfic->set_reg_24();
  d_rfic->set_reg_29();
  d_rfic->set_reg_30();
  d_rfic->set_reg_31();
  d_rfic->set_reg_32();
  d_rfic->set_reg_33();
  d_rfic->set_reg_34();
  d_rfic->set_reg_35();
  d_rfic->set_reg_36();
  d_rfic->set_reg_37();
  d_rfic->set_reg_38();
  d_rfic->set_reg_39();
  d_rfic->set_reg_40();
  d_rfic->set_reg_41();
  d_rfic->set_reg_42();
  d_rfic->set_reg_43();
  d_rfic->set_reg_156();
  d_rfic->set_reg_157();
  d_rfic->set_reg_158();
  d_rfic->set_reg_159();
  d_rfic->set_reg_160();
  d_rfic->set_reg_161();
  d_rfic->set_reg_162();
  d_rfic->set_reg_163();
  d_rfic->set_reg_164();
  d_rfic->set_reg_165();
  d_rfic->set_reg_166();
  d_rfic->set_reg_167();
  d_rfic->set_reg_168();
  d_rfic->set_reg_169();
  d_rfic->set_reg_170();
  d_rfic->set_reg_171();
  d_rfic->set_reg_172();
  d_rfic->set_reg_173();
  d_rfic->set_reg_174();
  d_rfic->set_reg_175();
  d_rfic->set_reg_176();
  d_rfic->set_reg_177();
  d_rfic->set_reg_178();
  d_rfic->set_reg_179();
  d_rfic->set_reg_180();
  d_rfic->set_reg_181();
    
  // Get digital block out of digital reset state
  d_rfic->Rst_n_async = 1;
  d_rfic->set_reg_24();
  
  // Turn on forward baseband reference section
  d_rfic->tx_bb_en = 1;
  // FIXME
  //d_rfic->set_reg_156();
  
  // Unroutes the Cartesian error signal through the BB Correction feedback
  // FIXME
  d_rfic->tx_bb_fdbk_cart_err_en = 0;
  
  // Routes the Cartesian feedback signal through the BB Correction feedback
  // FIXME
  d_rfic->tx_bb_fdbk_cart_fb_en = 1;
  d_rfic->set_reg_156();
  
  // Turn on baseband feedback section
  // FIXME
  //d_rfic->tx_bb_fdbk_en = 3;
  //d_rfic->set_reg_157();
  
  // Turn on forward RF transmit path
  d_rfic->RFForwardPathEnable_toMUX = 1;
  d_rfic->set_reg_175();
  
  // Turn on Cartesian FB path switch to forward summer
  d_rfic->CartesianFBpathSwitchtoforwardSummer = 1;
  d_rfic->set_reg_168();
  
  // Turn on Cartesian zero
  d_rfic->CartesianFBpathZeroEnable = 1;
  d_rfic->set_reg_170();
  
  // Select TX output path, default tx1
  // FIXME
  d_rfic->tx_output_channel_sel = 2;
  //d_rfic->tx_output_channel_sel = 1;
  d_rfic->set_reg_172();
  
  // Set TX Channel 1 Gain
  // The gain control on TX channel 1 is controlled by this DAC
  // The maximum voltage is 2.2 volts, which corresponds to 2750
  // This controls about 35 dB of gain ONLY ON TX 1
  d_rfic->usrp()->write_aux_dac(d_rfic->d_which, 3, 2750);
  

  // POR On. This enables the clock that drives the digital block (which
  // provides the tap selection process). It must be enabled to generate an
  // output. See Byp_fine, address 10, bit 6
  d_rfic->Clk_driver_en = 1;
  
  // POR On
  d_rfic->qu_reg_en = 1;
  
  // POR On
  d_rfic->qq_reg_en = 1;
  
  // POR Off
  d_rfic->win_rst = 0;
  
  // POR On
  d_rfic->fineEn = 0;
  
  // POR Off
  d_rfic->fineEnb = 1;
  
  // POR On
  //d_rfic->rsffEn = 0;
  
  // POR On
  d_rfic->dl_en = 1;
  
  // POR On
  d_rfic->cp_en = 1;
  
  d_rfic->set_reg_20();
  d_rfic->set_reg_21();
  }
  
db_rfic_tx::~db_rfic_tx()
{
  // print "rfic_base_tx.__del__"
  // Power down
  
  // Turn off output channel
  d_rfic->tx_output_channel_sel = 0;
  d_rfic->set_reg_172();
  
  // Turn off forward RF transmit path
  d_rfic->RFForwardPathEnable_toMUX = 0;
  d_rfic->set_reg_17();
  
  // Turn off forward baseband reference section
  d_rfic->tx_bb_en = 0;
  d_rfic->set_reg_156();
  
  // Unroutes the Cartesian error signal through the BB Correction feedback
  // FIXME
  d_rfic->tx_bb_fdbk_cart_err_en = 0;
  
  // Unroutes the Cartesian feedback signal through the BB Correction feedback
  d_rfic->tx_bb_fdbk_cart_fb_en = 0;
  d_rfic->set_reg_156();
  
  // Turn off Cartesian FB path switch to forward summer
  d_rfic->CartesianFBpathSwitchtoforwardSummer = 0;
  d_rfic->set_reg_168();
  
  // Turn off Cartesian zero
  d_rfic->CartesianFBpathZeroEnable = 0;
  d_rfic->set_reg_170();
  
  // Turn off baseband feedback section
  // FIXME
  //d_rfic->tx_bb_fdbk_en = 0;
  //d_rfic->set_reg_157()
  
  // POR Off. This enables the clock that drives the digital block (which
  // provides the tap selection process). It must be enabled to generate an
  // output. See Byp_fine, address 10, bit 6
  d_rfic->Clk_driver_en = 0;
  
  // POR Off
  d_rfic->qu_reg_en = 0;
  
  // POR Off
  d_rfic->qq_reg_en = 0;
  
  // POR Off
  d_rfic->win_rst = 0;
  
  // POR Off
  d_rfic->fineEn = 0;
  
  // POR Off
  d_rfic->fineEnb = 0;
  
  // POR Off
  //d_rfic->rsffEn = 0;
  
  // POR Off
  d_rfic->dl_en = 0;
  
  // POR Off
  d_rfic->cp_en = 0;
  
  d_rfic->set_reg_20();
  d_rfic->set_reg_21();
  
  // Put digital block in digital reset state
  d_rfic->Rst_n_async = 0;
  d_rfic->set_reg_24();
  shutdown();
}

  
bool
db_rfic_tx::select_tx_antenna(std::string which_antenna)
{
  //Specify which antenna port to use for transmission.
  //@param which_antenna: either 'tx1', 'tx2' or 'tx3'

  if (which_antenna == "tx1") {
    d_rfic->tx_output_channel_sel = 1;
    d_rfic->set_reg_172();
  }
  else if (which_antenna == "tx2") {
    d_rfic->tx_output_channel_sel = 2;
    d_rfic->set_reg_172();
  }
  else if (which_antenna  == "tx3") {
    d_rfic->tx_output_channel_sel = 4;
    d_rfic->set_reg_172();
  }
  else{
    std::cout << "which_antenna must be either tx1/0 , tx2/1 or tx3/2"
              << std::endl;

    return false;
  }

  return true;
}
    
    
bool
db_rfic_tx::select_tx_antenna(int which_antenna)
{
  //Specify which antenna port to use for transmission.
  //@param which_antenna: either 'tx1', 'tx2' or 'tx3'

  if (which_antenna == 0) {
    d_rfic->tx_output_channel_sel = 1;
    d_rfic->set_reg_172();
  }
  else if (which_antenna == 1) {
    d_rfic->tx_output_channel_sel = 2;
    d_rfic->set_reg_172();
  }
  else if (which_antenna  == 2) {
    d_rfic->tx_output_channel_sel = 4;
    d_rfic->set_reg_172();
  }
  else {
    std::cout << "which_antenna must be either tx1/0 , tx2/1 or tx3/2"
              << std::endl;

    return false;
  }

  return true;
}


void
db_rfic_tx::shutdown()
{
  if (!d_is_shutdown) {
    d_is_shutdown = true;
    shutdown_common();
  }
}


float
db_rfic_tx::gain_min()
{
  return 0.0;
}


float
db_rfic_tx::gain_max()
{
  return 45.0;
}


bool
db_rfic_tx::set_gain(float gain)
{
  return d_rfic->set_tx_gain(gain);
}


struct freq_result_t
db_rfic_tx::set_freq(double target_frequency)
{
  return d_rfic->set_tx_freq(target_frequency);
}


bool
db_rfic_tx::set_phase(int phase)
{
  return d_rfic->set_tx_phase(phase);
}


bool
db_rfic_tx::set_bw(float bw)
{
  return d_rfic->set_tx_bw(bw);
}


bool
db_rfic_tx::spectrum_inverted()
{
  return true;
}


float
db_rfic_tx::gain_db_per_step()
{
  return d_rfic->usrp()->pga_db_per_step();
}


db_rfic_rx::db_rfic_rx(usrp_basic_sptr usrp, int which)
  : db_rfic_base(usrp, which)
{
  std::string abc = "MIX5";
  this->select_rx_antenna(abc);
  d_rfic->set_reg_48();
  d_rfic->set_reg_49();
  d_rfic->set_reg_50();
  d_rfic->set_reg_51();
  d_rfic->set_reg_52();
  d_rfic->set_reg_53();
  d_rfic->set_reg_54();
  d_rfic->set_reg_55();
  d_rfic->set_reg_56();
  d_rfic->set_reg_57();
  d_rfic->set_reg_58();
  d_rfic->set_reg_60();
  d_rfic->set_reg_61();
  d_rfic->set_reg_62();
  d_rfic->set_reg_63();
  d_rfic->set_reg_64();
  d_rfic->set_reg_65();
  d_rfic->set_reg_66();
  d_rfic->set_reg_67();
  d_rfic->set_reg_68();
  d_rfic->set_reg_69();
  d_rfic->set_reg_70();
  d_rfic->set_reg_71();
  d_rfic->set_reg_72();
  d_rfic->set_reg_77();
  d_rfic->set_reg_78();
  d_rfic->set_reg_79();
  d_rfic->set_reg_80();
  d_rfic->set_reg_81();
  d_rfic->set_reg_82();
  d_rfic->set_reg_83();
  d_rfic->set_reg_84();
  d_rfic->set_reg_85();
  d_rfic->set_reg_86();
  d_rfic->set_reg_87();
  d_rfic->set_reg_88();
  d_rfic->set_reg_89();
  d_rfic->set_reg_90();
  d_rfic->set_reg_91();
  d_rfic->set_reg_96();
  d_rfic->set_reg_97();
  d_rfic->set_reg_98();
  d_rfic->set_reg_99();
  d_rfic->set_reg_104();
  d_rfic->set_reg_105();
  d_rfic->set_reg_106();
  d_rfic->set_reg_107();
  d_rfic->set_reg_108();
  d_rfic->set_reg_109();
  d_rfic->set_reg_110();
  d_rfic->set_reg_111();
  d_rfic->set_reg_112();
  d_rfic->set_reg_113();
  d_rfic->set_reg_114();
  d_rfic->set_reg_116();
  d_rfic->set_reg_117();
  d_rfic->set_reg_118();
  d_rfic->set_reg_119();
  d_rfic->set_reg_120();
  d_rfic->set_reg_121();
  d_rfic->set_reg_122();
  d_rfic->set_reg_123();
  d_rfic->set_reg_124();
  d_rfic->set_reg_125();
  d_rfic->set_reg_126();
  d_rfic->set_reg_127();
  d_rfic->set_reg_128();
  d_rfic->set_reg_133();
  d_rfic->set_reg_134();
  d_rfic->set_reg_135();
  d_rfic->set_reg_136();
  d_rfic->set_reg_137();
  d_rfic->set_reg_138();
  d_rfic->set_reg_139();
  d_rfic->set_reg_140();
  d_rfic->set_reg_141();
  d_rfic->set_reg_142();
  d_rfic->set_reg_143();
  d_rfic->set_reg_144();
  d_rfic->set_reg_145();
  d_rfic->set_reg_146();
  d_rfic->set_reg_147();
  d_rfic->set_reg_152();
  d_rfic->set_reg_153();
  d_rfic->set_reg_192();
  d_rfic->set_reg_193();
  d_rfic->set_reg_194();
  d_rfic->set_reg_195();
  d_rfic->set_reg_196();
  d_rfic->set_reg_197();
  d_rfic->set_reg_198();
  d_rfic->set_reg_199();
  d_rfic->set_reg_200();
  d_rfic->set_reg_201();
  d_rfic->set_reg_202();
  d_rfic->set_reg_203();
  d_rfic->set_reg_204();
  d_rfic->set_reg_205();
  d_rfic->set_reg_206();
  d_rfic->set_reg_207();
  
  // Get digital block out of digital reset state
  d_rfic->Rst_n_async_3 = 1;
  d_rfic->set_reg_128();
  
  // Set RX LNA port to LNA1 (SGO non-chopping mixer)
  // FIXME
  //d_rfic->rx_lna = 1;
  d_rfic->rx_lna = 5;
  
  // Set LNA bias
  d_rfic->rx_lnab = 1;
  
  // Enable LO clock to mixer
  d_rfic->rx_rxchen = 1;
  
  d_rfic->set_reg_205();
  
  // Enable RX Filter
  d_rfic->rx_fen = 1;
  
  // Enable baseband filter chopper clock
  d_rfic->rx_chcken = 1;
  
  // Enable chopper clock to all mixers
  d_rfic->rx_cen = 7;
  
  // Set chopper divide setting
  // FIXME
  //d_rfic->rx_chck = 0
  d_rfic->rx_chck = 1;
  
  d_rfic->set_reg_195();
  
  // Enable filter output
  d_rfic->rx_foe = 1;
  
  // Enable on-channel detector
  //d_rfic->rx_onchen = 1
  
  // Enable off-channel detector
  //d_rfic->rx_offchen = 1
  
  
  d_rfic->set_reg_196();
  
  // Set BQ filter Q to 1.33
  d_rfic->rx_qs = 2;
  
  // Set BQ resistor value to 1.4 kohms
  d_rfic->rx_rq = 0;
  
  d_rfic->set_reg_198();
  
  // Set VGA resistor value to 2.5 kohms
  d_rfic->rx_rv = 0;
  
  // Set PMA Rf resistor to 5 kohms
  d_rfic->rx_rfp = 00;
  
  d_rfic->set_reg_199();
  
  // Set compensation control
  d_rfic->rx_cc_2to0 = 0;
  
  d_rfic->set_reg_203();
  
  // Enable DCOC DAC
  d_rfic->rx_den = 1;
  
  d_rfic->set_reg_192();
  
  // Enable DCOC comparator
  d_rfic->rx_cmpen = 1;
  
  d_rfic->set_reg_193();
  
  // RC Tune enable
  // FIXME
  //d_rfic->rx_ten = 1;
  d_rfic->rx_ten = 0;
  
  // RC Tune ramp circuit enable
  // FIXME
  //d_rfic->rx_ren = 1;
  d_rfic->rx_ren = 0;
  
  // Select DCOC/RC Tune divider, divide by 8
  d_rfic->rx_dv = 3;
  
  d_rfic->set_reg_194();
  
  // Enable DCOC
  d_rfic->rx_dcoc = 1;
  
  d_rfic->set_reg_193();
  
  // POR On. This enables the clock that drives the digital block (which
  // provides the tap selection process). It must be enabled to generate an 
  // output. See Byp_fine, address 10, bit 6
  d_rfic->Clk_driver_en_3 = 1;
  
  // POR On
  d_rfic->qu_reg_en_3 = 1;
  
  // POR On
  d_rfic->qq_reg_en_3 = 1;
  // POR Off
  d_rfic->win_rst_3 = 0;
  
  // POR On
  d_rfic->fineEn_3 = 0 ;
  
  // POR Off
  d_rfic->fineEnb_3 = 1;
  
  // POR Off
  //d_rfic->rsffEn_3 = 0;
  
  // POR On
  d_rfic->dl_en_3 = 1;
  
  // POR On
  d_rfic->cp_en_3 = 1;
  
  d_rfic->set_reg_124();
  d_rfic->set_reg_125();
}
  
db_rfic_rx::~db_rfic_rx()
{
  // std::cout << "inside db_rfic_rx destructor "<< std::endl;
  // Power down
  
  // Set RX LNA path (off)
  d_rfic->rx_lna = 0;
  
  // Disable LO clock to mixer
  d_rfic->rx_rxchen = 0;
  
  d_rfic->set_reg_205();
  // Disable RX Filter
  d_rfic->rx_fen = 0;
  
  // Disable baseband filter chipper clock
  d_rfic->rx_chcken = 0;
  
  // Disable chopper clock to all mixers
  d_rfic->rx_cen = 0;
  d_rfic->set_reg_195();
  
  // Disable filter output
  d_rfic->rx_foe = 0;
  
  // Disable on-channel detector
  d_rfic->rx_onchen = 0;
  
  // Disable off-channel detector
  d_rfic->rx_offchen = 0;
  
  d_rfic->set_reg_196();
  
  // Disable DCOC DAC
  d_rfic->rx_den = 0;
  
  d_rfic->set_reg_192();
  
  // Disable DCOC comparator
  d_rfic->rx_cmpen = 0;
  
  d_rfic->set_reg_193();
  
  // RC Tune disable
  d_rfic->rx_ten = 0;
  
  // RC Tune ramp circuit disable
  d_rfic->rx_ren = 0;
  
  d_rfic->set_reg_194();
  
  // Disable DCOC
  d_rfic->rx_dcoc = 0;
  
  d_rfic->set_reg_193();
  
  // POR Off. This enables the clock that drives the digital block (which
  // provides the tap selection process). It must be enabled to generate an
  // output. See Byp_fine, address 10, bit 6
  d_rfic->Clk_driver_en_3 = 0;
  
  // POR Off
  d_rfic->qu_reg_en_3 = 0;
  
  // POR Off
  d_rfic->qq_reg_en_3 = 0;
  
  // POR Off
  d_rfic->win_rst_3 = 0;
  
  // POR Off
  d_rfic->fineEn_3 = 0;
  
  // POR Off
  d_rfic->fineEnb_3 = 0;
  
  // POR Off
  //d_rfic->rsffEn_3 = 0;
  
  // POR Off
  d_rfic->dl_en_3 = 0;
  
  // POR Off
  d_rfic->cp_en_3 = 0;
  
  d_rfic->set_reg_124();
  d_rfic->set_reg_125();
  
  // Put digital block into digital reset state
  d_rfic->Rst_n_async_3 = 0;
  d_rfic->set_reg_58();
  shutdown();
}
  
void
db_rfic_rx::shutdown()
{
  if (!d_is_shutdown) {
    d_is_shutdown = true;
    shutdown_common();
  }
}

bool
db_rfic_rx::select_rx_antenna(std::string which_antenna) {

  //Specif(y which antenna port to use for transmission.
  //@param which_antenna: either  LNA1/0, LNA2/1, LNA3/2, LNA4/3 or MIX5/4

  which_antenna = "MIX5";
  if( which_antenna == "LNA1") {
    d_rfic->rx_lna = 1;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == "LNA2") {
    d_rfic->rx_lna = 2;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == "LNA3") {
    d_rfic->rx_lna = 3;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == "LNA4") {
    d_rfic->rx_lna = 4;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == "MIX5") {
    d_rfic->rx_lna = 5;
    d_rfic->set_reg_205();
  }
  else {
    std::cout << "Antenna must be LNA1, LNA2, LNA3, LNA4 or MIX5" << std::endl;
    return false;
  }
  return true;
}
  
bool
db_rfic_rx::select_rx_antenna(int which_antenna)
{
  //Specif(y which antenna port to use for transmission.
  //@param which_antenna: either 'rx1', 'rx2' or 'rx3'

  if( which_antenna == 0) {
    d_rfic->rx_lna = 1;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == 1) {
    d_rfic->rx_lna = 2;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == 2) {
    d_rfic->rx_lna = 3;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == 3) {
    d_rfic->rx_lna = 4;
    d_rfic->set_reg_205();
  }
  else if( which_antenna == 4) {
    d_rfic->rx_lna = 5;
    d_rfic->set_reg_205();
  }
  else{
    std::cout << "Antenna must be LNA1, LNA2, LNA3, LNA4 or MIX5" << std::endl;
    return false;
  }
  return true;
}

  
float
db_rfic_rx::gain_min()
{
  return 0.0;
}


float
db_rfic_rx::gain_max()
{
  return 40.0;
}
  
  
bool
db_rfic_rx::set_gain(float gain)
{
  return d_rfic->set_rx_gain(gain);
}


struct freq_result_t
db_rfic_rx::set_freq(double target_frequency)
{
  return d_rfic->set_rx_freq(target_frequency);
}


bool
db_rfic_rx::set_phase(int phase)
{
  return d_rfic->set_rx_phase(phase);
}


bool
db_rfic_rx::set_bw(float bw)
{
  return d_rfic->set_rx_bw(bw);
}


void 
db_rfic_rx::enable_fb()
{
  // Enable transmitter feedback to receiver for DC offset, etc.
  d_rfic->enable_tx_fb();
}


void 
db_rfic_rx::disable_tx_fb()
{
  // Disable transmitter feedback to receiver
  return d_rfic->disable_tx_fb();
}


float 
db_rfic_rx::fb_gain_min() {
  return 0.0;
}


float 
db_rfic_rx::fb_gain_max() {
  return 40.0;
}


void 
db_rfic_rx::set_fb_gain(float gain) {
  // Set feedback gain, in dB
  d_rfic->set_fb_gain(gain);
}


bool
db_rfic_rx::set_fb_freq(double target_freq) {
  // Set feedback frequency, in Hz
  return d_rfic->set_fb_freq(target_freq);
}


bool 
db_rfic_rx::set_fb_phase(int phase) {
  // Set feedback phase offset, in degrees
  return d_rfic->set_fb_phase(phase);
}


void 
db_rfic_rx::set_fb_bw(float bw) {
  // Set feedback bandwidth, in Hz
  d_rfic->set_fb_bw(bw);
}


int 
db_rfic_rx::RSSI_fade() {
  // Get received signal strength indicators
  // Returns fade
  // Fade is proportional to how often the signal is low
  return d_rfic->RSSI_fade();
}


int 
db_rfic_rx::RSSI_clip() {
  // Get received signal strength indicators
  // Returns clip
  // Clip is proportional to how often the signal is high
  return d_rfic->RSSI_clip();
}


float
db_rfic_rx::gain_db_per_step()
{
  return d_rfic->usrp()->pga_db_per_step();
}
