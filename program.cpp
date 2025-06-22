#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <shellapi.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mmsystem.h>
#include <fstream>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

#define HOSTS_PATH "C:\\Windows\\System32\\drivers\\etc\\hosts"

void appendToHostsFile(const std::string &entry)
{
    std::ofstream hostsFile(HOSTS_PATH, std::ios::app);
    if (hostsFile.is_open())
    {
        hostsFile << "\n"
                  << entry << "\n";
        hostsFile.close();
        std::cout << "Entry appended successfully." << std::endl;
    }
    else
    {
        std::cerr << "Unable to open hosts file for writing." << std::endl;
    }
}

void setDNSServer(const std::string &interface, const std::string &dnsServer)
{
    std::string command = "netsh interface ip set dns name=\"" + interface + "\" static " + dnsServer;
    int result = system(command.c_str());
    if (result == 0)
    {
        std::cout << "DNS server set successfully for interface: " << interface << std::endl;
    }
    else
    {
        std::cerr << "Failed to set DNS server for interface: " << interface << std::endl;
    }
}

void removeDNSServers(const std::string &interface)
{
    std::string command = "netsh interface ip set dns name=\"" + interface + "\" dhcp";
    int result = system(command.c_str());
    if (result == 0)
    {
        std::cout << "Existing DNS servers removed for interface: " << interface << std::endl;
    }
    else
    {
        std::cerr << "Failed to remove DNS servers for interface: " << interface << std::endl;
    }
}
std::string getActiveInterfaceName()
{
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_UNSPEC; // both IPv4 and IPv6

    ULONG outBufLen = 15000;
    std::vector<char> buffer(outBufLen);
    PIP_ADAPTER_ADDRESSES addresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());

    if (GetAdaptersAddresses(family, flags, nullptr, addresses, &outBufLen) != ERROR_SUCCESS)
    {
        std::cerr << "Failed to get adapter addresses." << std::endl;
        return "";
    }

    for (PIP_ADAPTER_ADDRESSES adapter = addresses; adapter != nullptr; adapter = adapter->Next)
    {
        if (adapter->OperStatus == IfOperStatusUp && adapter->IfType != IF_TYPE_SOFTWARE_LOOPBACK)
        {
            std::wstring ws(adapter->FriendlyName);
            std::string interfaceName(ws.begin(), ws.end());
            return interfaceName;
        }
    }

    return "";
}
int main()
{

    appendToHostsFile("127.0.0.1   mercy.edu");
    std::string interface = getActiveInterfaceName();
    if (interface.empty())
    {
        std::cerr << "Could not detect active network interface." << std::endl;
        return 1;
    }
    std::cout << "Detected active interface: " << interface << std::endl;
    std::string dnsServer = "127.0.0.1";

    appendToHostsFile("127.0.0.1   mercy.edu");

    removeDNSServers(interfaceName);
    setDNSServer(interfaceName, dnsServer);

    return 0;
}
