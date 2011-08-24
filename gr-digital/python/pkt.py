#
# Copyright 2005-2011 Free Software Foundation, Inc.
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
import gnuradio.gr.gr_threading as threading
import gnuradio.digital
import gnuradio.digital.packet_utils
import struct

class dummy_thread(threading.Thread):
    def set_val(self, access_code=None,
                msgq_in=None, msgq_out=None,
                use_whitener_offset=False):

        self._msgq_in = msgq_in
        self._msgq_out = msgq_out
        self._use_whitener_offset = use_whitener_offset
        self._whitener_offset = 0

        if access_code is None:
            access_code = gnuradio.digital.packet_utils.default_access_code
        if not gnuradio.digital.packet_utils.is_1_0_string(access_code):
            raise ValueError, "Invalid access_code %r. Must be string of 1's and 0's" % (access_code,)
        self._access_code = access_code

    def send_pkt(self, payload='', eof=False):
        if eof:
            msg = gr.message(1)
        else:
            if self._use_whitener_offset is True:
                self._whitener_offset = (self._whitener_offset + 1) % 16

            pkt = gnuradio.digital.packet_utils.make_packet(payload,
                                           0,
                                           0,
                                           self._access_code,
                                           0,
                                           self._whitener_offset)

            msg = gr.message_from_string(pkt)
            self._msgq_out.insert_tail(msg)

    def run(self):
        while 1:
            msg = self._msgq_in.delete_head()
            self.send_pkt(msg.to_string())

class mod_pkts(gr.hier_block2):
    def __init__(self, access_code=None,
                 msgq_in=None, msgq_out=None,
                 use_whitener_offset=False):

	gr.hier_block2.__init__(self, "mod_pkts",
				gr.io_signature(0, 0, 0),
				gr.io_signature(0, 0, 0))
        self.connect(self)

        t = dummy_thread()
        t.set_val(access_code, msgq_in, msgq_out, use_whitener_offset)
        t.start()

class demod_pkts(gr.hier_block2):
    def __init__(self, access_code=None, msgq_out=None, threshold=-1):

	gr.hier_block2.__init__(self, "demod_pkts",
				gr.io_signature(1, 1, 1),
				gr.io_signature(0, 0, 0))

        if access_code is None:
            access_code = gnuradio.digital.packet_utils.default_access_code
        if not gnuradio.digital.packet_utils.is_1_0_string(access_code):
            raise ValueError, "Invalid access_code %r. Must be string of 1's and 0's" % (access_code,)
        self._access_code = access_code

        if threshold == -1:
            threshold = 12              # FIXME raise exception

        self._rcvd_pktq = gr.msg_queue()
        self.correlator = gnuradio.digital.correlate_access_code_bb(access_code, threshold)

        self.framer_sink = gr.framer_sink_1(self._rcvd_pktq)
        self.connect(self, self.correlator, self.framer_sink)
        
        self._watcher = _queue_watcher_thread(self._rcvd_pktq, msgq_out)

class _queue_watcher_thread(threading.Thread):
    def __init__(self, rcvd_pktq, msgq_out):
        threading.Thread.__init__(self)
        self.setDaemon(1)
        self.rcvd_pktq = rcvd_pktq
        self.msgq_out = msgq_out
        self.keep_running = True
        self.start()

    def run(self):
        while self.keep_running:
            msg = self.rcvd_pktq.delete_head()
            ok, payload = gnuradio.digital.packet_utils.unmake_packet(msg.to_string(), int(msg.arg1()))
            (pktno,) = struct.unpack('!H', payload[0:2])
            msg = gr.message_from_string(payload)
            self.msgq_out.handle(msg)
