#ifndef RIFTIA_SERIAL_H
#define RIFTIA_SERIAL_H
//serial:20140313
#include <iostream>
#include <boost/asio.hpp>

namespace riftia
{
class serial{
public:
    serial(boost::asio::io_service& io_service) : 
		io_service_(io_service), serial_port_(io_service){}

	void init_serial(const std::string& port_name, unsigned int baud_rate){
		serial_port_.open(port_name.c_str());
		serial_port_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
	}

	void start_main_loop(){
			boost::asio::streambuf buf;
			std::string line;
		while(true){
			boost::asio::read_until(serial_port_, buf, "\r\n");
			std::istream is(&buf);
			std::getline(is, line);
			std::cout << line << std::endl;
		}
	}

	std::string step(){
		boost::asio::streambuf buf;
		std::string line;
		boost::asio::read_until(serial_port_, buf, "\r\n");
		std::istream is(&buf);
		std::getline(is, line);
		return line;
	}


private:
	boost::asio::io_service& io_service_;
	boost::asio::serial_port serial_port_; 

};
}

#endif //RIFTIA_SERIAL_H
