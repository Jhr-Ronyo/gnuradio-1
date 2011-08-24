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

#include <gr_udp_msg_sink.h>
#include <gruel/thread.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

class gr_udp_msg_sink_impl : public gr_udp_msg_sink {
public:
    gr_udp_msg_sink_impl(const std::string host,
                         const std::string port,
                         gr_msg_queue_sptr msgq)
        : _host(host), _port(port), _msgq(msgq), _running(false)
    {
        _msg_thread =
            gruel::thread(boost::bind(&gr_udp_msg_sink_impl::run_loop, this));
    }

    ~gr_udp_msg_sink_impl()
    {
        _running = false;
        _msg_thread.join();
    }

    void run_loop()
    {
        gr_message_sptr msg;
        boost::asio::io_service io_svc;

        udp::socket sock(io_svc, udp::endpoint(udp::v4(), 0));
        udp::resolver resolver(io_svc);
        udp::resolver::query query(udp::v4(), _host, _port);
        udp::resolver::iterator iter = resolver.resolve(query);

        _running = true;
        while (_running) {
            msg = _msgq->delete_head();
            sock.send_to(boost::asio::buffer(msg->msg(), msg->length()), *iter);
        }
    }

protected:
    const std::string _host;
    const std::string _port;
    gr_msg_queue_sptr _msgq;
    bool _running;
    gruel::thread _msg_thread;
};

gr_udp_msg_sink_sptr gr_make_udp_msg_sink(const std::string host,
                                          const std::string port, 
                                          gr_msg_queue_sptr msgq)
{
    return gr_udp_msg_sink_sptr(new gr_udp_msg_sink_impl(host, port, msgq));
}


