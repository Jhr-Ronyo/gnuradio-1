#
# Copyright 2010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr
from gnuradio import eng_notation
from gnuradio import digital
from gnuradio.digital import pkt
from gnuradio import uhd

import copy
import sys

class transmit_path(gr.hier_block2):
    def __init__(self, modulator_class, options):
        '''
        See below for what options should hold
        '''
   	gr.hier_block2.__init__(self, "transmit_path",
				gr.io_signature(0, 0, 0),                    # Input signature
				#gr.io_signature(1, 1, gr.sizeof_gr_complex)) # Output signature
       				gr.io_signature(0, 0, 0))                    # Output signature
 
        options = copy.copy(options)    # make a copy so we can destructively modify

        self._verbose            = options.verbose
        self._tx_amplitude       = options.tx_amplitude    # digital amplitude sent to USRP
        self._sample_rate        = options.sample_rate     # desired bit rate
        self._gain               = options.gain            # desired rf gain
        self._freq               = options.freq            # desired transmit frequency
        self._samples_per_symbol = options.samples_per_symbol  # desired samples/baud

        self._modulator_class = modulator_class         # the modulator_class we are using

        # Get mod_kwargs
        mod_kwargs = self._modulator_class.extract_kwargs_from_options(options)
    
        # transmitter
	modulator = self._modulator_class(**mod_kwargs)
        print modulator
        self.packet_transmitter = pkt.mod_pkts(modulator,
                                               access_code=None,
                                               msgq_limit=8,
                                               pad_for_usrp=False)

        self.amp = gr.multiply_const_cc(1)
        self.set_tx_amplitude(self._tx_amplitude)

        self.setup_uhd_sink(options)

        # Display some information about the setup
        if self._verbose:
            self._print_verbage()

        # Connect components in the flowgraph
        self.connect(self.packet_transmitter, self.amp, self.u)

    def set_tx_amplitude(self, ampl):
        """
        Sets the transmit amplitude sent to the USRP in volts
        @param: ampl 0 <= ampl < 1.
        """
        self._tx_amplitude = max(0.0, min(ampl, 1))
        self.amp.set_k(self._tx_amplitude)
        
    def send_pkt(self, payload='', eof=False, fill=False):
        """
        Calls the transmitter method to send a packet
        """
        return self.packet_transmitter.send_pkt(payload, eof, fill)
        
    def sample_rate(self):
        return self._sample_rate

    def samples_per_symbol(self):
        return self._samples_per_symbol

    def add_options(normal, expert):
        """
        Adds transmitter-specific options to the Options Parser
        """
        if not normal.has_option('--sample_rate'):
            normal.add_option("-r", "--sample_rate", type="eng_float", default=100e3,
                              help="specify sample_rate [default=%default].")
        normal.add_option("", "--tx-amplitude", type="eng_float", default=0.250, metavar="AMPL",
                          help="set transmitter digital amplitude: 0 <= AMPL < 1 [default=%default]")
        normal.add_option("-f", "--freq", type="eng_float", default=0,
                          help="specify transmit frequency [default=%default]")
        normal.add_option("-g", "--gain", type="eng_float", default=0,
                          help="specify transmit gain [default=%default]")
        normal.add_option("-v", "--verbose", action="store_true", default=False)
        expert.add_option("-S", "--samples-per-symbol", type="float", default=None,
                          help="set samples/symbol [default=%default]")
        expert.add_option("", "--log", action="store_true", default=False,
                          help="Log all parts of flow graph to file (CAUTION: lots of data)")

    # Make a static method to call before instantiation
    add_options = staticmethod(add_options)

    def _print_verbage(self):
        """
        Prints information about the transmit path
        """
        print "Tx amplitude     %s"    % (self._tx_amplitude)
        print "modulation:      %s"    % (self._modulator_class.__name__)
        print "sample_rate:     %sb/s" % (eng_notation.num_to_str(self._sample_rate))
        print "samples/symbol:  %.4f"  % (self._samples_per_symbol)
        print "center freq:     %sHz"  % (self._freq)
        print "gain:            %sdB"  % (self._gain)

    def setup_uhd_sink(self, options):
        """
        Creates a UHD sink
        """
        self.u = uhd.usrp_sink(device_addr="",
                               io_type=uhd.io_type.COMPLEX_FLOAT32,
                               num_channels=1)
            
        self.u.set_samp_rate(self._sample_rate)
        self.u.set_center_freq(self._freq)
        self.u.set_gain(self._gain)
