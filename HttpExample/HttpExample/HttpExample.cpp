#pragma comment (lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstring>
using namespace std;




//void printData() {
//    ifstream file("погода.json");
//
//    // Проверяем, удалось ли открыть файл
//    if (!file.is_open()) {
//        cout << "Не удалось открыть файл." << std::endl;
//
//    }
//
//    // Строка для хранения текущей строки из файла
//    string line;
//
//    // Искомые подстроки
//    const char* country = "\"name\"";
//    const char* coordinatesX = "\"lon\"";
//    const char* coordinatesY = "\"lat\"";
//    const char* dateKey = "\"dt\"";
//    const char* city = "\"name\"";
//    const char* temperature = "\"temp\"";
//    const char* sunset = "\"sunset\"";
//    const char* sunrise = "\"sunrise\"";
//    // Флаги для отслеживания, были ли уже найдены страна и координаты
//    bool foundCountry = false;
//    bool foundCoordinates = false;
//    bool foundCity = false;
//    bool foundTemperature = false;
//    bool foundSunset = false;
//    bool foundSunrise = false;
//
//    // Читаем файл построчно
//    while (getline(file, line)) {
//        // Проверяем, содержит ли текущая строка искомую подстроку страны
//        if (!foundCountry && strstr(line.c_str(), country) != nullptr) {
//            cout << "Страна: " << line << endl;
//            foundCountry = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//
//        // Проверяем, содержит ли текущая строка искомую подстроку города
//        if (!foundCity && strstr(line.c_str(), city) != nullptr) {
//            cout << "Город: " << line << endl;
//            foundCity = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//
//        // Проверяем, содержит ли текущая строка искомую подстроку заката
//        if (!foundCountry && strstr(line.c_str(), sunset) != nullptr) {
//            cout << "Закат: " << line << endl;
//            foundSunset = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//
//        // Проверяем, содержит ли текущая строка искомую подстроку рассвета
//        if (!foundCity && strstr(line.c_str(), sunrise) != nullptr) {
//            cout << "Рассвет: " << line << endl;
//            foundSunrise = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//
//
//        // Проверяем, содержит ли текущая строка искомую подстроку температуры
//        if (!foundCountry && strstr(line.c_str(), temperature) != nullptr) {
//            cout << "Температура: " << line << endl;
//            foundTemperature = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//        // Проверяем, содержит ли текущая строка искомую подстроку для долготы
//        if (!foundCoordinates && strstr(line.c_str(), coordinatesX) != nullptr) {
//            cout << "Долгота: " << line << endl;
//            foundCoordinates = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//        // Проверяем, содержит ли текущая строка искомую подстроку для широты
//        if (!foundCoordinates && strstr(line.c_str(), coordinatesY) != nullptr) {
//            cout << "Широта: " << line << endl;
//            foundCoordinates = true; // Устанавливаем флаг, чтобы не анализировать это снова
//        }
//
//
//        // Проверяем, содержит ли текущая строка искомую подстроку с датой
//        if (strstr(line.c_str(), dateKey) != nullptr) {
//            // Если содержит, то извлекаем значение даты из строки
//            size_t pos = line.find(":");
//            if (pos != string::npos) {
//                string dateValue = line.substr(pos + 1);
//                time_t timestamp = stoi(dateValue);
//                // Преобразуем значение времени в структуру tm безопасным способом
//                struct tm timeinfo;
//                localtime_s(&timeinfo, &timestamp);
//                // Выводим дату в удобочитаемом формате
//                char dateBuffer[80];
//                strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
//                cout << "Дата: " << dateBuffer << endl;
//            }
//            break; // Прекращаем анализ, так как мы уже нашли дату
//        }
//    }
//
//    // Закрываем файл
//    file.close();
//}
void printData(const std::string& response) {
    // Искомые подстроки
    const string countryKey = "\"name\"";
    const string coordinatesKey = "\"coord\"";
    const string dateKey = "\"dt\"";
    const string temperatureKey = "\"temp\"";
    const string sunsetKey = "\"sunset\"";
    const string sunriseKey = "\"sunrise\"";

    // Поиск ключевых подстрок в строке JSON-ответа
    size_t pos;

    // Поиск страны
    pos = response.find(countryKey);
    if (pos != string::npos) {
        cout << "Город: " << response.substr(pos + countryKey.length() + 3, response.find("\",", pos) - pos - countryKey.length() - 3) << endl;
    }

    // Поиск координат
    pos = response.find(coordinatesKey);
    if (pos != string::npos) {
        size_t lonPos = response.find("\"lon\"", pos);
        size_t latPos = response.find("\"lat\"", lonPos);
        cout << "Долгота: " << response.substr(lonPos + temperatureKey.length() + 3, response.find(",", lonPos) - lonPos - temperatureKey.length() - 3) << endl;
        cout << "Широта: " << response.substr(latPos + temperatureKey.length() + 3, response.find("}", latPos) - latPos - temperatureKey.length() - 3) << endl;
    }

    // Поиск температуры
    pos = response.find(temperatureKey);
    if (pos != string::npos) {
        cout << "Температура: " << response.substr(pos + temperatureKey.length() + 2, response.find(",", pos) - pos - temperatureKey.length() - 2) << endl;
    }

    // Поиск даты
    pos = response.find(dateKey);
    if (pos != string::npos) {
        time_t timestamp = stoi(response.substr(pos + dateKey.length() + 1, response.find(",", pos) - pos - dateKey.length() - 1));
        struct tm timeinfo;
        localtime_s(&timeinfo, &timestamp);
        char dateBuffer[80];
        std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo); 
        std::cout << "Дата: " << dateBuffer << endl;
    }
}


