#include <uWS/uWS.h>
#include <iostream>
#include <sstream>
#include "TokenGenerator.h"


using namespace DsprBff;

    int main()
    {
        TokenGenerator tokenGenerator = TokenGenerator();
        uWS::Hub h;

        h.onConnection([&h](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
                       {

        });

        h.onMessage([&h, &tokenGenerator](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode)
                    {
            if (strncmp(data, "gameservers/1.0/join", 20) == 0)
            {
                //generate a playertoken
                std::string playerToken = tokenGenerator.generate_playertoken();

                //send playertoken to gameserver

                //send playertoken to player
                std::stringstream msg;
                msg << "gameserver/connect|www.deuspora.com:3173|";
                msg << playerToken;
                msg << "\r\n";
                ws->send(msg.str().c_str(), uWS::BINARY); //the \r\n makes it happen on EMSC! Don't remove!

                //logging
                std::cout << "dspr-bff: Received '" << std::string(data, length) << "', Sent '" << msg.str() << "'";
            }
        });

        h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
        if (h.listen("localhost", 3172)) {
            std::cout << "dspr-bff: Listening to port 3172" << std::endl;
        } else {
            std::cerr << "dspr-bff: Failed to listen to port" << std::endl;
            return -1;
        }

        h.run();
    }