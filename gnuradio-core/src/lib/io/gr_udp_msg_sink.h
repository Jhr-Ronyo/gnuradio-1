/* -*- c++ -*- */
/*
 * Copyright 2005 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GR_UDP_MSG_SINK_H
#define INCLUDED_GR_UDP_MSG_SINK_H

#include <gr_core_api.h>
#include <gr_sync_block.h>
#include <gr_message.h>
#include <gr_msg_queue.h>
#include <gruel/thread.h>
#include <string>

class gr_udp_msg_sink;
typedef boost::shared_ptr<gr_udp_msg_sink> gr_udp_msg_sink_sptr;

GR_CORE_API
gr_udp_msg_sink_sptr gr_make_udp_msg_sink(gr_msg_queue_sptr msgq, const std::string host, const std::string port);

class GR_CORE_API gr_udp_msg_sink : public gr_sync_block {
private:
    gr_msg_queue_sptr d_msgq;
    const std::string d_host;
    const std::string d_port;
    bool d_running;
    gruel::thread d_thread;

    friend GR_CORE_API
    gr_udp_msg_sink_sptr gr_make_udp_msg_sink(gr_msg_queue_sptr msgq, const std::string host, const std::string port);

protected:
    gr_udp_msg_sink(gr_msg_queue_sptr msgq, const std::string host, const std::string port);

public:
    ~gr_udp_msg_sink();

    bool start();
    bool stop();

    int work(int noutput_items,
             gr_vector_const_void_star &input_items,
             gr_vector_void_star &output_items);
};

#endif /* INCLUDED_GR_UDP_MSG_SINK_H */