int main()
{
    setlocale(0, "ru");

    //1. инициализация "Ws2_32.dll" для текущего процесса
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

        cout << "WSAStartup failed with error: " << err << endl;
        return 1;
    }

    //инициализация структуры, для указания ip адреса и порта сервера с которым мы хотим соединиться

    char hostname[255] = "api.openweathermap.org";

    addrinfo* result = NULL;

    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo(hostname, "http", &hints, &result);
    if (iResult != 0) {
        cout << "getaddrinfo failed with error: " << iResult << endl;
        WSACleanup();
        return 3;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    addrinfo* ptr = NULL;

    //Пробуем присоединиться к полученному адресу
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        //2. создание клиентского сокета
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (connectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        //3. Соединяемся с сервером
        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    //4. HTTP Request

    string uri = "/data/2.5/weather?q=Odessa&appid=75f6e64d49db78658d09cb5ab201e483&mode=JSON";

    string request = "GET " + uri + " HTTP/1.1\n";
    request += "Host: " + string(hostname) + "\n";
    request += "Accept: */*\n";
    request += "Accept-Encoding: gzip, deflate, br\n";
    request += "Connection: close\n";
    request += "\n";

    //отправка сообщения
    if (send(connectSocket, request.c_str(), request.length(), 0) == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 5;
    }
    cout << "send data" << endl;

    //5. HTTP Response

    string response;

    const size_t BUFFERSIZE = 1024;
    char resBuf[BUFFERSIZE];

    int respLength;

    do {
        respLength = recv(connectSocket, resBuf, BUFFERSIZE, 0);
        if (respLength > 0) {
            response += string(resBuf).substr(0, respLength);
        }
        else {
            cout << "recv failed: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            return 6;
        }

    } while (respLength == BUFFERSIZE);

    //cout << response << endl;
    printData(response);

    //отключает отправку и получение сообщений сокетом
    iResult = shutdown(connectSocket, SD_BOTH);
    if (iResult == SOCKET_ERROR) {
        cout << "shutdown failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 7;
    }

    closesocket(connectSocket);
    WSACleanup();
}