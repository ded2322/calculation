#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

class TcpServer {
    private:
        int port;
        int server;
        int client;
        struct sockaddr_in address;
    public:
        TcpServer (int port): port(port), server(-1), client(-1) {
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(port);
        }

        bool startTcpSerer() {
            // Создание сокета
            server = socket(AF_INET, SOCK_STREAM, 0);
            if (server < 0) {
                std::cerr << "failed create socket\n";
                return false;
            }

            // Разрешение для повторного использования адреса
            int opt = 1;
            setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            
            // Резервация порта
            if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) {
                std::cerr << "Failed create bind\n";
                return false;
            }
            // Начинаем слушать соединения
            if (listen(server, 5) < 0) {
                std::cerr << ("Failed start listen\n");
                return false;
            }
            std::cout << "Server start\n";
            return true;
        }

        void closeUserConnection() {
            close(client);
            std::cout << "Connection with client close\n"; 
        }

        void closeTcpServer() {
            closeUserConnection();
            close(server);
            std::cout << "Server turn off\n";
        }

        bool acceptClient() {
            socklen_t addrlen = sizeof(address);
            client = accept(server, (struct sockaddr *)&address, (socklen_t *)&addrlen);

            if(client < 0) {
                std::cerr << "Failed accept connection\n";
                return false;
            }
            std::cout << "Accept connection\n";
            return true;
        }

        std::string readMessage() {
            if(client < 0) return "";
            
            char buffer[1024] = {0};
            int bites_read = read(client, buffer, 1024);

            if( bites_read < 0 ) {
                std::cerr << "Failed read message\n";
                return "";
            }

            return std::string(buffer, bites_read);
        }
        
        bool sendMessage(const std::string& message) {
            if(client < 0) return false;

            int bite_send = send(client, message.c_str(), message.length(), 0);

            if(bite_send < 0) {
                std::cerr << "Failed send message\n";
                return false;
            }
            return true;
        }
        ~TcpServer() {
            closeTcpServer();
        }
};

// int main() {
//     TcpServer server(8080);

//     if(!server.startTcpSerer()) return -1;

//     std::string start_text = "For exit calculate input: -1\nEntered expression: ";

//     if(server.acceptClient()) {
//         server.sendMessage(start_text);
//         std::string user_message { server.readMessage() };

//         std::cout << "User input: " << user_message << "\n";
//         server.closeTcpServer();
//     }
// }