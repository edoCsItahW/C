在 Windows 和 Linux 中使用 C++ 操作套接字的基本步骤大致相同，但实现细节和API有所不同。下面分别介绍在这两种系统中创建和使用套接字的基本步骤。

1. **包含头文件**：
   * Linux
      ```cpp
      #include <iostream>
      #include <cstring>     // memset
      #include <sys/types.h>
      #include <sys/socket.h>
      #include <netinet/in.h>
      #include <arpa/inet.h>
      #include <unistd.h>    // close
      ```
   
   * Windows
      ```cpp
      #include <iostream>
      #include <winsock2.h> // Windows Sockets
      #pragma comment(lib, "ws2_32.lib") // 链接 ws2_32.lib
      ```

> 独windows需要初始化
>   ```cpp
>   WSADATA wsaData;
>   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
>       std::cerr << "WSAStartup failed" << std::endl;
>       return -1;
>   }
>   ```

2. **创建套接字**：
   * Linux
      ```cpp
      int sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0) {
          std::cerr << "Error opening socket" << std::endl;
          return -1;
      }
      ```

   * Windows
      ```cpp
      SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd == INVALID_SOCKET) {
      std::cerr << "Error opening socket" << std::endl;
      WSACleanup();
      return -1;
      }
      ```

3. **绑定套接字**：
   * Linux
      ```cpp
      struct sockaddr_in serv_addr;
      memset(&serv_addr, 0, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = INADDR_ANY; // 或指定地址
      serv_addr.sin_port = htons(8080);
      
      if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
          std::cerr << "Binding failed" << std::endl;
          close(sockfd);
          return -1;
      }
      ```
     
   * Windows
      ```cpp
      struct sockaddr_in serv_addr;
      memset(&serv_addr, 0, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = INADDR_ANY; // 或指定地址
      serv_addr.sin_port = htons(8080);
      
      if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
          std::cerr << "Binding failed" << std::endl;
          closesocket(sockfd);
          WSACleanup();
          return -1;
      }
      ```

4. **监听并接受连接**：
   * Linux
      ```cpp
      listen(sockfd, 5);
      int new_sock = accept(sockfd, nullptr, nullptr);
      if (new_sock < 0) {
          std::cerr << "Accept failed" << std::endl;
      }
      ```
      
   * Windows
      ```cpp
      listen(sockfd, SOMAXCONN);
      SOCKET new_sock = accept(sockfd, nullptr, nullptr);
      if (new_sock == INVALID_SOCKET) {
          std::cerr << "Accept failed" << std::endl;
      }
      ```

5. **发送和接收数据**：
   * Linux
      ```cpp
      char buffer[256];
      ssize_t n = read(new_sock, buffer, sizeof(buffer)-1);
      if (n > 0) {
          buffer[n] = '\0';
          std::cout << "Received: " << buffer << std::endl;
      }
      write(new_sock, "Hello, World!", 13);
      ```
      
   * Windows
      ```cpp
      char buffer[256];
      int n = recv(new_sock, buffer, sizeof(buffer) - 1, 0);
      if (n > 0) {
          buffer[n] = '\0';
          std::cout << "Received: " << buffer << std::endl;
      }
      send(new_sock, "Hello, World!", 13, 0);
      ```
   
6. **关闭套接字**：
   * Linux
      ```cpp
      close(new_sock);
      close(sockfd);
      ```
      
   * Windows
      ```cpp
      closesocket(new_sock);
      closesocket(sockfd);
      WSACleanup();
      ```

7. **使用 `recvfrom` 接收数据**：
   * Linux
      ```cpp
      struct sockaddr_in client_addr;
      socklen_t addr_len = sizeof(client_addr);
      char buffer[1024];
      
      ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer), 0, 
                           (struct sockaddr *)&client_addr, &addr_len);
      if (n < 0) {
          std::cerr << "Error in recvfrom" << std::endl;
      } else {
          buffer[n] = '\0'; // Null-terminate the received data
          std::cout << "Received: " << buffer << std::endl;
      }
      ```
      
   * Windows
      ```cpp
      struct sockaddr_in client_addr;
      int addr_len = sizeof(client_addr);
      char buffer[1024];
      
      int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, 
                       (struct sockaddr *)&client_addr, &addr_len);
      if (n == SOCKET_ERROR) {
          std::cerr << "Error in recvfrom" << std::endl;
      } else {
          buffer[n] = '\0'; // Null-terminate the received data
          std::cout << "Received: " << buffer << std::endl;
      }
      ```