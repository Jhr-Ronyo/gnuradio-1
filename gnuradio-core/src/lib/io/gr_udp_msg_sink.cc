/* -*- c++ -*- */
/*
 * Copyright 2011 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_udp_msg_sink.h>
#include <gr_msg_queue.h>
#include <gr_io_signature.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

void msgq_reader(gr_msg_queue_sptr msgq, const std::string host, const std::string port)
{
    gr_message_sptr msg;
    boost::asio::io_service io_svc;

    udp::socket sock(io_svc, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(io_svc);
    udp::resolver::query query(udp::v4(), host, port);
    udp::resolver::iterator iter = resolver.resolve(query);

    while (1) {
        msg = msgq->delete_head();
        sock.send_to(boost::asio::buffer(msg->msg(), msg->length()), *iter);
    }
}

gr_udp_msg_sink_sptr gr_make_udp_msg_sink(gr_msg_queue_sptr msgq,
                                          const std::string host,
                                          const std::string port)
{
    return gnuradio::get_initial_sptr(new gr_udp_msg_sink(msgq, host, port));
}

gr_udp_msg_sink::gr_udp_msg_sink(gr_msg_queue_sptr msgq,
                                 const std::string host,
                                 const std::string port)
    : gr_sync_block("udp_msg_sink",
                    gr_make_io_signature(0, 0, 0),
                    gr_make_io_signature(0, 0, 0)),
    d_msgq(msgq), d_host(host), d_port(port), d_running(false)
{
}

gr_udp_msg_sink::~gr_udp_msg_sink()
{
    stop();
    d_thread.join();
}

bool gr_udp_msg_sink::start()
{
    if (d_running)
        return false;

    d_thread = boost::thread(msgq_reader, d_msgq, d_host, d_port);

    return true;
}

bool gr_udp_msg_sink::stop()
{
    if (!d_running)
        return false; 

    d_thread.interrupt();

    return true;
}

int gr_udp_msg_sink::work(int noutput_items,
                          gr_vector_const_void_star &input_items,
                          gr_vector_void_star &output_items)
{
    return -1;
}
