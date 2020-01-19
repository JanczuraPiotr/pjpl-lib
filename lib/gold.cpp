#include "napisy.h"

namespace pjpl {

std::string exec(const std::string &cmd) {
    std::array<char, 1024> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 1024, pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }
    return result;
}

float systemLoad() {
    std::string execOut = pjpl::exec("mpstat");
    execOut = execOut.substr(execOut.find("all") + 3);
    execOut = execOut.substr(0, execOut.find("\n"));
    execOut = pjpl::old::DelSpaceFlank(execOut);
    std::vector<std::string> tokens = pjpl::split(execOut, " ");
    tokens.erase(tokens.end()--);
    float load = 0;
    std::size_t pos;
    for (auto &it : tokens) {
        if ((pos = it.find(",") != std::string::npos)) {
            it.replace(pos, 1, ".");
        }
        load += std::stof(it);
    }
    return load;
}

std::vector<uint8_t> getNet(const std::string &ipAddr, const std::string &netMask)
{
    std::vector<uint8_t > net;
    std::vector<std::string> addr = split(ipAddr, '.');
    std::vector<std::string> mask = split(netMask, '.');

    auto addrIT = addr.begin();
    for (auto &item : mask) {
        if (item == "255") {
            net.push_back(static_cast<uint8_t >(std::stoi(*addrIT)));
        } else {
            net.push_back(0);
        }
        ++addrIT;
    }

    return net;
}

std::vector<uint8_t > getNet(const std::string &ipAddr)
{
    std::vector<uint8_t > net;
    std::vector<std::string> addr = split(ipAddr, '.');

    for (auto &item : addr) {
        if (item == "0") {
            net.push_back(0);
        } else {
            net.push_back(static_cast<uint8_t >(std::stoi(item)));
        }
    }

    return net;

}

std::string getIpAddress()
{
    std::string ipAddress="Unable to get IP Address";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if(strcmp(temp_addr->ifa_name, "en0")){
                    ipAddress = inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr);
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }

    freeifaddrs(interfaces);
    return ipAddress;
}

std::vector<int> splitIpAddr(const std::string &ipAddr)
{
    std::vector<int> nr;
    std::vector<std::string> addr = split(ipAddr, '.');

    for (auto &item : addr) {
        nr.push_back(static_cast<uint8_t >(std::stoi(item)));
    }

    return nr;
}



}

//=============================================================================

std::string pjpl::GetErrStr(int err_) {
    switch (err_) {
        case pjpl::OK:
            return "Wszystko OK!";
        case pjpl::ERR:
            return "nie rozpoznany błąd";
        case pjpl::ERR_SIGNED:
            return "Liczba otrzymana w wyniku przetwarzania posiada znak gdy miała być bez znaku";
        case pjpl::ERR_RANGE:
            return "Zmienna poza zakresem.";
        case pjpl::ERR_REDEF:
            return "Pewna stała zmieniła swoją wartość";
        case pjpl::ERR_NOT_FIND:
            return "Nie znaleziono oczekiwanej wartości";
        case pjpl::ERR_BAD_VALUE:
            return "Wartość którą przekazano do dalszego przetwarzania jest nie właściwa, ma złą strukturę.";
        case pjpl::ERR_NOT_VALUE:
            return "Zmienna choć posiada poprawną strukturę nie pozwala określić wartości np pusty napis";
        case pjpl::ERR_BAD_DEF:
            return "Wyrażenie definiujące wartość jest nie poprawne.";
        case pjpl::ERR_MATHOP:
            return "Błąd powstały podczas próby wykonania podstawowej operacji matematycznej";
        case pjpl::ERR_CALC_LATER:
            return "Wartość przekazana do obliczenia jest wyrażeniem którego składowe jeszcze nie się wyznaczone";
        case pjpl::ERR_THREAD_STOP:
            return "Awaryjne zakończenie wątku. Wątek przerwano mimo trwania pracy (obliczeń)";
    }
    return "nie zdefiniowana wartość zmiennej err";
}



