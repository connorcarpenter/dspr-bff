#include <uWS/uWS.h>
#include <iostream>

int main()
{
    uWS::Hub h;

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
    {

    });

    h.onMessage([&h](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode)
    {
        if (strncmp(data, "gameservers/1.0/join", 20) == 0){
            ws->send("gameserver/connect|www.deuspora.com:3173|player1code\r\n", uWS::BINARY); //the \r\n makes it happen on EMSC! Don't remove!
            std::cout << "dspr-bff: Received 'gameservers/1.0/join', Sent 'gameserver/connect|www.deuspora.com:3173|player1code'" << std::endl;
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
