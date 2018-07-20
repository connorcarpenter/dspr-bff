#include <uWS/uWS.h>
#include <iostream>

int main()
{
    uWS::Hub h;

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req)
    {
        ws->send("connected to bff!\r\n", uWS::BINARY);
    });

    h.onMessage([&h](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode)
    {
        ws->send("message from bff!\r\n", uWS::BINARY);
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
    if (h.listen("localhost", 3172)) {
        std::cout << "Listening to port 3172" << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}
