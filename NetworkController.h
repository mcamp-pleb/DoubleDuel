#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <SFML\Network.hpp>

class NetworkController
{
	protected:
		struct NetInfo
		{
			sf::IpAddress	sfm_otherIP;
			std::string		mstr_otherName;
		};

		sf::IpAddress		sfm_thisIP;
		sf::SocketSelector	sfm_selector;

		SystemSettings	*m_Settings;
	public:
		//Send Data with UDP
		void SendUDPString(const std::string &temp, const sf::IpAddress &outgoingIP)
		{
			sf::UdpSocket	sfm_outgoingSocket;
			sf::Packet packet;
			
			packet << temp;
			sfm_outgoingSocket.bind(m_Settings->outPortUDP);
			sfm_outgoingSocket.send(packet, outgoingIP, m_Settings->inPortUDP);
		}

		//Send Data with TCP
		sf::Socket::Status SendTCPData(sf::TcpSocket &socket, sf::Packet &packet)
		{
			return socket.send(packet);
		}

		// Receive a message with UDP
		void ReceiveUDPConnection(NetInfo &sender)
		{
			sf::UdpSocket	sfm_incomingSocket;
			sf::Packet		packet;
			unsigned short	port;

			sfm_incomingSocket.bind(m_Settings->inPortUDP);
			sfm_selector.add(sfm_incomingSocket);

			if (sfm_selector.wait(sf::milliseconds(10)))
			{
				if (sfm_selector.isReady(sfm_incomingSocket))
				{
					if (sfm_incomingSocket.receive(packet, sender.sfm_otherIP, port) != sf::Socket::NotReady)
					{
						packet >> sender.mstr_otherName;
					}
				}
			}
			sfm_selector.remove(sfm_incomingSocket);
		}

		// Receive a message with TCP
		sf::Socket::Status ReceiveTCPData(sf::TcpSocket &tcpSocket, sf::Packet &packet)
		{
			sf::Socket::Status status = sf::Socket::NotReady;
			if (sfm_selector.wait(sf::milliseconds(5)))
			{
				bool test = sfm_selector.isReady(tcpSocket);//test and change
				if (test)
				{
					status = tcpSocket.receive(packet);
				}
			}
			return status;
		}

		void RetrieveLocalIP()
		{
			sfm_thisIP = sf::IpAddress::getLocalAddress();
		}
};

#endif