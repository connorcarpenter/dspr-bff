#include <uWS/uWS.h>
#include <iostream>
#include <sstream>
#include "TokenGenerator.h"


using namespace DsprBff;

uWS::Hub h;

uWS::WebSocket<uWS::CLIENT>* gameServer = nullptr;

    int main()
    {
        std::string bffToken = "nwlrbbmqbhcdacon";
        TokenGenerator tokenGenerator = TokenGenerator();


        h.onConnection([&h, &gameServer](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req)
        {
            if (gameServer != nullptr) exit(EXIT_FAILURE); //if this thing connects to more than one ws server... well... i want to know
            gameServer = ws;
            std::cout << "dspr-bff: connected to gameserver" << std::endl;
        });

        h.onDisconnection([&h, &gameServer](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length)
        {
           gameServer = nullptr;
           std::cout << "dspr-bff: discconnected from gameserver" << std::endl;
        });

        h.onMessage([&h, &tokenGenerator, &bffToken, &gameServer](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode)
        {
            if (strncmp(data, "gameservers/1.0/join", 20) == 0)
            {
                //generate a playertoken
                std::string playerToken = tokenGenerator.generate_playertoken();

                //send playertoken to gameserver
                std::stringstream gameServerMsg;
                gameServerMsg << "player/1.0/add|"
                     << bffToken
                     << "|"
                     << playerToken
                     << "\r\n";
                gameServer->send(gameServerMsg.str().c_str(), uWS::BINARY);

                //send playertoken to player
                std::stringstream playerMsg;
                playerMsg << "gameserver/connect|www.deuspora.com:3173|"
                          << playerToken
                          << "\r\n";
                ws->send(playerMsg.str().c_str(), uWS::BINARY); //the \r\n makes it happen on EMSC! Don't remove!

                //logging
                std::cout << "dspr-bff: Received '" << std::string(data, length) << "', Sent '" << playerMsg.str() << "'";
            }
        });

        h.connect("ws://localhost:3173", (void *) 1);

        auto timer = new Timer(h.getLoop());
        timer->start([](Timer* timer){
            if (gameServer != nullptr) return;
            h.connect("ws://localhost:3173", (void *) 1);
            std::cout << "trying to reconnect to gameserver..." << std::endl;
        }, 1000, 1000);

        h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
        if (h.listen("localhost", 3172)) {
            std::cout << "dspr-bff: Listening to port 3172" << std::endl;
        } else {
            std::cerr << "dspr-bff: Failed to listen to port" << std::endl;
            return -1;
        }

        h.run();
    }