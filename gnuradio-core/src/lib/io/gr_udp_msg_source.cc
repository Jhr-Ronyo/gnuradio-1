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

#include <gr_udp_msg_source.h>
#include <gruel/thread.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

static const int max_buf_size = 4096;

using boost::asio::ip::udp;

class gr_udp_msg_source_impl : public gr_udp_msg_source {
public:
    gr_udp_msg_source_impl(int port, gr_msg_queue_sptr msgq)
      : _port(port), _msgq(msgq), _running(false)
    {
        _udp_thread =
            gruel::thread(boost::bind(&gr_udp_msg_source_impl::recv_loop, this));
    }

    ~gr_udp_msg_source_impl()
    {
        _running = false;
        _udp_thread.join();
    }

    void recv_loop()
    {
        size_t len;
        char data[max_buf_size];
        gr_message_sptr msg;

        boost::asio::io_service io_svc;
        udp::endpoint ep;
        udp::socket sock(io_svc, udp::endpoint(udp::v4(), _port));

        boost::asio::socket_base::bytes_readable cmd(true);
        sock.io_control(cmd);

        _running = true;
        while (_running) {
#if 1
            len = cmd.get();
            if (len > 0) {
                len = sock.receive_from(boost::asio::buffer(data, max_buf_size), ep);
                msg = gr_make_message(0, 0.0, 0.0, len);
                memcpy(msg->msg(), data, len);
                _msgq->handle(msg);
            } else {
                msg = gr_make_message(0, 0.0, 0.0, 1384);
                if (!_msgq->full_p())
                    _msgq->handle(msg);
            }
#else
            len = sock.receive_from(boost::asio::buffer(data, max_buf_size), ep);
            if (len > 0) {
                msg = gr_make_message(0, 0.0, 0.0, len);
                memcpy(msg->msg(), data, len);
                _msgq->handle(msg);
            } else {
                msg = gr_make_message(0, 0.0, 0.0, 1384);
                if (!_msgq->full_p())
                    _msgq->handle(msg);
            }
#endif
        }
    }

protected:
    int _port;
    gr_msg_queue_sptr _msgq;
    bool _running;
    gruel::thread _udp_thread;
};

gr_udp_msg_source_sptr gr_make_udp_msg_source(int port, gr_msg_queue_sptr msgq)
{
    return gr_udp_msg_source_sptr(new gr_udp_msg_source_impl(port, msgq));
}
