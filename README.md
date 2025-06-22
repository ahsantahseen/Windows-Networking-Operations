# Windows-Networking-Operations

### 🧠 Module of the **Mercy Uni STEM Research Institute (SRI)** Project  
🔧 C++ Tool for Managing Windows Hosts and DNS Configuration

---

## 🚀 Overview

**Windows-Networking-Operations** is a lightweight C++ module built using the Windows API to control and automate network settings on Windows machines. It enables programmatic changes to the system's DNS servers and `hosts` file—useful in controlled environments like university labs, research terminals, and testing sandboxes.

This project is a core component of the Mercy Uni **STEM Research Institute (SRI)** infrastructure initiative.

---

## 🔐 Use Case in SRI

This module supports:

- Lab-based access control through DNS rerouting
- Quick configuration resets on research terminals
- Local name resolution for air-gapped internal servers
- Department-managed endpoint networking enforcement

---

## ✨ Features

- ✅ Automatically detects the **active network interface**
- ✅ Modifies the system **`hosts` file**
- ✅ Sets **custom DNS servers** (internal, secure)
- ✅ Written in **modern C++** using **WinAPI**
- ✅ Requires **Administrator** privileges

---

## 🛠 Functions

```cpp
std::string GetActiveNetworkInterfaceName();
bool SetDNSForActiveInterface(const std::string& dnsServer);
bool UpdateHostsFile(const std::string& domain, const std::string& ipAddress);