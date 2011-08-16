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

#include <gr_udp_msg_source.h>
#include <gr_io_signature.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>

const int max_len = 4096;

using boost::asio::ip::udp;

class udp_reader {
public:
    udp_reader(boost::asio::io_service &io_svc,
               gr_msg_queue_sptr msgq,
               short port);

    void recv_handler(const boost::system::error_code& err,
                      size_t bytes_recvd);

private:
    boost::asio::io_service& io_svc;
    udp::socket sock;
    udp::endpoint sender_ep;
    char data[max_len];
    gr_msg_queue_sptr msgq;
};

udp_reader::udp_reader(boost::asio::io_service &io_svc,
                       gr_msg_queue_sptr msgq,
                       short port)
    : io_svc(io_svc), sock(io_svc, udp::endpoint(udp::v4(), port)),
      msgq(msgq)
{
    sock.async_receive_from(boost::asio::buffer(data, max_len), sender_ep,
        boost::bind(&udp_reader::recv_handler, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void udp_reader::recv_handler(const boost::system::error_code& err,
                              size_t bytes_recvd)
{
    if (!err && bytes_recvd > 0) {
        gr_message_sptr msg = gr_make_message(0, 0, 0, bytes_recvd);
        memcpy(msg->msg(), data, bytes_recvd);
        msgq->handle(msg);
    }

    sock.async_receive_from(boost::asio::buffer(data, max_len), sender_ep,
    boost::bind(&udp_reader::recv_handler, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

gr_udp_msg_source_sptr gr_make_udp_msg_source(gr_msg_queue_sptr msgq, int port)
{
    return gnuradio::get_initial_sptr(new gr_udp_msg_source(msgq, port));
}

gr_udp_msg_source::gr_udp_msg_source(gr_msg_queue_sptr msgq, int port)
    : gr_sync_block("udp_msg_source",
                    gr_make_io_signature(0, 0, 0),
                    gr_make_io_signature(0, 0, 0)),
    d_msgq(msgq), d_port(port)
{
    start();
}

gr_udp_msg_source::~gr_udp_msg_source()
{
    thrd_grp.join_all();
}

bool gr_udp_msg_source::start()
{
    thrd_grp.create_thread(boost::bind(&gr_udp_msg_source::dummy_loop, this));
    return true;
}

void gr_udp_msg_source::dummy_loop()
{
    try {
        boost::asio::io_service io_srv;
        udp_reader s(io_srv, d_msgq, d_port);
        io_srv.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int gr_udp_msg_source::work(int noutput_items,
                            gr_vector_const_void_star &input_items,
                            gr_vector_void_star &output_items)
{
    return -1;
;}
